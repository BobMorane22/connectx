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

#include <gtkmm/messagedialog.h>

#include <cxinv/include/assertion.h>
#include <NewGameView.h>
#include "../../cxmodel/include/NewGameInformation.h"

namespace
{

/**********************************************************************************************//**
 * @brief Display a warning dialog.
 *
 * @pre p_message Is not empty.
 *
 * @param p_message The warning message.
 *
 ************************************************************************************************/
void DisplayWarningDialog(const std::string& p_message)
{
    PRECONDITION(!p_message.empty());

    constexpr bool NO_MARKUP = false;

    Gtk::MessageDialog errorDlg{p_message, NO_MARKUP, Gtk::MessageType::MESSAGE_WARNING, Gtk::ButtonsType::BUTTONS_OK, true};

    errorDlg.run();
}

void DisplayNumericalValuesExpectedWarningDialog()
{
    DisplayWarningDialog("Enter numerical values for in-a-row and grid size values.");
}

void DisplayNumericalValuesOutOfRangeWarningDialog()
{
    DisplayWarningDialog("Numerical value(s) out of range.");
}

void DisplayEmptyEntriesWarningDialog()
{
    DisplayWarningDialog("Player names and disc cannot be empty.");
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

void cxgui::NewGameView::SetLayout()
{
    constexpr int TOTAL_WIDTH = 2;

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
    m_viewLayout.attach(m_player1NameEntry, 0, 8, 1, 1);
    m_viewLayout.attach(m_player2NameEntry, 0, 9, 1, 1);
    m_viewLayout.attach(m_discRowTitle, 1, 7, 1, 1);
    m_viewLayout.attach(m_disc1Entry, 1, 8, 1, 1);
    m_viewLayout.attach(m_disc2Entry, 1, 9, 1, 1);

    m_viewLayout.attach(m_startButton, 0, 10, TOTAL_WIDTH, 1);
}

void cxgui::NewGameView::PopulateWidgets()
{
    m_title.set_text(m_presenter.GetNewGameViewTitle());

    m_gameSectionTitle.set_text(m_presenter.GetNewGameViewGameSectionTitle());
    m_inARowLabel.set_text(m_presenter.GetNewGameViewInARowLabelText());

    m_gridSectionTitle.set_text(m_presenter.GetNewGameViewGridSectionTitle());
    m_gridWidthLabel.set_text(m_presenter.GetNewGameViewWidthLabelText());
    m_gridHeightLabel.set_text(m_presenter.GetNewGameViewHeightLabelText());

    m_playersSectionTitle.set_text(m_presenter.GetNewGameViewPlayersSectionTitle());
    m_nameRowTitle.set_text(m_presenter.GetNewGameViewNameColumnHeaderText());
    m_discRowTitle.set_text(m_presenter.GetNewGameViewDiscColumnHeaderText());

    m_startButton.set_label(m_presenter.GetNewGameViewStartButtonText());
}

void cxgui::NewGameView::OnStart()
{
    cxmodel::NewGameInformation gameInformation;

    try
    {
        gameInformation.m_inARowValue = std::stoul(m_inARowEntry.get_text());
        gameInformation.m_gridWidth = std::stoul(m_gridWidthEntry.get_text());
        gameInformation.m_gridHeight = std::stoul(m_gridHeightEntry.get_text());
    }
    catch(const std::invalid_argument& p_exception)
    {
        DisplayNumericalValuesExpectedWarningDialog();
        return;
    }
    catch(const std::out_of_range& p_exception)
    {
        DisplayNumericalValuesOutOfRangeWarningDialog();
        return;
    }

    const std::string name1 = m_player1NameEntry.get_text();
    const std::string name2 = m_player2NameEntry.get_text();

    if(name1.empty() || name2.empty())
    {
        DisplayEmptyEntriesWarningDialog();
        return;
    }

    const std::string disc1 = m_disc1Entry.get_text();
    const std::string disc2 = m_disc2Entry.get_text();

    if(disc1.empty() || disc2.empty())
    {
        DisplayEmptyEntriesWarningDialog();
        return;
    }

    gameInformation.AddPlayer({name1, disc1});
    gameInformation.AddPlayer({name2, disc2});

    m_controller.OnStart(gameInformation);
}
