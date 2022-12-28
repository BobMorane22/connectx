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
 * @file IChip.h
 * @date 2020
 *
 *************************************************************************************************/

#ifndef ICHIP_H_FFD62B76_D91D_40E6_8195_BA1FE9F76597
#define ICHIP_H_FFD62B76_D91D_40E6_8195_BA1FE9F76597

#include "ChipColor.h"

namespace cxmodel
{

/*********************************************************************************************//**
 * @brief Interface representing chips that can be used to play Connect X.
 *
 * To play the Connect X game, players must drop 'chips' (or pieces) into the board to create a
 * winning series of adjacent same pieces. This interface represents any 'chip' that can be used
 * to play the Connect X game.
 *
 ************************************************************************************************/
class IChip
{

public:

    /******************************************************************************************//**
     * @brief Destructor.
     *
     ********************************************************************************************/
    virtual ~IChip() = default;

    /******************************************************************************************//**
     * @brief Color accessor.
     *
     * @return
     *      The chip color.
     *
     ********************************************************************************************/
    virtual ChipColor GetColor() const = 0;

    /******************************************************************************************//**
     * @brief Resets the chip as if it had never been set.
     *
     * After a call to this method, the chip color should be transparent.
     *
     ********************************************************************************************/
    virtual void Reset() = 0;
};

/******************************************************************************************//**
 * @brief Equal-to operator.
 *
 * @param p_lhs
 *      The left hand side chip.
 * @param p_rhs
 *      The right hand side chip.
 *
 * @return
 *      `true` if the chips are considered equal, `false` otherwise.
 *
 ********************************************************************************************/
[[nodiscard]] bool operator==(const IChip& p_lhs, const IChip& p_rhs);

/******************************************************************************************//**
 * @brief Not-equal-to operator.
 *
 * @param p_lhs
 *      The left hand side chip.
 * @param p_rhs
 *      The right hand side chip.
 *
 * @return
 *      `true` if the chips are considered NOT equal, `false` otherwise.
 *
 ********************************************************************************************/
[[nodiscard]] bool operator!=(const IChip& p_lhs, const IChip& p_rhs);

} // namespace cxmodel

#endif // ICHIP_H_FFD62B76_D91D_40E6_8195_BA1FE9F76597
