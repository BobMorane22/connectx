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

#include <cxinv/include/assertion.h>
#include <cxmodel/include/IConnectXGameActions.h>
#include <cxmodel/include/Subject.h>

#include <CmdArgMainStrategy.h>

cx::CmdArgMainStrategy::CmdArgMainStrategy(int argc,
                                           char *argv[],
                                           cxmodel::Subject& p_modelAsSubject,
                                           cxmodel::IConnectXGameActions& p_modelAsGameActions,
                                           cxmodel::IConnectXGameInformation& p_modelAsGameInformation,
                                           cxmodel::IConnectXLimits& p_modelAsLimits)
{
    PRECONDITION(argc > 0);
    PRECONDITION(argv);

    argc = 1;
    m_uiMgr = std::make_unique<cx::GtkmmUIManager>(argc,
                                                   argv,
                                                   p_modelAsSubject,
                                                   p_modelAsGameActions,
                                                   p_modelAsGameInformation,
                                                   p_modelAsLimits);

    POSTCONDITION(m_uiMgr);
}

int cx::CmdArgMainStrategy::Handle()
{
    INVARIANT(m_uiMgr);

    if(m_uiMgr)
    {
        return m_uiMgr->Manage();
    }

    return EXIT_FAILURE;
}
