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
 * Inspired by the technique presented in the book "Professional CMake : A Practical Guide",
 * version 1.0.0 by Craig Scott. See "Source Code Access to Version Details" in Chapter 19.
 * 
 * @file version.h
 * @date 2021
 *
 *************************************************************************************************/

#ifndef VERSION_H_A110E2C5_E337_4BE2_B076_A860B92A5D19                                                                                                                                                             
#define VERSION_H_A110E2C5_E337_4BE2_B076_A860B92A5D19                                                                                                                                                             

namespace cxmodel
{

/**********************************************************************************************//**
 * @brief Gets the major version number.
 *
 * @return The major version number.
 *
 *************************************************************************************************/
unsigned int GetVersionMajor();

/**********************************************************************************************//**
 * @brief Gets the minor version number.
 *
 * @return The minor version number.
 *
 *************************************************************************************************/
unsigned int GetVersionMinor();

} // namespace cxmodel

#endif // VERSION_H_A110E2C5_E337_4BE2_B076_A860B92A5D19 
