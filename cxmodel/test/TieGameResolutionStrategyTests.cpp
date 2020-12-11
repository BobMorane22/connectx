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
 * @file TieGameResolutionStrategyTests.cpp
 * @date 2020
 *
 *************************************************************************************************/

#include <TieGameResolutionStrategy.h>
#include <WinGameResolutionStrategy.h>

#include "GameResolutionStrategyTestFixture.h"

TEST_F(GameResolutionStrategyTestFixture, /*DISABLED*/TieHandle_ClassicGameBoardEmpty_ReturnsFalse)
{
    cxmodel::Board board = MakeClassicBoard();
    const size_t inARowValue = 4u;
    const std::vector<cxmodel::Player> players = MakeTwoPlayersList();
    std::vector<cxmodel::IBoard::Position> takenPositions;
    ASSERT_TRUE(takenPositions.empty());

    cxmodel::TieGameResolutionStrategy tieStrategy{board, inARowValue, players, takenPositions};
    ASSERT_FALSE(tieStrategy.Handle(players[0]));
}

TEST_F(GameResolutionStrategyTestFixture, /*DISABLED*/TieHandle_ClassicGameBoardEdgeCaseHorizontal_ReturnsTrue)
{
    cxmodel::Board board = MakeClassicBoard();
    const size_t inARowValue = 4u;
    const std::vector<cxmodel::Player> players = MakeTwoPlayersList();
    std::vector<cxmodel::IBoard::Position> takenPositions;
    ASSERT_TRUE(takenPositions.empty());

    cxmodel::WinGameResolutionStrategy winStrategy{board, inARowValue, players, takenPositions};

    DropChip(0u, players[0].GetChip(), board, takenPositions);    ASSERT_FALSE(winStrategy.Handle(players[0]));
    DropChip(1u, players[1].GetChip(), board, takenPositions);    ASSERT_FALSE(winStrategy.Handle(players[1]));

    DropChip(2u, players[0].GetChip(), board, takenPositions);    ASSERT_FALSE(winStrategy.Handle(players[0]));
    DropChip(3u, players[1].GetChip(), board, takenPositions);    ASSERT_FALSE(winStrategy.Handle(players[1]));

    DropChip(4u, players[0].GetChip(), board, takenPositions);    ASSERT_FALSE(winStrategy.Handle(players[0]));
    DropChip(5u, players[1].GetChip(), board, takenPositions);    ASSERT_FALSE(winStrategy.Handle(players[1]));

    DropChip(6u, players[0].GetChip(), board, takenPositions);    ASSERT_FALSE(winStrategy.Handle(players[0]));
    DropChip(0u, players[1].GetChip(), board, takenPositions);    ASSERT_FALSE(winStrategy.Handle(players[1]));

    DropChip(1u, players[0].GetChip(), board, takenPositions);    ASSERT_FALSE(winStrategy.Handle(players[0]));
    DropChip(2u, players[1].GetChip(), board, takenPositions);    ASSERT_FALSE(winStrategy.Handle(players[1]));

    DropChip(3u, players[0].GetChip(), board, takenPositions);    ASSERT_FALSE(winStrategy.Handle(players[0]));
    DropChip(4u, players[1].GetChip(), board, takenPositions);    ASSERT_FALSE(winStrategy.Handle(players[1]));

    DropChip(5u, players[0].GetChip(), board, takenPositions);    ASSERT_FALSE(winStrategy.Handle(players[0]));
    DropChip(6u, players[1].GetChip(), board, takenPositions);    ASSERT_FALSE(winStrategy.Handle(players[1]));

    DropChip(1u, players[0].GetChip(), board, takenPositions);    ASSERT_FALSE(winStrategy.Handle(players[0]));
    DropChip(0u, players[1].GetChip(), board, takenPositions);    ASSERT_FALSE(winStrategy.Handle(players[1]));

    DropChip(3u, players[0].GetChip(), board, takenPositions);    ASSERT_FALSE(winStrategy.Handle(players[0]));
    DropChip(2u, players[1].GetChip(), board, takenPositions);    ASSERT_FALSE(winStrategy.Handle(players[1]));

    DropChip(5u, players[0].GetChip(), board, takenPositions);    ASSERT_FALSE(winStrategy.Handle(players[0]));
    DropChip(4u, players[1].GetChip(), board, takenPositions);    ASSERT_FALSE(winStrategy.Handle(players[1]));

    DropChip(0u, players[0].GetChip(), board, takenPositions);    ASSERT_FALSE(winStrategy.Handle(players[0]));
    DropChip(6u, players[1].GetChip(), board, takenPositions);    ASSERT_FALSE(winStrategy.Handle(players[1]));

    DropChip(2u, players[0].GetChip(), board, takenPositions);    ASSERT_FALSE(winStrategy.Handle(players[0]));
    DropChip(1u, players[1].GetChip(), board, takenPositions);    ASSERT_FALSE(winStrategy.Handle(players[1]));

    DropChip(4u, players[0].GetChip(), board, takenPositions);    ASSERT_FALSE(winStrategy.Handle(players[0]));
    DropChip(3u, players[1].GetChip(), board, takenPositions);    ASSERT_FALSE(winStrategy.Handle(players[1]));

    DropChip(6u, players[0].GetChip(), board, takenPositions);    ASSERT_FALSE(winStrategy.Handle(players[0]));
    DropChip(5u, players[1].GetChip(), board, takenPositions);    ASSERT_FALSE(winStrategy.Handle(players[1]));

    DropChip(0u, players[0].GetChip(), board, takenPositions);    ASSERT_FALSE(winStrategy.Handle(players[0]));
    DropChip(1u, players[1].GetChip(), board, takenPositions);    ASSERT_FALSE(winStrategy.Handle(players[1]));

    DropChip(2u, players[0].GetChip(), board, takenPositions);    ASSERT_FALSE(winStrategy.Handle(players[0]));
    DropChip(3u, players[1].GetChip(), board, takenPositions);    ASSERT_FALSE(winStrategy.Handle(players[1]));

    DropChip(4u, players[0].GetChip(), board, takenPositions);    ASSERT_FALSE(winStrategy.Handle(players[0]));
    DropChip(5u, players[1].GetChip(), board, takenPositions);    ASSERT_FALSE(winStrategy.Handle(players[1]));

    DropChip(6u, players[0].GetChip(), board, takenPositions);    ASSERT_FALSE(winStrategy.Handle(players[0]));
    DropChip(0u, players[1].GetChip(), board, takenPositions);    ASSERT_FALSE(winStrategy.Handle(players[1]));

    cxmodel::TieGameResolutionStrategy tieStrategy{board, inARowValue, players, takenPositions};
    ASSERT_FALSE(tieStrategy.Handle(players[0]));

    // From this point on, the game should report a tie on every move, until completion:
    DropChip(1u, players[0].GetChip(), board, takenPositions);    ASSERT_FALSE(winStrategy.Handle(players[0]));
    ASSERT_TRUE(tieStrategy.Handle(players[1]));

    DropChip(2u, players[1].GetChip(), board, takenPositions);    ASSERT_FALSE(winStrategy.Handle(players[1]));
    ASSERT_TRUE(tieStrategy.Handle(players[0]));

    DropChip(3u, players[0].GetChip(), board, takenPositions);    ASSERT_FALSE(winStrategy.Handle(players[0]));
    ASSERT_TRUE(tieStrategy.Handle(players[1]));

    DropChip(4u, players[1].GetChip(), board, takenPositions);    ASSERT_FALSE(winStrategy.Handle(players[1]));
    ASSERT_TRUE(tieStrategy.Handle(players[0]));

    DropChip(5u, players[0].GetChip(), board, takenPositions);    ASSERT_FALSE(winStrategy.Handle(players[0]));
    ASSERT_TRUE(tieStrategy.Handle(players[1]));

    DropChip(6u, players[1].GetChip(), board, takenPositions);    ASSERT_FALSE(winStrategy.Handle(players[1]));
    ASSERT_TRUE(tieStrategy.Handle(players[0]));
}

TEST_F(GameResolutionStrategyTestFixture, /*DISABLED*/TieHandle_9by8GameBoardConnect7ThreePlayersEdgeCaseHorizontal_ReturnsTrue)
{
    cxmodel::Board board = Make9By8Board();
    const size_t inARowValue = 7u;
    const std::vector<cxmodel::Player> players = MakeThreePlayersList();
    std::vector<cxmodel::IBoard::Position> takenPositions;
    ASSERT_TRUE(takenPositions.empty());

    cxmodel::WinGameResolutionStrategy winStrategy{board, inARowValue, players, takenPositions};

    DropChip(0u, players[0].GetChip(), board, takenPositions);    ASSERT_FALSE(winStrategy.Handle(players[0]));
    DropChip(1u, players[1].GetChip(), board, takenPositions);    ASSERT_FALSE(winStrategy.Handle(players[1]));
    DropChip(2u, players[2].GetChip(), board, takenPositions);    ASSERT_FALSE(winStrategy.Handle(players[2]));

    DropChip(3u, players[0].GetChip(), board, takenPositions);    ASSERT_FALSE(winStrategy.Handle(players[0]));
    DropChip(4u, players[1].GetChip(), board, takenPositions);    ASSERT_FALSE(winStrategy.Handle(players[1]));
    DropChip(5u, players[2].GetChip(), board, takenPositions);    ASSERT_FALSE(winStrategy.Handle(players[2]));

    DropChip(6u, players[0].GetChip(), board, takenPositions);    ASSERT_FALSE(winStrategy.Handle(players[0]));
    DropChip(7u, players[1].GetChip(), board, takenPositions);    ASSERT_FALSE(winStrategy.Handle(players[1]));
    DropChip(2u, players[2].GetChip(), board, takenPositions);    ASSERT_FALSE(winStrategy.Handle(players[2]));

    DropChip(0u, players[0].GetChip(), board, takenPositions);    ASSERT_FALSE(winStrategy.Handle(players[0]));
    DropChip(1u, players[1].GetChip(), board, takenPositions);    ASSERT_FALSE(winStrategy.Handle(players[1]));
    DropChip(5u, players[2].GetChip(), board, takenPositions);    ASSERT_FALSE(winStrategy.Handle(players[2]));

    DropChip(3u, players[0].GetChip(), board, takenPositions);    ASSERT_FALSE(winStrategy.Handle(players[0]));
    DropChip(4u, players[1].GetChip(), board, takenPositions);    ASSERT_FALSE(winStrategy.Handle(players[1]));
    DropChip(2u, players[2].GetChip(), board, takenPositions);    ASSERT_FALSE(winStrategy.Handle(players[2]));

    DropChip(6u, players[0].GetChip(), board, takenPositions);    ASSERT_FALSE(winStrategy.Handle(players[0]));
    DropChip(7u, players[1].GetChip(), board, takenPositions);    ASSERT_FALSE(winStrategy.Handle(players[1]));
    DropChip(5u, players[2].GetChip(), board, takenPositions);    ASSERT_FALSE(winStrategy.Handle(players[2]));

    DropChip(0u, players[0].GetChip(), board, takenPositions);    ASSERT_FALSE(winStrategy.Handle(players[0]));
    DropChip(1u, players[1].GetChip(), board, takenPositions);    ASSERT_FALSE(winStrategy.Handle(players[1]));
    DropChip(2u, players[2].GetChip(), board, takenPositions);    ASSERT_FALSE(winStrategy.Handle(players[2]));

    DropChip(3u, players[0].GetChip(), board, takenPositions);    ASSERT_FALSE(winStrategy.Handle(players[0]));
    DropChip(4u, players[1].GetChip(), board, takenPositions);    ASSERT_FALSE(winStrategy.Handle(players[1]));
    DropChip(5u, players[2].GetChip(), board, takenPositions);    ASSERT_FALSE(winStrategy.Handle(players[2]));

    DropChip(6u, players[0].GetChip(), board, takenPositions);    ASSERT_FALSE(winStrategy.Handle(players[0]));
    DropChip(7u, players[1].GetChip(), board, takenPositions);    ASSERT_FALSE(winStrategy.Handle(players[1]));
    DropChip(0u, players[2].GetChip(), board, takenPositions);    ASSERT_FALSE(winStrategy.Handle(players[2]));

    DropChip(1u, players[0].GetChip(), board, takenPositions);    ASSERT_FALSE(winStrategy.Handle(players[0]));
    DropChip(3u, players[1].GetChip(), board, takenPositions);    ASSERT_FALSE(winStrategy.Handle(players[1]));
    DropChip(4u, players[2].GetChip(), board, takenPositions);    ASSERT_FALSE(winStrategy.Handle(players[2]));

    DropChip(6u, players[0].GetChip(), board, takenPositions);    ASSERT_FALSE(winStrategy.Handle(players[0]));
    DropChip(7u, players[1].GetChip(), board, takenPositions);    ASSERT_FALSE(winStrategy.Handle(players[1]));
    DropChip(0u, players[2].GetChip(), board, takenPositions);    ASSERT_FALSE(winStrategy.Handle(players[2]));

    DropChip(1u, players[0].GetChip(), board, takenPositions);    ASSERT_FALSE(winStrategy.Handle(players[0]));
    DropChip(2u, players[1].GetChip(), board, takenPositions);    ASSERT_FALSE(winStrategy.Handle(players[1]));
    DropChip(3u, players[2].GetChip(), board, takenPositions);    ASSERT_FALSE(winStrategy.Handle(players[2]));

    DropChip(4u, players[0].GetChip(), board, takenPositions);    ASSERT_FALSE(winStrategy.Handle(players[0]));
    DropChip(5u, players[1].GetChip(), board, takenPositions);    ASSERT_FALSE(winStrategy.Handle(players[1]));
    DropChip(6u, players[2].GetChip(), board, takenPositions);    ASSERT_FALSE(winStrategy.Handle(players[2]));

    DropChip(7u, players[0].GetChip(), board, takenPositions);    ASSERT_FALSE(winStrategy.Handle(players[0]));
    DropChip(0u, players[1].GetChip(), board, takenPositions);    ASSERT_FALSE(winStrategy.Handle(players[1]));
    DropChip(1u, players[2].GetChip(), board, takenPositions);    ASSERT_FALSE(winStrategy.Handle(players[2]));

    DropChip(2u, players[0].GetChip(), board, takenPositions);    ASSERT_FALSE(winStrategy.Handle(players[0]));
    DropChip(3u, players[1].GetChip(), board, takenPositions);    ASSERT_FALSE(winStrategy.Handle(players[1]));
    DropChip(4u, players[2].GetChip(), board, takenPositions);    ASSERT_FALSE(winStrategy.Handle(players[2]));

    DropChip(5u, players[0].GetChip(), board, takenPositions);    ASSERT_FALSE(winStrategy.Handle(players[0]));
    DropChip(6u, players[1].GetChip(), board, takenPositions);    ASSERT_FALSE(winStrategy.Handle(players[1]));
    DropChip(7u, players[2].GetChip(), board, takenPositions);    ASSERT_FALSE(winStrategy.Handle(players[2]));

    DropChip(0u, players[0].GetChip(), board, takenPositions);    ASSERT_FALSE(winStrategy.Handle(players[0]));
    DropChip(1u, players[1].GetChip(), board, takenPositions);    ASSERT_FALSE(winStrategy.Handle(players[1]));
    DropChip(2u, players[2].GetChip(), board, takenPositions);    ASSERT_FALSE(winStrategy.Handle(players[2]));

    DropChip(0u, players[0].GetChip(), board, takenPositions);    ASSERT_FALSE(winStrategy.Handle(players[0]));
    DropChip(1u, players[1].GetChip(), board, takenPositions);    ASSERT_FALSE(winStrategy.Handle(players[1]));

    cxmodel::TieGameResolutionStrategy tieStrategy{board, inARowValue, players, takenPositions};
    ASSERT_FALSE(tieStrategy.Handle(players[2]));

    // From this point on, the game should report a tie on every move, until completion:
    DropChip(2u, players[2].GetChip(), board, takenPositions);    ASSERT_FALSE(winStrategy.Handle(players[2]));
    ASSERT_TRUE(tieStrategy.Handle(players[0]));

    DropChip(0u, players[0].GetChip(), board, takenPositions);    ASSERT_FALSE(winStrategy.Handle(players[0]));
    ASSERT_TRUE(tieStrategy.Handle(players[1]));

    DropChip(1u, players[1].GetChip(), board, takenPositions);    ASSERT_FALSE(winStrategy.Handle(players[1]));
    ASSERT_TRUE(tieStrategy.Handle(players[2]));

    DropChip(2u, players[2].GetChip(), board, takenPositions);    ASSERT_FALSE(winStrategy.Handle(players[2]));
    ASSERT_TRUE(tieStrategy.Handle(players[0]));

    DropChip(3u, players[0].GetChip(), board, takenPositions);    ASSERT_FALSE(winStrategy.Handle(players[0]));
    ASSERT_TRUE(tieStrategy.Handle(players[1]));

    DropChip(4u, players[1].GetChip(), board, takenPositions);    ASSERT_FALSE(winStrategy.Handle(players[1]));
    ASSERT_TRUE(tieStrategy.Handle(players[2]));

    DropChip(5u, players[2].GetChip(), board, takenPositions);    ASSERT_FALSE(winStrategy.Handle(players[2]));
    ASSERT_TRUE(tieStrategy.Handle(players[0]));

    DropChip(3u, players[0].GetChip(), board, takenPositions);    ASSERT_FALSE(winStrategy.Handle(players[0]));
    ASSERT_TRUE(tieStrategy.Handle(players[1]));

    DropChip(4u, players[1].GetChip(), board, takenPositions);    ASSERT_FALSE(winStrategy.Handle(players[1]));
    ASSERT_TRUE(tieStrategy.Handle(players[2]));

    DropChip(5u, players[2].GetChip(), board, takenPositions);    ASSERT_FALSE(winStrategy.Handle(players[2]));
    ASSERT_TRUE(tieStrategy.Handle(players[0]));

    DropChip(3u, players[0].GetChip(), board, takenPositions);    ASSERT_FALSE(winStrategy.Handle(players[0]));
    ASSERT_TRUE(tieStrategy.Handle(players[1]));

    DropChip(4u, players[1].GetChip(), board, takenPositions);    ASSERT_FALSE(winStrategy.Handle(players[1]));
    ASSERT_TRUE(tieStrategy.Handle(players[2]));

    DropChip(5u, players[2].GetChip(), board, takenPositions);    ASSERT_FALSE(winStrategy.Handle(players[2]));
    ASSERT_TRUE(tieStrategy.Handle(players[0]));

    DropChip(6u, players[0].GetChip(), board, takenPositions);    ASSERT_FALSE(winStrategy.Handle(players[0]));
    ASSERT_TRUE(tieStrategy.Handle(players[1]));

    DropChip(6u, players[1].GetChip(), board, takenPositions);    ASSERT_FALSE(winStrategy.Handle(players[1]));
    ASSERT_TRUE(tieStrategy.Handle(players[2]));

    DropChip(6u, players[2].GetChip(), board, takenPositions);    ASSERT_FALSE(winStrategy.Handle(players[2]));
    ASSERT_TRUE(tieStrategy.Handle(players[0]));

    DropChip(7u, players[0].GetChip(), board, takenPositions);    ASSERT_FALSE(winStrategy.Handle(players[0]));
    ASSERT_TRUE(tieStrategy.Handle(players[1]));

    DropChip(7u, players[1].GetChip(), board, takenPositions);    ASSERT_FALSE(winStrategy.Handle(players[1]));
    ASSERT_TRUE(tieStrategy.Handle(players[2]));

    DropChip(7u, players[2].GetChip(), board, takenPositions);    ASSERT_FALSE(winStrategy.Handle(players[2]));
    ASSERT_TRUE(tieStrategy.Handle(players[0]));
}

// This test may not be such an edge case... Enhancement seems possible.
TEST_F(GameResolutionStrategyTestFixture, /*DISABLED*/TieHandle_ClassicGameBoardEdgeCaseVertical_ReturnsTrue)
{
    cxmodel::Board board = MakeClassicBoard();
    const size_t inARowValue = 4u;
    const std::vector<cxmodel::Player> players = MakeTwoPlayersList();
    std::vector<cxmodel::IBoard::Position> takenPositions;
    ASSERT_TRUE(takenPositions.empty());

    cxmodel::WinGameResolutionStrategy winStrategy{board, inARowValue, players, takenPositions};

    DropChip(4u, players[0].GetChip(), board, takenPositions);    ASSERT_FALSE(winStrategy.Handle(players[0]));
    DropChip(4u, players[1].GetChip(), board, takenPositions);    ASSERT_FALSE(winStrategy.Handle(players[1]));

    DropChip(4u, players[0].GetChip(), board, takenPositions);    ASSERT_FALSE(winStrategy.Handle(players[0]));
    DropChip(4u, players[1].GetChip(), board, takenPositions);    ASSERT_FALSE(winStrategy.Handle(players[1]));

    DropChip(4u, players[0].GetChip(), board, takenPositions);    ASSERT_FALSE(winStrategy.Handle(players[0]));
    DropChip(4u, players[1].GetChip(), board, takenPositions);    ASSERT_FALSE(winStrategy.Handle(players[1]));

    DropChip(3u, players[0].GetChip(), board, takenPositions);    ASSERT_FALSE(winStrategy.Handle(players[0]));
    DropChip(3u, players[1].GetChip(), board, takenPositions);    ASSERT_FALSE(winStrategy.Handle(players[1]));

    DropChip(3u, players[0].GetChip(), board, takenPositions);    ASSERT_FALSE(winStrategy.Handle(players[0]));
    DropChip(3u, players[1].GetChip(), board, takenPositions);    ASSERT_FALSE(winStrategy.Handle(players[1]));

    DropChip(3u, players[0].GetChip(), board, takenPositions);    ASSERT_FALSE(winStrategy.Handle(players[0]));
    DropChip(3u, players[1].GetChip(), board, takenPositions);    ASSERT_FALSE(winStrategy.Handle(players[1]));

    DropChip(0u, players[0].GetChip(), board, takenPositions);    ASSERT_FALSE(winStrategy.Handle(players[0]));
    DropChip(0u, players[1].GetChip(), board, takenPositions);    ASSERT_FALSE(winStrategy.Handle(players[1]));

    DropChip(0u, players[0].GetChip(), board, takenPositions);    ASSERT_FALSE(winStrategy.Handle(players[0]));
    DropChip(0u, players[1].GetChip(), board, takenPositions);    ASSERT_FALSE(winStrategy.Handle(players[1]));

    DropChip(0u, players[0].GetChip(), board, takenPositions);    ASSERT_FALSE(winStrategy.Handle(players[0]));
    DropChip(0u, players[1].GetChip(), board, takenPositions);    ASSERT_FALSE(winStrategy.Handle(players[1]));

    DropChip(1u, players[0].GetChip(), board, takenPositions);    ASSERT_FALSE(winStrategy.Handle(players[0]));
    DropChip(2u, players[1].GetChip(), board, takenPositions);    ASSERT_FALSE(winStrategy.Handle(players[1]));

    DropChip(2u, players[0].GetChip(), board, takenPositions);    ASSERT_FALSE(winStrategy.Handle(players[0]));
    DropChip(1u, players[1].GetChip(), board, takenPositions);    ASSERT_FALSE(winStrategy.Handle(players[1]));

    DropChip(1u, players[0].GetChip(), board, takenPositions);    ASSERT_FALSE(winStrategy.Handle(players[0]));
    DropChip(2u, players[1].GetChip(), board, takenPositions);    ASSERT_FALSE(winStrategy.Handle(players[1]));

    DropChip(2u, players[0].GetChip(), board, takenPositions);    ASSERT_FALSE(winStrategy.Handle(players[0]));
    DropChip(1u, players[1].GetChip(), board, takenPositions);    ASSERT_FALSE(winStrategy.Handle(players[1]));

    DropChip(1u, players[0].GetChip(), board, takenPositions);    ASSERT_FALSE(winStrategy.Handle(players[0]));
    DropChip(2u, players[1].GetChip(), board, takenPositions);    ASSERT_FALSE(winStrategy.Handle(players[1]));

    DropChip(2u, players[0].GetChip(), board, takenPositions);    ASSERT_FALSE(winStrategy.Handle(players[0]));
    DropChip(1u, players[1].GetChip(), board, takenPositions);    ASSERT_FALSE(winStrategy.Handle(players[1]));

    DropChip(6u, players[0].GetChip(), board, takenPositions);    ASSERT_FALSE(winStrategy.Handle(players[0]));
    DropChip(5u, players[1].GetChip(), board, takenPositions);    ASSERT_FALSE(winStrategy.Handle(players[1]));

    DropChip(5u, players[0].GetChip(), board, takenPositions);    ASSERT_FALSE(winStrategy.Handle(players[0]));
    DropChip(6u, players[1].GetChip(), board, takenPositions);    ASSERT_FALSE(winStrategy.Handle(players[1]));

    DropChip(6u, players[0].GetChip(), board, takenPositions);    ASSERT_FALSE(winStrategy.Handle(players[0]));
    DropChip(5u, players[1].GetChip(), board, takenPositions);    ASSERT_FALSE(winStrategy.Handle(players[1]));

    DropChip(5u, players[0].GetChip(), board, takenPositions);    ASSERT_FALSE(winStrategy.Handle(players[0]));
    DropChip(5u, players[1].GetChip(), board, takenPositions);    ASSERT_FALSE(winStrategy.Handle(players[1]));

    cxmodel::TieGameResolutionStrategy tieStrategy{board, inARowValue, players, takenPositions};
    ASSERT_FALSE(tieStrategy.Handle(players[0]));

    // From this point on, the game should report a tie on every move, until completion:
    DropChip(5u, players[0].GetChip(), board, takenPositions);    ASSERT_FALSE(winStrategy.Handle(players[0]));
    ASSERT_TRUE(tieStrategy.Handle(players[1]));

    DropChip(6u, players[1].GetChip(), board, takenPositions);    ASSERT_FALSE(winStrategy.Handle(players[1]));
    ASSERT_TRUE(tieStrategy.Handle(players[0]));

    DropChip(6u, players[0].GetChip(), board, takenPositions);    ASSERT_FALSE(winStrategy.Handle(players[0]));
    ASSERT_TRUE(tieStrategy.Handle(players[1]));

    DropChip(6u, players[1].GetChip(), board, takenPositions);    ASSERT_FALSE(winStrategy.Handle(players[1]));
    ASSERT_TRUE(tieStrategy.Handle(players[0]));
}

TEST_F(GameResolutionStrategyTestFixture, /*DISABLED*/TieHandle_9by8GameBoardConnect7ThreePlayersEdgeCaseVertical_ReturnsTrue)
{
    cxmodel::Board board = Make9By8Board();
    const size_t inARowValue = 7u;
    const std::vector<cxmodel::Player> players = MakeThreePlayersList();
    std::vector<cxmodel::IBoard::Position> takenPositions;
    ASSERT_TRUE(takenPositions.empty());

    cxmodel::WinGameResolutionStrategy winStrategy{board, inARowValue, players, takenPositions};

    DropChip(0u, players[0].GetChip(), board, takenPositions);    ASSERT_FALSE(winStrategy.Handle(players[0]));
    DropChip(1u, players[1].GetChip(), board, takenPositions);    ASSERT_FALSE(winStrategy.Handle(players[1]));
    DropChip(0u, players[2].GetChip(), board, takenPositions);    ASSERT_FALSE(winStrategy.Handle(players[2]));

    DropChip(1u, players[0].GetChip(), board, takenPositions);    ASSERT_FALSE(winStrategy.Handle(players[0]));
    DropChip(0u, players[1].GetChip(), board, takenPositions);    ASSERT_FALSE(winStrategy.Handle(players[1]));
    DropChip(1u, players[2].GetChip(), board, takenPositions);    ASSERT_FALSE(winStrategy.Handle(players[2]));

    DropChip(0u, players[0].GetChip(), board, takenPositions);    ASSERT_FALSE(winStrategy.Handle(players[0]));
    DropChip(1u, players[1].GetChip(), board, takenPositions);    ASSERT_FALSE(winStrategy.Handle(players[1]));
    DropChip(0u, players[2].GetChip(), board, takenPositions);    ASSERT_FALSE(winStrategy.Handle(players[2]));

    DropChip(1u, players[0].GetChip(), board, takenPositions);    ASSERT_FALSE(winStrategy.Handle(players[0]));
    DropChip(0u, players[1].GetChip(), board, takenPositions);    ASSERT_FALSE(winStrategy.Handle(players[1]));
    DropChip(1u, players[2].GetChip(), board, takenPositions);    ASSERT_FALSE(winStrategy.Handle(players[2]));

    DropChip(0u, players[0].GetChip(), board, takenPositions);    ASSERT_FALSE(winStrategy.Handle(players[0]));
    DropChip(1u, players[1].GetChip(), board, takenPositions);    ASSERT_FALSE(winStrategy.Handle(players[1]));
    DropChip(0u, players[2].GetChip(), board, takenPositions);    ASSERT_FALSE(winStrategy.Handle(players[2]));

    DropChip(1u, players[0].GetChip(), board, takenPositions);    ASSERT_FALSE(winStrategy.Handle(players[0]));
    DropChip(0u, players[1].GetChip(), board, takenPositions);    ASSERT_FALSE(winStrategy.Handle(players[1]));
    DropChip(1u, players[2].GetChip(), board, takenPositions);    ASSERT_FALSE(winStrategy.Handle(players[2]));

    DropChip(2u, players[0].GetChip(), board, takenPositions);    ASSERT_FALSE(winStrategy.Handle(players[0]));
    DropChip(3u, players[1].GetChip(), board, takenPositions);    ASSERT_FALSE(winStrategy.Handle(players[1]));
    DropChip(2u, players[2].GetChip(), board, takenPositions);    ASSERT_FALSE(winStrategy.Handle(players[2]));

    DropChip(3u, players[0].GetChip(), board, takenPositions);    ASSERT_FALSE(winStrategy.Handle(players[0]));
    DropChip(2u, players[1].GetChip(), board, takenPositions);    ASSERT_FALSE(winStrategy.Handle(players[1]));
    DropChip(3u, players[2].GetChip(), board, takenPositions);    ASSERT_FALSE(winStrategy.Handle(players[2]));

    DropChip(2u, players[0].GetChip(), board, takenPositions);    ASSERT_FALSE(winStrategy.Handle(players[0]));
    DropChip(3u, players[1].GetChip(), board, takenPositions);    ASSERT_FALSE(winStrategy.Handle(players[1]));
    DropChip(2u, players[2].GetChip(), board, takenPositions);    ASSERT_FALSE(winStrategy.Handle(players[2]));

    DropChip(3u, players[0].GetChip(), board, takenPositions);    ASSERT_FALSE(winStrategy.Handle(players[0]));
    DropChip(2u, players[1].GetChip(), board, takenPositions);    ASSERT_FALSE(winStrategy.Handle(players[1]));
    DropChip(3u, players[2].GetChip(), board, takenPositions);    ASSERT_FALSE(winStrategy.Handle(players[2]));

    DropChip(2u, players[0].GetChip(), board, takenPositions);    ASSERT_FALSE(winStrategy.Handle(players[0]));
    DropChip(3u, players[1].GetChip(), board, takenPositions);    ASSERT_FALSE(winStrategy.Handle(players[1]));
    DropChip(2u, players[2].GetChip(), board, takenPositions);    ASSERT_FALSE(winStrategy.Handle(players[2]));

    DropChip(3u, players[0].GetChip(), board, takenPositions);    ASSERT_FALSE(winStrategy.Handle(players[0]));
    DropChip(2u, players[1].GetChip(), board, takenPositions);    ASSERT_FALSE(winStrategy.Handle(players[1]));
    DropChip(3u, players[2].GetChip(), board, takenPositions);    ASSERT_FALSE(winStrategy.Handle(players[2]));

    DropChip(4u, players[0].GetChip(), board, takenPositions);    ASSERT_FALSE(winStrategy.Handle(players[0]));
    DropChip(4u, players[1].GetChip(), board, takenPositions);    ASSERT_FALSE(winStrategy.Handle(players[1]));
    DropChip(4u, players[2].GetChip(), board, takenPositions);    ASSERT_FALSE(winStrategy.Handle(players[2]));

    DropChip(4u, players[0].GetChip(), board, takenPositions);    ASSERT_FALSE(winStrategy.Handle(players[0]));
    DropChip(4u, players[1].GetChip(), board, takenPositions);    ASSERT_FALSE(winStrategy.Handle(players[1]));
    DropChip(4u, players[2].GetChip(), board, takenPositions);    ASSERT_FALSE(winStrategy.Handle(players[2]));

    DropChip(4u, players[0].GetChip(), board, takenPositions);    ASSERT_FALSE(winStrategy.Handle(players[0]));
    DropChip(4u, players[1].GetChip(), board, takenPositions);    ASSERT_FALSE(winStrategy.Handle(players[1]));
    DropChip(4u, players[2].GetChip(), board, takenPositions);    ASSERT_FALSE(winStrategy.Handle(players[2]));

    DropChip(5u, players[0].GetChip(), board, takenPositions);    ASSERT_FALSE(winStrategy.Handle(players[0]));
    DropChip(6u, players[1].GetChip(), board, takenPositions);    ASSERT_FALSE(winStrategy.Handle(players[1]));
    DropChip(7u, players[2].GetChip(), board, takenPositions);    ASSERT_FALSE(winStrategy.Handle(players[2]));

    DropChip(7u, players[0].GetChip(), board, takenPositions);    ASSERT_FALSE(winStrategy.Handle(players[0]));
    DropChip(5u, players[1].GetChip(), board, takenPositions);    ASSERT_FALSE(winStrategy.Handle(players[1]));
    DropChip(6u, players[2].GetChip(), board, takenPositions);    ASSERT_FALSE(winStrategy.Handle(players[2]));

    DropChip(5u, players[0].GetChip(), board, takenPositions);    ASSERT_FALSE(winStrategy.Handle(players[0]));
    DropChip(6u, players[1].GetChip(), board, takenPositions);    ASSERT_FALSE(winStrategy.Handle(players[1]));
    DropChip(7u, players[2].GetChip(), board, takenPositions);    ASSERT_FALSE(winStrategy.Handle(players[2]));

    DropChip(7u, players[0].GetChip(), board, takenPositions);    ASSERT_FALSE(winStrategy.Handle(players[0]));

    cxmodel::TieGameResolutionStrategy tieStrategy{board, inARowValue, players, takenPositions};
    ASSERT_FALSE(tieStrategy.Handle(players[1]));

    // From this point on, the game should report a tie on every move, until completion:
    DropChip(5u, players[1].GetChip(), board, takenPositions);    ASSERT_FALSE(winStrategy.Handle(players[1]));
    ASSERT_TRUE(tieStrategy.Handle(players[2]));

    DropChip(5u, players[2].GetChip(), board, takenPositions);    ASSERT_FALSE(winStrategy.Handle(players[2]));
    ASSERT_TRUE(tieStrategy.Handle(players[0]));

    DropChip(5u, players[0].GetChip(), board, takenPositions);    ASSERT_FALSE(winStrategy.Handle(players[0]));
    ASSERT_TRUE(tieStrategy.Handle(players[1]));

    DropChip(5u, players[1].GetChip(), board, takenPositions);    ASSERT_FALSE(winStrategy.Handle(players[1]));
    ASSERT_TRUE(tieStrategy.Handle(players[2]));

    DropChip(5u, players[2].GetChip(), board, takenPositions);    ASSERT_FALSE(winStrategy.Handle(players[2]));
    ASSERT_TRUE(tieStrategy.Handle(players[0]));

    DropChip(5u, players[0].GetChip(), board, takenPositions);    ASSERT_FALSE(winStrategy.Handle(players[0]));
    ASSERT_TRUE(tieStrategy.Handle(players[1]));

    DropChip(6u, players[1].GetChip(), board, takenPositions);    ASSERT_FALSE(winStrategy.Handle(players[1]));
    ASSERT_TRUE(tieStrategy.Handle(players[2]));

    DropChip(6u, players[2].GetChip(), board, takenPositions);    ASSERT_FALSE(winStrategy.Handle(players[2]));
    ASSERT_TRUE(tieStrategy.Handle(players[0]));

    DropChip(6u, players[0].GetChip(), board, takenPositions);    ASSERT_FALSE(winStrategy.Handle(players[0]));
    ASSERT_TRUE(tieStrategy.Handle(players[1]));

    DropChip(6u, players[1].GetChip(), board, takenPositions);    ASSERT_FALSE(winStrategy.Handle(players[1]));
    ASSERT_TRUE(tieStrategy.Handle(players[2]));

    DropChip(6u, players[2].GetChip(), board, takenPositions);    ASSERT_FALSE(winStrategy.Handle(players[2]));
    ASSERT_TRUE(tieStrategy.Handle(players[0]));

    DropChip(6u, players[0].GetChip(), board, takenPositions);    ASSERT_FALSE(winStrategy.Handle(players[0]));
    ASSERT_TRUE(tieStrategy.Handle(players[1]));

    DropChip(7u, players[1].GetChip(), board, takenPositions);    ASSERT_FALSE(winStrategy.Handle(players[1]));
    ASSERT_TRUE(tieStrategy.Handle(players[2]));

    DropChip(7u, players[2].GetChip(), board, takenPositions);    ASSERT_FALSE(winStrategy.Handle(players[2]));
    ASSERT_TRUE(tieStrategy.Handle(players[0]));

    DropChip(7u, players[0].GetChip(), board, takenPositions);    ASSERT_FALSE(winStrategy.Handle(players[0]));
    ASSERT_TRUE(tieStrategy.Handle(players[1]));

    DropChip(7u, players[1].GetChip(), board, takenPositions);    ASSERT_FALSE(winStrategy.Handle(players[1]));
    ASSERT_TRUE(tieStrategy.Handle(players[2]));

    DropChip(7u, players[2].GetChip(), board, takenPositions);    ASSERT_FALSE(winStrategy.Handle(players[2]));
    ASSERT_TRUE(tieStrategy.Handle(players[0]));
}

TEST_F(GameResolutionStrategyTestFixture, /*DISABLED*/TieHandle_ClassicGameBoardEdgeCaseDiagonalUpward_ReturnsTrue)
{
    cxmodel::Board board = MakeClassicBoard();
    const size_t inARowValue = 4u;
    const std::vector<cxmodel::Player> players = MakeTwoPlayersList();
    std::vector<cxmodel::IBoard::Position> takenPositions;
    ASSERT_TRUE(takenPositions.empty());

    cxmodel::WinGameResolutionStrategy winStrategy{board, inARowValue, players, takenPositions};

    DropChip(0u, players[0].GetChip(), board, takenPositions);    ASSERT_FALSE(winStrategy.Handle(players[0]));
    DropChip(0u, players[1].GetChip(), board, takenPositions);    ASSERT_FALSE(winStrategy.Handle(players[1]));

    DropChip(0u, players[0].GetChip(), board, takenPositions);    ASSERT_FALSE(winStrategy.Handle(players[0]));
    DropChip(0u, players[1].GetChip(), board, takenPositions);    ASSERT_FALSE(winStrategy.Handle(players[1]));

    DropChip(0u, players[0].GetChip(), board, takenPositions);    ASSERT_FALSE(winStrategy.Handle(players[0]));
    DropChip(0u, players[1].GetChip(), board, takenPositions);    ASSERT_FALSE(winStrategy.Handle(players[1]));

    DropChip(1u, players[0].GetChip(), board, takenPositions);    ASSERT_FALSE(winStrategy.Handle(players[0]));
    DropChip(2u, players[1].GetChip(), board, takenPositions);    ASSERT_FALSE(winStrategy.Handle(players[1]));

    DropChip(2u, players[0].GetChip(), board, takenPositions);    ASSERT_FALSE(winStrategy.Handle(players[0]));
    DropChip(1u, players[1].GetChip(), board, takenPositions);    ASSERT_FALSE(winStrategy.Handle(players[1]));

    DropChip(4u, players[0].GetChip(), board, takenPositions);    ASSERT_FALSE(winStrategy.Handle(players[0]));
    DropChip(5u, players[1].GetChip(), board, takenPositions);    ASSERT_FALSE(winStrategy.Handle(players[1]));

    DropChip(6u, players[0].GetChip(), board, takenPositions);    ASSERT_FALSE(winStrategy.Handle(players[0]));
    DropChip(5u, players[1].GetChip(), board, takenPositions);    ASSERT_FALSE(winStrategy.Handle(players[1]));

    DropChip(6u, players[0].GetChip(), board, takenPositions);    ASSERT_FALSE(winStrategy.Handle(players[0]));
    DropChip(6u, players[1].GetChip(), board, takenPositions);    ASSERT_FALSE(winStrategy.Handle(players[1]));

    DropChip(1u, players[0].GetChip(), board, takenPositions);    ASSERT_FALSE(winStrategy.Handle(players[0]));
    DropChip(1u, players[1].GetChip(), board, takenPositions);    ASSERT_FALSE(winStrategy.Handle(players[1]));

    DropChip(1u, players[0].GetChip(), board, takenPositions);    ASSERT_FALSE(winStrategy.Handle(players[0]));
    DropChip(1u, players[1].GetChip(), board, takenPositions);    ASSERT_FALSE(winStrategy.Handle(players[1]));

    DropChip(3u, players[0].GetChip(), board, takenPositions);    ASSERT_FALSE(winStrategy.Handle(players[0]));
    DropChip(2u, players[1].GetChip(), board, takenPositions);    ASSERT_FALSE(winStrategy.Handle(players[1]));

    DropChip(2u, players[0].GetChip(), board, takenPositions);    ASSERT_FALSE(winStrategy.Handle(players[0]));
    DropChip(2u, players[1].GetChip(), board, takenPositions);    ASSERT_FALSE(winStrategy.Handle(players[1]));

    DropChip(2u, players[0].GetChip(), board, takenPositions);    ASSERT_FALSE(winStrategy.Handle(players[0]));
    DropChip(3u, players[1].GetChip(), board, takenPositions);    ASSERT_FALSE(winStrategy.Handle(players[1]));

    DropChip(3u, players[0].GetChip(), board, takenPositions);    ASSERT_FALSE(winStrategy.Handle(players[0]));
    DropChip(3u, players[1].GetChip(), board, takenPositions);    ASSERT_FALSE(winStrategy.Handle(players[1]));

    DropChip(3u, players[0].GetChip(), board, takenPositions);    ASSERT_FALSE(winStrategy.Handle(players[0]));
    DropChip(3u, players[1].GetChip(), board, takenPositions);    ASSERT_FALSE(winStrategy.Handle(players[1]));

    DropChip(5u, players[0].GetChip(), board, takenPositions);    ASSERT_FALSE(winStrategy.Handle(players[0]));
    DropChip(4u, players[1].GetChip(), board, takenPositions);    ASSERT_FALSE(winStrategy.Handle(players[1]));

    DropChip(4u, players[0].GetChip(), board, takenPositions);    ASSERT_FALSE(winStrategy.Handle(players[0]));
    DropChip(5u, players[1].GetChip(), board, takenPositions);    ASSERT_FALSE(winStrategy.Handle(players[1]));

    DropChip(6u, players[0].GetChip(), board, takenPositions);    ASSERT_FALSE(winStrategy.Handle(players[0]));
    DropChip(4u, players[1].GetChip(), board, takenPositions);    ASSERT_FALSE(winStrategy.Handle(players[1]));

    DropChip(4u, players[0].GetChip(), board, takenPositions);    ASSERT_FALSE(winStrategy.Handle(players[0]));
    DropChip(5u, players[1].GetChip(), board, takenPositions);    ASSERT_FALSE(winStrategy.Handle(players[1]));

    DropChip(6u, players[0].GetChip(), board, takenPositions);    ASSERT_FALSE(winStrategy.Handle(players[0]));

    cxmodel::TieGameResolutionStrategy tieStrategy{board, inARowValue, players, takenPositions};
    ASSERT_FALSE(tieStrategy.Handle(players[1]));

    // From this point on, the game should report a tie on every move, until completion:
    DropChip(4u, players[1].GetChip(), board, takenPositions);    ASSERT_FALSE(winStrategy.Handle(players[1]));
    ASSERT_TRUE(tieStrategy.Handle(players[0]));

    DropChip(5u, players[0].GetChip(), board, takenPositions);    ASSERT_FALSE(winStrategy.Handle(players[0]));
    ASSERT_TRUE(tieStrategy.Handle(players[1]));

    DropChip(6u, players[1].GetChip(), board, takenPositions);    ASSERT_FALSE(winStrategy.Handle(players[1]));
    ASSERT_TRUE(tieStrategy.Handle(players[0]));
}

TEST_F(GameResolutionStrategyTestFixture, /*DISABLED*/TieHandle_9by8GameBoardConnect7ThreePlayersEdgeCaseDiagonalUpward_ReturnsTrue)
{
    cxmodel::Board board = Make9By8Board();
    const size_t inARowValue = 7u;
    const std::vector<cxmodel::Player> players = MakeThreePlayersList();
    std::vector<cxmodel::IBoard::Position> takenPositions;
    ASSERT_TRUE(takenPositions.empty());

    cxmodel::WinGameResolutionStrategy winStrategy{board, inARowValue, players, takenPositions};

    DropChip(0u, players[0].GetChip(), board, takenPositions);    ASSERT_FALSE(winStrategy.Handle(players[0]));
    DropChip(0u, players[1].GetChip(), board, takenPositions);    ASSERT_FALSE(winStrategy.Handle(players[1]));
    DropChip(0u, players[2].GetChip(), board, takenPositions);    ASSERT_FALSE(winStrategy.Handle(players[2]));

    DropChip(0u, players[0].GetChip(), board, takenPositions);    ASSERT_FALSE(winStrategy.Handle(players[0]));
    DropChip(0u, players[1].GetChip(), board, takenPositions);    ASSERT_FALSE(winStrategy.Handle(players[1]));
    DropChip(0u, players[2].GetChip(), board, takenPositions);    ASSERT_FALSE(winStrategy.Handle(players[2]));

    DropChip(0u, players[0].GetChip(), board, takenPositions);    ASSERT_FALSE(winStrategy.Handle(players[0]));
    DropChip(0u, players[1].GetChip(), board, takenPositions);    ASSERT_FALSE(winStrategy.Handle(players[1]));
    DropChip(0u, players[2].GetChip(), board, takenPositions);    ASSERT_FALSE(winStrategy.Handle(players[2]));

    DropChip(1u, players[0].GetChip(), board, takenPositions);    ASSERT_FALSE(winStrategy.Handle(players[0]));
    DropChip(1u, players[1].GetChip(), board, takenPositions);    ASSERT_FALSE(winStrategy.Handle(players[1]));
    DropChip(1u, players[2].GetChip(), board, takenPositions);    ASSERT_FALSE(winStrategy.Handle(players[2]));

    DropChip(1u, players[0].GetChip(), board, takenPositions);    ASSERT_FALSE(winStrategy.Handle(players[0]));
    DropChip(1u, players[1].GetChip(), board, takenPositions);    ASSERT_FALSE(winStrategy.Handle(players[1]));
    DropChip(1u, players[2].GetChip(), board, takenPositions);    ASSERT_FALSE(winStrategy.Handle(players[2]));

    DropChip(1u, players[0].GetChip(), board, takenPositions);    ASSERT_FALSE(winStrategy.Handle(players[0]));
    DropChip(1u, players[1].GetChip(), board, takenPositions);    ASSERT_FALSE(winStrategy.Handle(players[1]));
    DropChip(1u, players[2].GetChip(), board, takenPositions);    ASSERT_FALSE(winStrategy.Handle(players[2]));

    DropChip(3u, players[0].GetChip(), board, takenPositions);    ASSERT_FALSE(winStrategy.Handle(players[0]));
    DropChip(2u, players[1].GetChip(), board, takenPositions);    ASSERT_FALSE(winStrategy.Handle(players[1]));
    DropChip(2u, players[2].GetChip(), board, takenPositions);    ASSERT_FALSE(winStrategy.Handle(players[2]));

    DropChip(3u, players[0].GetChip(), board, takenPositions);    ASSERT_FALSE(winStrategy.Handle(players[0]));
    DropChip(3u, players[1].GetChip(), board, takenPositions);    ASSERT_FALSE(winStrategy.Handle(players[1]));
    DropChip(2u, players[2].GetChip(), board, takenPositions);    ASSERT_FALSE(winStrategy.Handle(players[2]));

    DropChip(2u, players[0].GetChip(), board, takenPositions);    ASSERT_FALSE(winStrategy.Handle(players[0]));
    DropChip(3u, players[1].GetChip(), board, takenPositions);    ASSERT_FALSE(winStrategy.Handle(players[1]));
    DropChip(3u, players[2].GetChip(), board, takenPositions);    ASSERT_FALSE(winStrategy.Handle(players[2]));

    DropChip(2u, players[0].GetChip(), board, takenPositions);    ASSERT_FALSE(winStrategy.Handle(players[0]));
    DropChip(2u, players[1].GetChip(), board, takenPositions);    ASSERT_FALSE(winStrategy.Handle(players[1]));
    DropChip(3u, players[2].GetChip(), board, takenPositions);    ASSERT_FALSE(winStrategy.Handle(players[2]));

    DropChip(3u, players[0].GetChip(), board, takenPositions);    ASSERT_FALSE(winStrategy.Handle(players[0]));
    DropChip(2u, players[1].GetChip(), board, takenPositions);    ASSERT_FALSE(winStrategy.Handle(players[1]));
    DropChip(2u, players[2].GetChip(), board, takenPositions);    ASSERT_FALSE(winStrategy.Handle(players[2]));

    DropChip(5u, players[0].GetChip(), board, takenPositions);    ASSERT_FALSE(winStrategy.Handle(players[0]));
    DropChip(4u, players[1].GetChip(), board, takenPositions);    ASSERT_FALSE(winStrategy.Handle(players[1]));
    DropChip(4u, players[2].GetChip(), board, takenPositions);    ASSERT_FALSE(winStrategy.Handle(players[2]));

    DropChip(5u, players[0].GetChip(), board, takenPositions);    ASSERT_FALSE(winStrategy.Handle(players[0]));
    DropChip(5u, players[1].GetChip(), board, takenPositions);    ASSERT_FALSE(winStrategy.Handle(players[1]));
    DropChip(4u, players[2].GetChip(), board, takenPositions);    ASSERT_FALSE(winStrategy.Handle(players[2]));

    DropChip(4u, players[0].GetChip(), board, takenPositions);    ASSERT_FALSE(winStrategy.Handle(players[0]));
    DropChip(5u, players[1].GetChip(), board, takenPositions);    ASSERT_FALSE(winStrategy.Handle(players[1]));
    DropChip(5u, players[2].GetChip(), board, takenPositions);    ASSERT_FALSE(winStrategy.Handle(players[2]));

    DropChip(4u, players[0].GetChip(), board, takenPositions);    ASSERT_FALSE(winStrategy.Handle(players[0]));
    DropChip(4u, players[1].GetChip(), board, takenPositions);    ASSERT_FALSE(winStrategy.Handle(players[1]));
    DropChip(6u, players[2].GetChip(), board, takenPositions);    ASSERT_FALSE(winStrategy.Handle(players[2]));

    DropChip(7u, players[0].GetChip(), board, takenPositions);    ASSERT_FALSE(winStrategy.Handle(players[0]));
    DropChip(7u, players[1].GetChip(), board, takenPositions);    ASSERT_FALSE(winStrategy.Handle(players[1]));
    DropChip(6u, players[2].GetChip(), board, takenPositions);    ASSERT_FALSE(winStrategy.Handle(players[2]));

    DropChip(6u, players[0].GetChip(), board, takenPositions);    ASSERT_FALSE(winStrategy.Handle(players[0]));
    DropChip(7u, players[1].GetChip(), board, takenPositions);    ASSERT_FALSE(winStrategy.Handle(players[1]));
    DropChip(6u, players[2].GetChip(), board, takenPositions);    ASSERT_FALSE(winStrategy.Handle(players[2]));

    DropChip(7u, players[0].GetChip(), board, takenPositions);    ASSERT_FALSE(winStrategy.Handle(players[0]));
    DropChip(5u, players[1].GetChip(), board, takenPositions);    ASSERT_FALSE(winStrategy.Handle(players[1]));
    DropChip(5u, players[2].GetChip(), board, takenPositions);    ASSERT_FALSE(winStrategy.Handle(players[2]));

    DropChip(5u, players[0].GetChip(), board, takenPositions);    ASSERT_FALSE(winStrategy.Handle(players[0]));

    cxmodel::TieGameResolutionStrategy tieStrategy{board, inARowValue, players, takenPositions};
    ASSERT_FALSE(tieStrategy.Handle(players[1]));

    // From this point on, the game should report a tie on every move, until completion:
    DropChip(5u, players[1].GetChip(), board, takenPositions);    ASSERT_FALSE(winStrategy.Handle(players[1]));
    ASSERT_TRUE(tieStrategy.Handle(players[2]));

    DropChip(2u, players[2].GetChip(), board, takenPositions);    ASSERT_FALSE(winStrategy.Handle(players[2]));
    ASSERT_TRUE(tieStrategy.Handle(players[0]));

    DropChip(3u, players[0].GetChip(), board, takenPositions);    ASSERT_FALSE(winStrategy.Handle(players[0]));
    ASSERT_TRUE(tieStrategy.Handle(players[1]));

    DropChip(3u, players[1].GetChip(), board, takenPositions);    ASSERT_FALSE(winStrategy.Handle(players[1]));
    ASSERT_TRUE(tieStrategy.Handle(players[2]));

    DropChip(4u, players[2].GetChip(), board, takenPositions);    ASSERT_FALSE(winStrategy.Handle(players[2]));
    ASSERT_TRUE(tieStrategy.Handle(players[0]));

    DropChip(4u, players[0].GetChip(), board, takenPositions);    ASSERT_FALSE(winStrategy.Handle(players[0]));
    ASSERT_TRUE(tieStrategy.Handle(players[1]));

    DropChip(4u, players[1].GetChip(), board, takenPositions);    ASSERT_FALSE(winStrategy.Handle(players[1]));
    ASSERT_TRUE(tieStrategy.Handle(players[2]));

    DropChip(6u, players[2].GetChip(), board, takenPositions);    ASSERT_FALSE(winStrategy.Handle(players[2]));
    ASSERT_TRUE(tieStrategy.Handle(players[0]));

    DropChip(6u, players[0].GetChip(), board, takenPositions);    ASSERT_FALSE(winStrategy.Handle(players[0]));
    ASSERT_TRUE(tieStrategy.Handle(players[1]));

    DropChip(6u, players[1].GetChip(), board, takenPositions);    ASSERT_FALSE(winStrategy.Handle(players[1]));
    ASSERT_TRUE(tieStrategy.Handle(players[2]));

    DropChip(6u, players[2].GetChip(), board, takenPositions);    ASSERT_FALSE(winStrategy.Handle(players[2]));
    ASSERT_TRUE(tieStrategy.Handle(players[0]));

    DropChip(6u, players[0].GetChip(), board, takenPositions);    ASSERT_FALSE(winStrategy.Handle(players[0]));
    ASSERT_TRUE(tieStrategy.Handle(players[1]));

    DropChip(7u, players[1].GetChip(), board, takenPositions);    ASSERT_FALSE(winStrategy.Handle(players[1]));
    ASSERT_TRUE(tieStrategy.Handle(players[2]));

    DropChip(7u, players[2].GetChip(), board, takenPositions);    ASSERT_FALSE(winStrategy.Handle(players[2]));
    ASSERT_TRUE(tieStrategy.Handle(players[0]));

    DropChip(7u, players[0].GetChip(), board, takenPositions);    ASSERT_FALSE(winStrategy.Handle(players[0]));
    ASSERT_TRUE(tieStrategy.Handle(players[1]));

    DropChip(7u, players[1].GetChip(), board, takenPositions);    ASSERT_FALSE(winStrategy.Handle(players[1]));
    ASSERT_TRUE(tieStrategy.Handle(players[2]));

    DropChip(7u, players[2].GetChip(), board, takenPositions);    ASSERT_FALSE(winStrategy.Handle(players[2]));
    ASSERT_TRUE(tieStrategy.Handle(players[0]));
}

TEST_F(GameResolutionStrategyTestFixture, /*DISABLED*/TieHandle_ClassicGameBoardEdgeCaseDiagonalDownward_ReturnsTrue)
{
    cxmodel::Board board = MakeClassicBoard();
    const size_t inARowValue = 4u;
    const std::vector<cxmodel::Player> players = MakeTwoPlayersList();
    std::vector<cxmodel::IBoard::Position> takenPositions;
    ASSERT_TRUE(takenPositions.empty());

    cxmodel::WinGameResolutionStrategy winStrategy{board, inARowValue, players, takenPositions};

    DropChip(6u, players[0].GetChip(), board, takenPositions);    ASSERT_FALSE(winStrategy.Handle(players[0]));
    DropChip(6u, players[1].GetChip(), board, takenPositions);    ASSERT_FALSE(winStrategy.Handle(players[1]));

    DropChip(6u, players[0].GetChip(), board, takenPositions);    ASSERT_FALSE(winStrategy.Handle(players[0]));
    DropChip(6u, players[1].GetChip(), board, takenPositions);    ASSERT_FALSE(winStrategy.Handle(players[1]));

    DropChip(6u, players[0].GetChip(), board, takenPositions);    ASSERT_FALSE(winStrategy.Handle(players[0]));
    DropChip(6u, players[1].GetChip(), board, takenPositions);    ASSERT_FALSE(winStrategy.Handle(players[1]));

    DropChip(5u, players[0].GetChip(), board, takenPositions);    ASSERT_FALSE(winStrategy.Handle(players[0]));
    DropChip(4u, players[1].GetChip(), board, takenPositions);    ASSERT_FALSE(winStrategy.Handle(players[1]));

    DropChip(4u, players[0].GetChip(), board, takenPositions);    ASSERT_FALSE(winStrategy.Handle(players[0]));
    DropChip(5u, players[1].GetChip(), board, takenPositions);    ASSERT_FALSE(winStrategy.Handle(players[1]));

    DropChip(2u, players[0].GetChip(), board, takenPositions);    ASSERT_FALSE(winStrategy.Handle(players[0]));
    DropChip(1u, players[1].GetChip(), board, takenPositions);    ASSERT_FALSE(winStrategy.Handle(players[1]));

    DropChip(0u, players[0].GetChip(), board, takenPositions);    ASSERT_FALSE(winStrategy.Handle(players[0]));
    DropChip(1u, players[1].GetChip(), board, takenPositions);    ASSERT_FALSE(winStrategy.Handle(players[1]));

    DropChip(0u, players[0].GetChip(), board, takenPositions);    ASSERT_FALSE(winStrategy.Handle(players[0]));
    DropChip(0u, players[1].GetChip(), board, takenPositions);    ASSERT_FALSE(winStrategy.Handle(players[1]));

    DropChip(5u, players[0].GetChip(), board, takenPositions);    ASSERT_FALSE(winStrategy.Handle(players[0]));
    DropChip(5u, players[1].GetChip(), board, takenPositions);    ASSERT_FALSE(winStrategy.Handle(players[1]));

    DropChip(5u, players[0].GetChip(), board, takenPositions);    ASSERT_FALSE(winStrategy.Handle(players[0]));
    DropChip(5u, players[1].GetChip(), board, takenPositions);    ASSERT_FALSE(winStrategy.Handle(players[1]));

    DropChip(3u, players[0].GetChip(), board, takenPositions);    ASSERT_FALSE(winStrategy.Handle(players[0]));
    DropChip(4u, players[1].GetChip(), board, takenPositions);    ASSERT_FALSE(winStrategy.Handle(players[1]));

    DropChip(4u, players[0].GetChip(), board, takenPositions);    ASSERT_FALSE(winStrategy.Handle(players[0]));
    DropChip(4u, players[1].GetChip(), board, takenPositions);    ASSERT_FALSE(winStrategy.Handle(players[1]));

    DropChip(4u, players[0].GetChip(), board, takenPositions);    ASSERT_FALSE(winStrategy.Handle(players[0]));
    DropChip(3u, players[1].GetChip(), board, takenPositions);    ASSERT_FALSE(winStrategy.Handle(players[1]));

    DropChip(3u, players[0].GetChip(), board, takenPositions);    ASSERT_FALSE(winStrategy.Handle(players[0]));
    DropChip(3u, players[1].GetChip(), board, takenPositions);    ASSERT_FALSE(winStrategy.Handle(players[1]));

    DropChip(3u, players[0].GetChip(), board, takenPositions);    ASSERT_FALSE(winStrategy.Handle(players[0]));
    DropChip(3u, players[1].GetChip(), board, takenPositions);    ASSERT_FALSE(winStrategy.Handle(players[1]));

    DropChip(1u, players[0].GetChip(), board, takenPositions);    ASSERT_FALSE(winStrategy.Handle(players[0]));
    DropChip(2u, players[1].GetChip(), board, takenPositions);    ASSERT_FALSE(winStrategy.Handle(players[1]));

    DropChip(2u, players[0].GetChip(), board, takenPositions);    ASSERT_FALSE(winStrategy.Handle(players[0]));
    DropChip(1u, players[1].GetChip(), board, takenPositions);    ASSERT_FALSE(winStrategy.Handle(players[1]));

    DropChip(0u, players[0].GetChip(), board, takenPositions);    ASSERT_FALSE(winStrategy.Handle(players[0]));
    DropChip(2u, players[1].GetChip(), board, takenPositions);    ASSERT_FALSE(winStrategy.Handle(players[1]));

    DropChip(2u, players[0].GetChip(), board, takenPositions);    ASSERT_FALSE(winStrategy.Handle(players[0]));
    DropChip(1u, players[1].GetChip(), board, takenPositions);    ASSERT_FALSE(winStrategy.Handle(players[1]));

    DropChip(0u, players[0].GetChip(), board, takenPositions);    ASSERT_FALSE(winStrategy.Handle(players[0]));

    cxmodel::TieGameResolutionStrategy tieStrategy{board, inARowValue, players, takenPositions};
    ASSERT_FALSE(tieStrategy.Handle(players[1]));

    // From this point on, the game should report a tie on every move, until completion:
    DropChip(2u, players[1].GetChip(), board, takenPositions);    ASSERT_FALSE(winStrategy.Handle(players[1]));
    ASSERT_TRUE(tieStrategy.Handle(players[0]));

    DropChip(1u, players[0].GetChip(), board, takenPositions);    ASSERT_FALSE(winStrategy.Handle(players[0]));
    ASSERT_TRUE(tieStrategy.Handle(players[1]));

    DropChip(0u, players[1].GetChip(), board, takenPositions);    ASSERT_FALSE(winStrategy.Handle(players[1]));
    ASSERT_TRUE(tieStrategy.Handle(players[0]));
}

TEST_F(GameResolutionStrategyTestFixture, /*DISABLED*/TieHandle_9by8GameBoardConnect7ThreePlayersEdgeCaseDiagonalDownward_ReturnsTrue)
{
    cxmodel::Board board = Make9By8Board();
    const size_t inARowValue = 7u;
    const std::vector<cxmodel::Player> players = MakeThreePlayersList();
    std::vector<cxmodel::IBoard::Position> takenPositions;
    ASSERT_TRUE(takenPositions.empty());

    cxmodel::WinGameResolutionStrategy winStrategy{board, inARowValue, players, takenPositions};

    DropChip(7u, players[0].GetChip(), board, takenPositions);    ASSERT_FALSE(winStrategy.Handle(players[0]));
    DropChip(7u, players[1].GetChip(), board, takenPositions);    ASSERT_FALSE(winStrategy.Handle(players[1]));
    DropChip(7u, players[2].GetChip(), board, takenPositions);    ASSERT_FALSE(winStrategy.Handle(players[2]));

    DropChip(7u, players[0].GetChip(), board, takenPositions);    ASSERT_FALSE(winStrategy.Handle(players[0]));
    DropChip(7u, players[1].GetChip(), board, takenPositions);    ASSERT_FALSE(winStrategy.Handle(players[1]));
    DropChip(7u, players[2].GetChip(), board, takenPositions);    ASSERT_FALSE(winStrategy.Handle(players[2]));

    DropChip(7u, players[0].GetChip(), board, takenPositions);    ASSERT_FALSE(winStrategy.Handle(players[0]));
    DropChip(7u, players[1].GetChip(), board, takenPositions);    ASSERT_FALSE(winStrategy.Handle(players[1]));
    DropChip(7u, players[2].GetChip(), board, takenPositions);    ASSERT_FALSE(winStrategy.Handle(players[2]));

    DropChip(6u, players[0].GetChip(), board, takenPositions);    ASSERT_FALSE(winStrategy.Handle(players[0]));
    DropChip(6u, players[1].GetChip(), board, takenPositions);    ASSERT_FALSE(winStrategy.Handle(players[1]));
    DropChip(6u, players[2].GetChip(), board, takenPositions);    ASSERT_FALSE(winStrategy.Handle(players[2]));

    DropChip(6u, players[0].GetChip(), board, takenPositions);    ASSERT_FALSE(winStrategy.Handle(players[0]));
    DropChip(6u, players[1].GetChip(), board, takenPositions);    ASSERT_FALSE(winStrategy.Handle(players[1]));
    DropChip(6u, players[2].GetChip(), board, takenPositions);    ASSERT_FALSE(winStrategy.Handle(players[2]));

    DropChip(6u, players[0].GetChip(), board, takenPositions);    ASSERT_FALSE(winStrategy.Handle(players[0]));
    DropChip(6u, players[1].GetChip(), board, takenPositions);    ASSERT_FALSE(winStrategy.Handle(players[1]));
    DropChip(6u, players[2].GetChip(), board, takenPositions);    ASSERT_FALSE(winStrategy.Handle(players[2]));

    DropChip(4u, players[0].GetChip(), board, takenPositions);    ASSERT_FALSE(winStrategy.Handle(players[0]));
    DropChip(5u, players[1].GetChip(), board, takenPositions);    ASSERT_FALSE(winStrategy.Handle(players[1]));
    DropChip(5u, players[2].GetChip(), board, takenPositions);    ASSERT_FALSE(winStrategy.Handle(players[2]));

    DropChip(4u, players[0].GetChip(), board, takenPositions);    ASSERT_FALSE(winStrategy.Handle(players[0]));
    DropChip(4u, players[1].GetChip(), board, takenPositions);    ASSERT_FALSE(winStrategy.Handle(players[1]));
    DropChip(5u, players[2].GetChip(), board, takenPositions);    ASSERT_FALSE(winStrategy.Handle(players[2]));

    DropChip(5u, players[0].GetChip(), board, takenPositions);    ASSERT_FALSE(winStrategy.Handle(players[0]));
    DropChip(4u, players[1].GetChip(), board, takenPositions);    ASSERT_FALSE(winStrategy.Handle(players[1]));
    DropChip(4u, players[2].GetChip(), board, takenPositions);    ASSERT_FALSE(winStrategy.Handle(players[2]));

    DropChip(5u, players[0].GetChip(), board, takenPositions);    ASSERT_FALSE(winStrategy.Handle(players[0]));
    DropChip(5u, players[1].GetChip(), board, takenPositions);    ASSERT_FALSE(winStrategy.Handle(players[1]));
    DropChip(4u, players[2].GetChip(), board, takenPositions);    ASSERT_FALSE(winStrategy.Handle(players[2]));

    DropChip(4u, players[0].GetChip(), board, takenPositions);    ASSERT_FALSE(winStrategy.Handle(players[0]));
    DropChip(5u, players[1].GetChip(), board, takenPositions);    ASSERT_FALSE(winStrategy.Handle(players[1]));
    DropChip(5u, players[2].GetChip(), board, takenPositions);    ASSERT_FALSE(winStrategy.Handle(players[2]));

    DropChip(2u, players[0].GetChip(), board, takenPositions);    ASSERT_FALSE(winStrategy.Handle(players[0]));
    DropChip(3u, players[1].GetChip(), board, takenPositions);    ASSERT_FALSE(winStrategy.Handle(players[1]));
    DropChip(3u, players[2].GetChip(), board, takenPositions);    ASSERT_FALSE(winStrategy.Handle(players[2]));

    DropChip(2u, players[0].GetChip(), board, takenPositions);    ASSERT_FALSE(winStrategy.Handle(players[0]));
    DropChip(2u, players[1].GetChip(), board, takenPositions);    ASSERT_FALSE(winStrategy.Handle(players[1]));
    DropChip(3u, players[2].GetChip(), board, takenPositions);    ASSERT_FALSE(winStrategy.Handle(players[2]));

    DropChip(3u, players[0].GetChip(), board, takenPositions);    ASSERT_FALSE(winStrategy.Handle(players[0]));
    DropChip(2u, players[1].GetChip(), board, takenPositions);    ASSERT_FALSE(winStrategy.Handle(players[1]));
    DropChip(2u, players[2].GetChip(), board, takenPositions);    ASSERT_FALSE(winStrategy.Handle(players[2]));

    DropChip(3u, players[0].GetChip(), board, takenPositions);    ASSERT_FALSE(winStrategy.Handle(players[0]));
    DropChip(3u, players[1].GetChip(), board, takenPositions);    ASSERT_FALSE(winStrategy.Handle(players[1]));
    DropChip(1u, players[2].GetChip(), board, takenPositions);    ASSERT_FALSE(winStrategy.Handle(players[2]));

    DropChip(0u, players[0].GetChip(), board, takenPositions);    ASSERT_FALSE(winStrategy.Handle(players[0]));
    DropChip(0u, players[1].GetChip(), board, takenPositions);    ASSERT_FALSE(winStrategy.Handle(players[1]));
    DropChip(1u, players[2].GetChip(), board, takenPositions);    ASSERT_FALSE(winStrategy.Handle(players[2]));

    DropChip(1u, players[0].GetChip(), board, takenPositions);    ASSERT_FALSE(winStrategy.Handle(players[0]));
    DropChip(0u, players[1].GetChip(), board, takenPositions);    ASSERT_FALSE(winStrategy.Handle(players[1]));
    DropChip(1u, players[2].GetChip(), board, takenPositions);    ASSERT_FALSE(winStrategy.Handle(players[2]));

    DropChip(0u, players[0].GetChip(), board, takenPositions);    ASSERT_FALSE(winStrategy.Handle(players[0]));
    DropChip(2u, players[1].GetChip(), board, takenPositions);    ASSERT_FALSE(winStrategy.Handle(players[1]));
    DropChip(2u, players[2].GetChip(), board, takenPositions);    ASSERT_FALSE(winStrategy.Handle(players[2]));

    DropChip(2u, players[0].GetChip(), board, takenPositions);    ASSERT_FALSE(winStrategy.Handle(players[0]));

    cxmodel::TieGameResolutionStrategy tieStrategy{board, inARowValue, players, takenPositions};
    ASSERT_FALSE(tieStrategy.Handle(players[1]));

    // From this point on, the game should report a tie on every move, until completion:
    DropChip(2u, players[1].GetChip(), board, takenPositions);    ASSERT_FALSE(winStrategy.Handle(players[1]));
    ASSERT_TRUE(tieStrategy.Handle(players[2]));

    DropChip(5u, players[2].GetChip(), board, takenPositions);    ASSERT_FALSE(winStrategy.Handle(players[2]));
    ASSERT_TRUE(tieStrategy.Handle(players[0]));

    DropChip(4u, players[0].GetChip(), board, takenPositions);    ASSERT_FALSE(winStrategy.Handle(players[0]));
    ASSERT_TRUE(tieStrategy.Handle(players[1]));

    DropChip(4u, players[1].GetChip(), board, takenPositions);    ASSERT_FALSE(winStrategy.Handle(players[1]));
    ASSERT_TRUE(tieStrategy.Handle(players[2]));

    DropChip(3u, players[2].GetChip(), board, takenPositions);    ASSERT_FALSE(winStrategy.Handle(players[2]));
    ASSERT_TRUE(tieStrategy.Handle(players[0]));

    DropChip(3u, players[0].GetChip(), board, takenPositions);    ASSERT_FALSE(winStrategy.Handle(players[0]));
    ASSERT_TRUE(tieStrategy.Handle(players[1]));

    DropChip(3u, players[1].GetChip(), board, takenPositions);    ASSERT_FALSE(winStrategy.Handle(players[1]));
    ASSERT_TRUE(tieStrategy.Handle(players[2]));

    DropChip(1u, players[2].GetChip(), board, takenPositions);    ASSERT_FALSE(winStrategy.Handle(players[2]));
    ASSERT_TRUE(tieStrategy.Handle(players[0]));

    DropChip(1u, players[0].GetChip(), board, takenPositions);    ASSERT_FALSE(winStrategy.Handle(players[0]));
    ASSERT_TRUE(tieStrategy.Handle(players[1]));

    DropChip(1u, players[1].GetChip(), board, takenPositions);    ASSERT_FALSE(winStrategy.Handle(players[1]));
    ASSERT_TRUE(tieStrategy.Handle(players[2]));

    DropChip(1u, players[2].GetChip(), board, takenPositions);    ASSERT_FALSE(winStrategy.Handle(players[2]));
    ASSERT_TRUE(tieStrategy.Handle(players[0]));

    DropChip(1u, players[0].GetChip(), board, takenPositions);    ASSERT_FALSE(winStrategy.Handle(players[0]));
    ASSERT_TRUE(tieStrategy.Handle(players[1]));

    DropChip(0u, players[1].GetChip(), board, takenPositions);    ASSERT_FALSE(winStrategy.Handle(players[1]));
    ASSERT_TRUE(tieStrategy.Handle(players[2]));

    DropChip(0u, players[2].GetChip(), board, takenPositions);    ASSERT_FALSE(winStrategy.Handle(players[2]));
    ASSERT_TRUE(tieStrategy.Handle(players[0]));

    DropChip(0u, players[0].GetChip(), board, takenPositions);    ASSERT_FALSE(winStrategy.Handle(players[0]));
    ASSERT_TRUE(tieStrategy.Handle(players[1]));

    DropChip(0u, players[1].GetChip(), board, takenPositions);    ASSERT_FALSE(winStrategy.Handle(players[1]));
    ASSERT_TRUE(tieStrategy.Handle(players[2]));

    DropChip(0u, players[2].GetChip(), board, takenPositions);    ASSERT_FALSE(winStrategy.Handle(players[2]));
    ASSERT_TRUE(tieStrategy.Handle(players[0]));
}
