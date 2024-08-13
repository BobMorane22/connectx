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
 * @file Gtkmm3MainWindow.h
 * @date 2019
 *
 *************************************************************************************************/

#ifndef GTKMM3MAINWINDOW_H_F0ED11E8_831A_4C6A_8A9B_8C329506BD72
#define GTKMM3MAINWINDOW_H_F0ED11E8_831A_4C6A_8A9B_8C329506BD72

#include <memory>

#include <cxmodel/common.h>
#include <cxcmnuigtkmm3/Window.h>

namespace cx::cmn::ui
{
    class IMenuBar;
    class IMenu;
    class IMenuItem;
    class IStatusBar;
    class IStatusBarPresenter;
}

namespace cx::ui
{
    class IMainWindowController;
    class IMainWindowPresenter;
    class IView;
}

namespace Gtk
{
    class Application;
}

namespace cx::ui::gtkmm3
{

/*********************************************************************************************//**
 * @brief The Connect X main application window.
 *
 * A Gtkmm window that acts as the application main window. This main window is composed of
 * three components:
 *
 *  1. A menu bar
 *  2. A view (which can be swapped for another)
 *  3. A status bar.
 *
 * Visually:
 *
 *                                 +------------------------+
 *                                 |        Menu bar        |
 *                                 |------------------------|
 *                                 |                        |
 *                                 |                        |
 *                                 |          View          |
 *                                 |                        |
 *                                 |                        |
 *                                 |------------------------|
 *                                 |       Status bar       |
 *                                 +------------------------+
 *
 * The view area is the meat of the window and contains all of its contents. Views are lazy
 * evaluated and can be swapped at runtime, depending on the state of the game. For example,
 * when the application is launched, the 'New Game' view is made available. When the user
 * starts the game, the 'New Game' view is swapped for the 'Game' view, which contains all
 * the gaming widgets, such as the board.
 *
 ************************************************************************************************/
class Gtkmm3MainWindow : public cx::cmn::ui::gtkmm3::Window
{

public:

    /******************************************************************************************//**
     * @brief Constructor.
     *
     * @param p_gtkApplication
     *      The Gtkmm application object
     * @param p_model
     *      The Connect X compatible model.
     * @param p_controller
     *      The main window controller.
     * @param p_presenter
     *      The main window presenter.
     * @param p_widgetsFactories
     *      The widgets factories.
     *
     ********************************************************************************************/
    Gtkmm3MainWindow(
        Gtk::Application& p_gtkApplication,
        cx::model::ModelSubject& p_model,
        cx::ui::IMainWindowController& p_controller,
        cx::ui::IMainWindowPresenter& p_presenter,
        cx::ui::WidgetsFactories& p_widgetsFactories);

    // cx::cmn::ui::IWindow:
    ~Gtkmm3MainWindow() override;
    [[nodiscard]] int Show() override;

private:

    void Update(cx::model::ModelNotificationContext p_context, cx::model::ModelSubject* p_subject) override;

    void UpdateCreateNewGame();
    void UpdateChipDropped(cx::model::ModelNotificationContext p_context);
    void UpdateChipMoved(cx::model::ModelNotificationContext p_context);
    void UpdateGameWon(cx::model::ModelNotificationContext p_context);
    void UpdateGameTied(cx::model::ModelNotificationContext p_context);
    void UpdateGameEnded();
    void UpdateGameReinitialized(cx::model::ModelNotificationContext p_context);
    void UpdateMenuItems(cx::model::ModelNotificationContext p_context);

    void InitializeWidgets() override;
    void ConfigureWindow() override;
    void RegisterLayouts() override;
    void RegisterWidgets() override;
    void ConfigureLayouts() override;
    void ConfigureWidgets() override;
    void ConfigureSignalHandlers() override;

    void RegisterStatusBar();
    void RegisterMenuBar();

    void OnNewGame();
    void OnReinitializeCurrentGame();
    void OnUndo();
    void OnRedo();
    void OnHelpContentsRequested();
    void OnCreateAboutWindow();

    void CreateGameResolutionWindow(cx::model::ModelNotificationContext p_context);

    void ActivateNewGameView();
    void DeactivateNewGameView();

    void ActivateGameView();
    void DeactivateGameView();

private:

    Gtk::Application& m_gtkApplication;

    cx::model::ModelSubject& m_model;

    cx::ui::IMainWindowController& m_controller;
    cx::ui::IMainWindowPresenter& m_presenter;
    std::unique_ptr<cx::cmn::ui::IStatusBarPresenter> m_statusBarPresenter;

    // Widgets factories:
    cx::ui::WidgetsFactories& m_widgetsFactories;

    // Status bar:
    std::unique_ptr<cx::cmn::ui::IStatusBar> m_statusBar;

    // Menu bar:
    std::unique_ptr<cx::cmn::ui::IMenuBar> m_menuBar;
    std::unique_ptr<cx::cmn::ui::IMenu> m_gameMenu;
    std::unique_ptr<cx::cmn::ui::IMenuItem> m_newGameMenuItem;
    std::unique_ptr<cx::cmn::ui::IMenuItem> m_reinitializeMenuItem;
    std::unique_ptr<cx::cmn::ui::IMenuItem> m_undoMenuItem;
    std::unique_ptr<cx::cmn::ui::IMenuItem> m_redoMenuItem;
    std::unique_ptr<cx::cmn::ui::IMenuItem> m_quitMenuItem;
    std::unique_ptr<cx::cmn::ui::IMenu> m_helpMenu;
    std::unique_ptr<cx::cmn::ui::IMenuItem> m_contentsMenuItem;
    std::unique_ptr<cx::cmn::ui::IMenuItem> m_aboutMenuItem;

    // Views:
    const cx::model::Column m_viewLeft;
    const cx::model::Row m_viewTop;
    std::unique_ptr<cx::ui::IView> m_newGameView;
    std::unique_ptr<cx::ui::IView> m_gameView;

    // Other windows:
    std::unique_ptr<cx::cmn::ui::IWindow> m_aboutWindow;
    std::unique_ptr<cx::cmn::ui::IWindow> m_gameResolution;
};

} // namespace cx::ui::gtkmm3

#endif // GTKMM3MAINWINDOW_H_F0ED11E8_831A_4C6A_8A9B_8C329506BD72
