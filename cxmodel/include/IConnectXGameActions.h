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
 * @file IGameActions.h
 * @date 2020
 *
 *************************************************************************************************/

#ifndef IGAMEACTIONS_H_49B2D12C_4951_4989_AFE9_870A3940ED8F
#define IGAMEACTIONS_H_49B2D12C_4951_4989_AFE9_870A3940ED8F

#include "NewGameInformation.h"

namespace cxmodel
{

/*********************************************************************************************//**
 * @brief Interface for Connect X user game actions.
 *
 * This interface is a collection of all actions a user can do.
 *
 ************************************************************************************************/
class IConnectXGameActions
{

public:

    /******************************************************************************************//**
     * @brief Destructor.
     *
     ********************************************************************************************/
    virtual ~IConnectXGameActions() = default;

    /******************************************************************************************//**
     * @brief Creates a new game.
     *
     * @param p_gameInformation The necessary information to create a game.
     *
     ********************************************************************************************/
    virtual void CreateNewGame(const NewGameInformation& p_gameInformation) = 0;

    /******************************************************************************************//**
     * @brief Drops a chip in the game board.
     *
     * @param p_chip   The chip to drop.
     * @param p_column The column in which to drop the chip.
     *
     ********************************************************************************************/
    virtual void DropChip(const cxmodel::IChip& p_chip, size_t p_column) = 0;

    /******************************************************************************************//**
     * @brief Ends the current game.
     *
     * When a game is ended, all of its context (i.e. players, board status, etc) is cleared as
     * if no game had ever been created. Use, for example, when a game is completed (won or tied)
     * and that you want to make a new game available.
     *
     ********************************************************************************************/
    virtual void EndCurrentGame() = 0;

    /******************************************************************************************//**
     * @brief Reinitializes the current game.
     *
     * When a game is reinitialized, its initial context is brought back as the actual context,
     * as if the game had just been started.
     *
     ********************************************************************************************/
    virtual void ReinitializeCurrentGame() = 0;

};

} // namespace cxmodel

#endif // IGAMEACTIONS_H_49B2D12C_4951_4989_AFE9_870A3940ED8F
