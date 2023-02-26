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

#include <optional>

#include <gtkmm/button.h>
#include <gtkmm/entry.h>

#include "ColorComboBox.h"
#include "INewGameViewController.h"
#include "INewGameViewPresenter.h"
#include "IView.h"
#include "INewPlayersList.h"
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

    /*****************************************************************************************//**
     * @brief Constructor.
     *
     * @param p_presenter
     *      A main window presenter (new game view).
     * @param p_controller
     *      A main window controller (new game view).
     * @param p_mainLayout
     *      The main window's top level layout.
     * @param p_viewLeft
     *      The left position of the new game view within the main window's top level layout.
     * @param p_viewTop
     *      The top position of the new game view within the main window's top level layout.
     *
     ********************************************************************************************/
    NewGameView(INewGameViewPresenter& p_presenter,
                INewGameViewController& p_controller,
                Gtk::Grid& p_mainLayout,
                int p_viewLeft,
                int p_viewTop);

    // IView:
    void Activate() override;
    void DeActivate() override;
    void Update(cxmodel::ModelNotificationContext p_context) override;

private:

    void SetLayout();
    void PopulateWidgets();
    void ConfigureWidgets();

    void OnStart();
    void OnAddPlayer();
    void OnRemovePlayer();
    void OnNewGameParameterUpdated();

    [[nodiscard]] cxmodel::Status ExtractGameInformation(cxmodel::NewGameInformation& p_gameInformation) const;

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
    std::unique_ptr<cxgui::INewPlayersList> m_playersList;

    Gtk::Button m_removePlayerButton;
    Gtk::Button m_addPlayerButton;
    Gtk::Button m_startButton;

};

/*********************************************************************************************//**
 * @brief
 *
 ************************************************************************************************/
[[nodiscard]] cxmodel::Status Validate(const cxmodel::NewGameInformation& p_gameInformation,
                                       const cxgui::INewGameViewPresenter& p_presenter);

} // namespace cxgui

#endif // NEWGAMEVIEW_H_C5E65447_64C6_4DFE_B0F7_E6E9DB14BEAF
