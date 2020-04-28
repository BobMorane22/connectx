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

namespace cxmodel
{

/*********************************************************************************************//**
 * @brief Information for one player.
 *
 ************************************************************************************************/
struct PlayerInformation
{

    /******************************************************************************************//**
     * @brief Constructor.

     * @param p_name      The player's name.
     * @param p_discColor The player's disc color.
     *
     ********************************************************************************************/
    PlayerInformation(const std::string& p_name, const std::string& p_discColor)
    : m_name(p_name)
    , m_discColor(p_discColor)
    {
        // Nothing to do...
    }

    std::string m_name;
    std::string m_discColor;
};

/*********************************************************************************************//**
 * @brief Information describing a new Connect X game.
 *
 * This contains all the necessary information to create a new Connect X game.
 *
 ************************************************************************************************/
class NewGameInformation
{

public:

    using PlayersInformation = std::vector<PlayerInformation>;

    /******************************************************************************************//**
     * @brief Add a player to the game.
     *
     * @param p_playerInformation The new player's information.
     *
     * @return The updated number of players registered in the game.
     *
     ********************************************************************************************/
    std::size_t AddPlayer(const PlayerInformation& p_playerInformation);

    /******************************************************************************************//**
     * @brief Players information accessor.
     *
     * @return A list of registered players informations.
     *
     ********************************************************************************************/
    PlayersInformation GetPlayersInformation() const;

public:

    size_t m_gridWidth;
    size_t m_gridHeight;
    size_t m_inARowValue;

private:

    PlayersInformation m_playersInformation;
};

} // namespace cxmodel

#endif // NEWGAMEINFORMATION_H_BE24FB43_1A63_4A5D_BA34_DA52C92DFB4A
