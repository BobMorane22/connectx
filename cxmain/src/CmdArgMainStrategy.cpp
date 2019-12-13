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
 * @file CmdArgMainStrategy.cpp
 * @date 2019
 *
 *************************************************************************************************/

#include <cstdlib>
#include <iostream>

#include <cxinv/include/assertion.h>
#include <cxmodel/include/HelloWorld.h>

#include <CmdArgMainStrategy.h>

cx::CmdArgMainStrategy::CmdArgMainStrategy(int argc, char *argv[])
{
    PRECONDITION(argc > 0);
    PRECONDITION(argv != nullptr);

    m_uiMgr = std::make_unique<cx::GtkmmUIManager>(argc, argv);

    POSTCONDITION(m_uiMgr != nullptr);
}

int cx::CmdArgMainStrategy::Handle()
{
    INVARIANT(m_uiMgr != nullptr);

    if(m_uiMgr)
    {
        return m_uiMgr->Manage();
    }

    return EXIT_FAILURE;
}
