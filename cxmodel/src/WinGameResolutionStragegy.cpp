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
 * @file WinGameResolutionStragegy.cpp
 * @date 2020
 *
 *************************************************************************************************/

#include <algorithm>

#include <cxinv/assertion.h>
#include <cxmodel/Disc.h>
#include <cxmodel/IBoard.h>
#include <cxmodel/WinGameResolutionStrategy.h>

namespace
{

const cxmodel::Disc NO_CHIP = cxmodel::Disc::MakeTransparentDisc();

} // namespace

// Note: the class interface uses 'size_t', but internally, signed integers are used
//       because in some calculations, negative values are used which cause overflow.
cxmodel::WinGameResolutionStrategy::WinGameResolutionStrategy(const cxmodel::IBoard& p_board,
                                                              const size_t p_inARowValue,
                                                              const std::vector<Player>& p_players,
                                                              const std::vector<IBoard::Position>& p_takenPositions)
 : m_board{p_board}
 , m_inARowValue{-1}
 , m_players{p_players}
 , m_takenPositions{p_takenPositions}
{
    if(PRECONDITION(p_inARowValue >= 2u) &&
       PRECONDITION(p_inARowValue <= std::numeric_limits<size_t>::max()))
    {
        m_inARowValue = p_inARowValue;
    }

    PRECONDITION(m_players.size() >= 2);
    PRECONDITION(p_takenPositions.size() < m_board.GetNbPositions());
}

bool cxmodel::WinGameResolutionStrategy::Handle(const Player& /*p_activePlayer*/) const
{
    if(m_inARowValue == -1)
    {
        return false; // See constructor...
    }

    bool isWinner = false;

    const int nbOfSucessfulMoves = m_takenPositions.size();
    const int nbOfPlayers = m_players.size();

    if(nbOfSucessfulMoves >= nbOfPlayers * (m_inARowValue - 1) + 1)
    {
        if(CheckHorizontalWinner() || CheckVerticalWinner() || CheckUpwardWinner()|| CheckDownwardWinner())
        {
            isWinner = true;
        }
    }

    return isWinner;
}

cxmodel::IBoard::Position cxmodel::WinGameResolutionStrategy::PositionOfLastSuccessFullMove() const
{
    return m_takenPositions.back();
}

int cxmodel::WinGameResolutionStrategy::LeftValidationLimit(GridValidationType p_validationType) const
{
    const IBoard::Position lastMovePosition = PositionOfLastSuccessFullMove();
    ASSERT(lastMovePosition.m_row <= std::numeric_limits<size_t>::max());
    ASSERT(lastMovePosition.m_column <= std::numeric_limits<size_t>::max());

    const int lastPlayedRow = static_cast<int>(lastMovePosition.m_row);
    const int lastPlayedColumn = static_cast<int>(lastMovePosition.m_column);

    int leftSubscript = lastPlayedColumn - (m_inARowValue - 1);
    leftSubscript = std::max(leftSubscript, 0);

    if(p_validationType == GridValidationType::DiagonalDownward)
    {
        int lowerSubscript = lastPlayedRow + (m_inARowValue - 1);

        ASSERT(m_board.GetNbRows() <= std::numeric_limits<size_t>::max());
        lowerSubscript = std::min(static_cast<int>(m_board.GetNbRows()) - 1, lowerSubscript);

        if(lastPlayedColumn - leftSubscript > lowerSubscript - lastPlayedRow)
        {
            leftSubscript = lastPlayedColumn - (lowerSubscript - lastPlayedRow);
        }
    }
    else if(p_validationType == GridValidationType::DiagonalUpward)
    {
        int upperSubscript = lastPlayedRow - (m_inARowValue - 1);
        upperSubscript = std::max(0, upperSubscript);

        if(lastPlayedColumn - leftSubscript > lastPlayedRow - upperSubscript)
        {
            leftSubscript = lastPlayedColumn - (lastPlayedRow - upperSubscript);
        }
    }

    return leftSubscript;
}

int cxmodel::WinGameResolutionStrategy::RightValidationLimit(GridValidationType p_validationType) const

{
    const IBoard::Position lastMovePosition = PositionOfLastSuccessFullMove();
    ASSERT(lastMovePosition.m_row <= std::numeric_limits<size_t>::max());
    ASSERT(lastMovePosition.m_column <= std::numeric_limits<size_t>::max());

    const int lastPlayedRow = static_cast<int>(lastMovePosition.m_row);
    const int lastPlayedColumn = static_cast<int>(lastMovePosition.m_column);

    int rightSubscript = lastPlayedColumn + (m_inARowValue - 1);

    ASSERT(m_board.GetNbRows() <= std::numeric_limits<size_t>::max());
    rightSubscript = std::min(rightSubscript, static_cast<int>(m_board.GetNbColumns()) - 1);

    if(p_validationType == GridValidationType::DiagonalDownward)
    {
        int upperSubscript = lastPlayedRow - (m_inARowValue - 1);
        upperSubscript = std::max(0, upperSubscript);

        if(rightSubscript - lastPlayedColumn > lastPlayedRow - upperSubscript)
        {
            rightSubscript = lastPlayedColumn + (lastPlayedRow - upperSubscript);
        }
    }
    else if(p_validationType == GridValidationType::DiagonalUpward)
    {
        int lowerSubscript = lastPlayedRow + (m_inARowValue - 1u);

        ASSERT(m_board.GetNbRows() <= std::numeric_limits<size_t>::max());
        lowerSubscript = std::min(static_cast<int>(m_board.GetNbRows()) - 1, lowerSubscript);

        if(rightSubscript - lastPlayedColumn > lowerSubscript - lastPlayedRow)
        {
            rightSubscript = lastPlayedColumn + (lowerSubscript - lastPlayedRow);
        }
    }

    return rightSubscript;
}

int cxmodel::WinGameResolutionStrategy::UpperValidationLimit(GridValidationType p_validationType) const
{
    const IBoard::Position lastMovePosition = PositionOfLastSuccessFullMove();
    ASSERT(lastMovePosition.m_row <= std::numeric_limits<size_t>::max());
    ASSERT(lastMovePosition.m_column <= std::numeric_limits<size_t>::max());

    const int lastPlayedRow = lastMovePosition.m_row;
    const int lastPlayedColumn = lastMovePosition.m_column;

    int upperSubscript = lastPlayedRow + (m_inARowValue - 1);

    ASSERT(m_board.GetNbRows() <= std::numeric_limits<size_t>::max());
    upperSubscript = std::min(static_cast<int>(m_board.GetNbRows()) - 1, upperSubscript);

    if(p_validationType == GridValidationType::DiagonalDownward)
    {
        int leftSubscript = lastPlayedColumn - (m_inARowValue - 1);
        leftSubscript = std::max(leftSubscript, 0);

        if(upperSubscript - lastPlayedRow > lastPlayedColumn - leftSubscript)
        {
            upperSubscript = lastPlayedRow + (lastPlayedColumn - leftSubscript);
        }
    }

    return upperSubscript;
}

int cxmodel::WinGameResolutionStrategy::LowerValidationLimit(GridValidationType p_validationType) const
{
    const IBoard::Position lastMovePosition = PositionOfLastSuccessFullMove();
    ASSERT(lastMovePosition.m_row <= std::numeric_limits<size_t>::max());
    ASSERT(lastMovePosition.m_column <= std::numeric_limits<size_t>::max());

    const int lastPlayedRow = lastMovePosition.m_row;
    const int lastPlayedColumn = lastMovePosition.m_column;

    int lowerSubscript = lastPlayedRow - (m_inARowValue - 1);
    lowerSubscript = std::max(0, lowerSubscript);

    if(p_validationType == GridValidationType::DiagonalUpward)
    {
        int leftSubscript = lastPlayedColumn - (m_inARowValue - 1);
        leftSubscript = std::max(leftSubscript, 0);

        if(lastPlayedRow - lowerSubscript > lastPlayedColumn - leftSubscript)
        {
            lowerSubscript = lastPlayedRow - (lastPlayedColumn - leftSubscript);
        }
    }

    return lowerSubscript;
}

int cxmodel::WinGameResolutionStrategy::NbOfValidations(int p_minValidationLimit, int p_maxValidationLimit) const
{
    int nbCombinationsToCheck = std::abs(p_maxValidationLimit - p_minValidationLimit) + 1;

    return nbCombinationsToCheck - (m_inARowValue - 1);
}

int cxmodel::WinGameResolutionStrategy::HorizontalNbOfAdjacentDiscs() const
{
    const int leftLimit = LeftValidationLimit();
    const int rightLimit = RightValidationLimit();
    const int nbValidations = NbOfValidations(leftLimit, rightLimit);

    int pairIdenticalDiscs = 0;
    int nbIdenticalDiscs = 0;

    const IBoard::Position lastMovePosition = PositionOfLastSuccessFullMove();

    size_t rowLastPlacedDisc = lastMovePosition.m_row;

    for(int i = leftLimit; i < leftLimit + nbValidations; ++i)
    {
        for(int j = 0; j < m_inARowValue - 1; ++j)
        {
            ASSERT(i + j >= 0);
            const size_t currentColumn = static_cast<size_t>(i + j);
            const size_t adjacentColumn = currentColumn + 1;

            if(m_board.GetChip({rowLastPlacedDisc, currentColumn}) != NO_CHIP &&
               m_board.GetChip({rowLastPlacedDisc, currentColumn}) == m_board.GetChip({rowLastPlacedDisc, adjacentColumn}))
            {
                pairIdenticalDiscs++;
            }
        }

        if(pairIdenticalDiscs == m_inARowValue - 1)
        {
            nbIdenticalDiscs = pairIdenticalDiscs + 1;

            break;
        }
        else
        {
            pairIdenticalDiscs = 0;
        }
    }

    return nbIdenticalDiscs;
}

int cxmodel::WinGameResolutionStrategy::VerticalNbOfAdjacentDiscs() const
{
    const int lowerLimit = LowerValidationLimit();
    const int upperLimit = UpperValidationLimit();
    const int nbValidations = NbOfValidations(lowerLimit, upperLimit);

    int pairIdenticalDiscs = 0;
    int nbIdenticalDiscs = 0;

    const IBoard::Position lastMovePosition = PositionOfLastSuccessFullMove();

    size_t columnLastPlacedDisc = lastMovePosition.m_column;

    for(int i = lowerLimit; i < lowerLimit + nbValidations; ++i)
    {
        for(int j = 0; j < m_inARowValue - 1; ++j)
        {
            ASSERT(i + j >= 0);
            const size_t currentRow = static_cast<size_t>(i + j);
            const size_t adjacentRow = currentRow + 1;

            if(m_board.GetChip({currentRow, columnLastPlacedDisc}) != NO_CHIP &&
               m_board.GetChip({currentRow, columnLastPlacedDisc}) == m_board.GetChip({adjacentRow, columnLastPlacedDisc}))
            {
                pairIdenticalDiscs++;
            }
        }

        if(pairIdenticalDiscs == m_inARowValue - 1)
        {
            nbIdenticalDiscs = pairIdenticalDiscs + 1;

            break;
        }
        else
        {
            pairIdenticalDiscs = 0;
        }
    }

    return nbIdenticalDiscs;
}

int cxmodel::WinGameResolutionStrategy::UpwardNbOfAdjacentDiscs() const
{
    const int lowerLimit = LowerValidationLimit(GridValidationType::DiagonalUpward);
    const int leftLimit = LeftValidationLimit(GridValidationType::DiagonalUpward);
    const int rightLimit = RightValidationLimit(GridValidationType::DiagonalUpward);
    const int nbValidations = NbOfValidations(leftLimit, rightLimit);

    int pairIdenticalDiscs = 0;
    int nbIdenticalDiscs = 0;
    int counter = 0;

    for(int i = leftLimit; i < leftLimit + nbValidations; ++i)
    {
        int k = lowerLimit + counter;

        for(int j = 0; j < m_inARowValue - 1; ++j)
        {
            ASSERT(k >= 0);
            ASSERT(i + j >= 0);

            const size_t currentRow = static_cast<size_t>(k);
            const size_t adjacentRow = currentRow + 1;
            const size_t currentColumn = static_cast<size_t>(i + j);
            const size_t adjacentColumn = currentColumn + 1;

            if(m_board.GetChip({currentRow, currentColumn}) != NO_CHIP &&
               m_board.GetChip({currentRow, currentColumn}) == m_board.GetChip({adjacentRow, adjacentColumn}))
            {
                pairIdenticalDiscs++;
            }

            ++k;
        }

        if(pairIdenticalDiscs == m_inARowValue - 1)
        {
            nbIdenticalDiscs = pairIdenticalDiscs + 1;

            break;
        }

        pairIdenticalDiscs = 0;
        ++counter;
    }

    return nbIdenticalDiscs;
}

int cxmodel::WinGameResolutionStrategy::DownwardNbOfAdjacentDiscs() const
{
    const int upperLimit = UpperValidationLimit(GridValidationType::DiagonalDownward);
    const int leftLimit = LeftValidationLimit(GridValidationType::DiagonalDownward);
    const int rightLimit = RightValidationLimit(GridValidationType::DiagonalDownward);
    const int nbValidations = NbOfValidations(leftLimit, rightLimit);

    int pairIdenticalDiscs = 0;
    int nbIdenticalDiscs = 0;
    int counter = 0;

    for(int i = leftLimit; i < leftLimit + nbValidations; ++i)
    {
        int k = upperLimit - counter;

        for(int j = 0; j < m_inARowValue - 1; ++j)
        {
            ASSERT(k - 1 >= 0);
            ASSERT(i + j >= 0);

            const size_t currentRow = static_cast<size_t>(k);
            const size_t adjacentRow = static_cast<size_t>(k - 1);
            const size_t currentColumn = static_cast<size_t>(i + j);
            const size_t adjacentColumn = currentColumn + 1;

            if(m_board.GetChip({currentRow, currentColumn}) != NO_CHIP &&
               m_board.GetChip({currentRow, currentColumn}) == m_board.GetChip({adjacentRow, adjacentColumn}))
            {
                ++pairIdenticalDiscs;
            }

            --k;
        }

        if(pairIdenticalDiscs == m_inARowValue - 1)
        {
            nbIdenticalDiscs = pairIdenticalDiscs + 1;

            break;
        }

        pairIdenticalDiscs = 0u;
        ++counter;
    }

    return nbIdenticalDiscs;
}

bool cxmodel::WinGameResolutionStrategy::CheckHorizontalWinner() const
{
    return HorizontalNbOfAdjacentDiscs() == m_inARowValue;
}

bool cxmodel::WinGameResolutionStrategy::CheckVerticalWinner() const
{
    return VerticalNbOfAdjacentDiscs() == m_inARowValue;
}

bool cxmodel::WinGameResolutionStrategy::CheckUpwardWinner() const
{
    return UpwardNbOfAdjacentDiscs() == m_inARowValue;
}

bool cxmodel::WinGameResolutionStrategy::CheckDownwardWinner() const
{
    return DownwardNbOfAdjacentDiscs() == m_inARowValue;
}
