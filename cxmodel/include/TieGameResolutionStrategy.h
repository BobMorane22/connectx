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
     *
     * @param p_board              The game board.
     * @param p_inARowValue        The in-a-row value.
     * @param p_players            A list of players.
     * @param p_takenPositions     A list of all taken positions on the board.
     *
     ********************************************************************************************/
    TieGameResolutionStrategy(const IBoard& p_board,
                              size_t p_inARowValue,
                              const std::vector<Player>& p_players,
                              const std::vector<IBoard::Position>& p_takenPositions);

    // cxmodel::IGameResolutionStrategy:
    bool Handle(const Player& p_activePlayer) const override;

private:

    bool IsDraw(const Player& p_activePlayer) const;

    bool CanPlayerWinHorizontal(const Player& p_player) const;
    bool CanPlayerWinVertical(const Player& p_player, const Player& p_activePlayer) const;
    bool CanPlayerWinDiagonalUpward(const Player& p_player) const;
    bool CanPlayerWinDiagonalDownward(const Player& p_player) const;

    int GetNbOfRemainingMoves(const Player& p_player, const int p_nbOfCompletedMoves) const;
    int GetNbOfRemainingMoves(const Player& p_player) const;
    int GetMaxVerticalPositionForPlayerInColumn(const Player& p_player, const int p_column) const;
    int GetNbOfMovesSinceLastPlay(const Player& p_player, const Player& p_activePlayer) const;
    bool IsPlayerPresentInColumn(const Player& p_player, int p_column) const;
    int GetPlayerTurn(const Player& p_player, const Player& p_activePlayer) const;

    const IBoard& m_board;
    const int m_inARowValue;
    const std::vector<Player>& m_players;
    const std::vector<IBoard::Position>& m_takenPositions;
    const int m_nbRows;
    const int m_nbColumns;

    // The `m_turn` variable represented the active player's index
    // in the player list. I have decided to leave it here named
    // as such for historical reasons. Since it is an implementation
    // only variable, I have made it mutable because it only
    // remvoves the need to duplicated a calculation (I make it
    // once in `Handle`, which is `const`.
    mutable int m_turn;

};

} // namespace cxmodel

#endif // TIEGAMERESOLUTIONSTRATEGY_H_3571E08C_7D58_4402_AAFA_B0A3BD3FE53D
