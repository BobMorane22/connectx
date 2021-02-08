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
 * @file NotImplementedException.h
 * @date 2021
 *
 *************************************************************************************************/

#ifndef NOTIMPLEMENTEDEXCEPTION_H_E60FBB1F_01F8_425F_8129_762D383E89AC
#define NOTIMPLEMENTEDEXCEPTION_H_E60FBB1F_01F8_425F_8129_762D383E89AC

#include <stdexcept>
#include <string>

namespace cxunit
{

/*********************************************************************************************//**
 * @brief Exception class to represent a function, or method, that has not yet been implemented.
 *        
 * Typical use is in mocks, it which we only need to implement a subset of the interface.
 * Unused method can throw this exception.
 *
 ************************************************************************************************/
class NotImplementedException : public std::logic_error
{

public:

    /******************************************************************************************//**
     * @brief Constructor.
     *
     ********************************************************************************************/
    NotImplementedException();

};

} // namespace cxunit

#endif // NOTIMPLEMENTEDEXCEPTION_H_E60FBB1F_01F8_425F_8129_762D383E89AC
