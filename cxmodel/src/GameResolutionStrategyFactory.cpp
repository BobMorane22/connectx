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
 * @file GameResolutionStrategyFactory.cpp
 * @date 2020
 *
 *************************************************************************************************/

#include <cxinv/include/assertion.h>

#include <GameResolutionStrategyFactory.h>
#include <TieGameResolutionStrategy.h>
#include <WinGameResolutionStrategy.h>

namespace
{

// Default strategy. Should never be created.
class NoGameResolutionStrategy final : public cxmodel::IGameResolutionStrategy
{

public:

    bool Handle(const cxmodel::Player& /*p_activePlayer*/) const override
    {
        return false; // LCOV_EXCL_LINE
    }

};

} // namespace

std::unique_ptr<cxmodel::IGameResolutionStrategy> cxmodel::GameResolutionStrategyFactory::Make(const IBoard& p_board,
                                                                                               size_t p_inARowValue,
                                                                                               const std::vector<Player>& p_players,
                                                                                               const std::vector<IBoard::Position>& p_takenPositions,
                                                                                               GameResolution p_resolution)
{
    std::unique_ptr<IGameResolutionStrategy> strategy = std::make_unique<NoGameResolutionStrategy>();
    ASSERT(strategy);

    IF_PRECONDITION_NOT_MET_DO(p_inARowValue >= 2u, return strategy;);
    IF_PRECONDITION_NOT_MET_DO(p_inARowValue <= std::numeric_limits<int>::max(), return strategy;);
    IF_PRECONDITION_NOT_MET_DO(p_players.size() >= 2, return strategy;);

    switch(p_resolution)
    {
        case GameResolution::WIN:
        {
            strategy = std::make_unique<WinGameResolutionStrategy>(p_board, p_inARowValue, p_players, p_takenPositions);
            break;
        }

        case GameResolution::TIE:
        {
            strategy = std::make_unique<TieGameResolutionStrategy>(p_board, p_inARowValue, p_players, p_takenPositions);
            break;
        }

        default:
        {
            ASSERT_ERROR_MSG("No game resolution strategy found."); // LCOV_EXCL_LINE
            break;                                                  // LCOV_EXCL_LINE
        }
    }

    ASSERT(strategy);
    return strategy;
}
