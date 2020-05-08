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

#include "INewGameViewController.h"
#include "INewGameViewPresenter.h"
#include "IView.h"
#include "Window.h"

namespace cxgui
{

/*********************************************************************************************//**
 * @brief View for creating new games.
 *
 ************************************************************************************************/
class NewGameView : public cxgui::IView
{

public:

    NewGameView(INewGameViewPresenter& p_presenter,
                INewGameViewController& p_controller,
                Gtk::Grid& p_mainLayout,
                int p_viewLeft,
                int p_viewTop);

    void Activate() override;

private:

    void SetLayout();
    void PopulateWidgets();
    void ConfigureWidgets();
    void OnStart();

    INewGameViewPresenter& m_presenter;
    INewGameViewController& m_controller;

    Gtk::Grid& m_mainLayout;

    const int m_viewLeft;
    const int m_viewTop;

    Gtk::Grid m_viewLayout;

    // Controls:
    Gtk::Label m_title;

    Gtk::Label m_gameSectionTitle;
    Gtk::Label m_inARowLabel;
    Gtk::Entry m_inARowEntry;

    Gtk::Label m_gridSectionTitle;
    Gtk::Label m_gridWidthLabel;
    Gtk::Entry m_gridWidthEntry;
    Gtk::Label m_gridHeightLabel;
    Gtk::Entry m_gridHeightEntry;

    Gtk::Label m_playersSectionTitle;
    Gtk::Label m_nameRowTitle;
    Gtk::Entry m_player1NameEntry;
    Gtk::Entry m_player2NameEntry;
    Gtk::Label m_discRowTitle;
    Gtk::Entry m_disc1Entry;
    Gtk::Entry m_disc2Entry;

    Gtk::Button m_startButton;
};

} // namespace cxgui

#endif // NEWGAMEVIEW_H_C5E65447_64C6_4DFE_B0F7_E6E9DB14BEAF
