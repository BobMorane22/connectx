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
 * @file WinGameResolutionStrategy.h
 * @date 2020
 *
 *************************************************************************************************/

#ifndef WINGAMERESOLUTIONSTRATEGY_H_FADB6ACE_7D59_43BD_BC28_E9D29C1FD5B4
#define WINGAMERESOLUTIONSTRATEGY_H_FADB6ACE_7D59_43BD_BC28_E9D29C1FD5B4

#include <vector>

#include "IGameResolutionStrategy.h"

namespace cxmodel
{

class IBoard;
class IPlayer;

}

namespace cxmodel
{

/*********************************************************************************************//**
 * @brief Win game resolution strategy.
 *
 * Decides if a game is won by a player.
 *
 ************************************************************************************************/
class WinGameResolutionStrategy : public IGameResolutionStrategy
{

public:

    /******************************************************************************************//**
     * @brief Constructor.
     *
     * @pre The in-a-row value is bigger than 2 and fits into a signed integer.
     * @pre The number of players is at least 2.
     * @pre The number of taken positions is smaller or equal to the number of positions on the board.
     *
     * @param p_board          The game board.
     * @param p_inARowValue    The in-a-row value.
     * @param p_players        The list of players.
     * @param p_takenPositions A list of all taken (i.e. non free) positions on the board.
     *
     ********************************************************************************************/
    WinGameResolutionStrategy(const cxmodel::IBoard& p_board,
                              const size_t p_inARowValue,
                              const std::vector<std::shared_ptr<IPlayer>>& p_players,
                              const std::vector<IBoard::Position>& p_takenPositions);

    // cxmodel::IGameResolutionStrategy:
    bool Handle(const IPlayer& p_activePlayer) const override;

private:

    const cxmodel::IBoard& m_board;
    int m_inARowValue;
    const std::vector<std::shared_ptr<IPlayer>>& m_players;
    const std::vector<IBoard::Position>& m_takenPositions;

    enum class GridValidationType
    {
        Straight,
        Horizontal,
        Vertical,
        Oblique,
        DiagonalUpward,
        DiagonalDownward
    };

    IBoard::Position PositionOfLastSuccessFullMove() const;

    int LeftValidationLimit(GridValidationType p_validationType = GridValidationType::Straight) const;
    int RightValidationLimit(GridValidationType p_validationType = GridValidationType::Straight) const;
    int UpperValidationLimit(GridValidationType p_validationType = GridValidationType::Straight) const;
    int LowerValidationLimit(GridValidationType p_validationType = GridValidationType::Straight) const;

    int NbOfValidations(int p_minValidationLimit, int p_maxValidationLimit) const;

    int HorizontalNbOfAdjacentDiscs() const;
    int VerticalNbOfAdjacentDiscs() const;
    int UpwardNbOfAdjacentDiscs() const;
    int DownwardNbOfAdjacentDiscs() const;

    bool CheckHorizontalWinner() const;
    bool CheckVerticalWinner() const;
    bool CheckUpwardWinner() const;
    bool CheckDownwardWinner() const;

};

} // namespace cxmodel

#endif // WINGAMERESOLUTIONSTRATEGY_H_FADB6ACE_7D59_43BD_BC28_E9D29C1FD5B4
