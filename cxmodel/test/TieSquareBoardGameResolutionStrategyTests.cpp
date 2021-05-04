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
 * @file TieSquareBoardGameResolutionStrategyTests.cpp
 * @date 2021
 *
 *************************************************************************************************/

#include <sstream>

#include "GameResolutionStrategyTestFixture.h"

using SquareBoardThreePlayersGameTestFixture = GameResolutionStrategyTestFixture;

namespace
{

std::vector<cxmodel::Player> CreatePlayersList()
{
    return {
        {"Player 1", cxmodel::MakeRed()},
        {"Player 2", cxmodel::MakeBlue()},
        {"Player 3", cxmodel::MakeYellow()}
    };
}

} // namespace

TEST_F(SquareBoardThreePlayersGameTestFixture, /*DISABLED_*/Handle_LeftVerticalTie_ReturnsTrue)
{
    std::ostringstream game;
    game << "|    |     | 36 | 28 | 20 | 21 | 19 |" << std::endl;
    game << "|    |     | 34 | 27 | 17 | 18 | 16 |" << std::endl;
    game << "|    |     | 33 | 26 | 14 | 15 | 13 |" << std::endl;
    game << "|    |     | 32 | 25 | 11 | 12 | 10 |" << std::endl;
    game << "|    | 39t | 31 | 24 | 9  | 7  | 8  |" << std::endl;
    game << "|    | 37  | 30 | 23 | 4  | 5  | 6  |" << std::endl;
    game << "| 38 | 35  | 29 | 22 | 1  | 2  | 3  |";

    ASSERT_TRUE(ValidateGame(CreatePlayersList(), 5u, game.str()));
}

TEST_F(SquareBoardThreePlayersGameTestFixture, /*DISABLED_*/Handle_CenterVerticalTie_ReturnsTrue)
{
    std::ostringstream game;
    game << "| 21 | 20 | 19 |   |   | 35t | 28 |" << std::endl;
    game << "| 17 | 16 | 18 |   |   | 34  | 27 |" << std::endl;
    game << "| 13 | 14 | 15 |   |   | 33  | 26 |" << std::endl;
    game << "| 12 | 11 | 10 |   |   | 32  | 25 |" << std::endl;
    game << "| 8  | 7  | 9  |   |   | 31  | 24 |" << std::endl;
    game << "| 6  | 5  | 4  |   |   | 30  | 23 |" << std::endl;
    game << "| 1  | 2  | 3  |   |   | 29  | 22 |";

    ASSERT_TRUE(ValidateGame(CreatePlayersList(), 5u, game.str()));
}

TEST_F(SquareBoardThreePlayersGameTestFixture, /*DISABLED_*/Handle_RightVerticalTie_ReturnsTrue)
{
    std::ostringstream game;
    game << "| 19 | 21 | 20 | 28 | 36 |     |    |" << std::endl;
    game << "| 16 | 18 | 17 | 27 | 34 |     |    |" << std::endl;
    game << "| 13 | 15 | 14 | 26 | 33 |     |    |" << std::endl;
    game << "| 10 | 12 | 11 | 25 | 32 |     |    |" << std::endl;
    game << "| 8  | 7  | 9  | 24 | 31 | 39t |    |" << std::endl;
    game << "| 6  | 5  | 4  | 23 | 30 | 37  |    |" << std::endl;
    game << "| 3  | 2  | 1  | 22 | 29 | 35  | 38 |";

    ASSERT_TRUE(ValidateGame(CreatePlayersList(), 5u, game.str()));
}

TEST_F(SquareBoardThreePlayersGameTestFixture, /*DISABLED_*/Handle_LeftHorizontalTie_ReturnsTrue)
{
    std::ostringstream game;
    game << "|    |    |    |    |    | 39t | 37 |" << std::endl;
    game << "|    |    |    |    |    | 38  | 36 |" << std::endl;
    game << "| 30 | 29 | 31 | 32 | 33 | 34  | 35 |" << std::endl;
    game << "| 13 | 23 | 24 | 26 | 25 | 27  | 28 |" << std::endl;
    game << "| 3  | 6  | 9  | 12 | 16 | 19  | 22 |" << std::endl;
    game << "| 2  | 5  | 8  | 11 | 15 | 18  | 21 |" << std::endl;
    game << "| 1  | 4  | 7  | 10 | 14 | 17  | 20 |";

    ASSERT_TRUE(ValidateGame(CreatePlayersList(), 5u, game.str()));
}

TEST_F(SquareBoardThreePlayersGameTestFixture, /*DISABLED_*/Handle_CenterHorizontalTie_ReturnsTrue)
{
    std::ostringstream game;
    game << "|     |    |    |    |    |    | 37 |" << std::endl;
    game << "| 38t |    |    |    |    |    | 36 |" << std::endl;
    game << "| 30  | 29 | 31 | 32 | 33 | 34 | 35 |" << std::endl;
    game << "| 13  | 23 | 24 | 26 | 25 | 27 | 28 |" << std::endl;
    game << "| 3   | 6  | 9  | 12 | 16 | 19 | 22 |" << std::endl;
    game << "| 2   | 5  | 8  | 11 | 15 | 18 | 21 |" << std::endl;
    game << "| 1   | 4  | 7  | 10 | 14 | 17 | 20 |";

}

TEST_F(SquareBoardThreePlayersGameTestFixture, /*DISABLED_*/Handle_RightHorizontalTie_ReturnsTrue)
{
    std::ostringstream game;
    game << "| 37 | 39t |    |    |    |    |    |" << std::endl;
    game << "| 36 | 38  |    |    |    |    |    |" << std::endl;
    game << "| 35 | 34  | 33 | 32 | 31 | 29 | 30 |" << std::endl;
    game << "| 28 | 27  | 25 | 26 | 24 | 23 | 13 |" << std::endl;
    game << "| 22 | 19  | 16 | 12 | 9  | 6  | 3  |" << std::endl;
    game << "| 21 | 18  | 15 | 11 | 8  | 5  | 2  |" << std::endl;
    game << "| 20 | 17  | 14 | 10 | 7  | 4  | 1  |";

    ASSERT_TRUE(ValidateGame(CreatePlayersList(), 5u, game.str()));
}

TEST_F(SquareBoardThreePlayersGameTestFixture, /*DISABLED_*/Handle_RightAscendingTie_ReturnsTrue)
{
    // In reality, the earliest tie is at move 47, since it becomes
    // impossible for the third player (C below) to win if we consider
    // gravity when dropping discs:
    //
    //               | C | A | B | C | A | B |   |
    //               | B | A | C | B | A | C |   |
    //               | C | A | B | C | C | A | B |
    //               | B | A | B | C | A | C | B |
    //               | A | B | C | C | A | B | A |
    //               | B | A | C | B | A | C | B |
    //               | A | B | C | A | B | C | A |
    //
    // Here we see that the next turn is for the third player, but
    // this players has only one option, when gravity is considered.
    // This one option yields an early tie. However, in practice,
    // the algorithm does not detect invalid moves based on gravity.
    // This means that in the algorithm's point of view, the tie
    // does not occur here (he thinks the third players still has a
    // shot), but at the next turn.
    //
    // See TG-215 for more details.

    std::ostringstream game;
    game << "| 42 | 43 | 44 | 45 | 46 | 47 |     |" << std::endl;
    game << "| 41 | 40 | 39 | 38 | 37 | 36 | 48t |" << std::endl;
    game << "| 30 | 31 | 32 | 33 | 27 | 34 | 35  |" << std::endl;
    game << "| 29 | 28 | 26 | 21 | 25 | 24 | 23  |" << std::endl;
    game << "| 16 | 17 | 15 | 18 | 19 | 20 | 22  |" << std::endl;
    game << "| 14 | 13 | 12 | 11 | 10 | 9  | 8   |" << std::endl;
    game << "| 1  | 2  | 3  | 4  | 5  | 6  | 7   |";

    ASSERT_TRUE(ValidateGame(CreatePlayersList(), 5u, game.str()));
}

TEST_F(SquareBoardThreePlayersGameTestFixture, /*DISABLED_*/Handle_LeftDescendingTie_ReturnsTrue)
{
    // True early tie should happen at turn 47. See the `Handle_RightAscendingTie_ReturnsTrue`
    // test for more information.

    std::ostringstream game;
    game << "|     | 47 | 46 | 45 | 44 | 43 | 42 |" << std::endl;
    game << "| 48t | 36 | 37 | 38 | 39 | 40 | 41 |" << std::endl;
    game << "| 35  | 34 | 27 | 33 | 32 | 31 | 30 |" << std::endl;
    game << "| 23  | 24 | 25 | 21 | 26 | 28 | 29 |" << std::endl;
    game << "| 22  | 20 | 19 | 18 | 15 | 17 | 16 |" << std::endl;
    game << "| 8   | 9  | 10 | 11 | 12 | 13 | 14 |" << std::endl;
    game << "| 7   | 6  | 5  | 4  | 3  | 2  | 1  |";

    ASSERT_TRUE(ValidateGame(CreatePlayersList(), 5u, game.str()));
}

TEST_F(SquareBoardThreePlayersGameTestFixture, /*DISABLED_*/Handle_AlmostFullBoardTie_ReturnsTrue)
{
    std::ostringstream game;
    game << "| 43 | 44 | 45 | 46 |    | 47 | 48t |" << std::endl;
    game << "| 42 | 41 | 40 | 39 | 38 | 37 | 36  |" << std::endl;
    game << "| 29 | 31 | 30 | 32 | 33 | 34 | 35  |" << std::endl;
    game << "| 28 | 27 | 26 | 25 | 24 | 23 | 22  |" << std::endl;
    game << "| 15 | 16 | 17 | 18 | 19 | 20 | 21  |" << std::endl;
    game << "| 8  | 9  | 10 | 11 | 12 | 13 | 14  |" << std::endl;
    game << "| 1  | 2  | 3  | 4  | 5  | 6  | 7   |";

    ASSERT_TRUE(ValidateGame(CreatePlayersList(), 5u, game.str()));
}

