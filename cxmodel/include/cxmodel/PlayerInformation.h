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
 * @file PlayerInformation.h
 * @date 2020
 *
 *************************************************************************************************/

#ifndef PLAYERINFORMATION_H_B54E9667_5C5B_45B9_BF0A_CA42FAA168FB
#define PLAYERINFORMATION_H_B54E9667_5C5B_45B9_BF0A_CA42FAA168FB

#include <vector>

#include <cxinv/assertion.h>

#include "Player.h"

namespace cxmodel
{

using PlayersList = std::vector<Player>;

/*********************************************************************************************//**
 * @brief Data structure to hold all player related information.
 *
 ************************************************************************************************/
struct PlayerInformation final
{
    /******************************************************************************************//**
     * @brief Constructor.
     *
     * @pre The active player index is different than the next player index.
     *
     * @param p_players           The player list.
     * @param p_activePlayerIndex The active player's index in the list.
     * @param p_nextPlayerIndex   The next player's index in the list.
     *
     ********************************************************************************************/
    PlayerInformation(const PlayersList& p_players,
                      size_t p_activePlayerIndex,
                      size_t p_nextPlayerIndex)
    : m_players{p_players}
    , m_activePlayerIndex{p_activePlayerIndex}
    , m_nextPlayerIndex{p_nextPlayerIndex}
    {
        PRECONDITION(p_activePlayerIndex != p_nextPlayerIndex);
    }

    PlayersList m_players;
    size_t m_activePlayerIndex;
    size_t m_nextPlayerIndex;
};

}

#endif // PLAYERINFORMATION_H_B54E9667_5C5B_45B9_BF0A_CA42FAA168FB
