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
 * @file CmdArgVersionStrategy.cpp
 * @date 2019
 *
 *************************************************************************************************/

#include <cstdlib>
#include <iostream>

#include <CmdArgVersionStrategy.h>

namespace
{

const std::string VERSION = "v0.5";
const std::string COPYRIGHT_OWNER = "Eric Poirier";
const std::string COPYRIGHT_YEAR = "2019";

} // namespace

int cx::CmdArgVersionStrategy::Handle()
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
