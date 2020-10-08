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
 * @file IGameViewController.h
 * @date 2020
 *
 *************************************************************************************************/

#ifndef IGAMEVIEWCONTROLLER_H_3C41DCA5_1218_4228_A8C9_545FC5071BD3
#define IGAMEVIEWCONTROLLER_H_3C41DCA5_1218_4228_A8C9_545FC5071BD3

#include <cxmodel/include/ChipColor.h>

namespace cxgui
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
class IGameViewController
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
    virtual ~IGameViewController() = default;

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
    virtual void OnDown(const cxmodel::ChipColor& p_chipColor, size_t p_column) = 0;
};

} // namespace cxgui

#endif // IGAMEVIEWCONTROLLER_H_3C41DCA5_1218_4228_A8C9_545FC5071BD3
