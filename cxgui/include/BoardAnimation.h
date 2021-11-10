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
 * @file BoardAnimation.h
 * @date 2021
 *
 *************************************************************************************************/

#ifndef BOARDANIMATION_H_6A5C10D5_BDB2_4709_8B3F_3493764805CC
#define BOARDANIMATION_H_6A5C10D5_BDB2_4709_8B3F_3493764805CC

namespace cxgui
{

/******************************************************************************************//**
 * @brief Animations the board can perform.
 *
 *********************************************************************************************/
enum class BoardAnimation
{
    GAME_REINITIALIZED,
    GAME_WON,
    MOVE_CHIP_LEFT_ONE_COLUMN,
    MOVE_CHIP_RIGHT_ONE_COLUMN,
    DROP_CHIP,
    UNDO_DROP_CHIP,
    REDO_DROP_CHIP,
};

} // namespace cxgui

#endif // BOARDANIMATION_H_6A5C10D5_BDB2_4709_8B3F_3493764805CC
