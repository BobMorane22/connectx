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
#include <sstream>

#include <gtkmm/messagedialog.h>

#include <cxinv/assertion.h>
#include <cxmodel/IChip.h>
#include <cxmodel/NewGameInformation.h>
#include <cxgui/extractRawUserInput.h>
#include <cxgui/NewGameView.h>
#include <cxgui/NewPlayersList.h>

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
                                Gtk::Grid& p_mainLayout,
                                int p_viewLeft,
                                int p_viewTop)
 : m_presenter{p_presenter}
 , m_controller{p_controller}
 , m_mainLayout{p_mainLayout}
 , m_viewLeft{p_viewLeft}
 , m_viewTop{p_viewTop}
{
    m_playersList = std::make_unique<cxgui::NewPlayersList>(p_presenter);

    SetLayout();
    PopulateWidgets();
    ConfigureWidgets();

    m_removePlayerButton.signal_clicked().connect([this](){OnRemovePlayer();});
    m_addPlayerButton.signal_clicked().connect([this](){OnAddPlayer();});
    m_startButton.signal_clicked().connect([this](){OnStart();});

    // Start button validations:
    m_inARowEntry.signal_changed().connect([this](){OnNewGameParameterUpdated();});
    m_gridWidthEntry.signal_changed().connect([this](){OnNewGameParameterUpdated();});
    m_gridHeightEntry.signal_changed().connect([this](){OnNewGameParameterUpdated();});
    m_removePlayerButton.signal_clicked().connect([this](){OnNewGameParameterUpdated();});
    m_addPlayerButton.signal_clicked().connect([this](){OnNewGameParameterUpdated();});
    m_playersList->RowUpdatedSignalConnect([this](){OnNewGameParameterUpdated();});
}

void cxgui::NewGameView::Activate()
{
    auto* currentViewLayout = m_mainLayout.get_child_at(m_viewLeft, m_viewTop);

    if(!currentViewLayout)
    {
        // This is probably the init phase, so there is nothing to remove. In this
        // case, we simply add it:
        m_mainLayout.attach(m_viewLayout, m_viewLeft, m_viewTop, 2, 1);

        return;
    }

    // Remove previous view layout:
    m_mainLayout.remove(*currentViewLayout);

    // Add new view layout:
    m_mainLayout.attach(m_viewLayout, m_viewLeft, m_viewTop, 2, 1);
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
    constexpr int TOTAL_WIDTH = 2;

    m_viewLayout.set_column_homogeneous(true);

    m_viewLayout.attach(m_title, 0, 0, TOTAL_WIDTH, 1);

    m_viewLayout.attach(m_gameSectionTitle, 0, 1, TOTAL_WIDTH, 1);
    m_viewLayout.attach(m_inARowLabel, 0, 2, 1, 1);
    m_viewLayout.attach(m_inARowEntry, 1, 2, 1, 1);

    m_viewLayout.attach(m_gridSectionTitle, 0, 3, TOTAL_WIDTH, 1);
    m_viewLayout.attach(m_gridWidthLabel, 0, 4, 1, 1);
    m_viewLayout.attach(m_gridWidthEntry, 1, 4,  1, 1);
    m_viewLayout.attach(m_gridHeightLabel, 0, 5, 1, 1);
    m_viewLayout.attach(m_gridHeightEntry, 1, 5, 1, 1);

    m_viewLayout.attach(m_playersSectionTitle, 0, 6, TOTAL_WIDTH, 1);
    m_viewLayout.attach(m_playersList->GetUnderlying(), 0, 7, TOTAL_WIDTH, 1);

    m_viewLayout.attach(m_removePlayerButton, 0, 9, 1, 1);
    m_viewLayout.attach(m_addPlayerButton, 1, 9, 1, 1);

    m_viewLayout.attach(m_startButton, 0, 10, TOTAL_WIDTH, 1);
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
    m_mainLayout.set_margin_start(DIALOG_SIDE_MARGIN);
    m_mainLayout.set_margin_end(DIALOG_SIDE_MARGIN);
    m_mainLayout.set_margin_top(DIALOG_SIDE_MARGIN);
    m_mainLayout.set_margin_bottom(DIALOG_SIDE_MARGIN);

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
    m_gridWidthEntry.set_margin_bottom(CONTROL_BOTTOM_MARGIN);

    m_gridHeightLabel.set_halign(Gtk::Align::ALIGN_START);
    m_gridHeightLabel.set_text(INDENT_MARK + m_gridHeightLabel.get_text());
    m_gridHeightLabel.set_margin_bottom(CONTROL_BOTTOM_MARGIN);
    m_gridHeightEntry.set_margin_bottom(CONTROL_BOTTOM_MARGIN);

    // Players section:
    m_playersSectionTitle.set_use_markup(true);
    m_playersSectionTitle.set_markup("<b>" + m_playersSectionTitle.get_text() + "</b>");
    m_playersSectionTitle.set_halign(Gtk::Align::ALIGN_START);
    m_title.set_margin_bottom(SECTION_BOTTOM_MARGIN);

    // Player list:
    m_playersList->GetUnderlying().set_margin_bottom(CONTROL_BOTTOM_MARGIN);

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
    // First, we get an handle to the main window in case a warning dialog needs to be
    // displayed:
    Gtk::Container* mainWindow = m_mainLayout.get_parent();
    IF_CONDITION_NOT_MET_DO(mainWindow, return;);

    Gtk::Window* parent = dynamic_cast<Gtk::Window*>(mainWindow);
    IF_CONDITION_NOT_MET_DO(parent, return;);

    cxmodel::NewGameInformation gameInformation;
    const auto extractionStatus = ExtractGameInformation(gameInformation);
    if(!extractionStatus.IsSuccess())
    {
        DisplayWarningDialog(*parent, extractionStatus.GetMessage());
        return;
    }

    const auto inputValidationStatus = Validate(gameInformation, m_presenter);
    if(!inputValidationStatus.IsSuccess())
    {
        DisplayWarningDialog(*parent, inputValidationStatus.GetMessage());
        return;
    }

    // At this point all user input has been validated. We start the game:
    m_controller.OnStart(std::move(gameInformation));
}

void cxgui::NewGameView::OnAddPlayer()
{
    if(m_presenter.CanAddAnotherPlayer(m_playersList->GetSize()))
    {
        const size_t nbNext = m_playersList->GetSize() + 1;
        std::ostringstream os;
        os << "-- Player " << nbNext << " --";

        IF_CONDITION_NOT_MET_DO(m_playersList->AddRow(os.str(), cxmodel::MakeRed(), cxmodel::PlayerType::HUMAN), return;);
        m_playersList->GetUnderlying().show_all();
    }

    m_removePlayerButton.set_sensitive(m_presenter.CanRemoveAnotherPlayer(m_playersList->GetSize()));
    m_addPlayerButton.set_sensitive(m_presenter.CanAddAnotherPlayer(m_playersList->GetSize()));
}

void cxgui::NewGameView::OnRemovePlayer()
{
    if(m_presenter.CanRemoveAnotherPlayer(m_playersList->GetSize()))
    {
        IF_CONDITION_NOT_MET_DO(m_playersList->RemoveRow(m_playersList->GetSize() - 1), return;);

        // At this point, the rwo is removed. If we don't act though, the extra
        // space left by the removed row will still be displayed on the screen,
        // leaving the window with ugly extra space. We want the window to resize
        // to the new list. First, we get a handle to the main window:
        Gtk::Container* parentAsGtk = m_mainLayout.get_parent();
        IF_CONDITION_NOT_MET_DO(parentAsGtk != nullptr, return;);

        Gtk::Window* mainWindowAsGtk = dynamic_cast<Gtk::Window*>(parentAsGtk);
        IF_CONDITION_NOT_MET_DO(mainWindowAsGtk!= nullptr, return;);

        // Then, we get the preferred heights values:
        int minimumHeight, naturalHeight;
        mainWindowAsGtk->get_preferred_height(minimumHeight, naturalHeight);

        // Then, we make a size request using the minimum height. Notice the '100'
        // that is removed. This was added to make sure Gtkmm did not leave any
        // extra blank space by resizing smaller than the minimum value:
        mainWindowAsGtk->set_size_request(mainWindowAsGtk->get_width(), minimumHeight - 100);

        // Then resize accordingly:
        mainWindowAsGtk->resize(mainWindowAsGtk->get_width(), naturalHeight);
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
    size_t inARowValue;
    auto extractionStatus = extractRawUserInput(m_inARowEntry.get_text(), inARowValue);
    if(!extractionStatus.IsSuccess())
    {
        return extractionStatus;
    }

    size_t boardWidth;
    extractionStatus = extractRawUserInput(m_gridWidthEntry.get_text(), boardWidth);
    if(!extractionStatus.IsSuccess())
    {
        return extractionStatus;
    }

    size_t boardHeight;
    extractionStatus = extractRawUserInput(m_gridHeightEntry.get_text(), boardHeight);
    if(!extractionStatus.IsSuccess())
    {
        return extractionStatus;
    }

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

cxmodel::Status cxgui::Validate(const cxmodel::NewGameInformation& p_gameInformation, const cxgui::INewGameViewPresenter& p_presenter)
{
    const auto inARowInputStatus = p_presenter.IsInARowValueValid(p_gameInformation.m_inARowValue);
    if(!inARowInputStatus.IsSuccess())
    {
        return inARowInputStatus;
    }

    const auto boardDimensionInputStatus = p_presenter.AreBoardDimensionsValid(p_gameInformation.m_gridHeight, p_gameInformation.m_gridWidth);
    if(!boardDimensionInputStatus.IsSuccess())
    {
        return boardDimensionInputStatus;
    }

    std::vector<std::string> playerNames;
    for(const auto player : p_gameInformation.m_players)
    {
        playerNames.push_back(player->GetName());
    }
    const auto playerNamesInputStatus = p_presenter.ArePlayerNamesValid(playerNames);
    if(!playerNamesInputStatus.IsSuccess())
    {
        return playerNamesInputStatus;
    }

    std::vector<cxmodel::ChipColor> playerChipColors;
    for(const auto player : p_gameInformation.m_players)
    {
        playerChipColors.push_back(player->GetChip().GetColor());
    }
    const auto playerChipColorsInputStatus = p_presenter.ArePlayerChipColorsValid(playerChipColors);
    if(!playerChipColorsInputStatus.IsSuccess())
    {
        return playerChipColorsInputStatus;
    }

    std::vector<cxmodel::PlayerType> playerTypes;
    for(const auto player : p_gameInformation.m_players)
    {
        playerTypes.push_back(player->IsManaged() ? cxmodel::PlayerType::BOT : cxmodel::PlayerType::HUMAN );
    }
    const auto playerTypesInputStatus = p_presenter.ArePlayerTypesValid(playerTypes);
    if(!playerTypesInputStatus.IsSuccess())
    {
        return playerTypesInputStatus;
    }

    const auto newGameIsWinnableStatus = p_presenter.IsNewGameWinnable(p_gameInformation.m_inARowValue,
                                                                       playerNames.size(),
                                                                       p_gameInformation.m_gridHeight,
                                                                       p_gameInformation.m_gridWidth);
    if(!newGameIsWinnableStatus.IsSuccess())
    {
        return newGameIsWinnableStatus;
    }

    return cxmodel::MakeSuccess();
}
