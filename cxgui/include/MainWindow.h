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
 * A Gtkmm window that acts as the application main window. It is the responsibility of this
 * window to initialize the Gtkmm library and to show the window.
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
               cxmodel::Subject& p_model,
               IMainWindowController& p_controller,
               IMainWindowPresenter& p_presenter);

    int Show() override;


private:

    void Update(cxmodel::NotificationContext p_context, cxmodel::Subject* p_subject) override;

    void ConfigureWindowIcon() override;
    void ConfigureWindow() override;
    void RegisterLayouts() override;
    void RegisterWidgets() override;
    void ConfigureLayouts() override;
    void ConfigureWidgets() override;
    void ConfigureSignalHandlers() override;

    void RegisterStatusBar();
    void RegisterMenuBar();

    void CreateAboutWindow();

    Gtk::Application& m_gtkApplication;

    cxmodel::Subject& m_model;

    IMainWindowController& m_controller;
    IMainWindowPresenter& m_presenter;
    std::unique_ptr<IStatusBarPresenter> m_statusbarPresenter;

    Gtk::Button m_undoButton{Gtk::Stock::UNDO};
    Gtk::Button m_redoButton{Gtk::Stock::REDO};
    Gtk::Label m_counterLabel;
    Gtk::Button m_incrementButton;
    Gtk::Button m_reinitButton;

    std::unique_ptr<IStatusBar> m_statusbar;

    Gtk::MenuBar m_menubar;
    Gtk::MenuItem m_gameMenuItem;
    Gtk::Menu m_gameMenu;
    Gtk::MenuItem m_reinitMenuItem;
    Gtk::ImageMenuItem m_quitMenuItem{Gtk::Stock::QUIT};
    Gtk::MenuItem m_helpMenuItem;
    Gtk::Menu m_helpMenu;
    Gtk::ImageMenuItem m_aboutMenuItem{Gtk::Stock::ABOUT};

    std::unique_ptr<IWindow> m_about;
};

} // namespace cxgui

#endif // MAINWINDOW_H_F0ED11E8_831A_4C6A_8A9B_8C329506BD72
