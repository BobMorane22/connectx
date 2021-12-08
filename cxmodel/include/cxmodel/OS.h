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
 * @file OS.h
 * @date 2020
 *
 *************************************************************************************************/

#ifndef OS_H_706C5CF5_7AE1_4F00_88E3_BD79BA7F2F6A
#define OS_H_706C5CF5_7AE1_4F00_88E3_BD79BA7F2F6A

#include <string>

namespace cxmodel
{

/******************************************************************************************//**
 * @brief Produces a string containing the path for the current executable.
 *
 * @param p_pathOnly @c true if only the path is needed, @c false if the executable name is to be
 *                   included in the string.
 *
 * @return The path where the current executable is located, as a string.
 *
 * @note As of now, only barely supported on Linux (only tested on Ubuntu 16.04 and 18.04).
 *
 ********************************************************************************************/
std::string GetCurrentExecutablePath(const bool p_pathOnly);

} // namespace cxmodel

#endif // OS_H_706C5CF5_7AE1_4F00_88E3_BD79BA7F2F6A
