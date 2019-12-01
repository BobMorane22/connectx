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
 * @file CmdArgInvalidStrategy.cpp
 * @date 2019
 *
 *************************************************************************************************/

#include <cstdlib>
#include <iostream>

#include <CmdArgInvalidStrategy.h>

cx::CmdArgInvalidStrategy::CmdArgInvalidStrategy(const std::string& p_invalidArg) : m_invalidArg{p_invalidArg}
{
    // Nothing to do...
}

int cx::CmdArgInvalidStrategy::Handle()
{
    std::cout << "Connect X: invalid option '" + m_invalidArg + "'" << std::endl;

    return EXIT_FAILURE;
}
