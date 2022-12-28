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

#include "IPlayer.h"

namespace cxmodel
{

/*********************************************************************************************//**
 * @brief Information describing a new Connect X game.
 *
 * This contains all the necessary information to create a new Connect X game. The class is
 * designed to take ownership of the data.
 *
 ************************************************************************************************/
struct NewGameInformation final
{
    /** A list of Connect X players. */
    using Players = std::vector<std::shared_ptr<IPlayer>>;

    // Copying:
    NewGameInformation(const NewGameInformation&) = delete;
    NewGameInformation& operator=(const NewGameInformation&) = delete;

    /******************************************************************************************//**
     * @brief Default constructor.
     *
     ********************************************************************************************/
    NewGameInformation() = default;

    /******************************************************************************************//**
     * @brief Move constructor.
     *
     * @param p_other The game information to take ownership of.
     *
     ********************************************************************************************/
    NewGameInformation(NewGameInformation&& p_other);

    /******************************************************************************************//**
     * @brief Move assignement operator.
     *
     * @param p_other The game information to take ownership of.
     *
     * @return The assigned new game information.
     *
     ********************************************************************************************/
    NewGameInformation& operator=(NewGameInformation&& p_other);

    /******************************************************************************************//**
     * @brief Destructor.
     *
     ********************************************************************************************/
    ~NewGameInformation() = default;

    /** The board height (how many chips until a column is considered full) for the new game. */
    size_t m_gridHeight;

    /** The board width (how many chips until a row is considered full) for the new game. */
    size_t m_gridWidth;

    /** The in a in-a-row value for the new game. */
    size_t m_inARowValue;

    /** The list of players for the new game. */
    Players m_players;
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
