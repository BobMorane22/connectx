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
 * @file IGameResolutionDialogController.h
 * @date 2020
 *
 *************************************************************************************************/

#ifndef IGAMERESOLUTIONDIALOGCONTROLLER_H_95FD78FD_1348_4332_962B_3433710806E5
#define IGAMERESOLUTIONDIALOGCONTROLLER_H_95FD78FD_1348_4332_962B_3433710806E5

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
class IGameResolutionDialogController
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
    virtual ~IGameResolutionDialogController() = default;

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
    virtual void OnNewGameRequested() = 0;

};

} // namespace cxgui

#endif // IGAMERESOLUTIONDIALOGCONTROLLER_H_95FD78FD_1348_4332_962B_3433710806E5
