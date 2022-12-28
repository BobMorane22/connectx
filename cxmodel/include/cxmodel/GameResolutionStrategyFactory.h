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
 * @file GameResolutionStrategyFactory.h
 * @date 2020
 *
 *************************************************************************************************/

#ifndef GAMERESOLUTIONSTRATEGYFACTORY_H_CA3F96EF_84E2_4D20_BFF9_6D0FBB35DB44
#define GAMERESOLUTIONSTRATEGYFACTORY_H_CA3F96EF_84E2_4D20_BFF9_6D0FBB35DB44

#include <memory>
#include <vector>

#include "IBoard.h"
#include "IGameResolutionStrategy.h"
#include "IPlayer.h"

namespace cxmodel
{

/*********************************************************************************************//**
 * @brief Different game resolutions.
 *
 ************************************************************************************************/
enum class GameResolution
{
    WIN,
    TIE,
};

/*********************************************************************************************//**
 * @brief Factory that creates game resolution instances.
 *
 ************************************************************************************************/
class GameResolutionStrategyFactory final
{

public:

    /******************************************************************************************//**
     * @brief Create an instance of a `IGameResolutionStrategy` object according to a resolution.
     *
     * @pre
     *      The in-a-row value is bigger than 2 and fits into a signed integer.
     * @pre
     *      The number of players is at least 2.
     *
     * @param p_board
     *      The game board.
     * @param p_inARowValue
     *      The in-a-row value.
     * @param p_players
     *      A list of players.
     * @param p_takenPositions
     *      A list of all taken positions on the board.
     * @param p_resolution
     *      The wanted game resolution.
     *
     * @return
     *      The newly created game resolution strategy.
     *
     ********************************************************************************************/
    [[nodiscard]] static std::unique_ptr<cxmodel::IGameResolutionStrategy> Make(const IBoard& p_board,
                                                                                size_t p_inARowValue,
                                                                                const std::vector<std::shared_ptr<IPlayer>>& p_players,
                                                                                const std::vector<IBoard::Position>& p_takenPositions,
                                                                                GameResolution p_resolution);

};

} // namespace cxmodel

#endif // GAMERESOLUTIONSTRATEGYFACTORY_H_CA3F96EF_84E2_4D20_BFF9_6D0FBB35DB44
