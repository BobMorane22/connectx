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

#include <cxinv/include/assertion.h>

#include <GtkmmUIManager.h>

cx::GtkmmUIManager::GtkmmUIManager(int argc, char *argv[])
{
    PRECONDITION(argc > 0);
    PRECONDITION(argv != nullptr);

    m_mainWindow = std::make_unique<cxgui::MainWindow>(argc, argv);

    POSTCONDITION(m_mainWindow != nullptr);
}

int cx::GtkmmUIManager::Manage()
{
    INVARIANT(m_mainWindow != nullptr);

    if(m_mainWindow)
    {
        return m_mainWindow->Show();
    }

    return EXIT_FAILURE;
}
