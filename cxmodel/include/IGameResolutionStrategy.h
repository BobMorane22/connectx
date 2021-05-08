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
 * @file IGameResolutionStrategy.h
 * @date 2020
 *
 *************************************************************************************************/

#ifndef IGAMERESOLUTIONSTRATEGY_H_E0ECD7E2_8D97_422F_9387_79D4DB55D3DC
#define IGAMERESOLUTIONSTRATEGY_H_E0ECD7E2_8D97_422F_9387_79D4DB55D3DC

namespace cxmodel
{
    class Player;
}

namespace cxmodel
{

/*********************************************************************************************//**
 * @brief Interface for game resolution strategies.
 *
 * A game resolution is a way by which a game can be resolved (a win, a tie, etc).
 *
 ************************************************************************************************/
class IGameResolutionStrategy
{

public:

    /******************************************************************************************//**
     * @brief Destructor.
     *
     ********************************************************************************************/
    virtual ~IGameResolutionStrategy() = default;

    /******************************************************************************************//**
     * @brief Handles the game resolution.
     *
     * @pre The active player passed as an argument is one of the players in the game.
     *
     * @param p_activePlayer The active player. Note that if some player just dropped a chip,
     *                       the active is no longer that player, but the one after.
     *
     * @return `true` if the game is resolved, `false` if it goes on.
     *
     ********************************************************************************************/
    virtual bool Handle(const cxmodel::Player& p_activePlayer) const = 0;

};

} // namespace cxmodel

#endif // IGAMERESOLUTIONSTRATEGY_H_E0ECD7E2_8D97_422F_9387_79D4DB55D3DC
