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

#ifndef GTKMM3GAMERESOLUTIONDIALOG_H_E524D346_789D_4165_ABD3_4B876F7FBBD7
#define GTKMM3GAMERESOLUTIONDIALOG_H_E524D346_789D_4165_ABD3_4B876F7FBBD7

#include <cxui/WidgetsFactories.h>
#include <cxcmnuigtkmm3/Window.h>

namespace cx::cmn::ui
{
    class IButton;
    class ILabel;
}

namespace cx::ui
{
    class IGameResolutionDialogController;
    class IGameResolutionDialogPresenter;
    class WidgetsFactories;
}

namespace cx::ui::gtkmm3
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
class GameResolutionDialog : public cx::cmn::ui::gtkmm3::Window
{

public:

    /******************************************************************************************//**
     * @brief Constructor.
     *
     * @pre
     *     The presenter is valid.
     *
     * @param p_widgetsFactories
     *     The necessary factories to instanciate widgets.
     * @param p_presenter
     *     The window presenter.
     * @param p_controller
     *     The window presenter.
     *
     ********************************************************************************************/
    GameResolutionDialog(
       cx::ui::WidgetsFactories& p_widgetsFactories,
       std::unique_ptr<cx::ui::IGameResolutionDialogPresenter> p_presenter,
       std::unique_ptr<cx::ui::IGameResolutionDialogController> p_controller);

private:

    void Update(cx::model::ModelNotificationContext p_context, cx::model::ModelSubject* p_subject) final;

    void InitializeWidgets() final;
    void ConfigureWindow() final;
    void RegisterLayouts() final;
    void RegisterWidgets() final;
    void ConfigureLayouts() final;
    void ConfigureWidgets() final;
    void ConfigureSignalHandlers() final;

    const std::unique_ptr<cx::ui::IGameResolutionDialogPresenter> m_presenter;
    const std::unique_ptr<cx::ui::IGameResolutionDialogController> m_controller;

    cx::ui::WidgetsFactories& m_widgetsFactories;
    std::unique_ptr<cx::cmn::ui::ILabel> m_title;
    std::unique_ptr<cx::cmn::ui::ILabel> m_message;
    std::unique_ptr<cx::cmn::ui::IButton> m_startNewGame;

};

} // namespace cx::ui::gtkmm3

#endif // GTKMM3GAMERESOLUTIONDIALOG_H_E524D346_789D_4165_ABD3_4B876F7FBBD7
