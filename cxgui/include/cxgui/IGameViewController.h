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

#include <cxmodel/ChipColor.h>

namespace cxgui
{

/*********************************************************************************************//**
 * @brief Interface for the game view controller.
 *
 ************************************************************************************************/
class IGameViewController
{

public:

    /******************************************************************************************//**
     * @brief Destructor.
     *
     ********************************************************************************************/
    virtual ~IGameViewController() = default;

    /******************************************************************************************//**
     * @brief Handler for a disc drop.
     *
     * @pre The chip color passed as argument is not transparent.
     *
     * @param p_chipColor Then color of the dropped chip.
     * @param p_column    The column in which to drop the chip.
     *
     ********************************************************************************************/
    virtual void OnDown(const cxmodel::ChipColor& p_chipColor, size_t p_column) = 0;

    /******************************************************************************************//**
     * @brief Handler for left move by one column.
     *
     ********************************************************************************************/
    virtual void OnMoveLeftOneColumn() = 0;

    /******************************************************************************************//**
     * @brief Handler for right move by one column.
     *
     ********************************************************************************************/
    virtual void OnMoveRightOneColumn() = 0;

    /******************************************************************************************//**
     * @brief Handler for a new game request.
     *
     ********************************************************************************************/
    virtual void OnNewGame() = 0;

    /******************************************************************************************//**
     * @brief Handler for a current game reinitialization.
     *
     ********************************************************************************************/
    virtual void OnReinitializeCurrentGame() = 0;

    /******************************************************************************************//**
     * @brief Handler for undoing the last operation.
     *
     ********************************************************************************************/
    virtual void OnUndo() = 0;

    /******************************************************************************************//**
     * @brief Handler for redoing the last undoed operation.
     *
     ********************************************************************************************/
    virtual void OnRedo() = 0;

};

} // namespace cxgui

#endif // IGAMEVIEWCONTROLLER_H_3C41DCA5_1218_4228_A8C9_545FC5071BD3
