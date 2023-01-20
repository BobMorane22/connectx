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
 * @file MainWindow.h
 * @date 2019
 *
 *************************************************************************************************/

#ifndef MAINWINDOW_H_F0ED11E8_831A_4C6A_8A9B_8C329506BD72
#define MAINWINDOW_H_F0ED11E8_831A_4C6A_8A9B_8C329506BD72

#include <memory>

#include <gtkmm/applicationwindow.h>
#include <gtkmm/button.h>
#include <gtkmm/grid.h>
#include <gtkmm/imagemenuitem.h>
#include <gtkmm/label.h>
#include <gtkmm/menubar.h>
#include <gtkmm/menuitem.h>
#include <gtkmm/menu.h>
#include <gtkmm/stock.h>

#include "IStatusBar.h"
#include "IStatusBarPresenter.h"
#include "IView.h"
#include "Window.h"

namespace cxgui
{
    class IMainWindowController;
    class IMainWindowPresenter;
}

namespace Gtk
{
 class Application;
}

namespace cxgui
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
class MainWindow : public cxgui::Window<Gtk::ApplicationWindow>
{

public:

    /******************************************************************************************//**
     * @brief Constructor.
     *
     * @param p_gtkApplication The Gtkmm application object
     * @param p_model      The Connect X compatible model.
     * @param p_controller The main window controller.
     * @param p_presenter  The main window presenter.
     *
     ********************************************************************************************/
    MainWindow(Gtk::Application& p_gtkApplication,
               cxmodel::ModelSubject& p_model,
               IMainWindowController& p_controller,
               IMainWindowPresenter& p_presenter);

    int Show() override;


private:

    void Update(cxmodel::ModelNotificationContext p_context, cxmodel::ModelSubject* p_subject) override;

    void UpdateCreateNewGame();
    void UpdateChipDropped(cxmodel::ModelNotificationContext p_context);
    void UpdateChipMoved(cxmodel::ModelNotificationContext p_context);
    void UpdateGameWon(cxmodel::ModelNotificationContext p_context);
    void UpdateGameTied(cxmodel::ModelNotificationContext p_context);
    void UpdateGameEnded();
    void UpdateGameReinitialized(cxmodel::ModelNotificationContext p_context);
    void UpdateMenuItems(cxmodel::ModelNotificationContext p_context);

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

    void CreateGameResolutionWindow(cxmodel::ModelNotificationContext p_context);

    void ActivateNewGameView();
    void DeactivateNewGameView();

    void ActivateGameView();
    void DeactivateGameView();

    Gtk::Application& m_gtkApplication;

    cxmodel::ModelSubject& m_model;

    IMainWindowController& m_controller;
    IMainWindowPresenter& m_presenter;
    std::unique_ptr<IStatusBarPresenter> m_statusbarPresenter;

    std::unique_ptr<IStatusBar> m_statusbar;

    Gtk::MenuBar m_menubar;
    Gtk::MenuItem m_gameMenuItem;
    Gtk::Menu m_gameMenu;
    Gtk::MenuItem m_newGameMenuItem;
    Gtk::MenuItem m_reinitializeMenuItem;
    Gtk::ImageMenuItem m_undoMenuItem{Gtk::Stock::UNDO};
    Gtk::ImageMenuItem m_redoMenuItem{Gtk::Stock::REDO};
    Gtk::ImageMenuItem m_quitMenuItem{Gtk::Stock::QUIT};
    Gtk::MenuItem m_helpMenuItem;
    Gtk::Menu m_helpMenu;
    Gtk::ImageMenuItem m_contentsMenuItem{Gtk::Stock::HELP}; 
    Gtk::ImageMenuItem m_aboutMenuItem{Gtk::Stock::ABOUT};

    // Views:
    const int m_viewLeft;
    const int m_viewTop;
    std::unique_ptr<IView> m_newGameView;
    std::unique_ptr<IView> m_gameView;

    // Other windows:
    std::unique_ptr<IWindow> m_about;
    std::unique_ptr<IWindow> m_gameResolution;
};

} // namespace cxgui

#endif // MAINWINDOW_H_F0ED11E8_831A_4C6A_8A9B_8C329506BD72
