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
 * @file GameLeftKeyHandlerStrategy.h
 * @date 2020
 *
 *************************************************************************************************/

#ifndef GAMELEFTKEYHANDLERSTRATEGY_H_2D035C6F_05E4_4C1A_B433_0FE7F72F443F
#define GAMELEFTKEYHANDLERSTRATEGY_H_2D035C6F_05E4_4C1A_B433_0FE7F72F443F

#include "IGameKeyHandlerStrategy.h"

namespace cxgui
{

/*********************************************************************************************//**
 * @brief Left key handling strategy.
 *
 ************************************************************************************************/
class GameLeftKeyHandlerStrategy : public cxgui::IGameKeyHandlerStrategy
{
    /******************************************************************************************//**
     * @brief Handler for a left key press.
     *
     * @param p_controller The game view controller.
     * @param p_gameBoard  The board to act on.
     *
     ********************************************************************************************/
    bool Handle(IGameViewController& p_controller, IBoardInformation& p_gameBoard) override;
};

} // namespace cxgui

#endif // GAMELEFTKEYHANDLERSTRATEGY_H_2D035C6F_05E4_4C1A_B433_0FE7F72F443F
