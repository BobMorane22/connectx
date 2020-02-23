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
 * @file IStatusBar.h
 * @date 2020
 *
 *************************************************************************************************/

#ifndef ISTATUSBAR_H_B9E6A5FA_CB18_4646_9BD1_F38CE15F1A62
#define ISTATUSBAR_H_B9E6A5FA_CB18_4646_9BD1_F38CE15F1A62

#include <string>

#include <cxmodel/include/IObserver.h>

/*********************************************************************************************//**
 * @brief DESCRIPTION
 *
 * @invariant
 * @invariant
 *
 * DESCRIPTION
 *
 ************************************************************************************************/
class IStatusBar : public cxmodel::IObserver
{

public:

    /******************************************************************************************//**
     * @brief Destructor.
     *
     ********************************************************************************************/
    virtual ~IStatusBar() = default;

    /******************************************************************************************//**
     * @brief DESCRIPTION
     *
     * @pre
     * @post
     *
     * @param
     * @param
     *
     * @return
     *
     * DESCRIPTION
     *
     ********************************************************************************************/
    virtual void SetLastUserActionStatus(const std::string& p_lastUserActionDescription) = 0;

};

#endif // ISTATUSBAR_H_B9E6A5FA_CB18_4646_9BD1_F38CE15F1A62
