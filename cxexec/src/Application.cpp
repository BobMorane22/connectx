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
 * @file Application.cpp
 * @date 2019
 *
 *************************************************************************************************/

#include <memory>

#include <cxinv/include/assertion.h>
#include <cxlog/include/IChainLogging.h>

#include <Application.h>
#include <CmdArgWorkflowFactory.h>
#include <CmdArgNoStrategy.h>

cx::Application::Application(int argc,
                             char *argv[],
                             cxmodel::Subject& p_modelAsSubject,
                             cxmodel::IConnectXGameActions& p_modelAsGameActions,
                             cxmodel::IConnectXLimits& p_modelAsLimits,
                             cxmodel::IVersioning& p_modelAsVersionning,
                             cxlog::ILogger& p_logger)
{
    PRECONDITION(argc >= 1);
    PRECONDITION(argv != nullptr);

    CmdArgWorkflowFactory factory;

    m_workflow = factory.Create(argc,
                                argv,
                                p_modelAsSubject,
                                p_modelAsGameActions,
                                p_modelAsLimits,
                                p_modelAsVersionning,
                                p_logger);

    POSTCONDITION(m_workflow != nullptr);
}

int cx::Application::Run()
{
    if(m_workflow)
    {
        return m_workflow->Handle();
    }

    const auto workflow = std::make_unique<cx::CmdArgNoStrategy>();

    INVARIANT(m_workflow != nullptr);

    return workflow->Handle();
}
