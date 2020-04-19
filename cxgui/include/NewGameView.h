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
 * @file NewGameView.h
 * @date 2020
 *
 *************************************************************************************************/

#ifndef NEWGAMEVIEW_H_C5E65447_64C6_4DFE_B0F7_E6E9DB14BEAF
#define NEWGAMEVIEW_H_C5E65447_64C6_4DFE_B0F7_E6E9DB14BEAF

#include <gtkmm/button.h>
#include <gtkmm/entry.h>

#include "Window.h"
#include "IView.h"

namespace cxgui
{

/*********************************************************************************************//**
 * @brief DESCRIPTION
 *
 * @invariant
 * @invariant
 *
 * DESCRIPTION
 *
 ************************************************************************************************/
struct NewGameView : public cxgui::IView
{
    NewGameView(Gtk::Grid& p_mainLayout, int p_viewLeft, int p_viewTop);

    void Activate() override;

    Gtk::Grid m_viewLayout;

    Gtk::Label m_title{"New Game"};

    Gtk::Label m_gameSectionTitle{"Game"};
    Gtk::Label m_inARowLabel{"In a row:"};
    Gtk::Entry m_inARowEntry;

    Gtk::Label m_gridSectionTitle{"Grid"};
    Gtk::Label m_gridWidthLabel{"Width:"};
    Gtk::Entry m_gridWidthEntry;
    Gtk::Label m_gridHeightLabel{"Height:"};
    Gtk::Entry m_gridHeightEntry;

    Gtk::Label m_playersSectionTitle{"Players"};
    Gtk::Label m_nameRowTitle{"Name"};
    Gtk::Entry m_player1NameEntry;
    Gtk::Entry m_player2NameEntry;
    Gtk::Label m_discRowTitle{"Disc"};
    Gtk::Entry m_disc1Entry;
    Gtk::Entry m_disc2Entry;

    Gtk::Button m_startButton{"Start"};

private:

    Gtk::Grid& m_mainLayout;

    const int m_viewLeft;
    const int m_viewTop;
};

} // namespace cxgui

#endif // NEWGAMEVIEW_H_C5E65447_64C6_4DFE_B0F7_E6E9DB14BEAF
