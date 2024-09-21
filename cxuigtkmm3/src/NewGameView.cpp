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
 * @file NewGameView.cpp
 * @date 2020
 *
 *************************************************************************************************/

#include <algorithm>
#include <memory>
#include <sstream>

#include <cxcmn/helpers.h>
#include <cxinv/assertion.h>
#include <cxmodel/IChip.h>
#include <cxmodel/NewGameInformation.h>
#include <cxcmnui/common.h>
#include <cxcmnui/DialogRole.h>
#include <cxcmnui/EnabledState.h>
#include <cxcmnui/extractRawUserInput.h>
#include <cxcmnui/IAbstractWidgetsFactory.h>
#include <cxcmnui/IButton.h>
#include <cxcmnui/IWindow.h>
#include <cxcmnui/ILabel.h>
#include <cxcmnui/ILayout.h>
#include <cxcmnui/ISpinBox.h>
#include <cxcmnui/Margins.h>
#include <cxcmnui/NotSupported.h>
#include <cxcmnui/widgetUtilities.h>
#include <cxui/IAbstractConnectXWidgetsFactory.h>
#include <cxui/INewGameViewController.h>
#include <cxui/INewGameViewPresenter.h>
#include <cxui/INewPlayersList.h>
#include <cxui/WidgetsFactories.h>

#include "NewGameView.h"

namespace
{

void DisplayWarningDialog(
    const cx::cmn::ui::IAbstractWidgetsFactory& p_widgetsFactory,
    cx::cmn::ui::IWindow& p_parent,
    const std::string& p_message)
{
    using namespace cx::cmn::ui;

    IF_PRECONDITION_NOT_MET_DO(!p_message.empty(), return;);

    std::unique_ptr<IWindow> errorDialog = p_widgetsFactory.CreateDialog(p_parent, DialogRole::WARNING, p_message);
    IF_CONDITION_NOT_MET_DO(errorDialog, return;);

    // Blocks the main loop:
    const int result = errorDialog->Show();
    IF_PRECONDITION_NOT_MET_DO(result == EXIT_SUCCESS, return;);
}

} // namespace

cx::ui::gtkmm3::NewGameView::NewGameView(
    cx::ui::WidgetsFactories& p_widgetsFactories,
    cx::ui::INewGameViewPresenter& p_presenter,
    cx::ui::INewGameViewController& p_controller,
    cx::cmn::ui::IWindow& p_parentWindow,
    cx::cmn::ui::ILayout& p_mainLayout,
    const cx::cmn::ui::ILayout::Column& p_viewLeft,
    const cx::cmn::ui::ILayout::Row& p_viewTop)
 : m_widgetsFactories{p_widgetsFactories}
 , m_presenter{p_presenter}
 , m_controller{p_controller}
 , m_parentWindow{p_parentWindow}
 , m_mainLayout{p_mainLayout}
 , m_viewLeft{p_viewLeft}
 , m_viewTop{p_viewTop}
{
    const cx::ui::IAbstractConnectXWidgetsFactory& connectXWidgetsFactory = m_widgetsFactories.GetConnectXWidgetsFactory();
    const cx::cmn::ui::IAbstractWidgetsFactory& standardWidgetsFactory = m_widgetsFactories.GetStandardWidgetsFactory();

    m_viewLayout = standardWidgetsFactory.CreateLayout();
    m_playersList = connectXWidgetsFactory.CreateNewPlayersList(m_presenter);

    using namespace cx::cmn::ui;

    constexpr ISpinBox::ClimbRate climbRate{1u};
    {
        const int inARowMinValue = p_presenter.GetNewGameViewMinInARowValue();
        const int inARowMaxValue = p_presenter.GetNewGameViewMaxInARowValue();
        const int inARowDefaultValue = m_presenter.GetDefaultInARowValue();
        const ISpinBox::Range inARowValidRange{ISpinBox::Minimum{inARowMinValue}, ISpinBox::Maximum{inARowMaxValue}};
        m_inARowSpinBox = standardWidgetsFactory.CreateSpinBox(inARowDefaultValue, climbRate, inARowValidRange);
    }
    {
        const int boardWidthMinValue = p_presenter.GetNewGameViewMinBoardWidthValue();
        const int boardWidthMaxValue = p_presenter.GetNewGameViewMaxBoardWidthValue();
        const int boardWidthDefaultValue = m_presenter.GetDefaultBoardWidthValue();
        const ISpinBox::Range boardWidthValidRange{ISpinBox::Minimum{boardWidthMinValue}, ISpinBox::Maximum{boardWidthMaxValue}};
        m_boardWidthSpinBox = standardWidgetsFactory.CreateSpinBox(boardWidthDefaultValue, climbRate, boardWidthValidRange);
    }
    {
        const int boardHeightMinValue = p_presenter.GetNewGameViewMinBoardHeightValue();
        const int boardHeightMaxValue = p_presenter.GetNewGameViewMaxBoardHeightValue();
        const int boardHeightDefaultValue = m_presenter.GetDefaultBoardHeightValue();
        const ISpinBox::Range boardHeightValidRange{ISpinBox::Minimum{boardHeightMinValue}, ISpinBox::Maximum{boardHeightMaxValue}};
        m_boardHeightSpinBox = standardWidgetsFactory.CreateSpinBox(boardHeightDefaultValue, climbRate, boardHeightValidRange);
    }

    m_addPlayerButton = standardWidgetsFactory.CreateButton(m_presenter.GetNewGameViewAddPlayerButtonText());
    m_removePlayerButton = standardWidgetsFactory.CreateButton(m_presenter.GetNewGameViewRemovePlayerButtonText());
    m_startButton = standardWidgetsFactory.CreateButton(m_presenter.GetNewGameViewStartButtonText());

    m_title = standardWidgetsFactory.CreateLabel();
    m_gameSectionTitle = standardWidgetsFactory.CreateLabel();
    m_inARowLabel = standardWidgetsFactory.CreateLabel();
    m_gridSectionTitle = standardWidgetsFactory.CreateLabel();
    m_gridWidthLabel = standardWidgetsFactory.CreateLabel();
    m_gridHeightLabel = standardWidgetsFactory.CreateLabel();
    m_playersSectionTitle = standardWidgetsFactory.CreateLabel();

    SetLayout();
    PopulateWidgets();
    ConfigureWidgets();

    m_removePlayerButton->OnClicked()->Connect([this](){OnRemovePlayer();});
    m_addPlayerButton->OnClicked()->Connect([this](){OnAddPlayer();});
    m_startButton->OnClicked()->Connect([this](){OnStart();});

    // Start button validations:
    m_removePlayerButton->OnClicked()->Connect([this](){OnNewGameParameterUpdated();});
    m_addPlayerButton->OnClicked()->Connect([this](){OnNewGameParameterUpdated();});
    m_playersList->OnPlayerUpdated()->Connect([this](){OnNewGameParameterUpdated();});

    POSTCONDITION(m_viewLayout);
    POSTCONDITION(m_playersList);
    POSTCONDITION(m_inARowSpinBox);
    POSTCONDITION(m_boardWidthSpinBox);
    POSTCONDITION(m_boardHeightSpinBox);
    POSTCONDITION(m_addPlayerButton);
    POSTCONDITION(m_removePlayerButton);
    POSTCONDITION(m_startButton);
    POSTCONDITION(m_title);
    POSTCONDITION(m_gameSectionTitle);
    POSTCONDITION(m_inARowLabel);
    POSTCONDITION(m_gridSectionTitle);
    POSTCONDITION(m_gridWidthLabel);
    POSTCONDITION(m_gridHeightLabel);
    POSTCONDITION(m_playersSectionTitle);
}

void cx::ui::gtkmm3::NewGameView::Activate()
{
   m_mainLayout.Register(*m_viewLayout,
                         {m_viewTop, cx::cmn::ui::ILayout::RowSpan{1u}},
                         {m_viewLeft, cx::cmn::ui::ILayout::ColumnSpan{2u}});
}

void cx::ui::gtkmm3::NewGameView::DeActivate()
{
    // Nothing to do...
}

void cx::ui::gtkmm3::NewGameView::Update(cx::model::ModelNotificationContext /*p_context*/)
{
    // Noting to do...
}

size_t cx::ui::gtkmm3::NewGameView::GetWidth() const 
{
    return m_viewLayout->GetWidth();
}

size_t cx::ui::gtkmm3::NewGameView::GetHeight() const 
{
    return m_viewLayout->GetHeight();
}

void cx::ui::gtkmm3::NewGameView::SetEnabled(cx::cmn::ui::EnabledState p_enabled) 
{
    return m_viewLayout->SetEnabled(p_enabled);
}

void cx::ui::gtkmm3::NewGameView::SetMargins(const cx::cmn::ui::Margins& p_newMarginSizes) 
{
    return m_viewLayout->SetMargins(p_newMarginSizes);
}

void cx::ui::gtkmm3::NewGameView::SetTooltip(const std::string& p_tooltipContents)
{
    return m_viewLayout->SetTooltip(p_tooltipContents);
}

std::unique_ptr<cx::cmn::ui::ISignal<cx::cmn::ui::EventPropagation, cx::cmn::ui::KeyboardKeyPressedEvent>> cx::ui::gtkmm3::NewGameView::OnKeyPressed()
{
    return std::make_unique<cx::cmn::ui::NotSupported<cx::cmn::ui::EventPropagation, cx::cmn::ui::KeyboardKeyPressedEvent>>();
}

void cx::ui::gtkmm3::NewGameView::SetLayout()
{
    using namespace cx::cmn::ui;

    constexpr ILayout::Column column0{0u};
    constexpr ILayout::Column column1{1u};
    constexpr ILayout::ColumnSpan singleColumnSpan{1u};
    constexpr ILayout::ColumnSpan fullColumnSpan{2u};

    constexpr ILayout::Row row0{0u};
    constexpr ILayout::Row row1{1u};
    constexpr ILayout::Row row2{2u};
    constexpr ILayout::Row row3{3u};
    constexpr ILayout::Row row4{4u};
    constexpr ILayout::Row row5{5u};
    constexpr ILayout::Row row6{6u};
    constexpr ILayout::Row row7{7u};
    constexpr ILayout::Row row8{8u};
    constexpr ILayout::Row row9{9u};
    constexpr ILayout::RowSpan singleRowSpan{1u};

    constexpr ILayout::Alignement hAlignLeft{
        ILayout::VerticalAlignement::FILL,
        ILayout::HorizontalAlignement::LEFT
    };

    m_viewLayout->SetColumnSpacingMode(ILayout::ColumnSpacingMode::EQUAL);

    m_viewLayout->Register(*m_title,               {row0,  singleRowSpan}, {column0, fullColumnSpan}              );
    m_viewLayout->Register(*m_gameSectionTitle,    {row1,  singleRowSpan}, {column0, fullColumnSpan},   hAlignLeft);
    m_viewLayout->Register(*m_inARowLabel,         {row2,  singleRowSpan}, {column0, singleColumnSpan}, hAlignLeft);
    m_viewLayout->Register(*m_inARowSpinBox,       {row2,  singleRowSpan}, {column1, singleColumnSpan}            );
    m_viewLayout->Register(*m_gridSectionTitle,    {row3,  singleRowSpan}, {column0, fullColumnSpan},   hAlignLeft);
    m_viewLayout->Register(*m_gridWidthLabel,      {row4,  singleRowSpan}, {column0, singleRowSpan},    hAlignLeft);
    m_viewLayout->Register(*m_boardWidthSpinBox,   {row4,  singleRowSpan}, {column1, singleColumnSpan}            );
    m_viewLayout->Register(*m_gridHeightLabel,     {row5,  singleRowSpan}, {column0, singleColumnSpan}, hAlignLeft);
    m_viewLayout->Register(*m_boardHeightSpinBox,  {row5,  singleRowSpan}, {column1, singleColumnSpan}            );
    m_viewLayout->Register(*m_playersSectionTitle, {row6,  singleRowSpan}, {column0, fullColumnSpan},   hAlignLeft);
    m_viewLayout->Register(*m_playersList,         {row7,  singleRowSpan}, {column0, fullColumnSpan}              );
    m_viewLayout->Register(*m_removePlayerButton,  {row8,  singleRowSpan}, {column0, singleColumnSpan}            );
    m_viewLayout->Register(*m_addPlayerButton,     {row8,  singleRowSpan}, {column1, singleColumnSpan}            );
    m_viewLayout->Register(*m_startButton,         {row9,  singleRowSpan}, {column0, fullColumnSpan}              );
}

void cx::ui::gtkmm3::NewGameView::PopulateWidgets()
{
    m_title->UpdateContents(m_presenter.GetNewGameViewTitle());

    m_gameSectionTitle->UpdateContents(m_presenter.GetNewGameViewGameSectionTitle());
    m_inARowLabel->UpdateContents(m_presenter.GetNewGameViewInARowLabelText());

    m_gridSectionTitle->UpdateContents(m_presenter.GetNewGameViewBoardSectionTitle());
    m_gridWidthLabel->UpdateContents(m_presenter.GetNewGameViewWidthLabelText());
    m_gridHeightLabel->UpdateContents(m_presenter.GetNewGameViewHeightLabelText());

    m_playersSectionTitle->UpdateContents(m_presenter.GetNewGameViewPlayersSectionTitle());
}

void cx::ui::gtkmm3::NewGameView::ConfigureWidgets()
{
    using namespace cx::cmn::ui;

    // Window margin:
    m_mainLayout.SetMargins({
        TopMargin{DIALOG_SIDE_MARGIN},
        BottomMargin{DIALOG_SIDE_MARGIN},
        LeftMargin{DIALOG_SIDE_MARGIN},
        RightMargin{DIALOG_SIDE_MARGIN}
    });

    // View title:
    m_title->UpdateContents("<big><b>" + m_title->GetContents() + "</b></big>");
    m_title->SetMargins({TopMargin{0u}, BottomMargin{TITLE_BOTTOM_MARGIN}, LeftMargin{0u}, RightMargin{0u}});

    // Game section
    m_gameSectionTitle->UpdateContents("<b>" + m_gameSectionTitle->GetContents() + "</b>");
    m_title->SetMargins({TopMargin{0u}, BottomMargin{SECTION_BOTTOM_MARGIN}, LeftMargin{0u}, RightMargin{0u}});

    // In-a-row:
    m_inARowLabel->UpdateContents(INDENT_MARK + m_inARowLabel->GetContents());

    // Grid section:
    m_gridSectionTitle->UpdateContents("<b>" + m_gridSectionTitle->GetContents() + "</b>");
    m_title->SetMargins({TopMargin{0u}, BottomMargin{SECTION_BOTTOM_MARGIN}, LeftMargin{0u}, RightMargin{0u}});

    // Width/height:
    m_gridWidthLabel->UpdateContents(INDENT_MARK + m_gridWidthLabel->GetContents());
    m_gridWidthLabel->SetMargins({TopMargin{0u}, BottomMargin{CONTROL_BOTTOM_MARGIN}, LeftMargin{0u}, RightMargin{0u}});
    m_boardWidthSpinBox->SetMargins({TopMargin{0u}, BottomMargin{CONTROL_BOTTOM_MARGIN}, LeftMargin{0u}, RightMargin{0u}});

    m_gridHeightLabel->UpdateContents(INDENT_MARK + m_gridHeightLabel->GetContents());
    m_gridHeightLabel->SetMargins({TopMargin{0u}, BottomMargin{CONTROL_BOTTOM_MARGIN}, LeftMargin{0u}, RightMargin{0u}});
    m_boardHeightSpinBox->SetMargins({TopMargin{0u}, BottomMargin{CONTROL_BOTTOM_MARGIN}, LeftMargin{0u}, RightMargin{0u}});

    // Players section:
    m_playersSectionTitle->UpdateContents("<b>" + m_playersSectionTitle->GetContents() + "</b>");
    m_title->SetMargins({TopMargin{0u}, BottomMargin{SECTION_BOTTOM_MARGIN}, LeftMargin{0u}, RightMargin{0u}});

    // Player list:
    m_playersList->SetMargins({TopMargin{0u}, BottomMargin{DIALOG_SIDE_MARGIN}, LeftMargin{0u}, RightMargin{0u}});

    // Add/Remove player buttons:
    m_removePlayerButton->SetMargins({TopMargin{0u}, BottomMargin{CONTROL_BOTTOM_MARGIN}, LeftMargin{0u}, RightMargin{0u}});
    m_addPlayerButton->SetMargins({cx::cmn::ui::TopMargin{0u}, cx::cmn::ui::BottomMargin{CONTROL_BOTTOM_MARGIN}, cx::cmn::ui::LeftMargin{0u}, cx::cmn::ui::RightMargin{0u}});
    EnabledStateUpdate(*m_removePlayerButton, m_presenter.CanRemoveAnotherPlayer(m_playersList->GetNbPlayers()));
    EnabledStateUpdate(*m_addPlayerButton, m_presenter.CanAddAnotherPlayer(m_playersList->GetNbPlayers()));

    // Start button:
    m_startButton->SetMargins({TopMargin{0u}, BottomMargin{CONTROL_BOTTOM_MARGIN}, LeftMargin{0u}, RightMargin{0u}});
}

void cx::ui::gtkmm3::NewGameView::OnStart()
{
    cx::model::NewGameInformation gameInformation;
    const auto extractionStatus = ExtractGameInformation(gameInformation);
    if(!extractionStatus.IsSuccess())
    {
        DisplayWarningDialog(
            m_widgetsFactories.GetStandardWidgetsFactory(),
            m_parentWindow,
            extractionStatus.GetMessage());
        return;
    }

    const auto inputValidationStatus = Validate(gameInformation, m_presenter);
    if(!inputValidationStatus.IsSuccess())
    {
        DisplayWarningDialog(
            m_widgetsFactories.GetStandardWidgetsFactory(),
            m_parentWindow,
            inputValidationStatus.GetMessage());
        return;
    }

    // At this point all user input has been validated. We start the game:
    m_controller.OnStart(std::move(gameInformation));
}

void cx::ui::gtkmm3::NewGameView::OnAddPlayer()
{
    if(m_presenter.CanAddAnotherPlayer(m_playersList->GetNbPlayers()))
    {
        const size_t nextColumnIndex = m_playersList->GetNbPlayers() + 1u;
        IF_CONDITION_NOT_MET_DO(m_playersList->AddPlayer(nextColumnIndex), return;);
    }

    EnabledStateUpdate(*m_removePlayerButton, m_presenter.CanRemoveAnotherPlayer(m_playersList->GetNbPlayers()));
    EnabledStateUpdate(*m_addPlayerButton, m_presenter.CanAddAnotherPlayer(m_playersList->GetNbPlayers()));
}

void cx::ui::gtkmm3::NewGameView::OnRemovePlayer()
{
    if(m_presenter.CanRemoveAnotherPlayer(m_playersList->GetNbPlayers()))
    {
        IF_CONDITION_NOT_MET_DO(m_playersList->RemovePlayer(m_playersList->GetNbPlayers() - 1), return;);

        // One row is gone. We need to resize the window as to leave no extra space.
        m_parentWindow.ShrinkToContents(cx::cmn::ui::IWindow::Orientation::VERTICAL);
    }

    EnabledStateUpdate(*m_removePlayerButton, m_presenter.CanRemoveAnotherPlayer(m_playersList->GetNbPlayers()));
    EnabledStateUpdate(*m_addPlayerButton, m_presenter.CanAddAnotherPlayer(m_playersList->GetNbPlayers()));
}

void cx::ui::gtkmm3::NewGameView::OnNewGameParameterUpdated()
{
    m_startButton->SetEnabled(cx::cmn::ui::EnabledState::Disabled);

    cx::model::NewGameInformation gameInformation;
    const auto extractionStatus = ExtractGameInformation(gameInformation);
    if(!extractionStatus.IsSuccess())
    {
        m_startButton->SetTooltip(extractionStatus.GetMessage());
        return;
    }

    const auto inputValidationStatus = Validate(gameInformation, m_presenter);
    if(!inputValidationStatus.IsSuccess())
    {
        m_startButton->SetTooltip(inputValidationStatus.GetMessage());
        return;
    }

    // At this points all user inputs have been validated and a new game can be started.
    // We make the start button sensitive:
    m_startButton->SetEnabled(cx::cmn::ui::EnabledState::Enabled);
    m_startButton->SetTooltip("");
}

cx::cmn::Status cx::ui::gtkmm3::NewGameView::ExtractGameInformation(cx::model::NewGameInformation& p_gameInformation) const
{
    // Extracting game parameters from the GUI:
    const int valueInARow = m_inARowSpinBox->GetValue();
    IF_CONDITION_NOT_MET_DO(valueInARow > 0, return cx::cmn::MakeError("Unexpected error occured."););
    const size_t inARowValue = static_cast<size_t>(valueInARow);

    const int valueBoardWidth = m_boardWidthSpinBox->GetValue();
    IF_CONDITION_NOT_MET_DO(valueBoardWidth > 0, return cx::cmn::MakeError("Unexpected error occured."););
    const size_t boardWidth = static_cast<size_t>(valueBoardWidth);

    const int valueBoardHeight = m_boardHeightSpinBox->GetValue();
    IF_CONDITION_NOT_MET_DO(valueBoardHeight > 0, return cx::cmn::MakeError("Unexpected error occured."););
    const size_t boardHeight = static_cast<size_t>(valueBoardHeight);

    const std::vector<std::string> playerNames = m_playersList->GetAllPlayerNames();
    const std::vector<cx::model::ChipColor> playerChipColors = m_playersList->GetAllColors();
    const std::vector<cx::model::PlayerType> playerTypes = m_playersList->GetAllPlayerTypes();
    ASSERT(playerNames.size() == playerChipColors.size());
    ASSERT(playerTypes.size() == playerTypes.size());

    // Feeding the game information structure:
    p_gameInformation.m_inARowValue = inARowValue;
    p_gameInformation.m_gridHeight = boardHeight;
    p_gameInformation.m_gridWidth = boardWidth;
    for(size_t index = 0u; index < m_playersList->GetNbPlayers(); ++index)
    {
        p_gameInformation.m_players.push_back(cx::model::CreatePlayer(playerNames[index], playerChipColors[index], playerTypes[index]));
    }

    return cx::cmn::MakeSuccess();
}
