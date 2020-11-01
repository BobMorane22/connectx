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

#include <cxinv/include/assertion.h>
#include <cxmodel/include/NewGameInformation.h>

#include <extractRawUserInput.h>
#include <NewGameView.h>

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
    SetLayout();
    PopulateWidgets();
    ConfigureWidgets();

    m_removePlayerButton.signal_clicked().connect([this](){OnRemovePlayer();});
    m_addPlayerButton.signal_clicked().connect([this](){OnAddPlayer();});
    m_startButton.signal_clicked().connect([this](){OnStart();});
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

void cxgui::NewGameView::Update(cxmodel::NotificationContext /*p_context*/)
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
    m_viewLayout.attach(m_nameRowTitle, 0, 7, 1, 1);
    m_viewLayout.attach(m_discRowTitle, 1, 7, 1, 1);
    m_viewLayout.attach(m_playerList, 0, 8, TOTAL_WIDTH, 1);

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
    m_nameRowTitle.set_text(m_presenter.GetNewGameViewNameColumnHeaderText());
    m_discRowTitle.set_text(m_presenter.GetNewGameViewDiscColumnHeaderText());

    m_removePlayerButton.set_label(m_presenter.GetNewGameViewRemovePlayerButtonText());
    m_addPlayerButton.set_label(m_presenter.GetNewGameViewAddPlayerButtonText());

    m_startButton.set_label(m_presenter.GetNewGameViewStartButtonText());
}

void cxgui::NewGameView::ConfigureWidgets()
{
    // Window margin:
    m_mainLayout.set_margin_left(DIALOG_SIDE_MARGIN);
    m_mainLayout.set_margin_right(DIALOG_SIDE_MARGIN);
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
    m_nameRowTitle.set_margin_bottom(CONTROL_BOTTOM_MARGIN);
    m_discRowTitle.set_margin_bottom(CONTROL_BOTTOM_MARGIN);
    m_playerList.set_margin_bottom(CONTROL_BOTTOM_MARGIN);

    // Add/Remove player buttons:
    m_removePlayerButton.set_margin_bottom(CONTROL_BOTTOM_MARGIN);
    m_addPlayerButton.set_margin_bottom(CONTROL_BOTTOM_MARGIN);
    m_removePlayerButton.set_sensitive(m_presenter.CanRemoveAnotherPlayer(m_playerList.GetSize()));
    m_addPlayerButton.set_sensitive(m_presenter.CanAddAnotherPlayer(m_playerList.GetSize()));

    // Start button:
    m_startButton.set_margin_bottom(CONTROL_BOTTOM_MARGIN);
}

void cxgui::NewGameView::OnStart()
{
    // First, we get an handle to the main window in case a warning dialog needs to be
    // displayed:
    Gtk::Container* mainWindow = m_mainLayout.get_parent();
    if(!ASSERT(mainWindow))
    {
        return;
    }

    Gtk::Window* parent = dynamic_cast<Gtk::Window*>(mainWindow);
    if(!ASSERT(parent))
    {
        return;
    }

    // Retrieve game parameters:
    size_t inARowValue;
    auto extractionStatus = extractRawUserInput(m_inARowEntry.get_text(), inARowValue);
    if(!extractionStatus.IsSuccess())
    {
        DisplayWarningDialog(*parent, extractionStatus.GetMessage());
        return;
    }

    size_t boardWidth;
    extractionStatus = extractRawUserInput(m_gridWidthEntry.get_text(), boardWidth);
    if(!extractionStatus.IsSuccess())
    {
        DisplayWarningDialog(*parent, extractionStatus.GetMessage());
        return;
    }

    size_t boardHeight;
    extractionStatus = extractRawUserInput(m_gridHeightEntry.get_text(), boardHeight);
    if(!extractionStatus.IsSuccess())
    {
        DisplayWarningDialog(*parent, extractionStatus.GetMessage());
        return;
    }

    const std::vector<std::string> playerNames = m_playerList.GetAllPlayerNames();
    const std::vector<cxmodel::ChipColor> chipColors = m_playerList.GetAllColors();

    // Validate the input:
    const auto inARowInputStatus = m_presenter.IsInARowValueValid(inARowValue);
    if(!inARowInputStatus.IsSuccess())
    {
        DisplayWarningDialog(*parent, inARowInputStatus.GetMessage());
        return;
    }

    const auto boardDimensionInputStatus = m_presenter.AreBoardDimensionsValid(boardHeight, boardWidth);
    if(!boardDimensionInputStatus.IsSuccess())
    {
        DisplayWarningDialog(*parent, boardDimensionInputStatus.GetMessage());
        return;
    }

    const auto playerInfoInputStatus = m_presenter.ArePlayersInformationValid(playerNames, chipColors);
    if(!playerInfoInputStatus.IsSuccess())
    {
        DisplayWarningDialog(*parent, playerInfoInputStatus.GetMessage());
        return;
    }

    // Start game:
    cxmodel::NewGameInformation gameInformation;

    gameInformation.m_inARowValue = inARowValue;
    gameInformation.m_gridHeight = boardHeight;
    gameInformation.m_gridWidth = boardWidth;
    for(size_t index = 0; index < m_playerList.GetSize(); ++index)
    {
        gameInformation.AddPlayer({playerNames[index], chipColors[index]});
    }

    m_controller.OnStart(gameInformation);
}

void cxgui::NewGameView::OnAddPlayer()
{
    if(m_presenter.CanAddAnotherPlayer(m_playerList.GetSize()))
    {
        const size_t nbNext = m_playerList.GetSize() + 1;
        std::ostringstream os;
        os << "-- Player " << nbNext << " --";

        m_playerList.AddRow(os.str(), cxmodel::MakeRed());
        m_playerList.show_all();
    }

    m_removePlayerButton.set_sensitive(m_presenter.CanRemoveAnotherPlayer(m_playerList.GetSize()));
    m_addPlayerButton.set_sensitive(m_presenter.CanAddAnotherPlayer(m_playerList.GetSize()));
}

void cxgui::NewGameView::OnRemovePlayer()
{
    if(m_presenter.CanRemoveAnotherPlayer(m_playerList.GetSize()))
    {
        m_playerList.RemoveRow(m_playerList.GetSize() - 1);

        // At this point, the rwo is removed. If we don't act though, the extra
        // space left by the removed row will still be displayed on the screen,
        // leaving the window with ugly extra space. We want the window to resize
        // to the new list. First, we get a handle to the main window:
        Gtk::Container* parentAsGtk = m_mainLayout.get_parent();
        if(!ASSERT(bool(parentAsGtk)))
        {
            return;
        }

        Gtk::Window* mainWindowAsGtk = dynamic_cast<Gtk::Window*>(parentAsGtk);
        if(!ASSERT(bool(parentAsGtk)))
        {
            return;
        }

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

    m_removePlayerButton.set_sensitive(m_presenter.CanRemoveAnotherPlayer(m_playerList.GetSize()));
    m_addPlayerButton.set_sensitive(m_presenter.CanAddAnotherPlayer(m_playerList.GetSize()));
}
