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
 * @file NewGameInformation.h
 * @date 2020
 *
 *************************************************************************************************/

#ifndef NEWGAMEINFORMATION_H_BE24FB43_1A63_4A5D_BA34_DA52C92DFB4A
#define NEWGAMEINFORMATION_H_BE24FB43_1A63_4A5D_BA34_DA52C92DFB4A

#include <string>
#include <vector>

#include "Player.h"

namespace cxmodel
{

/*********************************************************************************************//**
 * @brief Information describing a new Connect X game.
 *
 * This contains all the necessary information to create a new Connect X game.
 *
 ************************************************************************************************/
class NewGameInformation
{

public:

    /******************************************************************************************//**
     * @brief Add a new player to the game.
     *
     * @param p_newPlayer The new player's information.
     *
     * @return The updated number of players registered in the game.
     *
     ********************************************************************************************/
    std::size_t AddPlayer(const Player& p_newPlayer);

    /******************************************************************************************//**
     * @brief New players accessor.
     *
     * @return A list of registered players informations.
     *
     ********************************************************************************************/
    std::vector<Player> GetNewPlayers() const;

    /******************************************************************************************//**
     * @brief Number of new players accessor.
     *
     * @return The number of new players registered.
     *
     ********************************************************************************************/
    size_t GetNbOfNewPlayers() const;

public:

    size_t m_gridWidth;
    size_t m_gridHeight;
    size_t m_inARowValue;

private:

    std::vector<Player> m_playersInformation;
};

/*********************************************************************************************//**
 * @brief Equal-to operator.
 *
 * @param p_lhs The first game information to compare with.
 * @param p_rhs The second game information to compare with.
 *
 * @return true if both game informations are the same, false otherwise.
 *
 * Two game information match if all of their data match and that player informations are
 * registered in the same order.
 *
 ************************************************************************************************/
bool operator==(const NewGameInformation& p_lhs, const NewGameInformation& p_rhs);

/*********************************************************************************************//**
 * @brief Not-equal-to operator.
 *
 * @param p_lhs The first game information to compare with.
 * @param p_rhs The second game information to compare with.
 *
 * @return true if both game informations are different, false otherwise.
 *
 * Two game informations do not match if any of their data does not match or that player
 * informations are not registered in the same order.
 *
 ************************************************************************************************/
bool operator!=(const NewGameInformation& p_lhs, const NewGameInformation& p_rhs);

} // namespace cxmodel

#endif // NEWGAMEINFORMATION_H_BE24FB43_1A63_4A5D_BA34_DA52C92DFB4A
