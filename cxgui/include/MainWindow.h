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

#include <gtkmm/application.h>
#include <gtkmm/applicationwindow.h>
#include <gtkmm/button.h>
#include <gtkmm/grid.h>
#include <gtkmm/label.h>

#include "IMainWindow.h"
#include "IStatusBar.h"
#include "IStatusBarPresenter.h"

namespace cxgui
{
    class IMainWindowController;
    class IMainWindowPresenter;
}

namespace cxgui
{

/*********************************************************************************************//**
 * @brief The Connect X main application window.
 *
 * @invariant m_app is not @c nullptr
 * @invariant m_mainWindow is not @c nullptr
 * @invariant m_mainLayout is not @c nullptr
 * @invariant m_undoButton is not @c nullptr
 * @invariant m_redoButton is not @c nullptr
 * @invariant m_counterLabel is not @c nullptr
 * @invariant m_incrementButton is not @c nullptr
 * @invariant m_reinitButton is not @c nullptr
 *
 * A Gtkmm window that acts as the application main window. It is the responsibility of this
 * window to initialize the Gtkmm library and to show the window.
 *
 ************************************************************************************************/
class MainWindow : public cxgui::IMainWindow
{

public:

    /******************************************************************************************//**
     * @brief Constructor.
     *
     * @pre The argument count is at least 1.
     * @pre The argument list is not @c nullptr.
     *
     * @post m_app is not @c nullptr
     * @post m_mainWindow is not @c nullptr
     * @post m_mainLayout is not @c nullptr
     * @post m_undoButton is not @c nullptr
     * @post m_redoButton is not @c nullptr
     * @post m_counterLabel is not @c nullptr
     * @post m_incrementButton is not @c nullptr
     * @post m_reinitButton is not @c nullptr
     *
     * @param argc Command line argument count.
     * @param argc A C-style array of arguments.
     * @param p_model The Connect X compatible model.
     *
     ********************************************************************************************/
    MainWindow(int argc,
               char *argv[],
               cxmodel::Subject& p_model,
               IMainWindowController& p_controller,
               IMainWindowPresenter& p_presenter);

    int Show() override;


private:

    void Update(cxmodel::NotificationContext p_context, cxmodel::Subject* p_subject) override;

    void InitializeGtkmm(int argc, char *argv[]);

    void CheckInvariants();

    Glib::RefPtr<Gtk::Application> m_app;

    IMainWindowController& m_controller;
    IMainWindowPresenter& m_presenter;
    std::unique_ptr<IStatusBarPresenter> m_statusbarPresenter;

    // These members must be pointers. They are default initialized to nullptr, so no widget is
    // actually constructed. We construct is by hand, after the Gtkmm library initialization.
    // This is necessary because until then, constructing a widget crashes the application. We
    // can't, then, have stack members.
    std::unique_ptr<Gtk::ApplicationWindow> m_mainWindow;

    std::unique_ptr<Gtk::Grid> m_mainLayout;

    std::unique_ptr<Gtk::Button> m_undoButton;
    std::unique_ptr<Gtk::Button> m_redoButton;
    std::unique_ptr<Gtk::Label> m_counterLabel;
    std::unique_ptr<Gtk::Button> m_incrementButton;
    std::unique_ptr<Gtk::Button> m_reinitButton;

    std::unique_ptr<IStatusBar> m_statusbar;
};

} // namespace cxgui

#endif // MAINWINDOW_H_F0ED11E8_831A_4C6A_8A9B_8C329506BD72
