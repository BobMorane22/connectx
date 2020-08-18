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
 * @file CmdArgWorkflowFactory.cpp
 * @date 2019
 *
 *************************************************************************************************/

#include <algorithm>
#include <memory>
#include <vector>

#include <cxinv/include/assertion.h>
#include <cxlog/include/ILogger.h>

#include <CmdArgWorkflowFactory.h>

#include <CmdArgHelpStrategy.h>
#include <CmdArgInvalidStrategy.h>
#include <CmdArgMainStrategy.h>
#include <CmdArgNoStrategy.h>
#include <CmdArgVerboseStrategy.h>
#include <CmdArgVersionStrategy.h>

namespace
{

const std::string HELP_ARG    = "--help";
const std::string VERSION_ARG = "--version";
const std::string VERBOSE_ARG = "--verbose";

} // namespace cx


std::unique_ptr<cx::ICmdArgWorkflowStrategy> cx::CmdArgWorkflowFactory::Create(int argc,
                                                                               char *argv[],
                                                                               cxmodel::Subject& p_modelAsSubject,
                                                                               cxmodel::IConnectXGameActions& p_modelAsGameActions,
                                                                               cxmodel::IVersionning& p_modelAsVersionning,
                                                                               cxlog::ILogger& p_logger)
{
    std::unique_ptr<cx::ICmdArgWorkflowStrategy> strategy = std::make_unique<CmdArgNoStrategy>();

    if(argc < 1)
    {
        strategy = std::make_unique<CmdArgNoStrategy>();
    }
    else if(argc == 1)
    {
        strategy = std::make_unique<CmdArgMainStrategy>(argc, argv, p_modelAsSubject, p_modelAsGameActions);
    }
    else
    {
        std::vector<std::string> arguments;
        for(int i = 1; i < argc; ++i)
        {
            arguments.push_back(argv[i]);
        }

        bool hasInvalidArguments = false;
        std::string firstInvalidArgument;
        for(const auto& argument : arguments)
        {
            if(argument != HELP_ARG && argument != VERSION_ARG && argument != VERBOSE_ARG)
            {
                hasInvalidArguments = true;
                firstInvalidArgument = argument;

                break;
            }
        }

        if(hasInvalidArguments)
        {
            strategy = std::make_unique<CmdArgInvalidStrategy>(firstInvalidArgument);
        }
        else
        {
            const auto helpIt = std::find(arguments.cbegin(), arguments.cend(), HELP_ARG);
            const auto versionIt = std::find(arguments.cbegin(), arguments.cend(), VERSION_ARG);
            const auto verboseIt = std::find(arguments.cbegin(), arguments.cend(), VERBOSE_ARG);

            if(helpIt != arguments.cend() || versionIt != arguments.cend())
            {
                // First, we deal with the --help and --version arguments, which precede any other:
                const std::size_t helpPos = std::distance(arguments.cbegin(), helpIt);
                const std::size_t versionPos = std::distance(arguments.cbegin(), versionIt);

                if(helpPos < versionPos)
                {
                    strategy = std::make_unique<CmdArgHelpStrategy>();
                }
                else if(helpPos > versionPos)
                {
                    strategy = std::make_unique<CmdArgVersionStrategy>(p_modelAsVersionning);
                }
                else
                {
                    ASSERT_ERROR_MSG("--help and --version can't have the same position");
                }
            }
            else
            {
                ASSERT_MSG(verboseIt != arguments.cend(), "There must be at least one argument.");

                strategy = std::make_unique<CmdArgVerboseStrategy>(argc,
                                                                   argv,
                                                                   p_modelAsSubject,
                                                                   p_modelAsGameActions,
                                                                   p_modelAsVersionning,
                                                                   &p_logger);
            }
        }
    }

    POSTCONDITION(strategy != nullptr);

    return strategy;
}
