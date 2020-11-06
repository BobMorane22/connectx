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
 * @file TieGameResolutionStrategy.h
 * @date 2020
 *
 *************************************************************************************************/

#ifndef TIEGAMERESOLUTIONSTRATEGY_H_3571E08C_7D58_4402_AAFA_B0A3BD3FE53D
#define TIEGAMERESOLUTIONSTRATEGY_H_3571E08C_7D58_4402_AAFA_B0A3BD3FE53D

#include <vector>

#include "IBoard.h"
#include "IGameResolutionStrategy.h"
#include "Player.h"

namespace cxmodel
{

/*********************************************************************************************//**
 * @brief Tie game resolution strategy.
 *
 * Decides if a game is a tie (nobody wins, nobody looses). The tie can happen before players
 * have completed the board (early tie), when it becomes known that, even if move are still
 * possible, a win can't happen on all sides.
 *
 ************************************************************************************************/
class TieGameResolutionStrategy : public IGameResolutionStrategy
{

public:

    /******************************************************************************************//**
     * @brief Constructor.
     *
     * @pre The in-a-row value is bigger than 2 and fits into a signed integer.
     * @pre The number of players is at least 2.
     * @pre The active player's index is included in the player list.
     * @pre The number of completed moves is smaller or equal to the number of positions on the board.
     *
     * @param p_board              The game board.
     * @param p_inARowValue        The in-a-row value.
     * @param p_players            A list of players.
     * @param p_activePlayerIndex  The index, in the list, of the active player.
     * @param p_nbOfCompletedMoves The number of completed moves so far.
     *
     ********************************************************************************************/
    TieGameResolutionStrategy(const IBoard& p_board,
                              size_t p_inARowValue,
                              const std::vector<Player>& p_players,
                              size_t p_activePlayerIndex,
                              size_t p_nbOfCompletedMoves);

    bool Handle() const override;

private:

    bool IsDraw() const;

    bool CanPlayerWinHorizontal(const cxmodel::Player& p_player) const;
    bool CanPlayerWinVertical(const cxmodel::Player& p_player) const;
    bool CanPlayerWinDiagonalUpward(const cxmodel::Player& p_player) const;
    bool CanPlayerWinDiagonalDownward(const cxmodel::Player& p_player) const;

    int GetNbOfRemainingMoves(const Player& p_player, const int p_nbOfCompletedMoves) const;
    int GetNbOfRemainingMoves(const Player& p_player) const;
    int GetMaxVerticalPositionForPlayerInColumn(const Player& p_player, const int p_column) const;
    int GetNbOfMovesSinceLastPlay(const Player& p_player) const;
    bool IsPlayerPresentInColumn(const Player& p_player, int p_column) const;
    int GetPlayerTurn(const Player& p_player) const;

    const IBoard& m_board;
    const int m_inARowValue;
    const std::vector<Player>& m_players;
    const size_t m_activePlayerIndex;
    const int m_nbOfCompletedMoves;
    const int m_nbRows;
    const int m_nbColumns;
    const int m_nbPositions;

};

} // namespace cxmodel

#endif // TIEGAMERESOLUTIONSTRATEGY_H_3571E08C_7D58_4402_AAFA_B0A3BD3FE53D
