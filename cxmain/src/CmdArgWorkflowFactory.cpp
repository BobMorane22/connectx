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

#include <memory>
#include <vector>

#include <CmdArgWorkflowFactory.h>

#include <CmdArgHelpStrategy.h>
#include <CmdArgInvalidStrategy.h>
#include <CmdArgMainStrategy.h>
#include <CmdArgNoStrategy.h>
#include <CmdArgVersionStrategy.h>

namespace
{

const std::string HELP_ARG = "--help";
const std::string VERSION_ARG = "--version";

} // namespace cx


std::unique_ptr<cx::ICmdArgWorkflowStrategy> cx::CmdArgWorkflowFactory::Create(int argc, char const *argv[])
{
    if(argc < 1)
    {
        return std::make_unique<CmdArgNoStrategy>();
    }
    else if(argc == 1)
    {
        return std::make_unique<CmdArgMainStrategy>();
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
            if(argument != HELP_ARG && argument != VERSION_ARG)
            {
                hasInvalidArguments = true;
                firstInvalidArgument = argument;

                break;
            }
        }

        if(hasInvalidArguments)
        {
            return std::make_unique<CmdArgInvalidStrategy>(firstInvalidArgument);
        }

        if(arguments.front() == HELP_ARG)
        {
            return std::make_unique<CmdArgHelpStrategy>();

        }

        if(arguments.front() == VERSION_ARG)
        {
            return std::make_unique<CmdArgVersionStrategy>();
        }
    }

    return std::make_unique<CmdArgNoStrategy>();
}
