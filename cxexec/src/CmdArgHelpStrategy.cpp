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
 * @file CmdArgHelpStrategy.cpp
 * @date 2019
 *
 *************************************************************************************************/

#include <cstdlib>
#include <iostream>

#include <cxexec/CmdArgHelpStrategy.h>

int cx::CmdArgHelpStrategy::Handle()
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
