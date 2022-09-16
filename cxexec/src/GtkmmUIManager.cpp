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
 * @file GtkmmUIManager.cpp
 * @date 2019
 *
 *************************************************************************************************/

#include <cxinv/assertion.h>
#include <cxgui/MainWindow.h>
#include <cxgui/MainWindowController.h>
#include <cxgui/MainWindowPresenter.h>
#include <cxexec/GtkmmUIManager.h>
#include <cxexec/ModelReferences.h>

cx::GtkmmUIManager::GtkmmUIManager(int argc, char *argv[], cx::ModelReferences& p_model)
{
    PRECONDITION(argc > 0);
    PRECONDITION(argv);

    InitializeGtkmm(argc, argv);

    // At this point, the Gtkmm engine is initialized. This means that Gtkmm widgets can safely be
    // instantiated...

    m_controller = std::make_unique<cxgui::MainWindowController>(p_model.m_asGameActions, p_model.m_asUndoRedo);
    m_presenter = std::make_unique<cxgui::MainWindowPresenter>(p_model.m_asLimits, p_model.m_asGameInformation, p_model.m_asUndoRedo, p_model.m_asAi);

    // Note: we must use the 'get' method with the 'operator*' because Gtk::RefPtr does not
    // support, like most smart pointers, accessing the underlying instance through 'operator*':
    {
        auto mainWindow = std::make_unique<cxgui::MainWindow>(*(m_app.get()), p_model.m_asSubject, *m_controller, *m_presenter);
        mainWindow->Init();

        m_mainWindow = std::move(mainWindow);
    }

    p_model.m_asSubject.Attach(m_presenter.get());
    m_presenter->Attach(m_mainWindow.get());

    POSTCONDITION(m_mainWindow);

    CheckInvariants();
}

int cx::GtkmmUIManager::Manage()
{
    CheckInvariants();

    if(m_mainWindow)
    {
        return m_mainWindow->Show();
    }

    return EXIT_FAILURE;
}

void cx::GtkmmUIManager::InitializeGtkmm(int argc, char *argv[])
{
    m_app = Gtk::Application::create(argc, argv, "bobmorane.connectx");

    POSTCONDITION(bool(m_app));
}

void cx::GtkmmUIManager::CheckInvariants()
{
    INVARIANT(m_controller);
    INVARIANT(m_presenter);
    INVARIANT(m_mainWindow);
}
