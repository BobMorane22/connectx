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
 * @file WinGameResolutionGameStrategy.h
 * @date 2020
 *
 *************************************************************************************************/

#ifndef WINGAMERESOLUTIONSTRATEGY_H_FADB6ACE_7D59_43BD_BC28_E9D29C1FD5B4
#define WINGAMERESOLUTIONSTRATEGY_H_FADB6ACE_7D59_43BD_BC28_E9D29C1FD5B4

#include <vector>

#include "IBoard.h"
#include "Player.h"
#include "IGameResolutionStrategy.h"

namespace cxmodel
{

class WinGameResolutionStrategy : public IGameResolutionStrategy
{

public:

    WinGameResolutionStrategy(const cxmodel::IBoard& p_board,
                              const size_t p_inARowValue,
                              const std::vector<Player>& p_players,
                              const std::vector<IBoard::Position>& p_takenPositions);

    bool Handle() const override;

private:

    const cxmodel::IBoard& m_board;
    const size_t m_inARowValue;
    const std::vector<Player>& m_players;
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

    size_t LeftValidationLimit(GridValidationType p_validationType = GridValidationType::Straight) const;
    size_t RightValidationLimit(GridValidationType p_validationType = GridValidationType::Straight) const;
    size_t UpperValidationLimit(GridValidationType p_validationType = GridValidationType::Straight) const;
    size_t LowerValidationLimit(GridValidationType p_validationType = GridValidationType::Straight) const;

    size_t NbOfValidations(size_t p_minValidationLimit, size_t p_maxValidationLimit) const;

    size_t HorizontalNbOfAdjacentDiscs() const;
    size_t VerticalNbOfAdjacentDiscs() const;
    size_t UpwardNbOfAdjacentDiscs() const;
    size_t DownwardNbOfAdjacentDiscs() const;

    bool CheckHorizontalWinner() const;
    bool CheckVerticalWinner() const;
    bool CheckUpwardWinner() const;
    bool CheckDownwardWinner() const;

};

} // namespace cxmodel

#endif // WINGAMERESOLUTIONSTRATEGY_H_FADB6ACE_7D59_43BD_BC28_E9D29C1FD5B4
