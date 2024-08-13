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

#include <cxinv/assertion.h>
#include <cxmodel/IChip.h>
#include <cxmodel/ModelNotificationContext.h>
#include <cxui/BoardAnimation.h>
#include <cxcmnui/common.h>
#include <cxcmnui/EventPropagation.h>
#include <cxui/GameViewKeyHandlerStrategyFactory.h>
#include <cxuigtkmm3/GameView.h>
#include <cxui/IAbstractConnectXWidgetsFactory.h>
#include <cxcmnui/IAbstractWidgetsFactory.h>
#include <cxui/IAnimatedBoard.h>
#include <cxui/IAnimatedBoardPresenter.h>
#include <cxui/IChip.h>
#include <cxui/IGameViewController.h>
#include <cxui/IGameViewPresenter.h>
#include <cxcmnui/ILabel.h>
#include <cxcmnui/ILayout.h>
#include <cxcmnui/IWindow.h>
#include <cxcmnui/KeyboardKeyPressedEvent.h>
#include <cxcmnui/Margins.h>
#include <cxcmnui/NotSupported.h>
#include <cxui/WidgetsFactories.h>

namespace
{

constexpr cx::ui::AnimationSpeed NUMBER_CHIPS_MOVED_PER_SECOND{3u};

} // namespace

cx::ui::gtkmm3::GameView::GameView(
    cx::ui::WidgetsFactories& p_widgetsFactories,
    cx::ui::IGameViewPresenter& p_presenter,
    cx::ui::IGameViewController& p_controller,
    cx::cmn::ui::IWindow& p_parentWindow,
    cx::cmn::ui::ILayout& p_mainLayout,
    const cx::model::Column& p_viewLeft,
    const cx::model::Row& p_viewTop)
: m_widgetsFactories{p_widgetsFactories}
, m_presenter{p_presenter}
, m_controller{p_controller}
, m_parentWindow{p_parentWindow}
, m_mainLayout{p_mainLayout}
, m_viewLeft{p_viewLeft}
, m_viewTop{p_viewTop}
{
    const cx::cmn::ui::IAbstractWidgetsFactory& standardWidgetsFactory = m_widgetsFactories.GetStandardWidgetsFactory();
    const cx::ui::IAbstractConnectXWidgetsFactory& connectXWidgetsFactory = m_widgetsFactories.GetConnectXWidgetsFactory();

    m_board = connectXWidgetsFactory.CreateGameBoard(m_presenter, NUMBER_CHIPS_MOVED_PER_SECOND);

    m_activePlayerChip = connectXWidgetsFactory.CreateChip(cx::model::MakeTransparent(), cx::model::MakeTransparent(), cx::cmn::ui::DEFAULT_CHIP_SIZE / 4);
    m_nextPlayerChip = connectXWidgetsFactory.CreateChip(cx::model::MakeTransparent(), cx::model::MakeTransparent(), cx::cmn::ui::DEFAULT_CHIP_SIZE / 4);

    m_viewLayout = standardWidgetsFactory.CreateLayout();
    m_playersInfoLayout = standardWidgetsFactory.CreateLayout();

    m_title = standardWidgetsFactory.CreateLabel();
    m_activePlayerLabel = standardWidgetsFactory.CreateLabel();
    m_activePlayerName = standardWidgetsFactory.CreateLabel();
    m_nextPlayerLabel = standardWidgetsFactory.CreateLabel();
    m_nextPlayerName = standardWidgetsFactory.CreateLabel();

    SetLayout();
    PopulateWidgets();
    ConfigureWidgets();

    // Attach to the board:
    if(m_board)
    {
        Attach(m_board.get());
        m_board->cx::ui::BoardAnimationSubject::Attach(this);
        m_board->cx::ui::UserActionSubject::Attach(this);
    }

    POSTCONDITION(m_board);
    POSTCONDITION(m_activePlayerChip);
    POSTCONDITION(m_nextPlayerChip);
    POSTCONDITION(m_viewLayout);
    POSTCONDITION(m_playersInfoLayout);
    POSTCONDITION(m_title);
    POSTCONDITION(m_activePlayerLabel);
    POSTCONDITION(m_activePlayerName);
    POSTCONDITION(m_nextPlayerLabel);
    POSTCONDITION(m_nextPlayerName);
}

cx::ui::gtkmm3::GameView::~GameView()
{
    DisableKeyHandlers();
}

void cx::ui::gtkmm3::GameView::Activate()
{
    EnableKeyHandlers();

    cx::cmn::ui::IWidget* currentViewLayout = m_mainLayout.GetWidgetAtPosition(m_viewTop, m_viewLeft);

    if(!currentViewLayout)
    {
        ASSERT_ERROR_MSG("Current view should be valid.");
        return;
    }

    // Unregister the previous view layout:
    m_mainLayout.Unregister(*currentViewLayout);

    // Register the new view layout:
    m_mainLayout.Register(*m_viewLayout,
                          {m_viewTop, cx::cmn::ui::ILayout::RowSpan{1u}},
                          {m_viewLeft, cx::cmn::ui::ILayout::ColumnSpan{2u}});

    // Renintialize animated game board.
    UpdateGameReinitialized();
}

void cx::ui::gtkmm3::GameView::DeActivate()
{
    // Since the Game View is recreated every time, we need to clear
    // the view layout from the main layout, otherwise we will have a
    // dangling reference in the main layout once the view is reset.
    cx::cmn::ui::IWidget* currentViewLayout = m_mainLayout.GetWidgetAtPosition(m_viewTop, m_viewLeft);
    if(INL_ASSERT(currentViewLayout))
    {
        m_mainLayout.Unregister(*currentViewLayout);
    }

    DisableKeyHandlers();
}

void cx::ui::gtkmm3::GameView::Update(cx::model::ModelNotificationContext p_context)
{
    switch(p_context)
    {
        case cx::model::ModelNotificationContext::CHIP_DROPPED:
        {
            UpdateChipDropped();
            break;
        }
        case cx::model::ModelNotificationContext::CHIP_DROPPED_FAILED:
        {
            UpdateChipDroppedFailed();
            break;
        }
        case cx::model::ModelNotificationContext::CHIP_MOVED_LEFT_ONE_COLUMN:
        {
            UpdateChipMovedLeftOneColumn();
            break;
        }
        case cx::model::ModelNotificationContext::CHIP_MOVED_RIGHT_ONE_COLUMN:
        {
            UpdateChipMovedRightOneColumn();
            break;
        }
        case cx::model::ModelNotificationContext::GAME_WON:
        case cx::model::ModelNotificationContext::GAME_TIED:
        {
            UpdateGameResolved();
            break;
        }
        case cx::model::ModelNotificationContext::GAME_REINITIALIZED:
        {
            UpdateGameReinitialized();
            break;
        }
        case cx::model::ModelNotificationContext::UNDO_CHIP_DROPPED:
        {
            UpdateUndoChipDropped();
            break;
        }
        case cx::model::ModelNotificationContext::REDO_CHIP_DROPPED:
        {
            UpdateRedoChipDropped();
            break;
        }
        default:
            break;
    }
}

size_t cx::ui::gtkmm3::GameView::GetWidth() const 
{
    return m_viewLayout->GetWidth();
}

size_t cx::ui::gtkmm3::GameView::GetHeight() const 
{
    return m_viewLayout->GetHeight();
}

void cx::ui::gtkmm3::GameView::SetEnabled(cx::cmn::ui::EnabledState p_enabled) 
{
    return m_viewLayout->SetEnabled(p_enabled);
}

void cx::ui::gtkmm3::GameView::SetMargins(const cx::cmn::ui::Margins& p_newMarginSizes) 
{
    return m_viewLayout->SetMargins(p_newMarginSizes);
}

void cx::ui::gtkmm3::GameView::SetTooltip(const std::string& p_tooltipContents)
{
    return m_viewLayout->SetTooltip(p_tooltipContents);
}

std::unique_ptr<cx::cmn::ui::ISignal<cx::cmn::ui::EventPropagation, cx::cmn::ui::KeyboardKeyPressedEvent>> cx::ui::gtkmm3::GameView::OnKeyPressed()
{
    return std::make_unique<cx::cmn::ui::NotSupported<cx::cmn::ui::EventPropagation, cx::cmn::ui::KeyboardKeyPressedEvent>>();
}

void cx::ui::gtkmm3::GameView::Update(cx::ui::BoardAnimationNotificationContext p_context, cx::ui::BoardAnimationSubject* p_subject)
{
    IF_CONDITION_NOT_MET_DO(p_subject, return;);

    switch(p_context)
    {
        case cx::ui::BoardAnimationNotificationContext::ANIMATION_MODEL_VALID:
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
        case cx::ui::BoardAnimationNotificationContext::ANIMATE_MOVE_LEFT_ONE_COLUMN:
        case cx::ui::BoardAnimationNotificationContext::ANIMATE_MOVE_RIGHT_ONE_COLUMN:
        case cx::ui::BoardAnimationNotificationContext::ANIMATE_MOVE_RIGHT_TO_TARGET:
        case cx::ui::BoardAnimationNotificationContext::ANIMATE_MOVE_DROP_CHIP:
        case cx::ui::BoardAnimationNotificationContext::ANIMATE_UNDO_DROP_CHIP:
        case cx::ui::BoardAnimationNotificationContext::ANIMATE_REDO_DROP_CHIP:
        case cx::ui::BoardAnimationNotificationContext::ANIMATE_REINITIALIZE_BOARD:
        {
            return;
        }

        case cx::ui::BoardAnimationNotificationContext::POST_ANIMATE_MOVE_LEFT_ONE_COLUMN:
        case cx::ui::BoardAnimationNotificationContext::POST_ANIMATE_MOVE_RIGHT_ONE_COLUMN:
        case cx::ui::BoardAnimationNotificationContext::POST_ANIMATE_DROP_CHIP:
        {
            if(m_presenter.IsCurrentPlayerABot())
            {
                UpdateChipMovedRightToTarget();
                break;
            }

            EnableKeyHandlers();
            break;
        }
        case cx::ui::BoardAnimationNotificationContext::POST_ANIMATE_UNDO_DROP_CHIP:
        case cx::ui::BoardAnimationNotificationContext::POST_ANIMATE_REDO_DROP_CHIP:
        {
            break;
        }
        case cx::ui::BoardAnimationNotificationContext::POST_ANIMATE_MOVE_RIGHT_TO_TARGET:
        {
            m_controller.OnDown(m_presenter.GetGameViewActivePlayerChipColor(), m_presenter.GetBotTarget());
            break;
        }
        case cx::ui::BoardAnimationNotificationContext::POST_ANIMATE_REINITIALIZE_BOARD:
        {
            break;
        }
    }
}

void cx::ui::gtkmm3::GameView::Update(cx::ui::UserAction p_context, cx::ui::UserActionSubject* p_subject)
{
    IF_CONDITION_NOT_MET_DO(p_subject, return;);

    switch(p_context)
    {
        case cx::ui::UserAction::MOUSE_CLICKED:
        {
            m_controller.OnDown(m_presenter.GetGameViewActivePlayerChipColor(), m_board->GetCurrentColumn().Get());
        }
    }
}

void cx::ui::gtkmm3::GameView::SetLayout()
{
    IF_CONDITION_NOT_MET_DO(m_viewLayout, return;);
    IF_CONDITION_NOT_MET_DO(m_playersInfoLayout, return;);

    using namespace cx::cmn::ui;

    constexpr cx::model::Row row0{0u};
    constexpr cx::model::Row row1{1u};
    constexpr cx::model::Row row4{4u};
    constexpr ILayout::RowSpan singleRowSpan{1u};

    constexpr cx::model::Column column0{0u};
    constexpr cx::model::Column column1{1u};
    constexpr cx::model::Column column2{2u};
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

void cx::ui::gtkmm3::GameView::PopulateWidgets()
{
    m_title->UpdateContents(m_presenter.GetGameViewTitle());

    m_activePlayerLabel->UpdateContents(m_presenter.GetGameViewActivePlayerLabelText());
    m_activePlayerName->UpdateContents(m_presenter.GetGameViewActivePlayerName());
    m_activePlayerChip->ChangeColor(m_presenter.GetGameViewActivePlayerChipColor());

    m_nextPlayerLabel->UpdateContents(m_presenter.GetGameViewNextPlayerLabelText());
    m_nextPlayerName->UpdateContents(m_presenter.GetGameViewNextPlayerName());
    m_nextPlayerChip->ChangeColor(m_presenter.GetGameViewNextPlayerChipColor());
}

void cx::ui::gtkmm3::GameView::ConfigureWidgets()
{
    using namespace cx::cmn::ui;

    // Window margin:
    m_mainLayout.SetMargins({
        cx::cmn::ui::TopMargin{DIALOG_SIDE_MARGIN},
        cx::cmn::ui::BottomMargin{DIALOG_SIDE_MARGIN},
        cx::cmn::ui::LeftMargin{DIALOG_SIDE_MARGIN},
        cx::cmn::ui::RightMargin{DIALOG_SIDE_MARGIN}
    });

    // View title:
    m_title->UpdateContents("<big><b>" + m_title->GetContents() + "</b></big>");
    m_title->SetMargins({TopMargin{0}, BottomMargin{TITLE_BOTTOM_MARGIN}, LeftMargin{0}, RightMargin{0}});

    // Players section:
    m_activePlayerLabel->UpdateContents("<b>" + m_activePlayerLabel->GetContents() + "</b>");
    m_nextPlayerLabel->UpdateContents("<b>" + m_nextPlayerLabel->GetContents() + "</b>");

    m_playersInfoLayout->SetMargins({
        cx::cmn::ui::TopMargin{0},
        cx::cmn::ui::BottomMargin{SECTION_BOTTOM_MARGIN},
        cx::cmn::ui::LeftMargin{0},
        cx::cmn::ui::RightMargin{0},
    });
}

cx::cmn::ui::EventPropagation cx::ui::gtkmm3::GameView::OnKeyPressed(cx::cmn::ui::KeyboardKeyPressedEvent p_event)
{
    IF_PRECONDITION_NOT_MET_DO(m_board, return cx::cmn::ui::EventPropagation::STOP;);

    // We do not want the user to be able to request another animation
    // while one is already running:
    DisableKeyHandlers();

    const auto strategy = cx::ui::GameViewKeyHandlerStrategyFactory::Create(p_event);

    if(!strategy)
    {
        // Here propagation of the event is wanted. Some key events are caught
        // here, but should be handled by the main window (undo for example).
        // If we stop the propagation, the main window never gets the event
        // and bugs can occur:
        EnableKeyHandlers();
        return cx::cmn::ui::EventPropagation::PROPAGATE;
    }

    return strategy->Handle(m_controller, *m_board);
}

void cx::ui::gtkmm3::GameView::EnableKeyHandlers()
{
    m_areKeyboardEventsAccepted = true;

    m_keysPressedConnection = m_parentWindow.OnKeyPressed()->Connect(
        [this](cx::cmn::ui::KeyboardKeyPressedEvent p_event)
        {
            return OnKeyPressed(p_event);
        });
}

void cx::ui::gtkmm3::GameView::DisableKeyHandlers()
{
    IF_CONDITION_NOT_MET_DO(m_keysPressedConnection, return;);

    m_keysPressedConnection->Disconnect();

    m_areKeyboardEventsAccepted = false;
}

void cx::ui::gtkmm3::GameView::UpdateChipDropped()
{
    IF_CONDITION_NOT_MET_DO(m_board, return;);

    SyncPlayers();
    Notify(cx::ui::BoardAnimationNotificationContext::ANIMATE_MOVE_DROP_CHIP);
}

void cx::ui::gtkmm3::GameView::UpdateUndoChipDropped()
{
    IF_CONDITION_NOT_MET_DO(m_board, return;);

    SyncPlayers();
    Notify(cx::ui::BoardAnimationNotificationContext::ANIMATE_UNDO_DROP_CHIP);
}

void cx::ui::gtkmm3::GameView::UpdateRedoChipDropped()
{
    IF_CONDITION_NOT_MET_DO(m_board, return;);

    SyncPlayers();
    Notify(cx::ui::BoardAnimationNotificationContext::ANIMATE_REDO_DROP_CHIP);
}

void cx::ui::gtkmm3::GameView::UpdateChipDroppedFailed()
{
    EnableKeyHandlers();
}

void cx::ui::gtkmm3::GameView::UpdateChipMovedLeftOneColumn()
{
    IF_CONDITION_NOT_MET_DO(m_board, return;);
    Notify(cx::ui::BoardAnimationNotificationContext::ANIMATE_MOVE_LEFT_ONE_COLUMN);
}

void cx::ui::gtkmm3::GameView::UpdateChipMovedRightOneColumn()
{
    IF_CONDITION_NOT_MET_DO(m_board, return;);
    Notify(cx::ui::BoardAnimationNotificationContext::ANIMATE_MOVE_RIGHT_ONE_COLUMN);
}

void cx::ui::gtkmm3::GameView::UpdateChipMovedRightToTarget()
{
    IF_CONDITION_NOT_MET_DO(m_board, return;);
    Notify(cx::ui::BoardAnimationNotificationContext::ANIMATE_MOVE_RIGHT_TO_TARGET);
}

void cx::ui::gtkmm3::GameView::UpdateGameResolved()
{
    IF_CONDITION_NOT_MET_DO(m_board, return;);
    Notify(cx::ui::BoardAnimationNotificationContext::ANIMATE_REINITIALIZE_BOARD);
}

void cx::ui::gtkmm3::GameView::UpdateGameReinitialized()
{
    IF_CONDITION_NOT_MET_DO(m_board, return;);

    SyncPlayers();
    Notify(cx::ui::BoardAnimationNotificationContext::ANIMATE_REINITIALIZE_BOARD);
}

void cx::ui::gtkmm3::GameView::SyncPlayers()
{
    m_activePlayerChip->ChangeColor(m_presenter.GetGameViewActivePlayerChipColor());
    m_activePlayerName->UpdateContents(m_presenter.GetGameViewActivePlayerName());

    m_nextPlayerChip->ChangeColor(m_presenter.GetGameViewNextPlayerChipColor());
    m_nextPlayerName->UpdateContents(m_presenter.GetGameViewNextPlayerName());
}
