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
 * @file GameResolutionDialog.h
 * @date 2020
 *
 *************************************************************************************************/

#ifndef GAMERESOLUTIONDIALOG_H_E524D346_789D_4165_ABD3_4B876F7FBBD7
#define GAMERESOLUTIONDIALOG_H_E524D346_789D_4165_ABD3_4B876F7FBBD7

#include <gtkmm/button.h>
#include <gtkmm/label.h>
#include <gtkmm/window.h>

#include "Window.h"

namespace cxgui
{
    class IGameResolutionDialogController;
    class IGameResolutionDialogPresenter;
}

namespace cxgui
{

/*********************************************************************************************//**
 * @brief Window shown when a game is resolved (win, tie, etc).
 *
 * When a game is resolved (won, tied, etc), this window is popped for the user to read some
 * resolution message a pick a next action.
 *
 * @note This window is modal.
 *
 ************************************************************************************************/
class GameResolutionDialog : public Window<Gtk::Window>
{

public:

    /******************************************************************************************//**
     * @brief Constructor.
     *
     * @pre
     *     The presenter is valid.
     *
     * @param p_presenter
     *     The window presenter.
     * @param p_controller
     *     The window presenter.
     *
     ********************************************************************************************/
    GameResolutionDialog(std::unique_ptr<IGameResolutionDialogPresenter> p_presenter,
                         std::unique_ptr<IGameResolutionDialogController> p_controller);

private:

    void Update(cxmodel::ModelNotificationContext p_context, cxmodel::ModelSubject* p_subject) override;

    void ConfigureWindow() override;
    void RegisterLayouts() override;
    void RegisterWidgets() override;
    void ConfigureLayouts() override;
    void ConfigureWidgets() override;
    void ConfigureSignalHandlers() override;

    const std::unique_ptr<IGameResolutionDialogPresenter> m_presenter;
    const std::unique_ptr<IGameResolutionDialogController> m_controller;

    Gtk::Label m_title;
    Gtk::Label m_message;
    Gtk::Button m_startNewGame;

};

} // namespace cxgui

#endif // GAMERESOLUTIONDIALOG_H_E524D346_789D_4165_ABD3_4B876F7FBBD7
