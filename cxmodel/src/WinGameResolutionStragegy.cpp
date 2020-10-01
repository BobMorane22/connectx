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

#include <Disc.h>
#include <IBoard.h>
#include <WinGameResolutionStrategy.h>

namespace
{

const cxmodel::Disc NO_CHIP = cxmodel::Disc::MakeTransparentDisc();

} // namespace

cxmodel::WinGameResolutionStrategy::WinGameResolutionStrategy(const cxmodel::IBoard& p_board,
                                                              const size_t p_inARowValue,
                                                              const std::vector<Player>& p_players,
                                                              const std::vector<IBoard::Position>& p_takenPositions)
 : m_board{p_board}
 , m_inARowValue{p_inARowValue}
 , m_players{p_players}
 , m_takenPositions{p_takenPositions}
{

}

bool cxmodel::WinGameResolutionStrategy::Handle() const
{
    bool isWinner = false;

    const size_t nbOfSucessfulMoves = m_takenPositions.size();
    const size_t nbOfPlayers = m_players.size();

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

size_t cxmodel::WinGameResolutionStrategy::LeftValidationLimit(GridValidationType p_validationType) const
{
    const IBoard::Position lastMovePosition = PositionOfLastSuccessFullMove();

    const size_t lastPlayedRow = lastMovePosition.m_row;
    const size_t lastPlayedColumn = lastMovePosition.m_column;

    size_t leftSubscript = lastPlayedColumn - (m_inARowValue - 1u);
    leftSubscript = std::max<size_t>(leftSubscript, 0u);

    if(p_validationType == GridValidationType::DiagonalDownward)
    {
        size_t lowerSubscript = lastPlayedRow + (m_inARowValue - 1u);
        lowerSubscript = std::min(m_board.GetNbRows() - 1u, lowerSubscript);

        if(lastPlayedColumn - leftSubscript > lowerSubscript - lastPlayedRow)
        {
            leftSubscript = lastPlayedColumn - (lowerSubscript - lastPlayedRow);
        }
    }
    else if(p_validationType == GridValidationType::DiagonalUpward)
    {
        size_t upperSubscript = lastPlayedRow - (m_inARowValue - 1u);
        upperSubscript = std::max<size_t>(0u, upperSubscript);

        if(lastPlayedColumn - leftSubscript > lastPlayedRow - upperSubscript)
        {
            leftSubscript = lastPlayedColumn - (lastPlayedRow - upperSubscript);
        }
    }

    return leftSubscript;
}

size_t cxmodel::WinGameResolutionStrategy::RightValidationLimit(GridValidationType p_validationType) const

{
    const IBoard::Position lastMovePosition = PositionOfLastSuccessFullMove();

    const size_t lastPlayedRow = lastMovePosition.m_row;
    const size_t lastPlayedColumn = lastMovePosition.m_column;

    size_t rightSubscript = lastPlayedColumn + (m_inARowValue - 1u);
    rightSubscript = std::min(rightSubscript, m_board.GetNbColumns() - 1u);

    if(p_validationType == GridValidationType::DiagonalDownward)
    {
        size_t upperSubscript = lastPlayedRow - (m_inARowValue - 1u);
        upperSubscript = std::max<size_t>(0u, upperSubscript);

        if(rightSubscript - lastPlayedColumn > lastPlayedRow - upperSubscript)
        {
            rightSubscript = lastPlayedColumn + (lastPlayedRow - upperSubscript);
        }
    }
    else if(p_validationType == GridValidationType::DiagonalUpward)
    {
        size_t lowerSubscript = lastPlayedRow + (m_inARowValue - 1u);
        lowerSubscript = std::min(m_board.GetNbRows() - 1u, lowerSubscript);

        if(rightSubscript - lastPlayedColumn > lowerSubscript - lastPlayedRow)
        {
            rightSubscript = lastPlayedColumn + (lowerSubscript - lastPlayedRow);
        }
    }

    return rightSubscript;
}

size_t cxmodel::WinGameResolutionStrategy::UpperValidationLimit(GridValidationType p_validationType) const
{
    const IBoard::Position lastMovePosition = PositionOfLastSuccessFullMove();

    const size_t lastPlayedRow = lastMovePosition.m_row;
    const size_t lastPlayedColumn = lastMovePosition.m_column;

    size_t upperSubscript = lastPlayedRow + (m_inARowValue - 1u);
    upperSubscript = std::min(m_board.GetNbRows() - 1u, upperSubscript);

    if(p_validationType == GridValidationType::DiagonalDownward)
    {
        size_t leftSubscript = lastPlayedColumn - (m_inARowValue - 1u);
        leftSubscript = std::max<size_t>(leftSubscript, 0u);

        if(upperSubscript - lastPlayedRow > lastPlayedColumn - leftSubscript)
        {
            upperSubscript = lastPlayedRow + (lastPlayedColumn - leftSubscript);
        }
    }
    else if(p_validationType == GridValidationType::DiagonalUpward)
    {
        size_t rightSubscript = lastPlayedColumn + (m_inARowValue - 1u);
        rightSubscript = std::min(rightSubscript, m_board.GetNbColumns() - 1u);

        if(upperSubscript - lastPlayedRow > rightSubscript - lastPlayedColumn)
        {
            upperSubscript = lastPlayedRow + (rightSubscript - lastPlayedColumn);
        }
    }

    return upperSubscript;
}

size_t cxmodel::WinGameResolutionStrategy::LowerValidationLimit(GridValidationType p_validationType) const
{
    const IBoard::Position lastMovePosition = PositionOfLastSuccessFullMove();

    const size_t lastPlayedRow = lastMovePosition.m_row;
    const size_t lastPlayedColumn = lastMovePosition.m_column;

    size_t lowerSubscript = lastPlayedRow - (m_inARowValue - 1u);
    lowerSubscript = std::max<size_t>(0u, lowerSubscript);

    if(p_validationType == GridValidationType::DiagonalDownward)
    {
        size_t rightSubscript = lastPlayedColumn + (m_inARowValue - 1u);
        rightSubscript = std::min<size_t>(rightSubscript, m_board.GetNbColumns() - 1u);

        if(lastPlayedRow - lowerSubscript > rightSubscript - lastPlayedColumn)
        {
            lowerSubscript = lastPlayedRow - (rightSubscript - lastPlayedColumn);
        }
    }
    else if(p_validationType == GridValidationType::DiagonalUpward)
    {
        size_t leftSubscript = lastPlayedColumn - (m_inARowValue - 1u);
        leftSubscript = std::max<size_t>(leftSubscript, 0u);

        if(lastPlayedRow - lowerSubscript > lastPlayedColumn - leftSubscript)
        {
            lowerSubscript = lastPlayedRow - (lastPlayedColumn - leftSubscript);
        }
    }

    return lowerSubscript;
}

size_t cxmodel::WinGameResolutionStrategy::NbOfValidations(size_t p_minValidationLimit, size_t p_maxValidationLimit) const
{
    size_t nbCombinationsToCheck;

    if(p_maxValidationLimit > p_minValidationLimit)
    {
        nbCombinationsToCheck = p_maxValidationLimit - p_minValidationLimit + 1u;
    }
    else
    {
        nbCombinationsToCheck = p_minValidationLimit - p_maxValidationLimit + 1u;
    }

    nbCombinationsToCheck = nbCombinationsToCheck - (m_inARowValue - 1u);

    return nbCombinationsToCheck;
}

size_t cxmodel::WinGameResolutionStrategy::HorizontalNbOfAdjacentDiscs() const
{
    const size_t leftLimit = LeftValidationLimit();
    const size_t rightLimit = RightValidationLimit();
    const size_t nbValidations = NbOfValidations(leftLimit, rightLimit);

    size_t pairIdenticalDiscs = 0u;
    size_t nbIdenticalDiscs = 0u;

    const IBoard::Position lastMovePosition = PositionOfLastSuccessFullMove();

    size_t rowLastPlacedDisc = lastMovePosition.m_row;

    for(size_t i = leftLimit; i < leftLimit + nbValidations; ++i)
    {
        for(size_t j = 0u; j < m_inARowValue - 1u; ++j)
        {
            if(m_board.GetChip({rowLastPlacedDisc, i + j}) != NO_CHIP &&
               m_board.GetChip({rowLastPlacedDisc, i + j}) == m_board.GetChip({rowLastPlacedDisc, i + j + 1u}))
            {
                pairIdenticalDiscs++;
            }
        }

        if(pairIdenticalDiscs == m_inARowValue - 1u)
        {
            nbIdenticalDiscs = pairIdenticalDiscs + 1u;

            break;
        }
        else
        {
            pairIdenticalDiscs = 0u;
        }
    }

    return nbIdenticalDiscs;
}

size_t cxmodel::WinGameResolutionStrategy::VerticalNbOfAdjacentDiscs() const
{
    const size_t lowerLimit = LowerValidationLimit();
    const size_t upperLimit = UpperValidationLimit();
    const size_t nbValidations = NbOfValidations(lowerLimit, upperLimit);

    size_t pairIdenticalDiscs = 0u;
    size_t nbIdenticalDiscs = 0u;

    const IBoard::Position lastMovePosition = PositionOfLastSuccessFullMove();

    size_t columnLastPlacedDisc = lastMovePosition.m_column;

    for(size_t i = lowerLimit; i < lowerLimit + nbValidations; ++i)
    {
        for(size_t j = 0u; j < m_inARowValue - 1u; ++j)
        {
            if(m_board.GetChip({i + j, columnLastPlacedDisc}) != NO_CHIP &&
               m_board.GetChip({i + j, columnLastPlacedDisc}) == m_board.GetChip({i + j + 1u, columnLastPlacedDisc}))
            {
                pairIdenticalDiscs++;
            }
        }

        if(pairIdenticalDiscs == m_inARowValue - 1u)
        {
            nbIdenticalDiscs = pairIdenticalDiscs + 1u;

            break;
        }
        else
        {
            pairIdenticalDiscs = 0u;
        }
    }

    return nbIdenticalDiscs;
}

size_t cxmodel::WinGameResolutionStrategy::UpwardNbOfAdjacentDiscs() const
{
    const size_t lowerLimit = LowerValidationLimit(GridValidationType::DiagonalUpward);
    const size_t leftLimit = LeftValidationLimit(GridValidationType::DiagonalUpward);
    const size_t rightLimit = RightValidationLimit(GridValidationType::DiagonalUpward);
    const size_t nbValidations = NbOfValidations(leftLimit, rightLimit);

    size_t pairIdenticalDiscs = 0u;
    size_t nbIdenticalDiscs = 0u;
    size_t counter = 0u;

    for(size_t i = leftLimit; i < leftLimit + nbValidations; ++i)
    {
        size_t k = lowerLimit + counter;

        for(size_t j = 0u; j < m_inARowValue - 1u; ++j)
        {
            if(m_board.GetChip({k, i + j}) != NO_CHIP &&
               m_board.GetChip({k, i + j}) == m_board.GetChip({k + 1u, i + j + 1u}))
            {
                pairIdenticalDiscs++;
            }

            ++k;
        }

        if(pairIdenticalDiscs == m_inARowValue - 1u)
        {
            nbIdenticalDiscs = pairIdenticalDiscs + 1u;

            break;
        }

        pairIdenticalDiscs = 0;
        ++counter;
    }

    return nbIdenticalDiscs;
}

size_t cxmodel::WinGameResolutionStrategy::DownwardNbOfAdjacentDiscs() const
{
    const size_t upperLimit = UpperValidationLimit(GridValidationType::DiagonalDownward);
    const size_t leftLimit = LeftValidationLimit(GridValidationType::DiagonalDownward);
    const size_t rightLimit = RightValidationLimit(GridValidationType::DiagonalDownward);
    const size_t nbValidations = NbOfValidations(leftLimit, rightLimit);

    size_t pairIdenticalDiscs = 0u;
    size_t nbIdenticalDiscs = 0u;
    size_t counter = 0u;

    for(size_t i = leftLimit; i < leftLimit + nbValidations; ++i)
    {
        size_t k = upperLimit - counter;

        for(size_t j = 0u; j < m_inARowValue - 1u; ++j)
        {
            if(m_board.GetChip({k, i + j}) != NO_CHIP &&
               m_board.GetChip({k, i + j}) == m_board.GetChip({k - 1u, i + j + 1u}))
            {
                ++pairIdenticalDiscs;
            }

            --k;
        }

        if(pairIdenticalDiscs == m_inARowValue - 1u)
        {
            nbIdenticalDiscs = pairIdenticalDiscs + 1u;

            break;
        }

        pairIdenticalDiscs = 0u;
        ++counter;
    }

    return nbIdenticalDiscs;
}

bool cxmodel::WinGameResolutionStrategy::CheckHorizontalWinner() const
{
    const size_t nbAdjacentIdenticalDiscs = HorizontalNbOfAdjacentDiscs();

    return nbAdjacentIdenticalDiscs == m_inARowValue;
}

bool cxmodel::WinGameResolutionStrategy::CheckVerticalWinner() const
{
    const size_t nbAdjacentIdenticalDiscs = VerticalNbOfAdjacentDiscs();

    return nbAdjacentIdenticalDiscs == m_inARowValue;
}

bool cxmodel::WinGameResolutionStrategy::CheckUpwardWinner() const
{
    const size_t nbAdjacentIdenticalDiscs = UpwardNbOfAdjacentDiscs();

    return nbAdjacentIdenticalDiscs == m_inARowValue;
}

bool cxmodel::WinGameResolutionStrategy::CheckDownwardWinner() const
{
    const size_t nbAdjacentIdenticalDiscs = DownwardNbOfAdjacentDiscs();

    return nbAdjacentIdenticalDiscs == m_inARowValue;
}
