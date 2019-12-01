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
 * @file IApplication.h
 * @date 2019
 *
 *************************************************************************************************/

#ifndef IAPPLICATION_H_323C05EC_2EC7_4CB7_B3E0_D9F1A57E4B7B
#define IAPPLICATION_H_323C05EC_2EC7_4CB7_B3E0_D9F1A57E4B7B

namespace cx
{

/*********************************************************************************************//**
 * @brief DESCRIPTION
 *
 * @invariant
 * @invariant
 *
 * DESCRIPTION
 *
 ************************************************************************************************/
class IApplication
{

public:

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
    virtual ~IApplication() = default;


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
    virtual int Run() = 0;

};

} // namespace cx

#endif // IAPPLICATION_H_323C05EC_2EC7_4CB7_B3E0_D9F1A57E4B7B
