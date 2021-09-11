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
 * @file IBoardAnimator.h
 * @date 2021
 *
 *************************************************************************************************/

#ifndef IBOARDANIMATOR_H_C5297993_B06E_4707_ABF4_46D42D673DA8
#define IBOARDANIMATOR_H_C5297993_B06E_4707_ABF4_46D42D673DA8

#include <cstddef>

namespace cxgui
{

class Chip;
enum class BoardAnimation;

}

namespace cxgui
{

/**********************************************************************************************//**
 * @brief Animate a Connect X game board.
 *
 * Enables board animations for Connect X.
 *
 *************************************************************************************************/
class IBoardAnimator
{

public:

    /******************************************************************************************//**
     * @brief Destructor.
     *
     *********************************************************************************************/
    virtual ~IBoardAnimator() = default;

    /******************************************************************************************//**
     * @brief Animates the chip on the board.
     *
     * @param p_direction
     *      The wanted animation.
     *
     *********************************************************************************************/
    virtual void PerformChipAnimation(BoardAnimation p_animation) = 0;

};

} // namespace cxgui

#endif // IBOARDANIMATOR_H_C5297993_B06E_4707_ABF4_46D42D673DA8
