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
 * @file TieGameResolutionStrategy.cpp
 * @date 2020
 *
 *************************************************************************************************/

#include <algorithm>

#include <cxinv/include/assertion.h>
#include <cxmodel/include/Disc.h>
#include <cxmodel/include/Player.h>

#include <TieGameResolutionStrategy.h>

namespace
{

const cxmodel::Disc NO_CHIP = cxmodel::Disc::MakeTransparentDisc();

} // namespace

cxmodel::TieGameResolutionStrategy::TieGameResolutionStrategy(const IBoard& p_board,
                                                              size_t p_inARowValue,
                                                              const std::vector<Player>& p_players,
                                                              const std::vector<IBoard::Position>& p_takenPositions)
: m_board{p_board}
, m_inARowValue(p_inARowValue)
, m_players{p_players}
, m_takenPositions{p_takenPositions}
, m_nbRows(m_board.GetNbRows())
, m_nbColumns(m_board.GetNbColumns())
, m_turn{0}
{
    PRECONDITION(p_inARowValue >= 2u);
    PRECONDITION(p_inARowValue <= std::numeric_limits<int>::max());
    PRECONDITION(m_players.size() >= 2);
}

bool cxmodel::TieGameResolutionStrategy::Handle(const Player& p_activePlayer) const
{
    if(!PRECONDITION(std::find(m_players.cbegin(), m_players.cend(), p_activePlayer) != m_players.cend()))
    {
        return false;
    }

    m_turn = static_cast<int>((m_takenPositions.size() + 1u) % m_players.size());

    return IsDraw(p_activePlayer);
}

bool cxmodel::TieGameResolutionStrategy::IsDraw(const Player& p_activePlayer) const
{
    if(m_takenPositions.size() == m_board.GetNbPositions())
    {
        // This is not an early draw:
        return true;
    }

    // Now checking for early draw:
    bool validPlaysAreStillAvailable{false};

    for(const auto& player : m_players)
    {
        validPlaysAreStillAvailable |= CanPlayerWinHorizontal(player);

        if(!validPlaysAreStillAvailable)
        {
            validPlaysAreStillAvailable |= CanPlayerWinVertical(player, p_activePlayer);
        }

        if(!validPlaysAreStillAvailable)
        {
            validPlaysAreStillAvailable |= CanPlayerWinDiagonalUpward(player);
        }

        if(!validPlaysAreStillAvailable)
        {
            validPlaysAreStillAvailable |= CanPlayerWinDiagonalDownward(player);
        }
    }

    return !validPlaysAreStillAvailable;
}

int cxmodel::TieGameResolutionStrategy::GetNbOfRemainingMoves(const Player& p_player, const int p_nbOfCompletedMoves) const
{
    const int nbMovesLeft = m_board.GetNbPositions() - p_nbOfCompletedMoves;
    const int remainingMovesQuotient = nbMovesLeft / static_cast<int>(m_players.size());
    const int remainingMovesRest = nbMovesLeft % static_cast<int>(m_players.size());

    int nbOfRemainingMoves = remainingMovesQuotient;

    // Check if process is really necessary: do all players deserve an equal share?
    if(remainingMovesRest != 0)
    {
        // Find position of p_player in the player list:
        const auto playerPosition = std::find(m_players.begin(), m_players.end(), p_player);

        // Check all candidate postition for an extra turn and see if the player is there:
        for(int offset = 0; offset < remainingMovesRest; ++offset)
        {
            const int firstTurnWithMoreMoves = m_takenPositions.size() % m_players.size();
            const int nextTurnWithMoreMoves = (firstTurnWithMoreMoves + offset) % static_cast<int>(m_players.size());

            const auto candidatePosition = m_players.begin() + nextTurnWithMoreMoves;

            if(playerPosition == candidatePosition)
            {
                nbOfRemainingMoves = remainingMovesQuotient + 1;
            }
            else
            {
                nbOfRemainingMoves = remainingMovesQuotient;
            }
        }
    }
    else
    {
        nbOfRemainingMoves = remainingMovesQuotient;
    }

    return nbOfRemainingMoves;
}


int cxmodel::TieGameResolutionStrategy::GetNbOfRemainingMoves(const Player& p_player) const
{
    return GetNbOfRemainingMoves(p_player, m_takenPositions.size());
}

int cxmodel::TieGameResolutionStrategy::GetMaxVerticalPositionForPlayerInColumn(const Player& p_player, const int p_column) const
{
    PRECONDITION(p_column >= 0);

    int maxPosition = 0;

    for(int rowIndex = 0; rowIndex < m_nbRows; ++rowIndex)
    {
        ASSERT(rowIndex >= 0);
        const size_t row = static_cast<size_t>(rowIndex);
        const size_t column = static_cast<size_t>(p_column);

        if(m_board.GetChip({row, column}) == p_player.GetChip())
        {
            maxPosition = rowIndex;
        }
    }

    return maxPosition;
}

int cxmodel::TieGameResolutionStrategy::GetNbOfMovesSinceLastPlay(const Player& p_player, const Player& p_activePlayer) const
{
    int positionCurrent = 0;

    if(m_turn == 0u)
    {
        positionCurrent = static_cast<int>(m_players.size()) - 1;
    }
    else
    {
        positionCurrent = m_turn - 1;
    }

    const int positionInspected = GetPlayerTurn(p_player, p_activePlayer);

    // Find the distance between the two Players:
    int nbOfMoves = 0;

    if(positionCurrent < positionInspected)
    {
        nbOfMoves = positionCurrent + (static_cast<int>(m_players.size()) - positionInspected);
    }

    if(positionCurrent > positionInspected)
    {
        nbOfMoves = positionCurrent - positionInspected;
    }

    return nbOfMoves;
}

bool cxmodel::TieGameResolutionStrategy::IsPlayerPresentInColumn(const Player& p_player, int p_column) const
{
    PRECONDITION(p_column >= 0);

    bool isPlayerPresent = false;

    for(int rowIndex = 0; rowIndex < m_nbRows; ++rowIndex)
    {
        ASSERT(rowIndex >= 0);
        const size_t row = static_cast<size_t>(rowIndex);
        const size_t column = static_cast<size_t>(p_column);

        if(m_board.GetChip({row, column}) == p_player.GetChip())
        {
            isPlayerPresent = true;
            break;
        }
    }

    return isPlayerPresent;
}

int cxmodel::TieGameResolutionStrategy::GetPlayerTurn(const Player& p_player, const Player& p_activePlayer) const
{
    int playerTurn = 0;

    if(p_player == p_activePlayer)
    {
        playerTurn = m_takenPositions.size() % m_players.size();
    }
    else
    {
        for(int position = 0; position < static_cast<int>(m_players.size()); ++position)
        {
            if(m_players[position] == p_player)
            {
                break;
            }

            ++playerTurn;
        }
    }

    return playerTurn;
}

bool cxmodel::TieGameResolutionStrategy::CanPlayerWinHorizontal(const Player& p_player) const
{
    bool canPlayerWin = false;

    // Row to check:
    for(int rowIndex = 0; rowIndex < m_nbRows; ++rowIndex)
    {
        // Use these columns for starting point of the checks:
        for(int columnIndex = 0; columnIndex < (m_nbColumns - m_inARowValue) + 1; ++columnIndex)
        {
            bool isPlayFree = true;
            int nbOfEmptyDiscsInRow = 0;

            // Check only for the good inARow value:
            for(int offset = 0; offset < m_inARowValue; ++offset)
            {
                ASSERT(rowIndex >= 0);
                ASSERT(columnIndex + offset >= 0);
                const size_t row = static_cast<size_t>(rowIndex);
                const size_t column = static_cast<size_t>(columnIndex + offset);

                isPlayFree &= m_board.GetChip({row, column}) == p_player.GetChip() ||
                              m_board.GetChip({row, column}) == NO_CHIP;

                // If the space is free, we record it for later checks:
                if(m_board.GetChip({row, column}) == NO_CHIP)
                {
                    ++nbOfEmptyDiscsInRow;
                }
            }

            // Make sure there is enough space left for the current player to win:
            isPlayFree &= (nbOfEmptyDiscsInRow <= GetNbOfRemainingMoves(p_player));

            // As soon as one play is still free for a win, we record it:
            canPlayerWin |= isPlayFree;

            if(canPlayerWin)
            {
                break;
            }
        }

        if(canPlayerWin)
        {
            break;
        }
    }

    return canPlayerWin;
}

bool cxmodel::TieGameResolutionStrategy::CanPlayerWinVertical(const Player& p_player, const Player& p_activePlayer) const
{
    bool canPlayerWin = false;

    // We calculate the number of remaining moves for all the other players:
    int nbOfRemainingMovesOtherPlayers = 0;

    // Find the inspected Player's turn:
    int inspectedPlayerTurn = GetPlayerTurn(p_player, p_activePlayer);

    for(int playerTurn = 0; playerTurn < static_cast<int>(m_players.size()); ++playerTurn)
    {
        if(playerTurn != inspectedPlayerTurn)
        {
            const int nbOfTurnsRemainingFromLastMove = m_takenPositions.size() - GetNbOfMovesSinceLastPlay(m_players[playerTurn], p_activePlayer);
            nbOfRemainingMovesOtherPlayers += GetNbOfRemainingMoves(m_players[playerTurn], nbOfTurnsRemainingFromLastMove);
        }
    }

    // Then we perform the check on the grid:

    // Column to check:
    for(int columnIndex = 0; columnIndex <  m_nbColumns; ++columnIndex)
    {
        // Use these columns for starting point of the checks:
        for(int rowIndex = 0; rowIndex < m_nbRows - (m_inARowValue - 1); ++rowIndex)
        {
            bool isPlayFree = true;

            // Check only for the good inARow value:
            for(int offset = 0; offset < m_inARowValue; ++offset)
            {
                ASSERT(rowIndex + offset >= 0);
                ASSERT(columnIndex >= 0);
                const size_t row = static_cast<size_t>(rowIndex + offset);
                const size_t column = static_cast<size_t>(columnIndex);

                isPlayFree &= m_board.GetChip({row, column}) == p_player.GetChip() ||
                              m_board.GetChip({row, column}) == NO_CHIP;
            }

                // The following makes sure that even though a move is seen as free, there is
                // enough free positions and remaining moves for the current player.
                if(isPlayFree)
                {
                    const int  nbOfRemainingMovesTotal = m_board.GetNbPositions() - m_takenPositions.size();
                    const bool isPlayerInColumn = IsPlayerPresentInColumn(p_player, columnIndex);
                    const int  maxVerticalPositionForPlayer = isPlayerInColumn ? GetMaxVerticalPositionForPlayerInColumn(p_player, columnIndex): -1;
                    const int  nbOfRemainingMovesInOtherColumns = nbOfRemainingMovesTotal - (m_nbRows - (maxVerticalPositionForPlayer + 1));

                    // There should be enough room elswhere on the board to store all other players'
                    // remaining moves, otherwhise the move will pile up on the critical column and
                    // a win becomes impossible: the discs will alternate!
                    isPlayFree &= (nbOfRemainingMovesOtherPlayers <= nbOfRemainingMovesInOtherColumns);
                }

            // As soon as one play is still free for a win, we record it:
            canPlayerWin |= isPlayFree;
        }
    }

    return canPlayerWin;
}

bool cxmodel::TieGameResolutionStrategy::CanPlayerWinDiagonalUpward(const Player& p_player) const
{
    bool canPlayerWin = false;

    // Row to check:
    for(int rowIndex = 0; rowIndex < (m_nbRows - m_inARowValue) + 1; ++rowIndex)
    {
        // Use these columns for starting point of the checks:
        for(int columnIndex = 0; columnIndex < (m_nbColumns - m_inARowValue) + 1; ++columnIndex)
        {
            bool isPlayFree = true;
            int nbOfEmptyDiscsInDiagonal = 0;

            // Check only for the good inARow value:
            for(int offset = 0; offset < m_inARowValue; ++offset)
            {
                ASSERT(rowIndex + offset >= 0);
                ASSERT(columnIndex + offset >= 0);
                const size_t row = static_cast<size_t>(rowIndex + offset);
                const size_t column = static_cast<size_t>(columnIndex + offset);

                isPlayFree &= m_board.GetChip({row, column}) == p_player.GetChip() ||
                              m_board.GetChip({row, column}) == NO_CHIP;

                // If the space is free, we record it for later checks:
                if(m_board.GetChip({row, column}) == NO_CHIP)
                {
                    ++nbOfEmptyDiscsInDiagonal;
                }
            }

            // Make sure there is enough space left for the current player to win:
            isPlayFree &= (nbOfEmptyDiscsInDiagonal <= GetNbOfRemainingMoves(p_player));

            // As soon as one play is still free for a win, we record it:
            canPlayerWin |= isPlayFree;

            if(canPlayerWin)
            {
                break;
            }
        }

        if(canPlayerWin)
        {
            break;
        }
    }

    return canPlayerWin;
}

bool cxmodel::TieGameResolutionStrategy::CanPlayerWinDiagonalDownward(const Player& p_player) const
{
    bool canPlayerWin = false;

    // Row to check:
    for(int rowIndex = 0; rowIndex < (m_nbRows - (m_inARowValue - 1)); ++rowIndex)
    {
        // Use these columns for starting point of the checks:
        for(int columnIndex = m_inARowValue - 1; columnIndex < m_nbColumns - 1; ++columnIndex)
        {
            bool isPlayFree = true;
            int nbOfEmptyDiscsInDiagonal = 0;

            // Check only for the good inARow value:
            for(int offset = 0; offset < m_inARowValue; ++offset)
            {
                ASSERT(rowIndex + offset >= 0);
                ASSERT(columnIndex - offset >= 0);
                const size_t row = static_cast<size_t>(rowIndex + offset);
                const size_t column = static_cast<size_t>(columnIndex - offset);

                isPlayFree &= m_board.GetChip({row, column}) == p_player.GetChip() ||
                              m_board.GetChip({row, column}) == NO_CHIP;

                // If the space is free, we record it for later checks:
                if(m_board.GetChip({row, column}) == NO_CHIP)
                {
                    ++nbOfEmptyDiscsInDiagonal;
                }
            }

            // Make sure there is enough space left for the current player to win:
            isPlayFree &= (nbOfEmptyDiscsInDiagonal <= GetNbOfRemainingMoves(p_player));

            // As soon as one play is still free for a win, we record it:
            canPlayerWin |= isPlayFree;

            if(canPlayerWin)
            {
                break;
            }
        }

        if(canPlayerWin)
        {
            break;
        }
    }

    return canPlayerWin;
}
