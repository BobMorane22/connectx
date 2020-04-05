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

#include <cxgui/include/MainWindow.h>
#include <cxgui/include/MainWindowController.h>
#include <cxgui/include/MainWindowPresenter.h>
#include <cxinv/include/assertion.h>
#include <cxmodel/include/IModel.h>

#include <GtkmmUIManager.h>

cx::GtkmmUIManager::GtkmmUIManager(int argc, char *argv[], cxmodel::IModel& p_model)
{
    PRECONDITION(argc > 0);
    PRECONDITION(argv != nullptr);

    m_controller = std::make_unique<cxgui::MainWindowController>(p_model);
    m_presenter = std::make_unique<cxgui::MainWindowPresenter>();
    m_mainWindow = std::make_unique<cxgui::MainWindow>(argc, argv, p_model, *m_controller, *m_presenter);

    p_model.Attach(m_presenter.get());
    m_presenter->Attach(m_mainWindow.get());

    POSTCONDITION(m_mainWindow != nullptr);

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

void cx::GtkmmUIManager::CheckInvariants()
{
    INVARIANT(m_controller != nullptr);
    INVARIANT(m_presenter != nullptr);
    INVARIANT(m_mainWindow != nullptr);
}
