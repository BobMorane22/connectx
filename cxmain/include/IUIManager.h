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
 * @file IUIManager.h
 * @date 2019
 *
 *************************************************************************************************/

#ifndef IUIMANAGER_H_C426182A_242D_4305_A936_DCF78C10A9F8
#define IUIMANAGER_H_C426182A_242D_4305_A936_DCF78C10A9F8

namespace cx
{

/*********************************************************************************************//**
 * @brief Interface for creating UI managers.
 *
 * Inherit from this to implement a dependent specific UI. The main should be blind to the UI
 * implementation.
 *
 ************************************************************************************************/
class IUIManager
{

public:

    /******************************************************************************************//**
     * @brief Default destructor.
     *
     ********************************************************************************************/
    virtual ~IUIManager() = default;

    /******************************************************************************************//**
     * @brief Manages the execution of the user interface.
     *
     * Manages the execution of the user interface in an implementation independent fashion.
     *
     ********************************************************************************************/
    virtual int Manage() = 0;

};

} // namespace cx

#endif // IUIMANAGER_H_C426182A_242D_4305_A936_DCF78C10A9F8
