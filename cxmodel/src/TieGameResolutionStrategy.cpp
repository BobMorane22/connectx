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

#include <cxinv/assertion.h>
#include <cxmodel/Disc.h>
#include <cxmodel/IBoard.h>
#include <cxmodel/IPlayer.h>
#include <cxmodel/TieGameResolutionStrategy.h>

namespace
{

// A transparent chip is used to represent the absence of a chip.
const cxmodel::Disc NO_CHIP = cxmodel::Disc::MakeTransparentDisc();

} // namespace

/**************************************************************************************************
 * @brief Constructor.
 *
 * @param p_board
 *      The board in which chips are dropped.
 * @param p_inARowValue
 *      The in-a-row value for the game.
 * @param p_players
 *      A list of all players.
 * @param p_takenPositions
 *      A list of all positions on the board at which chips have been dropped.
 *
 *************************************************************************************************/
cxmodel::TieGameResolutionStrategy::TieGameResolutionStrategy(const IBoard& p_board,
                                                              size_t p_inARowValue,
                                                              const std::vector<std::shared_ptr<IPlayer>>& p_players,
                                                              const std::vector<IBoard::Position>& p_takenPositions)
: m_board{p_board}
, m_inARowValue(p_inARowValue) , m_players{p_players}
, m_takenPositions{p_takenPositions}
, m_nbRows(m_board.GetNbRows())
, m_nbColumns(m_board.GetNbColumns())
, m_turn{0}
{
    PRECONDITION(p_inARowValue >= 2u);
    PRECONDITION(p_inARowValue <= std::numeric_limits<size_t>::max());
    PRECONDITION(m_players.size() >= 2);
}

/**************************************************************************************************
 * @brief Handles the game resolution (tie).
 *
 * @param p_activePlayer
 *      The active player. Note that this does not represent the player that just drop the last
 *      chip in the board (this player is no longer the active player). It represents the player
 *      that is active after the chip was dropped. For example, if player A just dropped a chip,
 *      it is now player B which is the active player.
 *
 * @return
 *      `true` if a tie is detected, `false` otherwise.
 *
 *************************************************************************************************/
bool cxmodel::TieGameResolutionStrategy::Handle(const IPlayer& p_activePlayer) const
{
    if(!INL_PRECONDITION(std::find_if(m_players.cbegin(),
                                      m_players.cend(),
                                      [&p_activePlayer](const std::shared_ptr<IPlayer>& p_player)
                                      {
                                          return *p_player == p_activePlayer;

                                      }) != m_players.cend()))
    {
        return false;
    }

    m_turn = static_cast<int>((m_takenPositions.size()) % m_players.size());

    return IsDraw(p_activePlayer);
}

/**************************************************************************************************
 * @brief Checks if a game is a draw.
 *
 * @param p_activePlayer
 *      The active player. Note that this does not represent the player that just drop the last
 *      chip in the board (this player is no longer the active player). It represents the player
 *      that is active after the chip was dropped. For example, if player A just dropped a chip,
 *      it is now player B which is the active player.
 *
 * @return
 *      `true` if a tie is detected, `false` otherwise.
 *
 *************************************************************************************************/
bool cxmodel::TieGameResolutionStrategy::IsDraw(const IPlayer& p_activePlayer) const
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
        validPlaysAreStillAvailable |= CanPlayerWinHorizontal(*player);

        if(!validPlaysAreStillAvailable)
        {
            validPlaysAreStillAvailable |= CanPlayerWinVertical(*player, p_activePlayer);
        }

        if(!validPlaysAreStillAvailable)
        {
            validPlaysAreStillAvailable |= CanPlayerWinDiagonalUpward(*player);
        }

        if(!validPlaysAreStillAvailable)
        {
            validPlaysAreStillAvailable |= CanPlayerWinDiagonalDownward(*player);
        }
    }

    return !validPlaysAreStillAvailable;
}

/**************************************************************************************************
 * @brief Computes the number of remaining possible moves a player has from the numbers of moves
 *        already concluded in the game.
 *
 * @param p_player
 *      The player for which we want to know the current count of remaining available moves.
 * @param p_nbOfCompletedMoves
 *      The number of moves completed at the point in the game for which the number of remaining
 *      moves needs to be known.
 *
 * @return
 *      The number of remaining moves for the player.
 *
 *************************************************************************************************/
int cxmodel::TieGameResolutionStrategy::GetNbOfRemainingMoves(const IPlayer& p_player, const int p_nbOfCompletedMoves) const
{
    const int nbMovesLeft = m_board.GetNbPositions() - p_nbOfCompletedMoves;
    const int remainingMovesQuotient = nbMovesLeft / static_cast<int>(m_players.size());
    const int remainingMovesRest = nbMovesLeft % static_cast<int>(m_players.size());

    int nbOfRemainingMoves = remainingMovesQuotient;

    // Check if process is really necessary: do all players deserve an equal share?
    if(remainingMovesRest != 0)
    {
        // Some players have more moves left than others. We find position of
        // p_player in the player list:
        const auto playerPosition = std::find_if(m_players.cbegin(),
                                                 m_players.cend(),
                                                 [&p_player](const std::shared_ptr<IPlayer>& p_listPlayer)
                                                 {
                                                     return p_player == *p_listPlayer;
                                                 });

        // Check all such players and see if one matches the player is there. In other
        // words, we check if p_player has some extra moves left:
        for(int offset = 0; offset < remainingMovesRest; ++offset)
        {
            const int firstTurnWithMoreMoves = p_nbOfCompletedMoves % m_players.size();
            const int nextTurnWithMoreMoves = (firstTurnWithMoreMoves + offset) % static_cast<int>(m_players.size());

            const auto candidatePosition = m_players.begin() + nextTurnWithMoreMoves;

            // He does, we signal it:
            if(playerPosition == candidatePosition)
            {
                nbOfRemainingMoves = remainingMovesQuotient + 1;

                return nbOfRemainingMoves;
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

/**************************************************************************************************
 * @brief Computes the number of remaining possible moves a player has from the numbers of moves
 *        already concluded in the game.
 *
 * This version only is a convenience wrapper that considers all currently completed moves.
 *
 * @param p_player
 *      The player for which we want to know the current count of remaining available moves.
 *
 * @return
 *      The number of remaining moves for the player.
 *
 *************************************************************************************************/
int cxmodel::TieGameResolutionStrategy::GetNbOfRemainingMoves(const IPlayer& p_player) const
{
    return GetNbOfRemainingMoves(p_player, m_takenPositions.size());
}

/**************************************************************************************************
 * @brief Gets the maximum vertical position at which a specific player is located in a given
 *        column.
 *
 * Note that this functions assumes the speficied player is indeed present in the given column.
 * Because of this, a call to `IsPlayerPresentInColumn` should be made before using this.
 *
 * @param p_player
 *      The player to look for.
 * @param p_column
 *      The column in which to look for the player.
 *
 * @return
 *      The row index at which the player is located in the column (and 0 if not found, which
 *      is ambiguous, see note above).
 *
 *************************************************************************************************/
int cxmodel::TieGameResolutionStrategy::GetMaxVerticalPositionForPlayerInColumn(const IPlayer& p_player, const int p_column) const
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

/**************************************************************************************************
 * @brief Gets the number of moves that have been completed since the last time the speficied
 *        player last played.
 *
 * @param p_player
 *      The player of interest.
 * @param p_activePlayer
 *      The active player. Note that this does not represent the player that just drop the last
 *      chip in the board (this player is no longer the active player). It represents the player
 *      that is active after the chip was dropped. For example, if player A just dropped a chip,
 *      it is now player B which is the active player.
 *
 * @return
 *      The number of completed moves since the last move of the specified player.
 *
 *************************************************************************************************/
int cxmodel::TieGameResolutionStrategy::GetNbOfMovesSinceLastPlay(const IPlayer& p_player, const IPlayer& p_activePlayer) const
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

    // Find the distance between the two players:
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

/**************************************************************************************************
 * @brief Checks if a specific player is present in a given column.
 *
 * @param p_player
 *      The player to look for.
 * @param p_column
 *      The column to look into.
 *
 * @return
 *      `true` if the player is found in the given column, `false` otherwise.
 *
 *************************************************************************************************/
bool cxmodel::TieGameResolutionStrategy::IsPlayerPresentInColumn(const IPlayer& p_player, int p_column) const
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

/**************************************************************************************************
 * @brief Gets the 'turn' associated to a player.
 *
 * A turn is an integer representing the location of a player in the players list. For example,
 * given a game with three players A, B and C, the turns are the following:
 *
 *                                       +--------+------+
 *                                       | Player | Turn |
 *                                       +--------+------+
 *                                       | A      | 0    |
 *                                       | B      | 1    |
 *                                       | C      | 2    |
 *                                       +--------+------+
 *
 * @param p_player
 *      The player to look for.
 * @param p_activePlayer
 *      The active player. Note that this does not represent the player that just drop the last
 *      chip in the board (this player is no longer the active player). It represents the player
 *      that is active after the chip was dropped. For example, if player A just dropped a chip,
 *      it is now player B which is the active player.
 *
 * @return
 *      The speficied player's turn.
 *
 *************************************************************************************************/
int cxmodel::TieGameResolutionStrategy::GetPlayerTurn(const IPlayer& p_player, const IPlayer& p_activePlayer) const
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
            if(*m_players[position] == p_player)
            {
                break;
            }

            ++playerTurn;
        }
    }

    return playerTurn;
}

/**************************************************************************************************
 * @brief Counts the number of free spaces for a specific column in between a given row index range.
 *
 * The number of free spaces is counted in the interval [p_fromRowIndex, p_toRowIndex].
 *
 * @param p_columnIndex
 *      The index of the column for which we want to count free spaces.
 * @param p_fromRowIndex
 *      The lower row index at which to start counting.
 * @param p_toRowIndex
 *      The upper row index at which to stop counting.
 *
 * @return
 *      The number of free spaces for the specified column in the given row range.
 *
 ************************************************************************************************/
size_t cxmodel::TieGameResolutionStrategy::GetNbAvailableFreeMovesInColumn(size_t p_columnIndex,
                                                                           size_t p_fromRowIndex,
                                                                           size_t p_toRowIndex) const
{
    const int columnIndex = static_cast<int>(p_columnIndex);
    IF_CONDITION_NOT_MET_DO(columnIndex >= 0, return 0u;);
    IF_CONDITION_NOT_MET_DO(columnIndex < m_nbColumns, return 0u;);

    const int fromRowIndex = static_cast<int>(p_fromRowIndex);
    IF_CONDITION_NOT_MET_DO(fromRowIndex >= 0, return 0u;);
    IF_CONDITION_NOT_MET_DO(fromRowIndex < m_nbRows, return 0u;);

    const int toRowIndex = static_cast<int>(p_toRowIndex);
    IF_CONDITION_NOT_MET_DO(toRowIndex >= 0, return 0u;);
    IF_CONDITION_NOT_MET_DO(toRowIndex < m_nbRows, return 0u;);

    IF_CONDITION_NOT_MET_DO(fromRowIndex <= toRowIndex, return 0u;);

    size_t nbFreePositions = 0u;
    for(int rowIndex = fromRowIndex; rowIndex < toRowIndex + 1; ++rowIndex)
    {
        const cxmodel::IBoard::Position position{static_cast<size_t>(rowIndex), static_cast<size_t>(columnIndex)};
        if(m_board.GetChip(position) == NO_CHIP)
        {
            ++nbFreePositions;
        }
    }

    return nbFreePositions;
}

/**************************************************************************************************
 * @brief Indicates if the specified player has a chance of winning with an horizontal combination.
 *
 * @param p_player
 *      The specific player.
 *
 * @return
 *      `true` if the specified player can still win horizontally, `false` otherwise.
 *
 *************************************************************************************************/
bool cxmodel::TieGameResolutionStrategy::CanPlayerWinHorizontal(const IPlayer& p_player) const
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

            // At this point, gravity must be taken into account. Even if there is
            // enough moves left for a possible win, it does not mean that these moves
            // are actually playable, because some other players, forced by gravity,
            // might have to drop its chip on winning path, invalidating it.
            if(isPlayFree)
            {
                // We calculate the available moves in the column not
                // impacted by the winning path (i.e. outside of it):
                size_t nbFreeMovesInUnusedColumns = 0u;

                // First, the columns before the winning path:
                const size_t lastColumnIndexBeforeFreePlay = static_cast<size_t>(columnIndex);
                for(size_t beforeIndex = 0u; beforeIndex < lastColumnIndexBeforeFreePlay; ++beforeIndex)
                {
                    const size_t lowerRowIndex = 0u;
                    const size_t upperRowIndex = static_cast<size_t>(m_nbRows) - 1u;
                    nbFreeMovesInUnusedColumns += GetNbAvailableFreeMovesInColumn(beforeIndex, lowerRowIndex, upperRowIndex);
                }

                // Second, the columns after:
                const int firstColumnIndexAfterFreePlay = columnIndex + m_inARowValue;
                for(int afterIndex = firstColumnIndexAfterFreePlay; afterIndex < m_nbColumns; ++afterIndex)
                {
                    const size_t lowerRowIndex = 0u;
                    const size_t upperRowIndex = static_cast<size_t>(m_nbRows) - 1u;
                    nbFreeMovesInUnusedColumns += GetNbAvailableFreeMovesInColumn(static_cast<size_t>(afterIndex), lowerRowIndex, upperRowIndex);
                }

                // At this point, all free spaces in columns that do not cross the winning
                // path are calculated. There remains the free spaces over and under the
                // winning path to consider.
                size_t nbOfFreePlaysBelowAndAboveWinPath = 0u;

                // First we compute the number of available moves under the winning path's row:
                for(int column = columnIndex; column < columnIndex + m_inARowValue; ++column)
                {
                    const size_t lowerRowIndex = 0u;
                    const size_t upperRowIndex = rowIndex > 0 ? static_cast<size_t>(rowIndex) - 1u : 0;
                    nbOfFreePlaysBelowAndAboveWinPath += GetNbAvailableFreeMovesInColumn(column, lowerRowIndex, upperRowIndex);
                }

                // Then, we compute the number of available moves over (on top
                // of) the winning path:
                for(int column = columnIndex; column < columnIndex + m_inARowValue - 1; ++column)
                {
                    const size_t lowerRowIndex = std::min(static_cast<size_t>(rowIndex) + 1u, static_cast<size_t>(m_nbRows) - 1u);
                    const size_t upperRowIndex = static_cast<size_t>(m_nbRows) - 1u;
                    nbOfFreePlaysBelowAndAboveWinPath += GetNbAvailableFreeMovesInColumn(column, lowerRowIndex, upperRowIndex);
                }

                // Finally, we compute the number of moves that players other than
                // the expected player have to make before the win can occur:
                const size_t nbOfOtherPlayersFreeMovesLeft = (nbOfEmptyDiscsInRow - 1) * (m_players.size() - 1u);
                
                // We check the play really is free:
                isPlayFree &= (nbOfOtherPlayersFreeMovesLeft <= nbFreeMovesInUnusedColumns + nbOfFreePlaysBelowAndAboveWinPath);
            }

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

/**************************************************************************************************
 * @brief Indicates if the specified player has a chance of winning with a vertical combination.
 *
 * @param p_player
 *      The specific player.
 * @param p_activePlayer
 *      The active player. Note that this does not represent the player that just drop the last
 *      chip in the board (this player is no longer the active player). It represents the player
 *      that is active after the chip was dropped. For example, if player A just dropped a chip,
 *      it is now player B which is the active player.
 *
 * @return
 *      `true` if the specified player can still win vertically, `false` otherwise.
 *
 *************************************************************************************************/
bool cxmodel::TieGameResolutionStrategy::CanPlayerWinVertical(const IPlayer& p_player, const IPlayer& p_activePlayer) const
{
    bool canPlayerWin = false;

    // Find the inspected Player's turn:
    int inspectedPlayerTurn = GetPlayerTurn(p_player, p_activePlayer);

    // We calculate the number of remaining moves for all the other players. For each
    // player which is not p_player (the inspected player), we calculate:
    //
    //   1. The number of available moves remaining at the time of the last
    //      player's move.
    //   2. From this, we can dedude the number of remaining available moves
    //      for this particular player.
    //
    // We add up all of these results to get the total number of remaining moves for
    // the other players.
    //
    int nbOfRemainingMovesOtherPlayers = 0;

    for(int playerTurn = 0; playerTurn < static_cast<int>(m_players.size()); ++playerTurn)
    {
        if(playerTurn != inspectedPlayerTurn)
        {
            const int nbOfTurnsRemainingFromLastMove = m_takenPositions.size() - GetNbOfMovesSinceLastPlay(*m_players[playerTurn], p_activePlayer);
            nbOfRemainingMovesOtherPlayers += GetNbOfRemainingMoves(*m_players[playerTurn], nbOfTurnsRemainingFromLastMove);
        }
    }

    // Then we perform the check on the grid:
    for(int columnIndex = 0; columnIndex <  m_nbColumns; ++columnIndex)
    {
        // Use these columns for starting point of the checks:
        for(int rowIndex = 0; rowIndex < m_nbRows - (m_inARowValue - 1); ++rowIndex)
        {
            bool isPlayFree = true;

            // Check only for the good inARow value:
            int nbPiledDiscs = 0;
            for(int offset = 0; offset < m_inARowValue; ++offset)
            {
                ASSERT(rowIndex + offset >= 0);
                ASSERT(columnIndex >= 0);
                const size_t row = static_cast<size_t>(rowIndex + offset);
                const size_t column = static_cast<size_t>(columnIndex);

                isPlayFree &= m_board.GetChip({row, column}) == p_player.GetChip() ||
                              m_board.GetChip({row, column}) == NO_CHIP;

                if(m_board.GetChip({row, column}) == p_player.GetChip())
                {
                    ++nbPiledDiscs;
                }
            }

            // We check here that even though there are enough moves left to the
            // player to possibly win on the column. We take into account the
            // moves already done (in previous turns) by the player:
            const int  nbOfRemainingMovesTotal = m_board.GetNbPositions() - m_takenPositions.size();
            isPlayFree &= (m_inARowValue - nbPiledDiscs <= nbOfRemainingMovesTotal - nbOfRemainingMovesOtherPlayers);

            // The player may have enough moves left to possibly win, but we must also make
            // sure other players have enough room in other columns to make their moves, otherwise
            // there chips will pile up on the inspected player's chips and cancel the win:
            if(isPlayFree)
            {
                const bool isPlayerInColumn = IsPlayerPresentInColumn(p_player, columnIndex);
                const int  maxVerticalPositionForPlayer = isPlayerInColumn ? GetMaxVerticalPositionForPlayerInColumn(p_player, columnIndex): -1;
                const int  nbOfRemainingMovesInOtherColumns = nbOfRemainingMovesTotal - (m_nbRows - (maxVerticalPositionForPlayer + 1));

                // Other players minimal amount of moves needed to make sure the current
                // player can still play all of its chips safely is computed here. It depends
                // on the amount of moves already successfully piled by the inspected player
                // on the column:
                const int otherPlayersMinimalRequiredMoves = (m_players.size() - 1) * (m_inARowValue  - nbPiledDiscs - 1);
                isPlayFree &= (otherPlayersMinimalRequiredMoves <= nbOfRemainingMovesInOtherColumns);
            }

            // As soon as one play is still free for a win, we record it:
            canPlayerWin |= isPlayFree;
        }
    }

    return canPlayerWin;
}

/**************************************************************************************************
 * @brief Indicates if the specified player has a chance of winning with a diagonal ascending
 *        combination.
 *
 * @param p_player
 *      The specific player.
 *
 * @return
 *      `true` if the specified player can still win diagonally (ascending), `false` otherwise.
 *
 *************************************************************************************************/
bool cxmodel::TieGameResolutionStrategy::CanPlayerWinDiagonalUpward(const IPlayer& p_player) const
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

/**************************************************************************************************
 * @brief Indicates if the specified player has a chance of winning with a diagonal descending
 *        combination.
 *
 * @param p_player
 *      The specific player.
 *
 * @return
 *      `true` if the specified player can still win diagonally (descending), `false` otherwise.
 *
 *************************************************************************************************/
bool cxmodel::TieGameResolutionStrategy::CanPlayerWinDiagonalDownward(const IPlayer& p_player) const
{
    bool canPlayerWin = false;

    // Row to check:
    for(int rowIndex = 0; rowIndex < (m_nbRows - (m_inARowValue - 1)); ++rowIndex)
    {
        // Use these columns for starting point of the checks:
        for(int columnIndex = m_inARowValue - 1; columnIndex < m_nbColumns; ++columnIndex)
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
