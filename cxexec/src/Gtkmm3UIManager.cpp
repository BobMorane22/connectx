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
 * @file Gtkmm3UIManager.cpp
 * @date 2019
 *
 *************************************************************************************************/

#include <cxinv/assertion.h>
#include <cxcmnui/IAbstractWidgetsFactory.h>
#include <cxcmnui/IWindow.h>
#include <cxui/MainWindowController.h>
#include <cxui/MainWindowPresenter.h>
#include <cxui/WidgetsFactories.h>
#include <cxcmnuigtkmm3/AbstractWidgetsFactory.h>
#include <cxuigtkmm3/AbstractConnectXWidgetsFactory.h>
#include <cxexec/Gtkmm3UIManager.h>
#include <cxexec/ModelReferences.h>

cx::Gtkmm3UIManager::Gtkmm3UIManager(int argc, char *argv[], cx::ModelReferences& p_model)
{
    PRECONDITION(argc > 0);
    PRECONDITION(argv);

    {
        Glib::RefPtr<Gtk::Application> gtkApplication = Gtk::Application::create(argc, argv, "bobmorane.connectx");
        ASSERT(gtkApplication);

        m_abstractWidgetsFactory = cx::cmn::ui::gtkmm3::FactoryCreate(gtkApplication);
        ASSERT(m_abstractWidgetsFactory);

        {
            auto abstractConnectXWidgetsFactory = std::make_unique<cx::ui::gtkmm3::AbstractConnectXWidgetsFactory>(gtkApplication);
            ASSERT(abstractConnectXWidgetsFactory);

            abstractConnectXWidgetsFactory->RegisterStandardWidgetsFactory(*m_abstractWidgetsFactory);

            m_abstractConnectXWidgetsFactory = std::move(abstractConnectXWidgetsFactory);
            ASSERT(m_abstractConnectXWidgetsFactory);
        }

        m_widgetsFactories = std::make_unique<cx::ui::WidgetsFactories>(*m_abstractWidgetsFactory, *m_abstractConnectXWidgetsFactory);
        ASSERT(m_widgetsFactories);
    }

    // At this point, the Gtkmm engine is initialized. This means that Gtkmm widgets can safely be
    // instantiated...

    m_controller = std::make_unique<cx::ui::MainWindowController>(p_model.m_asGameActions, p_model.m_asUndoRedo);
    m_presenter = std::make_unique<cx::ui::MainWindowPresenter>(p_model.m_asLimits, p_model.m_asGameInformation, p_model.m_asUndoRedo, p_model.m_asAi);

    m_mainWindow = m_abstractConnectXWidgetsFactory->CreateMainWindow(p_model.m_asSubject, *m_controller, *m_presenter);
    ASSERT(m_mainWindow);

    p_model.m_asSubject.Attach(m_presenter.get());
    m_presenter->Attach(m_mainWindow.get());

    POSTCONDITION(m_abstractWidgetsFactory);
    POSTCONDITION(m_abstractConnectXWidgetsFactory);
    POSTCONDITION(m_widgetsFactories);
    POSTCONDITION(m_mainWindow);

    CheckInvariants();
}

int cx::Gtkmm3UIManager::Manage()
{
    CheckInvariants();

    if(m_mainWindow)
    {
        return m_mainWindow->Show();
    }

    return EXIT_FAILURE;
}

void cx::Gtkmm3UIManager::CheckInvariants()
{
    INVARIANT(m_controller);
    INVARIANT(m_presenter);
    INVARIANT(m_mainWindow);
}
