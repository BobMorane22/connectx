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
 * @file main.cpp
 * @date 2019
 *
 *************************************************************************************************/

#include <iostream>
#include <string>
#include <vector>

#include <cxmodel/include/HelloWorld.h>

const std::string VERSION = "v0.2";
const std::string COPYRIGHT_OWNER = "Eric Poirier";
const std::string COPYRIGHT_YEAR = "2019";

const std::string HELP_ARG = "--help";
const std::string VERSION_ARG = "--version";

int main(int argc, char const *argv[])
{
    const bool noArguments = argc == 1;

    if(argc > 1)
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
            std::cout << "Connect X: invalid option '" + firstInvalidArgument + "'" << std::endl;

            return EXIT_FAILURE;
        }

        if(arguments[0] == HELP_ARG)
        {
            std::cout << "Usage: connectx [OPTION]..." << std::endl
            << std::endl
            << "Possible arguments:" << std::endl
            << "--help        display this help and exit" << std::endl
            << "--version     output version information and exit" << std::endl
            << std::endl
            << "Exit status:" << std::endl
            << " 0 if OK," << std::endl
            << " 1 if problems." << std::endl
            << std::endl
            << "Connect X available at: <https://github.com/BobMorane22/connectx/>" << std::endl;

            return EXIT_SUCCESS;

        }
        if(arguments[0] == VERSION_ARG)
        {
            std::cout << "Connect X " << VERSION << std::endl
            << std::endl
            << "Copyright (C) " << COPYRIGHT_YEAR << " " <<  COPYRIGHT_OWNER << "." << std::endl
            << "License GPLv3+: GNU GPL version 3 or later <gnu.org/licenses/gpl.html>." << std::endl
            << "This is free software: you are free to change and redistribute it." << std::endl
            << "There is NO WARRANTY, to the extent permitted by law." << std::endl
            << std::endl
            << "Written by " << COPYRIGHT_OWNER << "." << std::endl;

            return EXIT_SUCCESS;
        }
    }
    else if(!noArguments)
    {
        std::cout << "Connect X: Error parsing arguments." << std::endl;

        return EXIT_FAILURE;
    }

    const HelloWorld hw;
    const std::string HELLO_WORLD = hw.Make();

    std::cout << HELLO_WORLD << std::endl;

    return EXIT_SUCCESS;
}
