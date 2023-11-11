/**************************************************************************************************
 *  This file is part of Connect X.
 *
 *  Connect X is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.
 *
 *  Connect X is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with Connect X. If not, see <https://www.gnu.org/licenses/>.
 *
 *************************************************************************************************/
/**********************************************************************************************//**
 * @file GameView.cpp
 * @date 2020
 *
 *************************************************************************************************/

#include <gtkmm/window.h>

#include <cxinv/assertion.h>
#include <cxmodel/IChip.h>
#include <cxmodel/ModelNotificationContext.h>
#include <cxgui/BoardAnimation.h>
#include <cxgui/common.h>
#include <cxgui/DiscChip.h>
#include <cxgui/GameView.h>
#include <cxgui/GameViewKeyHandlerStrategyFactory.h>
#include <cxgui/Gtkmm3Layout.h>
#include <cxgui/IAnimatedBoardPresenter.h>

namespace
{

constexpr size_t NUMBER_CHIPS_MOVED_PER_SECOND = 3u;

} // namespace

cxgui::GameView::GameView(IGameViewPresenter& p_presenter,
                          IGameViewController& p_controller,
                          Gtk::Window& p_parentWindow,
                          cxgui::ILayout& p_mainLayout,
                          const cxmodel::Column& p_viewLeft,
                          const cxmodel::Row& p_viewTop)
: m_presenter{p_presenter}
, m_controller{p_controller}
, m_parentWindow{p_parentWindow}
, m_mainLayout{p_mainLayout}
, m_viewLeft{p_viewLeft}
, m_viewTop{p_viewTop}
, m_activePlayerChip{std::make_unique<cxgui::DiscChip>(cxmodel::MakeTransparent(), cxmodel::MakeTransparent(), cxgui::DEFAULT_CHIP_SIZE / 4)}
, m_nextPlayerChip{std::make_unique<cxgui::DiscChip>(cxmodel::MakeTransparent(), cxmodel::MakeTransparent(), cxgui::DEFAULT_CHIP_SIZE / 4)}
, m_board{std::make_unique<cxgui::AnimatedBoard>(m_presenter, cxgui::AnimationSpeed{NUMBER_CHIPS_MOVED_PER_SECOND})}
{
    PRECONDITION(m_activePlayerChip);
    PRECONDITION(m_nextPlayerChip);

    m_viewLayout = std::make_unique<Gtkmm3Layout>();
    m_playersInfoLayout = std::make_unique<Gtkmm3Layout>();

    SetLayout();
    PopulateWidgets();
    ConfigureWidgets();

    // Attach to the board:
    Attach(m_board.get());
    m_board->BoardAnimationSubject::Attach(this);
    m_board->UserActionSubject::Attach(this);
}

void cxgui::GameView::Activate()
{
    EnableKeyHandlers();

    cxgui::ILayout* currentViewLayout = m_mainLayout.GetLayoutAtPosition(m_viewTop, m_viewLeft);

    if(!currentViewLayout)
    {
        ASSERT_ERROR_MSG("Current view should be valid.");
        return;
    }

    // Unregister the previous view layout:
    m_mainLayout.Unregister(*currentViewLayout);

    // Register the new view layout:
    m_mainLayout.Register(*m_viewLayout,
                          {m_viewTop, cxgui::ILayout::RowSpan{1u}},
                          {m_viewLeft, cxgui::ILayout::ColumnSpan{2u}});
}

void cxgui::GameView::DeActivate()
{
    // Since the Game View is recreated every time, we need to clear
    // the view layout from the main layout, otherwise we will have a
    // dangling reference in the main layout once the view is reset.
    auto* currentViewLayout = m_mainLayout.GetLayoutAtPosition(m_viewTop, m_viewLeft);
    if(INL_ASSERT(currentViewLayout))
    {
        m_mainLayout.Unregister(*currentViewLayout);
    }

    DisableKeyHandlers();
}

void cxgui::GameView::Update(cxmodel::ModelNotificationContext p_context)
{
    switch(p_context)
    {
        case cxmodel::ModelNotificationContext::CHIP_DROPPED:
        {
            UpdateChipDropped();
            break;
        }
        case cxmodel::ModelNotificationContext::CHIP_DROPPED_FAILED:
        {
            UpdateChipDroppedFailed();
            break;
        }
        case cxmodel::ModelNotificationContext::CHIP_MOVED_LEFT_ONE_COLUMN:
        {
            UpdateChipMovedLeftOneColumn();
            break;
        }
        case cxmodel::ModelNotificationContext::CHIP_MOVED_RIGHT_ONE_COLUMN:
        {
            UpdateChipMovedRightOneColumn();
            break;
        }
        case cxmodel::ModelNotificationContext::GAME_WON:
        case cxmodel::ModelNotificationContext::GAME_TIED:
        {
            UpdateGameResolved();
            break;
        }
        case cxmodel::ModelNotificationContext::GAME_REINITIALIZED:
        {
            UpdateGameReinitialized();
            break;
        }
        case cxmodel::ModelNotificationContext::UNDO_CHIP_DROPPED:
        {
            UpdateUndoChipDropped();
            break;
        }
        case cxmodel::ModelNotificationContext::REDO_CHIP_DROPPED:
        {
            UpdateRedoChipDropped();
            break;
        }
        default:
            break;
    }
}

void cxgui::GameView::Update(cxgui::BoardAnimationNotificationContext p_context, cxgui::BoardAnimationSubject* p_subject)
{
    IF_CONDITION_NOT_MET_DO(p_subject, return;);

    switch(p_context)
    {
        case cxgui::BoardAnimationNotificationContext::ANIMATE_MOVE_LEFT_ONE_COLUMN:
        case cxgui::BoardAnimationNotificationContext::ANIMATE_MOVE_RIGHT_ONE_COLUMN:
        case cxgui::BoardAnimationNotificationContext::ANIMATE_MOVE_RIGHT_TO_TARGET:
        case cxgui::BoardAnimationNotificationContext::ANIMATE_MOVE_DROP_CHIP:
        case cxgui::BoardAnimationNotificationContext::ANIMATE_UNDO_DROP_CHIP:
        case cxgui::BoardAnimationNotificationContext::ANIMATE_REDO_DROP_CHIP:
        case cxgui::BoardAnimationNotificationContext::ANIMATE_REINITIALIZE_BOARD:
        {
            return;
        }

        case cxgui::BoardAnimationNotificationContext::POST_ANIMATE_MOVE_LEFT_ONE_COLUMN:
        case cxgui::BoardAnimationNotificationContext::POST_ANIMATE_MOVE_RIGHT_ONE_COLUMN:
        case cxgui::BoardAnimationNotificationContext::POST_ANIMATE_DROP_CHIP:
        {
            if(m_presenter.IsCurrentPlayerABot())
            {
                UpdateChipMovedRightToTarget();
                break;
            }

            EnableKeyHandlers();
            break;
        }
        case cxgui::BoardAnimationNotificationContext::POST_ANIMATE_UNDO_DROP_CHIP:
        case cxgui::BoardAnimationNotificationContext::POST_ANIMATE_REDO_DROP_CHIP:
        {
            // At this point the animation is completed. We reactivate keyboard events in
            // case the user wants to request another animation:
            break;
        }
        case cxgui::BoardAnimationNotificationContext::POST_ANIMATE_MOVE_RIGHT_TO_TARGET:
        {
            m_controller.OnDown(m_presenter.GetGameViewActivePlayerChipColor(), m_presenter.GetBotTarget());
            break;
        }
        case cxgui::BoardAnimationNotificationContext::POST_ANIMATE_REINITIALIZE_BOARD:
        {
            break;
        }
    }
}

void cxgui::GameView::Update(cxgui::UserAction p_context, cxgui::UserActionSubject* p_subject)
{
    IF_CONDITION_NOT_MET_DO(p_subject, return;);

    switch(p_context)
    {
        case cxgui::UserAction::MOUSE_CLICKED:
        {
            m_controller.OnDown(m_presenter.GetGameViewActivePlayerChipColor(), m_board->GetCurrentColumn().Get());
        }
    }
}

void cxgui::GameView::SetLayout()
{
    IF_CONDITION_NOT_MET_DO(m_viewLayout, return;);
    IF_CONDITION_NOT_MET_DO(m_playersInfoLayout, return;);

    constexpr cxmodel::Row row0{0u};
    constexpr cxmodel::Row row1{1u};
    constexpr cxmodel::Row row2{2u};
    constexpr cxmodel::Row row4{4u};
    constexpr cxgui::ILayout::RowSpan singleRowSpan{1u};

    constexpr cxmodel::Column column0{0u};
    constexpr cxmodel::Column column1{1u};
    constexpr cxmodel::Column column2{2u};
    constexpr cxgui::ILayout::ColumnSpan singleColumnSpan{1u};
    constexpr cxgui::ILayout::ColumnSpan fullSpan{2u};


    // Main view layout:
    m_viewLayout->Register(m_title, {row0, singleRowSpan}, {column0, fullSpan});
    m_viewLayout->Register(*m_playersInfoLayout, {row1, singleRowSpan}, {column0, fullSpan});

    if(INL_ASSERT(m_board))
    {
        m_viewLayout->Register(*m_board, {row4, singleRowSpan}, {column0, fullSpan});
    }

    // Players info layout:
    m_playersInfoLayout->Register(m_activePlayerLabel, {row0, singleRowSpan}, {column0, singleColumnSpan});
    m_playersInfoLayout->Register(m_activePlayerName, {row0, singleRowSpan}, {column1, singleColumnSpan});
    if(INL_ASSERT(m_activePlayerChip))
    {
        m_playersInfoLayout->Register(*m_activePlayerChip, {row0, singleRowSpan}, {column2, singleColumnSpan});
    }

    m_playersInfoLayout->Register(m_nextPlayerLabel, {row1, singleRowSpan}, {column0, singleColumnSpan});
    m_playersInfoLayout->Register(m_nextPlayerName, {row1, singleRowSpan}, {column1, singleColumnSpan});
    if(INL_ASSERT(m_nextPlayerChip))
    {
        m_playersInfoLayout->Register(*m_nextPlayerChip, {row1, singleRowSpan}, {column2, singleColumnSpan});
    }
}

void cxgui::GameView::PopulateWidgets()
{
    m_title.set_text(m_presenter.GetGameViewTitle());

    m_activePlayerLabel.set_text(m_presenter.GetGameViewActivePlayerLabelText());
    m_activePlayerName.set_text(m_presenter.GetGameViewActivePlayerName());
    m_activePlayerChip->ChangeColor(m_presenter.GetGameViewActivePlayerChipColor());

    m_nextPlayerLabel.set_text(m_presenter.GetGameViewNextPlayerLabelText());
    m_nextPlayerName.set_text(m_presenter.GetGameViewNextPlayerName());
    m_nextPlayerChip->ChangeColor(m_presenter.GetGameViewNextPlayerChipColor());
}

void cxgui::GameView::ConfigureWidgets()
{
    // Window margin:
    m_mainLayout.SetMargins({
        TopMargin{DIALOG_SIDE_MARGIN},
        BottomMargin{DIALOG_SIDE_MARGIN},
        LeftMargin{DIALOG_SIDE_MARGIN},
        RightMargin{DIALOG_SIDE_MARGIN}
    });

    // View title:
    m_title.set_use_markup(true);
    m_title.set_markup("<big><b>" + m_title.get_text() + "</b></big>");
    m_title.set_margin_bottom(TITLE_BOTTOM_MARGIN);

    // Players section:
    m_activePlayerLabel.set_halign(Gtk::Align::ALIGN_START);
    m_activePlayerLabel.set_hexpand(true);
    m_activePlayerLabel.set_markup("<b>" + m_activePlayerLabel.get_text() + "</b>");
    m_activePlayerName.set_halign(Gtk::Align::ALIGN_START);
    m_activePlayerName.set_hexpand(true);
    if(INL_ASSERT(m_activePlayerChip))
    {
        m_activePlayerChip->set_hexpand(true);
        m_activePlayerChip->set_vexpand(false);
        m_activePlayerChip->set_halign(Gtk::Align::ALIGN_START);
    }

    m_nextPlayerLabel.set_halign(Gtk::Align::ALIGN_START);
    m_nextPlayerLabel.set_hexpand(true);
    m_nextPlayerLabel.set_use_markup(true);
    m_nextPlayerLabel.set_markup("<b>" + m_nextPlayerLabel.get_text() + "</b>");
    m_nextPlayerName.set_halign(Gtk::Align::ALIGN_START);
    m_nextPlayerName.set_hexpand(true);
    if(INL_ASSERT(m_nextPlayerChip))
    {
        m_nextPlayerChip->set_hexpand(true);
        m_nextPlayerChip->set_vexpand(false);
        m_nextPlayerChip->set_halign(Gtk::Align::ALIGN_START);
    }

    m_playersInfoLayout->SetMargins({
        cxgui::TopMargin{0},
        cxgui::BottomMargin{SECTION_BOTTOM_MARGIN},
        cxgui::LeftMargin{0},
        cxgui::RightMargin{0},
    });
}

bool cxgui::GameView::OnKeyPressed(GdkEventKey* p_event)
{
    IF_PRECONDITION_NOT_MET_DO(p_event, return STOP_EVENT_PROPAGATION;);
    IF_PRECONDITION_NOT_MET_DO(m_board, return STOP_EVENT_PROPAGATION;);

    // We do not want the user to be able to request another animation
    // while one is already running:
    DisableKeyHandlers();

    const auto strategy = GameViewKeyHandlerStrategyFactory::Create(p_event);

    if(!strategy)
    {
        // Here propagation of the event is wanted. Some key events are caught
        // here, but should be handled by the main window (undo for example).
        // If we stop the propagation, the main window never gets the event
        // and bugs can occur:
        EnableKeyHandlers();
        return PROPAGATE_EVENT;
    }

    return strategy->Handle(m_controller, *m_board);
}

void cxgui::GameView::EnableKeyHandlers()
{
    m_parentWindow.add_events(Gdk::KEY_PRESS_MASK);
    m_keysPressedConnection = m_parentWindow.signal_key_press_event().connect([this](GdkEventKey* p_event){return OnKeyPressed(p_event);}, false);
}

void cxgui::GameView::DisableKeyHandlers()
{
   m_keysPressedConnection.disconnect();
   m_parentWindow.add_events(m_parentWindow.get_events() & ~Gdk::KEY_PRESS_MASK);
}

void cxgui::GameView::UpdateChipDropped()
{
    IF_CONDITION_NOT_MET_DO(m_board, return;);

    SyncPlayers();
    Notify(cxgui::BoardAnimationNotificationContext::ANIMATE_MOVE_DROP_CHIP);
}

void cxgui::GameView::UpdateUndoChipDropped()
{
    IF_CONDITION_NOT_MET_DO(m_board, return;);

    SyncPlayers();
    Notify(cxgui::BoardAnimationNotificationContext::ANIMATE_UNDO_DROP_CHIP);
}

void cxgui::GameView::UpdateRedoChipDropped()
{
    IF_CONDITION_NOT_MET_DO(m_board, return;);

    SyncPlayers();
    Notify(cxgui::BoardAnimationNotificationContext::ANIMATE_REDO_DROP_CHIP);
}

void cxgui::GameView::UpdateChipDroppedFailed()
{
    EnableKeyHandlers();
}

void cxgui::GameView::UpdateChipMovedLeftOneColumn()
{
    IF_CONDITION_NOT_MET_DO(m_board, return;);
    Notify(cxgui::BoardAnimationNotificationContext::ANIMATE_MOVE_LEFT_ONE_COLUMN);
}

void cxgui::GameView::UpdateChipMovedRightOneColumn()
{
    IF_CONDITION_NOT_MET_DO(m_board, return;);
    Notify(cxgui::BoardAnimationNotificationContext::ANIMATE_MOVE_RIGHT_ONE_COLUMN);
}

void cxgui::GameView::UpdateChipMovedRightToTarget()
{
    IF_CONDITION_NOT_MET_DO(m_board, return;);
    Notify(cxgui::BoardAnimationNotificationContext::ANIMATE_MOVE_RIGHT_TO_TARGET);
}

void cxgui::GameView::UpdateGameResolved()
{
    IF_CONDITION_NOT_MET_DO(m_board, return;);
    Notify(cxgui::BoardAnimationNotificationContext::ANIMATE_REINITIALIZE_BOARD);
}

void cxgui::GameView::UpdateGameReinitialized()
{
    IF_CONDITION_NOT_MET_DO(m_board, return;);

    SyncPlayers();
    Notify(cxgui::BoardAnimationNotificationContext::ANIMATE_REINITIALIZE_BOARD);
}

void cxgui::GameView::SyncPlayers()
{
    m_activePlayerChip->ChangeColor(m_presenter.GetGameViewActivePlayerChipColor());
    m_activePlayerName.set_text(m_presenter.GetGameViewActivePlayerName());

    m_nextPlayerChip->ChangeColor(m_presenter.GetGameViewNextPlayerChipColor());
    m_nextPlayerName.set_text(m_presenter.GetGameViewNextPlayerName());
}
