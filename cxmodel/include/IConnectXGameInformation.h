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
 * @file IConnectXGameInformation.h
 * @date 2020
 *
 *************************************************************************************************/

#ifndef IGAMEINFORMATION_H_9970E71B_B32B_4B39_8363_50B66B9CE1C3
#define IGAMEINFORMATION_H_9970E71B_B32B_4B39_8363_50B66B9CE1C3

#include "Player.h"

namespace cxmodel
{

/*********************************************************************************************//**
 * @brief Interface for querying current game information.
 *
 * All the information queried is on the current state of the game. On each player turn, it
 * may be updated.
 *
 ************************************************************************************************/
class IConnectXGameInformation
{

public:

    /******************************************************************************************//**
     * @brief Destructor.
     *
     ********************************************************************************************/
    virtual ~IConnectXGameInformation() = default;

    /******************************************************************************************//**
     * @brief Gets the current grid's height.
     *
     * @return The current grid's height.
     *
     ********************************************************************************************/
    virtual size_t GetCurrentGridHeight() const = 0;

    /******************************************************************************************//**
     * @brief Gets the current grid's width.
     *
     * @return The current grid's width.
     *
     ********************************************************************************************/
    virtual size_t GetCurrentGridWidth() const = 0;

    /******************************************************************************************//**
     * @brief Gets the current in-a-row value.
     *
     * @return The current in-a-row value.
     *
     ********************************************************************************************/
    virtual size_t GetCurrentInARowValue() const = 0;

    /******************************************************************************************//**
     * @brief Gets the active players (the one who's turn is the current).
     *
     * @return The active player.
     *
     ********************************************************************************************/
    virtual const Player& GetActivePlayer() const = 0;

    /******************************************************************************************//**
     * @brief Gets the next player (the one who's turn is the next).
     *
     * @return The next player.
     *
     ********************************************************************************************/
    virtual const Player& GetNextPlayer() const = 0;

    /******************************************************************************************//**
     * @brief Gets the chip at some specific location on the board. If the location does not
     *        exist on the board, a transparent chip is returned.
     *
     * @param p_row    The chip's row location on the board.
     * @param p_column The chip's column location on the board.
     *
     * @return The chip.
     *
     ********************************************************************************************/
    virtual const IChip& GetChip(size_t p_row, size_t p_column) const = 0;

    /******************************************************************************************//**
     * @brief Indicates if the Connect X game, in its current state, is won by any player.
     *
     * @return `true` if the game is won, `false` otherwise.
     *
     ********************************************************************************************/
    virtual bool IsWon() const = 0;

    /******************************************************************************************//**
     * @brief Indicates if the Connect X game, in its current state, is a tie between two players.
     *
     * @return `true` if the game is a tie, `false` otherwise.
     *
     ********************************************************************************************/
    virtual bool IsTie() const = 0;

};

} // namespace cxmodel

#endif // IGAMEINFORMATION_H_9970E71B_B32B_4B39_8363_50B66B9CE1C3
