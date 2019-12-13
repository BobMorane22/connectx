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
 * @file MainWindow.cpp
 * @date 2019
 *
 *************************************************************************************************/

#include <cxmodel/include/HelloWorld.h>
#include <cxinv/include/assertion.h>

#include <MainWindow.h>

cxgui::MainWindow::MainWindow(int argc, char *argv[])
{
    PRECONDITION(argc > 0);

    // This call must come first. Otherwise, we call operation on the window without
    // the Gtkmm library being initialized and the application crashes (segmentation
    // fault) when launched.
    InitializeGtkmm(argc, argv);

    const HelloWorld hw;
    m_helloWorld = std::make_unique<Gtk::Label>(hw.Make());

    m_mainWindow = std::make_unique<Gtk::ApplicationWindow>();
    m_mainWindow->set_default_size(200, 200);
    m_mainWindow->add(*m_helloWorld);

    POSTCONDITION(bool(m_app));
    POSTCONDITION(m_helloWorld != nullptr);
    POSTCONDITION(m_mainWindow != nullptr);
}

int cxgui::MainWindow::Show()
{
    m_mainWindow->show_all();
    return m_app->run(*m_mainWindow);

    INVARIANT(bool(m_app));
    INVARIANT(m_helloWorld != nullptr);
    INVARIANT(m_mainWindow != nullptr);
}

void cxgui::MainWindow::InitializeGtkmm(int argc, char *argv[])
{
    m_app = Gtk::Application::create(argc, argv, "bobmorane.connectx");

    POSTCONDITION(bool(m_app));
}
