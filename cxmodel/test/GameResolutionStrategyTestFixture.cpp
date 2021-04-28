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
 * @file GameResolutionStrategyTestFixture.cpp
 * @date 2020
 *
 *************************************************************************************************/

#include <algorithm>
#include <sstream>
#include <string>

#include <Board.h>
#include <Disc.h>

#include <cxmodel/include/TieGameResolutionStrategy.h>
#include <cxmodel/include/WinGameResolutionStrategy.h>

#include "GameResolutionStrategyTestFixture.h"

namespace
{

/*************************************************************************************************
 * @brief Information about a specific move in a game.
 *
 * Moves encode the sum of all the information necessary to retrace a player's move in a game.
 * Note that moves are tied to a specific game context.
 *
 ************************************************************************************************/
struct Move
{
    constexpr Move(size_t p_turn, size_t p_column, bool p_isWon, bool p_isTied)
    : m_turn{p_turn}
    , m_column{p_column}
    , m_isWon{p_isWon}
    , m_isTied{p_isTied}
    {
    }

    size_t m_turn;    // Represents the move position in the game (e.g. first, second, ..., nth, ...)
    size_t m_column;  // The column in which the disc is dropped.
    bool m_isWon;     // `true` if the drop represents a win, `false` otherwise.
    bool m_isTied;    // `true` if the drop represents a tie, `false` otherwise.
};

// A collection of moves:
using Moves = std::vector<Move>;

/*************************************************************************************************
 * @brief Information about board configuration after a game is completed.
 *
 * BoardConfigurationData encodes all that is necessary to be able to replay a game in its
 * integrity (even wins and ties).
 *
 ************************************************************************************************/
struct BoardConfigurationData
{
    BoardConfigurationData() = default;

    BoardConfigurationData(size_t p_nbRows, size_t p_nbColumns, const Moves& p_moves)
    : m_nbRows{p_nbRows}
    , m_nbColumns{p_nbColumns}
    , m_moves{p_moves}
    {
    }

    size_t m_nbRows;     // The number of rows of the board that was used in the game.
    size_t m_nbColumns;  // The number of rows of the board that was used in the game.
    Moves m_moves;       // The list of player moves resulting in the game.
};

/**********************************************************************************************
 * @brief Extracts board configuration data for an ASCII encoded game.
 *
 * @param p_asciiGame The ASCII encoded game as a string.
 *
 * @return The extracted board configuration data.
 *
 * @sa GameResolutionStrategyTestFixture::ValidateGame for more information about the ASCII
 *     format expected by this function.
 *
 ********************************************************************************************/
BoardConfigurationData ExtractBoardConfigurationData(const std::string& p_asciiGame)
{
    constexpr char COLUMN_SEPARATOR = '|';

    BoardConfigurationData boardConfigurationData;
    size_t nbRows = 0u;

    std::istringstream stream(p_asciiGame);
    for(std::string lineRow; std::getline(stream, lineRow);)
    {
        EXPECT_TRUE(!lineRow.empty());

        // Trim line from whitespaces:
        lineRow.erase(remove_if(lineRow.begin(), lineRow.end(), isspace), lineRow.end());

        EXPECT_TRUE(!lineRow.empty());
        EXPECT_TRUE(lineRow.front() == COLUMN_SEPARATOR);
        EXPECT_TRUE(lineRow.back() == COLUMN_SEPARATOR);

        // Getting the moves, if any:
        Moves move;
        size_t currentColumn = 0u;
        size_t offsetToNextCell = 0u;
        for(size_t index = 0u; index < lineRow.size() - 2; index += offsetToNextCell)
        {
            if(lineRow[index] == COLUMN_SEPARATOR && lineRow[index + 1] == COLUMN_SEPARATOR)
            {
                // Two adjacent separators, moving on:
                ++currentColumn;
                offsetToNextCell = 1u;
                continue;
            }

            size_t nbCharsInCell = 0u;
            while(lineRow[index + 1 + nbCharsInCell] != COLUMN_SEPARATOR)
            {
                ++nbCharsInCell;
            }

            EXPECT_TRUE(nbCharsInCell >= 1u);

            const std::string cellContents = lineRow.substr(index + 1, /*index + */nbCharsInCell);

            // At this point, we have the cell contents for the current cell. We have to
            // convert it to a move. We first check if a win or a tie is encoded in the
            // cell contents:
            constexpr char WIN_TOKEN = 'w';
            bool isWin = false;
            if(cellContents.back() == WIN_TOKEN)
            {
                EXPECT_TRUE(cellContents.size() >= 2u);

                isWin = true;
            }

            constexpr char TIE_TOKEN = 't';
            bool isTie = false;
            if(cellContents.back() == TIE_TOKEN)
            {
                EXPECT_TRUE(cellContents.size() >= 2u);
                EXPECT_FALSE(isWin);

                isTie = true;
            }

            std::string turnContents;
            if(isWin || isTie)
            {
                turnContents = cellContents.substr(0, cellContents.size() - 1);
            }
            else
            {
                turnContents = cellContents;
            }

            // We cast the remaining information to extract the turn:
            size_t turn = 0u;
            try
            {
                std::size_t nbProcessedChars = 0u;
                turn = std::stoul(turnContents, &nbProcessedChars);

                EXPECT_TRUE(nbProcessedChars == turnContents.size());
            }
            catch(const std::exception& p_exception)
            {
                ADD_FAILURE() << "Unable to cast " << turnContents << " (turn contents) to unsigned long." << std::endl;
            }

            boardConfigurationData.m_moves.emplace_back(turn, currentColumn, isWin, isTie);

            // We update running values:
            ++currentColumn;
            offsetToNextCell = cellContents.size() + 1u;
        }

        if(boardConfigurationData.m_nbColumns == 0u)
        {
            boardConfigurationData.m_nbColumns = std::count(lineRow.cbegin(), lineRow.cend(), COLUMN_SEPARATOR) - 1u;
        }

        ++nbRows;
    }

    boardConfigurationData.m_nbRows = nbRows;

    // We sort the moves in ascending turn values:
    auto& moves = boardConfigurationData.m_moves;
    std::sort(moves.begin(),
              moves.end(),
              [](const Move& p_lhs, const Move& p_rhs)
              {
                  return p_lhs.m_turn < p_rhs.m_turn;
              });

    // Post conditions:
    EXPECT_TRUE(boardConfigurationData.m_nbRows > 0u);
    EXPECT_TRUE(boardConfigurationData.m_nbColumns > 0u);
    if(boardConfigurationData.m_moves.size() == 0u)
    {
        ADD_FAILURE() << "No moves in game" << std::endl;
        return boardConfigurationData;
    }

    const auto& lastMove = moves.back();
    if(!lastMove.m_isWon && !lastMove.m_isTied)
    {
        ADD_FAILURE() << "Last move (" << lastMove.m_turn << ") is neither a win nor a tie." << std::endl;
    }

    for(size_t index = 0u; index < moves.size() - 1u; ++index)
    {
        if(moves[index].m_turn == moves[index + 1u].m_turn)
        {
            ADD_FAILURE() << "Duplicate turn found in the game :" << moves[index].m_turn << std::endl;
        }

        if( moves[index + 1u].m_turn - moves[index].m_turn > 1u )
        {
            ADD_FAILURE() << "Forgotten turn found in the game after :" << moves[index].m_turn << std::endl;
        }
    }

    const size_t nbWinAndTies = std::count_if(moves.cbegin(),
                                              moves.cend(),
                                              [](const Move& p_move)
                                              {
                                                  return p_move.m_isWon || p_move.m_isTied;
                                              });

    if(nbWinAndTies == 0u)
    {
        ADD_FAILURE() << "No win or tie detected in the encoded game." << std::endl;
    }

    if(nbWinAndTies > 1u)
    {
        ADD_FAILURE() << "More than one win or tie detected in the encoded game." << std::endl;
    }

    return boardConfigurationData;
}

/**********************************************************************************************
 * @brief Drops a chip and update related game information.
 *
 * @pre There is room in the specified column to welcome a chip.
 *
 * @param p_column         The column in which to drop the chip.
 * @param p_chip           The chip to drop.
 * @param p_board          The board in which to drop the chip.
 * @param p_takenPositions The list of taken positions.
 *
 * When a chip is dropped, for the win and tie algorithms to be able to perform accordinly,
 * a list of taken position must be available that reflects the current positions that
 * were taken by users while making moves. This methods makes sure that a disc is indeed
 * dropped by also updates the taken positions list to keep it valid across drops.
 *
 ********************************************************************************************/
void DropChipInternal(size_t p_column,
                      const cxmodel::IChip& p_chip,
                      cxmodel::IBoard& p_board,
                      std::vector<cxmodel::IBoard::Position>& p_takenPositions)
{
    cxmodel::IBoard::Position position;
    ASSERT_TRUE(p_board.DropChip(p_column, p_chip, position));

    p_takenPositions.push_back(position);
}

/**********************************************************************************************
 * @brief Runs the win and tie algorithms on every move to validate the game.
 *
 * @pre The number of players is in the model's limits.
 * @pre The in-a-row value is in the model's limits.
 * @pre The number of moves is enough so that either a win or a tie is possible.
 *
 * @param p_players     The list of players.
 * @param p_inARowValue The in-a-row value.
 * @param p_boardData   The board configuration data.
 * @param p_model       The model (Connect X limits).
 *
 * @return `true` if the game is valid, `false`otherwise.
 *
 * The validation is as follow: For every move...
 *
 *   - if a neither a win nor a tie is expected, the funtion validates that neither happens;
 *   - if a win is expected, the function validates that it indeed happens and that a tie
 *     does not;
 *   - if a tie is expected, the function validates that it indeed happens and that a win
 *     does not.
 *
 ********************************************************************************************/
bool ValidateGameInternal(const std::vector<cxmodel::Player>& p_players,
                          const size_t p_inARowValue,
                          const BoardConfigurationData& p_boardData,
                          const cxmodel::IConnectXLimits& p_model)
{
    // Preconditions:
    const size_t nbPlayers = p_players.size();
    const size_t inARow = p_inARowValue;

    EXPECT_TRUE(nbPlayers >= p_model.GetMinimumNumberOfPlayers());
    EXPECT_TRUE(nbPlayers <= p_model.GetMaximumNumberOfPlayers());

    EXPECT_TRUE(inARow >= p_model.GetMinimumInARowValue());
    EXPECT_TRUE(inARow <= p_model.GetMaximumInARowValue());

    // Game creation:
    cxmodel::Board board{p_boardData.m_nbRows, p_boardData.m_nbColumns, p_model};
    std::vector<cxmodel::IBoard::Position> takenPositions;
    EXPECT_TRUE(takenPositions.empty());

    cxmodel::WinGameResolutionStrategy winStrategy{board, inARow, p_players, takenPositions};
    cxmodel::TieGameResolutionStrategy tieStrategy{board, inARow, p_players, takenPositions};

    // Game validation:
    size_t index = 0u;
    bool winLocated = false;
    for(const auto& move : p_boardData.m_moves)
    {
        DropChipInternal(move.m_column, p_players[index].GetChip(), board, takenPositions);

        // After the drop, the next player becomes the active player:
        index = (index + 1u) % p_players.size();

        if(move.m_isWon)
        {
            if(!winStrategy.Handle(p_players[index]))
            {
                winStrategy.Handle(p_players[index]);
                ADD_FAILURE() << "Expected win at turn " << move.m_turn << ", but no win detected." << std::endl;
                return false;
            }

            winLocated = true;

            if(!winLocated && tieStrategy.Handle(p_players[index]))
            {
                tieStrategy.Handle(p_players[index]);
                ADD_FAILURE() << "Unexpected tie at turn " << move.m_turn << ", but a win was expected." << std::endl;
                return false;
            }

            continue;
        }

        if(move.m_isTied)
        {
            if(winStrategy.Handle(p_players[index]))
            {
                winStrategy.Handle(p_players[index]);
                ADD_FAILURE() << "Unexpected win at turn " << move.m_turn << ", but a tie was expected." << std::endl;
                return false;
            }

            if(!tieStrategy.Handle(p_players[index]))
            {
                tieStrategy.Handle(p_players[index]);
                ADD_FAILURE() << "Expected tie at turn " << move.m_turn << ", but no tie detected." << std::endl;
                return false;
            }

            continue;
        }

        if(winStrategy.Handle(p_players[index]))
        {
            winStrategy.Handle(p_players[index]);
            ADD_FAILURE() << "Unexpected win at turn " << move.m_turn << std::endl;
            return false;
        }

        if(tieStrategy.Handle(p_players[index]))
        {
            tieStrategy.Handle(p_players[index]);
            ADD_FAILURE() << "Unexpected tie at turn " << move.m_turn << std::endl;
            return false;
        }
    }

    return true;
}

} // namespace

bool GameResolutionStrategyTestFixture::ValidateGame(const std::vector<cxmodel::Player>& p_playerList,
                                                     const size_t p_inARowValue,
                                                     const std::string& p_asciiGame)
{
    EXPECT_TRUE(p_playerList.size() >= m_model.GetMinimumNumberOfPlayers());
    EXPECT_TRUE(p_playerList.size() <= m_model.GetMaximumNumberOfPlayers());

    EXPECT_TRUE(p_inARowValue >= m_model.GetMinimumInARowValue());
    EXPECT_TRUE(p_inARowValue <= m_model.GetMaximumInARowValue());

    BoardConfigurationData boardData;
    try
    {
        boardData = ExtractBoardConfigurationData(p_asciiGame);
    }
    catch(const std::exception& p_exception)
    {
        // Some exception was thrown...
        ADD_FAILURE() << p_exception.what() << std::endl;
        return false;
    }

    return ValidateGameInternal(p_playerList, p_inARowValue, boardData, m_model);
}
