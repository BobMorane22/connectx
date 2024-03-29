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

#include <cxinv/assertion.h>
#include <cxlog/IChainLogging.h>
#include <cxexec/Application.h>
#include <cxexec/CmdArgWorkflowFactory.h>
#include <cxexec/CmdArgNoStrategy.h>

cx::Application::Application(int argc,
                             char *argv[],
                             cx::ModelReferences& p_model,
                             cxlog::ILogger& p_logger)
{
    PRECONDITION(argc >= 1);
    PRECONDITION(argv);

    CmdArgWorkflowFactory factory;

    m_workflow = factory.Create(argc, argv, p_model, p_logger);

    POSTCONDITION(m_workflow);
}

int cx::Application::Run()
{
    if(m_workflow)
    {
        return m_workflow->Handle();
    }

    const auto workflow = std::make_unique<cx::CmdArgNoStrategy>();

    INVARIANT(m_workflow);

    return workflow->Handle();
}
