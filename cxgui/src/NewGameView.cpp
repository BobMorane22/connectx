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

#include <gtkmm/messagedialog.h>

#include <cxstd/helpers.h>
#include <cxinv/assertion.h>
#include <cxmodel/IChip.h>
#include <cxmodel/NewGameInformation.h>
#include <cxgui/ColorComboBox.h>
#include <cxgui/extractRawUserInput.h>
#include <cxgui/Gtkmm3Layout.h>
#include <cxgui/Gtkmm3NewPlayersList.h>
#include <cxgui/Gtkmm3SpinBox.h>
#include <cxgui/Gtkmm3WidgetDelegate.h>
#include <cxgui/INewGameViewController.h>
#include <cxgui/INewGameViewPresenter.h>
#include <cxgui/ISpinBox.h>
#include <cxgui/Margins.h>
#include <cxgui/NewGameView.h>

namespace
{

void DisplayWarningDialog(Gtk::Window& parent, const std::string& p_message)
{
    PRECONDITION(!p_message.empty());

    constexpr bool NO_MARKUP = false;

    Gtk::MessageDialog errorDlg{parent, p_message, NO_MARKUP, Gtk::MessageType::MESSAGE_WARNING, Gtk::ButtonsType::BUTTONS_OK, true};

    errorDlg.run();
}

} // namespace

cxgui::NewGameView::NewGameView(INewGameViewPresenter& p_presenter,
                                INewGameViewController& p_controller,
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
{
    {
        auto viewLayout = std::make_unique<Gtkmm3Layout>();
        ASSERT(viewLayout);

        auto* underlying = dynamic_cast<Gtk::Widget*>(viewLayout.get());
        ASSERT(underlying);

        auto widgetDelegate = std::make_unique<cxgui::Gtkmm3WidgetDelegate>();
        ASSERT(widgetDelegate);

        widgetDelegate->SetUnderlying(underlying);
        viewLayout->SetDelegate(std::move(widgetDelegate));

        m_viewLayout = std::move(viewLayout);
        ASSERT(m_viewLayout);
    }

    m_playersList = std::make_unique<cxgui::Gtkmm3NewPlayersList>(p_presenter);
    ASSERT(m_playersList);

    {
        const size_t inARowMinValue = p_presenter.GetNewGameViewMinInARowValue();
        const size_t inARowMaxValue = p_presenter.GetNewGameViewMaxInARowValue();
        auto inARowSpinBox = std::make_unique<Gtkmm3SpinBox>(m_presenter.GetDefaultInARowValue(),
                                                             ISpinBox::ClimbRate{1u},
                                                             ISpinBox::Range{ISpinBox::Minimum{static_cast<int>(inARowMinValue)},
                                                                             ISpinBox::Maximum{static_cast<int>(inARowMaxValue)}});
        ASSERT(inARowSpinBox);

        auto inARowSpinBoxDelegate = std::make_unique<cxgui::Gtkmm3WidgetDelegate>();
        ASSERT(inARowSpinBoxDelegate);

        auto* underlying = dynamic_cast<Gtk::Widget*>(inARowSpinBox.get());
        ASSERT(underlying);

        inARowSpinBoxDelegate->SetUnderlying(underlying);
        inARowSpinBox->SetDelegate(std::move(inARowSpinBoxDelegate));

        m_inARowSpinBox = std::move(inARowSpinBox);
        ASSERT(m_inARowSpinBox);
    }

    {
        const int boardWidthMinValue = p_presenter.GetNewGameViewMinBoardWidthValue();
        const int boardWidthMaxValue = p_presenter.GetNewGameViewMaxBoardWidthValue();
        auto boardWidthSpinBox = std::make_unique<Gtkmm3SpinBox>(m_presenter.GetDefaultBoardWidthValue(),
                                                                 ISpinBox::ClimbRate{1u},
                                                                 ISpinBox::Range{ISpinBox::Minimum{static_cast<int>(boardWidthMinValue)},
                                                                                 ISpinBox::Maximum{static_cast<int>(boardWidthMaxValue)}});
        ASSERT(boardWidthSpinBox);

        auto boardWidthSpinBoxDelegate = std::make_unique<cxgui::Gtkmm3WidgetDelegate>();
        ASSERT(boardWidthSpinBoxDelegate);

        auto* underlying = dynamic_cast<Gtk::Widget*>(boardWidthSpinBox.get());
        ASSERT(underlying);

        boardWidthSpinBoxDelegate->SetUnderlying(underlying);
        boardWidthSpinBox->SetDelegate(std::move(boardWidthSpinBoxDelegate));

        m_boardWidthSpinBox = std::move(boardWidthSpinBox);
        ASSERT(m_boardWidthSpinBox);
    }

    {
        const int boardHeightMinValue = p_presenter.GetNewGameViewMinBoardHeightValue();
        const int boardHeightMaxValue = p_presenter.GetNewGameViewMaxBoardHeightValue();
        auto boardHeightSpinBox = std::make_unique<Gtkmm3SpinBox>(m_presenter.GetDefaultBoardHeightValue(),
                                                                  ISpinBox::ClimbRate{1u},
                                                                  ISpinBox::Range{ISpinBox::Minimum{static_cast<int>(boardHeightMinValue)},
                                                                                  ISpinBox::Maximum{static_cast<int>(boardHeightMaxValue)}});
        ASSERT(boardHeightSpinBox);

        auto boardHeightSpinBoxDelegate = std::make_unique<cxgui::Gtkmm3WidgetDelegate>();
        ASSERT(boardHeightSpinBoxDelegate);

        auto* underlying = dynamic_cast<Gtk::Widget*>(boardHeightSpinBox.get());
        ASSERT(underlying);

        boardHeightSpinBoxDelegate->SetUnderlying(underlying);
        boardHeightSpinBox->SetDelegate(std::move(boardHeightSpinBoxDelegate));

        m_boardHeightSpinBox = std::move(boardHeightSpinBox);
        ASSERT(m_boardHeightSpinBox);
    }

    SetLayout();
    PopulateWidgets();
    ConfigureWidgets();

    m_removePlayerButton.signal_clicked().connect([this](){OnRemovePlayer();});
    m_addPlayerButton.signal_clicked().connect([this](){OnAddPlayer();});
    m_startButton.signal_clicked().connect([this](){OnStart();});

    // Start button validations:
    m_removePlayerButton.signal_clicked().connect([this](){OnNewGameParameterUpdated();});
    m_addPlayerButton.signal_clicked().connect([this](){OnNewGameParameterUpdated();});
    m_playersList->RowUpdatedSignalConnect([this](){OnNewGameParameterUpdated();});
}

void cxgui::NewGameView::Activate()
{
   m_mainLayout.Register(*m_viewLayout,
                         {m_viewTop, ILayout::RowSpan{1u}},
                         {m_viewLeft, ILayout::ColumnSpan{2u}});
}

void cxgui::NewGameView::DeActivate()
{
    // Nothing to do...
}

void cxgui::NewGameView::Update(cxmodel::ModelNotificationContext /*p_context*/)
{
    // Noting to do...
}

void cxgui::NewGameView::SetLayout()
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

    m_viewLayout->SetColumnSpacingMode(cxgui::ILayout::ColumnSpacingMode::EQUAL);

    m_viewLayout->Register(m_title,               {row0,  singleRowSpan}, {column0, fullColumnSpan});
    m_viewLayout->Register(m_gameSectionTitle,    {row1,  singleRowSpan}, {column0, fullColumnSpan});
    m_viewLayout->Register(m_inARowLabel,         {row2,  singleRowSpan}, {column0, singleColumnSpan});
    m_viewLayout->Register(*m_inARowSpinBox,      {row2,  singleRowSpan}, {column1, singleColumnSpan});
    m_viewLayout->Register(m_gridSectionTitle,    {row3,  singleRowSpan}, {column0, fullColumnSpan});
    m_viewLayout->Register(m_gridWidthLabel,      {row4,  singleRowSpan}, {column0, singleRowSpan});
    m_viewLayout->Register(*m_boardWidthSpinBox,  {row4,  singleRowSpan}, {column1, singleColumnSpan});
    m_viewLayout->Register(m_gridHeightLabel,     {row5,  singleRowSpan}, {column0, singleColumnSpan});
    m_viewLayout->Register(*m_boardHeightSpinBox, {row5,  singleRowSpan}, {column1, singleColumnSpan});
    m_viewLayout->Register(m_playersSectionTitle, {row6,  singleRowSpan}, {column0, fullColumnSpan});
    m_viewLayout->Register(*m_playersList,        {row7,  singleRowSpan}, {column0, fullColumnSpan});
    m_viewLayout->Register(m_removePlayerButton,  {row8,  singleRowSpan}, {column0, singleColumnSpan});
    m_viewLayout->Register(m_addPlayerButton,     {row8,  singleRowSpan}, {column1, singleColumnSpan});
    m_viewLayout->Register(m_startButton,         {row9,  singleRowSpan}, {column0, fullColumnSpan});
}

void cxgui::NewGameView::PopulateWidgets()
{
    m_title.set_text(m_presenter.GetNewGameViewTitle());

    m_gameSectionTitle.set_text(m_presenter.GetNewGameViewGameSectionTitle());
    m_inARowLabel.set_text(m_presenter.GetNewGameViewInARowLabelText());

    m_gridSectionTitle.set_text(m_presenter.GetNewGameViewBoardSectionTitle());
    m_gridWidthLabel.set_text(m_presenter.GetNewGameViewWidthLabelText());
    m_gridHeightLabel.set_text(m_presenter.GetNewGameViewHeightLabelText());

    m_playersSectionTitle.set_text(m_presenter.GetNewGameViewPlayersSectionTitle());

    m_removePlayerButton.set_label(m_presenter.GetNewGameViewRemovePlayerButtonText());
    m_addPlayerButton.set_label(m_presenter.GetNewGameViewAddPlayerButtonText());

    m_startButton.set_label(m_presenter.GetNewGameViewStartButtonText());
}

void cxgui::NewGameView::ConfigureWidgets()
{
    // Window margin:
    m_mainLayout.SetMargins({
        cxgui::TopMargin{DIALOG_SIDE_MARGIN},
        cxgui::BottomMargin{DIALOG_SIDE_MARGIN},
        cxgui::LeftMargin{DIALOG_SIDE_MARGIN},
        cxgui::RightMargin{DIALOG_SIDE_MARGIN}
    });

    // View title:
    m_title.set_use_markup(true);
    m_title.set_markup("<big><b>" + m_title.get_text() + "</b></big>");
    m_title.set_margin_bottom(TITLE_BOTTOM_MARGIN);

    // Game section
    m_gameSectionTitle.set_use_markup(true);
    m_gameSectionTitle.set_markup("<b>" + m_gameSectionTitle.get_text() + "</b>");
    m_gameSectionTitle.set_halign(Gtk::Align::ALIGN_START);
    m_title.set_margin_bottom(SECTION_BOTTOM_MARGIN);

    // In-a-row:
    m_inARowLabel.set_halign(Gtk::Align::ALIGN_START);
    m_inARowLabel.set_text(INDENT_MARK + m_inARowLabel.get_text());

    // Grid section:
    m_gridSectionTitle.set_use_markup(true);
    m_gridSectionTitle.set_markup("<b>" + m_gridSectionTitle.get_text() + "</b>");
    m_gridSectionTitle.set_halign(Gtk::Align::ALIGN_START);
    m_title.set_margin_bottom(SECTION_BOTTOM_MARGIN);

    // Width/height:
    m_gridWidthLabel.set_halign(Gtk::Align::ALIGN_START);
    m_gridWidthLabel.set_text(INDENT_MARK + m_gridWidthLabel.get_text());
    m_gridWidthLabel.set_margin_bottom(CONTROL_BOTTOM_MARGIN);
    m_boardWidthSpinBox->SetMargins({
        cxgui::TopMargin{0u},
        cxgui::BottomMargin{CONTROL_BOTTOM_MARGIN},
        cxgui::LeftMargin{0u},
        cxgui::RightMargin{0u}
    });

    m_gridHeightLabel.set_halign(Gtk::Align::ALIGN_START);
    m_gridHeightLabel.set_text(INDENT_MARK + m_gridHeightLabel.get_text());
    m_gridHeightLabel.set_margin_bottom(CONTROL_BOTTOM_MARGIN);
    m_boardHeightSpinBox->SetMargins({
        cxgui::TopMargin{0u},
        cxgui::BottomMargin{CONTROL_BOTTOM_MARGIN},
        cxgui::LeftMargin{0u},
        cxgui::RightMargin{0u}
    });

    // Players section:
    m_playersSectionTitle.set_use_markup(true);
    m_playersSectionTitle.set_markup("<b>" + m_playersSectionTitle.get_text() + "</b>");
    m_playersSectionTitle.set_halign(Gtk::Align::ALIGN_START);
    m_title.set_margin_bottom(SECTION_BOTTOM_MARGIN);

    // Player list:
    m_playersList->SetMargins({
        cxgui::TopMargin{0u},
        cxgui::BottomMargin{DIALOG_SIDE_MARGIN},
        cxgui::LeftMargin{0u},
        cxgui::RightMargin{0u}
    });

    // Add/Remove player buttons:
    m_removePlayerButton.set_margin_bottom(CONTROL_BOTTOM_MARGIN);
    m_addPlayerButton.set_margin_bottom(CONTROL_BOTTOM_MARGIN);
    m_removePlayerButton.set_sensitive(m_presenter.CanRemoveAnotherPlayer(m_playersList->GetSize()));
    m_addPlayerButton.set_sensitive(m_presenter.CanAddAnotherPlayer(m_playersList->GetSize()));

    // Start button:
    m_startButton.set_margin_bottom(CONTROL_BOTTOM_MARGIN);
}

void cxgui::NewGameView::OnStart()
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

void cxgui::NewGameView::OnAddPlayer()
{
    if(m_presenter.CanAddAnotherPlayer(m_playersList->GetSize()))
    {
        const size_t nextColumnIndex = m_playersList->GetSize() + 1u;
        IF_CONDITION_NOT_MET_DO(m_playersList->AddRow(m_presenter, nextColumnIndex), return;);
    }

    m_removePlayerButton.set_sensitive(m_presenter.CanRemoveAnotherPlayer(m_playersList->GetSize()));
    m_addPlayerButton.set_sensitive(m_presenter.CanAddAnotherPlayer(m_playersList->GetSize()));
}

void cxgui::NewGameView::OnRemovePlayer()
{
    if(m_presenter.CanRemoveAnotherPlayer(m_playersList->GetSize()))
    {
        IF_CONDITION_NOT_MET_DO(m_playersList->RemoveRow(m_playersList->GetSize() - 1), return;);

        // At this point, the row is removed. If we don't act though, the extra
        // space left by the removed row will still be displayed on the screen,
        // leaving the window with ugly extra space. We want the window to resize
        // to the new list. We get the preferred heights values:
        int minimumHeight, naturalHeight;
        m_parentWindow.get_preferred_height(minimumHeight, naturalHeight);

        // Then, we make a size request using the minimum height. Notice the '100'
        // that is removed. This was added to make sure Gtkmm did not leave any
        // extra blank space by resizing smaller than the minimum value:
        m_parentWindow.set_size_request(m_parentWindow.get_width(), minimumHeight - 100);

        // Then resize accordingly:
        m_parentWindow.resize(m_parentWindow.get_width(), naturalHeight);
    }

    m_removePlayerButton.set_sensitive(m_presenter.CanRemoveAnotherPlayer(m_playersList->GetSize()));
    m_addPlayerButton.set_sensitive(m_presenter.CanAddAnotherPlayer(m_playersList->GetSize()));
}

void cxgui::NewGameView::OnNewGameParameterUpdated()
{
    m_startButton.set_sensitive(false);

    cxmodel::NewGameInformation gameInformation;
    const auto extractionStatus = ExtractGameInformation(gameInformation);
    if(!extractionStatus.IsSuccess())
    {
        m_startButton.set_tooltip_text(extractionStatus.GetMessage());
        return;
    }

    const auto inputValidationStatus = Validate(gameInformation, m_presenter);
    if(!inputValidationStatus.IsSuccess())
    {
        m_startButton.set_tooltip_text(inputValidationStatus.GetMessage());
        return;
    }

    // At this points all user inputs have been validated and a new game can be started.
    // We make the start button sensitive:
    m_startButton.set_sensitive(true);
    m_startButton.set_tooltip_text("");
}

cxmodel::Status cxgui::NewGameView::ExtractGameInformation(cxmodel::NewGameInformation& p_gameInformation) const
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
