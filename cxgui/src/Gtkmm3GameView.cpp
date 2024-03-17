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
 * @file Gtkmm3GameView.cpp
 * @date 2020
 *
 *************************************************************************************************/

#include <gtkmm/window.h> // Still in use for keyboard events.

#include <cxinv/assertion.h>
#include <cxmodel/IChip.h>
#include <cxmodel/ModelNotificationContext.h>
#include <cxgui/BoardAnimation.h>
#include <cxgui/common.h>
#include <cxgui/GameViewKeyHandlerStrategyFactory.h>
#include <cxgui/Gtkmm3AnimatedBoard.h>
#include <cxgui/Gtkmm3DiscChip.h>
#include <cxgui/Gtkmm3GameView.h>
#include <cxgui/Gtkmm3Label.h>
#include <cxgui/Gtkmm3Layout.h>
#include <cxgui/Gtkmm3WidgetDelegate.h>
#include <cxgui/IAnimatedBoardPresenter.h>
#include <cxgui/IGameViewController.h>
#include <cxgui/IGameViewPresenter.h>
#include <cxgui/IWindow.h>
#include <cxgui/Margins.h>

namespace
{

constexpr cxgui::AnimationSpeed NUMBER_CHIPS_MOVED_PER_SECOND{3u};

} // namespace

cxgui::Gtkmm3GameView::Gtkmm3GameView(IGameViewPresenter& p_presenter,
                                      IGameViewController& p_controller,
                                      IWindow& p_parentWindow,
                                      cxgui::ILayout& p_mainLayout,
                                      const cxmodel::Column& p_viewLeft,
                                      const cxmodel::Row& p_viewTop)
: m_presenter{p_presenter}
, m_controller{p_controller}
, m_parentWindow{p_parentWindow}
, m_mainLayout{p_mainLayout}
, m_viewLeft{p_viewLeft}
, m_viewTop{p_viewTop}
{
    m_board = CreateWidget<cxgui::Gtkmm3AnimatedBoard>(m_presenter, NUMBER_CHIPS_MOVED_PER_SECOND);
    ASSERT(m_board);

    m_activePlayerChip = CreateWidget<Gtkmm3DiscChip>(cxmodel::MakeTransparent(), cxmodel::MakeTransparent(), cxgui::DEFAULT_CHIP_SIZE / 4);
    ASSERT(m_activePlayerChip);
    m_nextPlayerChip = CreateWidget<cxgui::Gtkmm3DiscChip>(cxmodel::MakeTransparent(), cxmodel::MakeTransparent(), cxgui::DEFAULT_CHIP_SIZE / 4);
    ASSERT(m_nextPlayerChip);

    m_viewLayout = CreateWidget<Gtkmm3Layout>();
    ASSERT(m_viewLayout);

    m_playersInfoLayout = CreateWidget<Gtkmm3Layout>();
    ASSERT(m_playersInfoLayout);

    m_title = CreateWidget<Gtkmm3Label>("");
    ASSERT(m_title);
    m_activePlayerLabel = CreateWidget<Gtkmm3Label>("");
    ASSERT(m_activePlayerLabel);
    m_activePlayerName = CreateWidget<Gtkmm3Label>("");
    ASSERT(m_activePlayerName);
    m_nextPlayerLabel = CreateWidget<Gtkmm3Label>("");
    ASSERT(m_nextPlayerLabel);
    m_nextPlayerName = CreateWidget<Gtkmm3Label>("");
    ASSERT(m_nextPlayerName);

    SetLayout();
    PopulateWidgets();
    ConfigureWidgets();

    // Attach to the board:
    Attach(m_board.get());
    m_board->BoardAnimationSubject::Attach(this);
    m_board->UserActionSubject::Attach(this);
}

cxgui::Gtkmm3GameView::~Gtkmm3GameView()
{
    DisableKeyHandlers();
}

void cxgui::Gtkmm3GameView::Activate()
{
    EnableKeyHandlers();

    cxgui::IWidget* currentViewLayout = m_mainLayout.GetWidgetAtPosition(m_viewTop, m_viewLeft);

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

    // Renintialize animated game board.
    UpdateGameReinitialized();
}

void cxgui::Gtkmm3GameView::DeActivate()
{
    // Since the Game View is recreated every time, we need to clear
    // the view layout from the main layout, otherwise we will have a
    // dangling reference in the main layout once the view is reset.
    cxgui::IWidget* currentViewLayout = m_mainLayout.GetWidgetAtPosition(m_viewTop, m_viewLeft);
    if(INL_ASSERT(currentViewLayout))
    {
        m_mainLayout.Unregister(*currentViewLayout);
    }

    DisableKeyHandlers();
}

void cxgui::Gtkmm3GameView::Update(cxmodel::ModelNotificationContext p_context)
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

size_t cxgui::Gtkmm3GameView::GetWidth() const 
{
    return m_viewLayout->GetWidth();
}

size_t cxgui::Gtkmm3GameView::GetHeight() const 
{
    return m_viewLayout->GetHeight();
}

void cxgui::Gtkmm3GameView::SetEnabled(EnabledState p_enabled) 
{
    return m_viewLayout->SetEnabled(p_enabled);
}

void cxgui::Gtkmm3GameView::SetMargins(const Margins& p_newMarginSizes) 
{
    return m_viewLayout->SetMargins(p_newMarginSizes);
}

void cxgui::Gtkmm3GameView::SetTooltip(const std::string& p_tooltipContents)
{
    return m_viewLayout->SetTooltip(p_tooltipContents);
}


void cxgui::Gtkmm3GameView::Update(cxgui::BoardAnimationNotificationContext p_context, cxgui::BoardAnimationSubject* p_subject)
{
    IF_CONDITION_NOT_MET_DO(p_subject, return;);

    switch(p_context)
    {
        case cxgui::BoardAnimationNotificationContext::ANIMATION_MODEL_VALID:
        {
            // If the first player is a bot, we simulate a chip drop. This is necessary
            // to start the board animation process.
            if(m_presenter.IsCurrentPlayerABot())
            {
                DisableKeyHandlers();
                UpdateChipMovedRightToTarget();
            }

            return;
        }
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

void cxgui::Gtkmm3GameView::Update(cxgui::UserAction p_context, cxgui::UserActionSubject* p_subject)
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

void cxgui::Gtkmm3GameView::SetLayout()
{
    IF_CONDITION_NOT_MET_DO(m_viewLayout, return;);
    IF_CONDITION_NOT_MET_DO(m_playersInfoLayout, return;);

    constexpr cxmodel::Row row0{0u};
    constexpr cxmodel::Row row1{1u};
    constexpr cxmodel::Row row4{4u};
    constexpr ILayout::RowSpan singleRowSpan{1u};

    constexpr cxmodel::Column column0{0u};
    constexpr cxmodel::Column column1{1u};
    constexpr cxmodel::Column column2{2u};
    constexpr ILayout::ColumnSpan singleColumnSpan{1u};
    constexpr ILayout::ColumnSpan fullSpan{2u};

    constexpr ILayout::Alignement hAlignLeft{
        ILayout::VerticalAlignement::FILL,
        ILayout::HorizontalAlignement::LEFT
    };

    // Main view layout:
    m_viewLayout->Register(*m_title,             {row0, singleRowSpan}, {column0, fullSpan});
    m_viewLayout->Register(*m_playersInfoLayout, {row1, singleRowSpan}, {column0, fullSpan});

    if(INL_ASSERT(m_board))
    {
        m_viewLayout->Register(*m_board, {row4, singleRowSpan}, {column0, fullSpan});
    }

    // Players info layout:
    m_playersInfoLayout->SetColumnSpacingMode(ILayout::ColumnSpacingMode::EQUAL);
    m_playersInfoLayout->Register(*m_activePlayerLabel, {row0, singleRowSpan}, {column0, singleColumnSpan}, hAlignLeft);
    m_playersInfoLayout->Register(*m_activePlayerName,  {row0, singleRowSpan}, {column1, singleColumnSpan}, hAlignLeft);
    if(INL_ASSERT(m_activePlayerChip))
    {
        m_playersInfoLayout->Register(*m_activePlayerChip, {row0, singleRowSpan}, {column2, singleColumnSpan});
    }

    m_playersInfoLayout->Register(*m_nextPlayerLabel, {row1, singleRowSpan}, {column0, singleColumnSpan}, hAlignLeft);
    m_playersInfoLayout->Register(*m_nextPlayerName,  {row1, singleRowSpan}, {column1, singleColumnSpan}, hAlignLeft);
    if(INL_ASSERT(m_nextPlayerChip))
    {
        m_playersInfoLayout->Register(*m_nextPlayerChip, {row1, singleRowSpan}, {column2, singleColumnSpan});
    }
}

void cxgui::Gtkmm3GameView::PopulateWidgets()
{
    m_title->UpdateContents(m_presenter.GetGameViewTitle());

    m_activePlayerLabel->UpdateContents(m_presenter.GetGameViewActivePlayerLabelText());
    m_activePlayerName->UpdateContents(m_presenter.GetGameViewActivePlayerName());
    m_activePlayerChip->ChangeColor(m_presenter.GetGameViewActivePlayerChipColor());

    m_nextPlayerLabel->UpdateContents(m_presenter.GetGameViewNextPlayerLabelText());
    m_nextPlayerName->UpdateContents(m_presenter.GetGameViewNextPlayerName());
    m_nextPlayerChip->ChangeColor(m_presenter.GetGameViewNextPlayerChipColor());
}

void cxgui::Gtkmm3GameView::ConfigureWidgets()
{
    // Window margin:
    m_mainLayout.SetMargins({
        cxgui::TopMargin{DIALOG_SIDE_MARGIN},
        cxgui::BottomMargin{DIALOG_SIDE_MARGIN},
        cxgui::LeftMargin{DIALOG_SIDE_MARGIN},
        cxgui::RightMargin{DIALOG_SIDE_MARGIN}
    });

    // View title:
    m_title->UpdateContents("<big><b>" + m_title->GetContents() + "</b></big>");
    m_title->SetMargins({TopMargin{0}, BottomMargin{TITLE_BOTTOM_MARGIN}, LeftMargin{0}, RightMargin{0}});

    // Players section:
    m_activePlayerLabel->UpdateContents("<b>" + m_activePlayerLabel->GetContents() + "</b>");
    m_nextPlayerLabel->UpdateContents("<b>" + m_nextPlayerLabel->GetContents() + "</b>");

    m_playersInfoLayout->SetMargins({
        cxgui::TopMargin{0},
        cxgui::BottomMargin{SECTION_BOTTOM_MARGIN},
        cxgui::LeftMargin{0},
        cxgui::RightMargin{0},
    });
}

bool cxgui::Gtkmm3GameView::OnKeyPressed(GdkEventKey* p_event)
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

void cxgui::Gtkmm3GameView::EnableKeyHandlers()
{
    auto* gtkWindow = dynamic_cast<Gtk::Window*>(&m_parentWindow);
    IF_CONDITION_NOT_MET_DO(gtkWindow, return;);

    gtkWindow->add_events(Gdk::KEY_PRESS_MASK);
    m_keysPressedConnection = gtkWindow->signal_key_press_event().connect(
        [this](GdkEventKey* p_event)
        {
            return OnKeyPressed(p_event);
        },
        false);
}

void cxgui::Gtkmm3GameView::DisableKeyHandlers()
{
    auto* gtkWindow = dynamic_cast<Gtk::Window*>(&m_parentWindow);
    IF_CONDITION_NOT_MET_DO(gtkWindow, return;);

    m_keysPressedConnection.disconnect();
    gtkWindow->add_events(gtkWindow->get_events() & ~Gdk::KEY_PRESS_MASK);
}

void cxgui::Gtkmm3GameView::UpdateChipDropped()
{
    IF_CONDITION_NOT_MET_DO(m_board, return;);

    SyncPlayers();
    Notify(cxgui::BoardAnimationNotificationContext::ANIMATE_MOVE_DROP_CHIP);
}

void cxgui::Gtkmm3GameView::UpdateUndoChipDropped()
{
    IF_CONDITION_NOT_MET_DO(m_board, return;);

    SyncPlayers();
    Notify(cxgui::BoardAnimationNotificationContext::ANIMATE_UNDO_DROP_CHIP);
}

void cxgui::Gtkmm3GameView::UpdateRedoChipDropped()
{
    IF_CONDITION_NOT_MET_DO(m_board, return;);

    SyncPlayers();
    Notify(cxgui::BoardAnimationNotificationContext::ANIMATE_REDO_DROP_CHIP);
}

void cxgui::Gtkmm3GameView::UpdateChipDroppedFailed()
{
    EnableKeyHandlers();
}

void cxgui::Gtkmm3GameView::UpdateChipMovedLeftOneColumn()
{
    IF_CONDITION_NOT_MET_DO(m_board, return;);
    Notify(cxgui::BoardAnimationNotificationContext::ANIMATE_MOVE_LEFT_ONE_COLUMN);
}

void cxgui::Gtkmm3GameView::UpdateChipMovedRightOneColumn()
{
    IF_CONDITION_NOT_MET_DO(m_board, return;);
    Notify(cxgui::BoardAnimationNotificationContext::ANIMATE_MOVE_RIGHT_ONE_COLUMN);
}

void cxgui::Gtkmm3GameView::UpdateChipMovedRightToTarget()
{
    IF_CONDITION_NOT_MET_DO(m_board, return;);
    Notify(cxgui::BoardAnimationNotificationContext::ANIMATE_MOVE_RIGHT_TO_TARGET);
}

void cxgui::Gtkmm3GameView::UpdateGameResolved()
{
    IF_CONDITION_NOT_MET_DO(m_board, return;);
    Notify(cxgui::BoardAnimationNotificationContext::ANIMATE_REINITIALIZE_BOARD);
}

void cxgui::Gtkmm3GameView::UpdateGameReinitialized()
{
    IF_CONDITION_NOT_MET_DO(m_board, return;);

    SyncPlayers();
    Notify(cxgui::BoardAnimationNotificationContext::ANIMATE_REINITIALIZE_BOARD);
}

void cxgui::Gtkmm3GameView::SyncPlayers()
{
    m_activePlayerChip->ChangeColor(m_presenter.GetGameViewActivePlayerChipColor());
    m_activePlayerName->UpdateContents(m_presenter.GetGameViewActivePlayerName());

    m_nextPlayerChip->ChangeColor(m_presenter.GetGameViewNextPlayerChipColor());
    m_nextPlayerName->UpdateContents(m_presenter.GetGameViewNextPlayerName());
}
