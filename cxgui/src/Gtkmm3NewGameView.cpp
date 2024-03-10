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
 * @file Gtkmm3NewGameView.cpp
 * @date 2020
 *
 *************************************************************************************************/

#include <algorithm>
#include <memory>
#include <sstream>

#include <cxstd/helpers.h>
#include <cxinv/assertion.h>
#include <cxmodel/IChip.h>
#include <cxmodel/NewGameInformation.h>
#include <cxgui/common.h>
#include <cxgui/DialogRole.h>
#include <cxgui/EnabledState.h>
#include <cxgui/extractRawUserInput.h>
#include <cxgui/Gtkmm3Button.h>
#include <cxgui/Gtkmm3Dialog.h>
#include <cxgui/Gtkmm3Label.h>
#include <cxgui/Gtkmm3Layout.h>
#include <cxgui/Gtkmm3NewGameView.h>
#include <cxgui/Gtkmm3NewPlayersList.h>
#include <cxgui/Gtkmm3SpinBox.h>
#include <cxgui/Gtkmm3WidgetDelegate.h>
#include <cxgui/INewGameViewController.h>
#include <cxgui/INewGameViewPresenter.h>
#include <cxgui/ISpinBox.h>
#include <cxgui/Margins.h>
#include <cxgui/widgetUtilities.h>

namespace
{

void DisplayWarningDialog(cxgui::IWindow& p_parent, const std::string& p_message)
{
    using namespace cxgui;

    IF_PRECONDITION_NOT_MET_DO(!p_message.empty(), return;);

    std::unique_ptr<IWindow> errorDialog = CreateWidget<Gtkmm3Dialog>(p_parent, DialogRole::WARNING, p_message);
    ASSERT(errorDialog);

    // Blocks the main loop:
    const int result = errorDialog->Show();
    IF_PRECONDITION_NOT_MET_DO(result == EXIT_SUCCESS, return;);
}

} // namespace

cxgui::Gtkmm3NewGameView::Gtkmm3NewGameView(INewGameViewPresenter& p_presenter,
                                            INewGameViewController& p_controller,
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
    m_viewLayout = CreateWidget<Gtkmm3Layout>();
    ASSERT(m_viewLayout);

    m_playersList = CreateWidget<Gtkmm3NewPlayersList>(p_presenter);
    ASSERT(m_playersList);

    const size_t inARowMinValue = p_presenter.GetNewGameViewMinInARowValue();
    const size_t inARowMaxValue = p_presenter.GetNewGameViewMaxInARowValue();
    m_inARowSpinBox = CreateWidget<Gtkmm3SpinBox>(m_presenter.GetDefaultInARowValue(),
                                                  ISpinBox::ClimbRate{1u},
                                                  ISpinBox::Range{ISpinBox::Minimum{static_cast<int>(inARowMinValue)},
                                                                  ISpinBox::Maximum{static_cast<int>(inARowMaxValue)}});
    ASSERT(m_inARowSpinBox);

    const int boardWidthMinValue = p_presenter.GetNewGameViewMinBoardWidthValue();
    const int boardWidthMaxValue = p_presenter.GetNewGameViewMaxBoardWidthValue();
    m_boardWidthSpinBox = CreateWidget<Gtkmm3SpinBox>(m_presenter.GetDefaultBoardWidthValue(),
                                                      ISpinBox::ClimbRate{1u},
                                                      ISpinBox::Range{ISpinBox::Minimum{static_cast<int>(boardWidthMinValue)},
                                                                      ISpinBox::Maximum{static_cast<int>(boardWidthMaxValue)}});
    ASSERT(m_boardWidthSpinBox);

    const int boardHeightMinValue = p_presenter.GetNewGameViewMinBoardHeightValue();
    const int boardHeightMaxValue = p_presenter.GetNewGameViewMaxBoardHeightValue();
    m_boardHeightSpinBox = CreateWidget<Gtkmm3SpinBox>(m_presenter.GetDefaultBoardHeightValue(),
                                                       ISpinBox::ClimbRate{1u},
                                                       ISpinBox::Range{ISpinBox::Minimum{static_cast<int>(boardHeightMinValue)},
                                                                       ISpinBox::Maximum{static_cast<int>(boardHeightMaxValue)}});
    ASSERT(m_boardHeightSpinBox);

    m_addPlayerButton = CreateWidget<Gtkmm3Button>(m_presenter.GetNewGameViewAddPlayerButtonText());
    ASSERT(m_addPlayerButton);
    m_removePlayerButton = CreateWidget<Gtkmm3Button>(m_presenter.GetNewGameViewRemovePlayerButtonText());
    ASSERT(m_removePlayerButton);
    m_startButton = CreateWidget<Gtkmm3Button>(m_presenter.GetNewGameViewStartButtonText());
    ASSERT(m_startButton);

    m_title = CreateWidget<Gtkmm3Label>("");
    ASSERT(m_title);
    m_gameSectionTitle = CreateWidget<Gtkmm3Label>("");
    ASSERT(m_gameSectionTitle);
    m_inARowLabel = CreateWidget<Gtkmm3Label>("");
    ASSERT(m_inARowLabel);
    m_gridSectionTitle = CreateWidget<Gtkmm3Label>("");
    ASSERT(m_gridSectionTitle);
    m_gridWidthLabel = CreateWidget<Gtkmm3Label>("");
    ASSERT(m_gridWidthLabel);
    m_gridHeightLabel = CreateWidget<Gtkmm3Label>("");
    ASSERT(m_gridHeightLabel);
    m_playersSectionTitle = CreateWidget<Gtkmm3Label>("");
    ASSERT(m_playersSectionTitle);

    SetLayout();
    PopulateWidgets();
    ConfigureWidgets();

    m_removePlayerButton->OnClicked()->Connect([this](){OnRemovePlayer();});
    m_addPlayerButton->OnClicked()->Connect([this](){OnAddPlayer();});
    m_startButton->OnClicked()->Connect([this](){OnStart();});

    // Start button validations:
    m_removePlayerButton->OnClicked()->Connect([this](){OnNewGameParameterUpdated();});
    m_addPlayerButton->OnClicked()->Connect([this](){OnNewGameParameterUpdated();});
    m_playersList->RowUpdatedSignalConnect([this](){OnNewGameParameterUpdated();});
}

void cxgui::Gtkmm3NewGameView::Activate()
{
   m_mainLayout.Register(*m_viewLayout,
                         {m_viewTop, ILayout::RowSpan{1u}},
                         {m_viewLeft, ILayout::ColumnSpan{2u}});
}

void cxgui::Gtkmm3NewGameView::DeActivate()
{
    // Nothing to do...
}

void cxgui::Gtkmm3NewGameView::Update(cxmodel::ModelNotificationContext /*p_context*/)
{
    // Noting to do...
}

size_t cxgui::Gtkmm3NewGameView::GetWidth() const 
{
    return m_viewLayout->GetWidth();
}

size_t cxgui::Gtkmm3NewGameView::GetHeight() const 
{
    return m_viewLayout->GetHeight();
}

void cxgui::Gtkmm3NewGameView::SetEnabled(EnabledState p_enabled) 
{
    return m_viewLayout->SetEnabled(p_enabled);
}

void cxgui::Gtkmm3NewGameView::SetMargins(const Margins& p_newMarginSizes) 
{
    return m_viewLayout->SetMargins(p_newMarginSizes);
}

void cxgui::Gtkmm3NewGameView::SetTooltip(const std::string& p_tooltipContents)
{
    return m_viewLayout->SetTooltip(p_tooltipContents);
}

void cxgui::Gtkmm3NewGameView::SetLayout()
{
    constexpr cxmodel::Column column0{0u};
    constexpr cxmodel::Column column1{1u};
    constexpr cxgui::ILayout::ColumnSpan singleColumnSpan{1u};
    constexpr cxgui::ILayout::ColumnSpan fullColumnSpan{2u};

    constexpr cxmodel::Row row0{0u};
    constexpr cxmodel::Row row1{1u};
    constexpr cxmodel::Row row2{2u};
    constexpr cxmodel::Row row3{3u};
    constexpr cxmodel::Row row4{4u};
    constexpr cxmodel::Row row5{5u};
    constexpr cxmodel::Row row6{6u};
    constexpr cxmodel::Row row7{7u};
    constexpr cxmodel::Row row8{8u};
    constexpr cxmodel::Row row9{9u};
    constexpr cxgui::ILayout::RowSpan singleRowSpan{1u};

    constexpr ILayout::Alignement hAlignLeft{
        ILayout::VerticalAlignement::FILL,
        ILayout::HorizontalAlignement::LEFT
    };

    m_viewLayout->SetColumnSpacingMode(cxgui::ILayout::ColumnSpacingMode::EQUAL);

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

void cxgui::Gtkmm3NewGameView::PopulateWidgets()
{
    m_title->UpdateContents(m_presenter.GetNewGameViewTitle());

    m_gameSectionTitle->UpdateContents(m_presenter.GetNewGameViewGameSectionTitle());
    m_inARowLabel->UpdateContents(m_presenter.GetNewGameViewInARowLabelText());

    m_gridSectionTitle->UpdateContents(m_presenter.GetNewGameViewBoardSectionTitle());
    m_gridWidthLabel->UpdateContents(m_presenter.GetNewGameViewWidthLabelText());
    m_gridHeightLabel->UpdateContents(m_presenter.GetNewGameViewHeightLabelText());

    m_playersSectionTitle->UpdateContents(m_presenter.GetNewGameViewPlayersSectionTitle());
}

void cxgui::Gtkmm3NewGameView::ConfigureWidgets()
{
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
    m_addPlayerButton->SetMargins({cxgui::TopMargin{0u}, cxgui::BottomMargin{CONTROL_BOTTOM_MARGIN}, cxgui::LeftMargin{0u}, cxgui::RightMargin{0u}});
    EnabledStateUpdate(*m_removePlayerButton, m_presenter.CanRemoveAnotherPlayer(m_playersList->GetSize()));
    EnabledStateUpdate(*m_addPlayerButton, m_presenter.CanAddAnotherPlayer(m_playersList->GetSize()));

    // Start button:
    m_startButton->SetMargins({TopMargin{0u}, BottomMargin{CONTROL_BOTTOM_MARGIN}, LeftMargin{0u}, RightMargin{0u}});
}

void cxgui::Gtkmm3NewGameView::OnStart()
{
    cxmodel::NewGameInformation gameInformation;
    const auto extractionStatus = ExtractGameInformation(gameInformation);
    if(!extractionStatus.IsSuccess())
    {
        DisplayWarningDialog(m_parentWindow, extractionStatus.GetMessage());
        return;
    }

    const auto inputValidationStatus = Validate(gameInformation, m_presenter);
    if(!inputValidationStatus.IsSuccess())
    {
        DisplayWarningDialog(m_parentWindow, inputValidationStatus.GetMessage());
        return;
    }

    // At this point all user input has been validated. We start the game:
    m_controller.OnStart(std::move(gameInformation));
}

void cxgui::Gtkmm3NewGameView::OnAddPlayer()
{
    if(m_presenter.CanAddAnotherPlayer(m_playersList->GetSize()))
    {
        const size_t nextColumnIndex = m_playersList->GetSize() + 1u;
        IF_CONDITION_NOT_MET_DO(m_playersList->AddRow(m_presenter, nextColumnIndex), return;);
    }

    EnabledStateUpdate(*m_removePlayerButton, m_presenter.CanRemoveAnotherPlayer(m_playersList->GetSize()));
    EnabledStateUpdate(*m_addPlayerButton, m_presenter.CanAddAnotherPlayer(m_playersList->GetSize()));
}

void cxgui::Gtkmm3NewGameView::OnRemovePlayer()
{
    if(m_presenter.CanRemoveAnotherPlayer(m_playersList->GetSize()))
    {
        IF_CONDITION_NOT_MET_DO(m_playersList->RemoveRow(m_playersList->GetSize() - 1), return;);

        // One row is gone. We need to resize the window as to leave no extra space.
        m_parentWindow.ShrinkToContents(cxgui::IWindow::Orientation::HORIZONTAL);
    }

    EnabledStateUpdate(*m_removePlayerButton, m_presenter.CanRemoveAnotherPlayer(m_playersList->GetSize()));
    EnabledStateUpdate(*m_addPlayerButton, m_presenter.CanAddAnotherPlayer(m_playersList->GetSize()));
}

void cxgui::Gtkmm3NewGameView::OnNewGameParameterUpdated()
{
    m_startButton->SetEnabled(cxgui::EnabledState::Disabled);

    cxmodel::NewGameInformation gameInformation;
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
    m_startButton->SetEnabled(cxgui::EnabledState::Enabled);
    m_startButton->SetTooltip("");
}

cxmodel::Status cxgui::Gtkmm3NewGameView::ExtractGameInformation(cxmodel::NewGameInformation& p_gameInformation) const
{
    // Extracting game parameters from the GUI:
    const int valueInARow = m_inARowSpinBox->GetValue();
    IF_CONDITION_NOT_MET_DO(valueInARow > 0, return cxmodel::MakeError("Unexpected error occured."););
    const size_t inARowValue = static_cast<size_t>(valueInARow);

    const int valueBoardWidth = m_boardWidthSpinBox->GetValue();
    IF_CONDITION_NOT_MET_DO(valueBoardWidth > 0, return cxmodel::MakeError("Unexpected error occured."););
    const size_t boardWidth = static_cast<size_t>(valueBoardWidth);

    const int valueBoardHeight = m_boardHeightSpinBox->GetValue();
    IF_CONDITION_NOT_MET_DO(valueBoardHeight > 0, return cxmodel::MakeError("Unexpected error occured."););
    const size_t boardHeight = static_cast<size_t>(valueBoardHeight);

    const std::vector<std::string> playerNames = m_playersList->GetAllPlayerNames();
    const std::vector<cxmodel::ChipColor> playerChipColors = m_playersList->GetAllColors();
    const std::vector<cxmodel::PlayerType> playerTypes = m_playersList->GetAllPlayerTypes();
    ASSERT(playerNames.size() == playerChipColors.size());
    ASSERT(playerTypes.size() == playerTypes.size());

    // Feeding the game information structure:
    p_gameInformation.m_inARowValue = inARowValue;
    p_gameInformation.m_gridHeight = boardHeight;
    p_gameInformation.m_gridWidth = boardWidth;
    for(size_t index = 0u; index < m_playersList->GetSize(); ++index)
    {
        p_gameInformation.m_players.push_back(cxmodel::CreatePlayer(playerNames[index], playerChipColors[index], playerTypes[index]));
    }

    return cxmodel::MakeSuccess();
}
