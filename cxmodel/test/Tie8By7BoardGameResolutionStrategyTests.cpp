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
 * @file Tie8By7BoardGameResolutionStrategyTests.cpp
 * @date 2021
 *
 *************************************************************************************************/

#include <sstream>

#include "GameResolutionStrategyTestFixture.h"

using HeightBySevenFourPlayersGameTestFixture = GameResolutionStrategyTestFixture;

namespace
{

std::vector<cxmodel::Player> CreatePlayersList()
{
    return {
        {"Player 1", cxmodel::MakeRed()},
        {"Player 2", cxmodel::MakeBlue()},
        {"Player 3", cxmodel::MakeYellow()},
        {"Player 4", cxmodel::MakeGreen()}
    };
}

} // namespace

TEST_F(HeightBySevenFourPlayersGameTestFixture, /*DISABLED_*/Handle_LeftVerticalTie1_ReturnsTrue)
{
    std::ostringstream game;
    game << "|   |   |     | 8  | 16 | 25 | 32 |" << std::endl;
    game << "|   |   |     | 7  | 15 | 24 | 31 |" << std::endl;
    game << "|   |   |     | 6  | 14 | 23 | 30 |" << std::endl;
    game << "|   |   |     | 5  | 13 | 22 | 29 |" << std::endl;
    game << "|   |   | 36t | 4  | 12 | 21 | 28 |" << std::endl;
    game << "|   |   | 35  | 3  | 11 | 20 | 27 |" << std::endl;
    game << "|   |   | 34  | 2  | 10 | 19 | 26 |" << std::endl;
    game << "|   |   | 33  | 1  | 9  | 18 | 17 |";

    ASSERT_TRUE(ValidateGame(CreatePlayersList(), 6u, game.str()));
}

TEST_F(HeightBySevenFourPlayersGameTestFixture, /*DISABLED_*/Handle_LeftVerticalTie2_ReturnsTrue)
{
    std::ostringstream game;
    game << "|   |     |    | 8  | 16 | 25 | 32 |" << std::endl;
    game << "|   |     |    | 7  | 15 | 24 | 31 |" << std::endl;
    game << "|   |     |    | 6  | 14 | 23 | 30 |" << std::endl;
    game << "|   |     |    | 5  | 13 | 22 | 29 |" << std::endl;
    game << "|   | 39t |    | 4  | 12 | 21 | 28 |" << std::endl;
    game << "|   | 38  | 35 | 3  | 11 | 20 | 27 |" << std::endl;
    game << "|   | 37  | 34 | 2  | 10 | 19 | 26 |" << std::endl;
    game << "|   | 36  | 33 | 1  | 9  | 18 | 17 |";

    ASSERT_TRUE(ValidateGame(CreatePlayersList(), 6u, game.str()));
}

TEST_F(HeightBySevenFourPlayersGameTestFixture, /*DISABLED_*/Handle_LeftVerticalTie3_ReturnsTrue)
{
    std::ostringstream game;
    game << "|   |     |    | 8  | 16 | 25 | 32 |" << std::endl;
    game << "|   | 43t |    | 7  | 15 | 24 | 31 |" << std::endl;
    game << "|   | 42  |    | 6  | 14 | 23 | 30 |" << std::endl;
    game << "|   | 41  |    | 5  | 13 | 22 | 29 |" << std::endl;
    game << "|   | 40  | 39 | 4  | 12 | 21 | 28 |" << std::endl;
    game << "|   | 38  | 35 | 3  | 11 | 20 | 27 |" << std::endl;
    game << "|   | 37  | 34 | 2  | 10 | 19 | 26 |" << std::endl;
    game << "|   | 36  | 33 | 1  | 9  | 18 | 17 |";

    ASSERT_TRUE(ValidateGame(CreatePlayersList(), 6u, game.str()));
}

TEST_F(HeightBySevenFourPlayersGameTestFixture, /*DISABLED_*/Handle_LeftVerticalTie4_ReturnsTrue)
{
    std::ostringstream game;
    game << "|     |    |    | 8  | 16 | 25 | 32 |" << std::endl;
    game << "|     | 44 |    | 7  | 15 | 24 | 31 |" << std::endl;
    game << "|     | 42 |    | 6  | 14 | 23 | 30 |" << std::endl;
    game << "|     | 41 | 43 | 5  | 13 | 22 | 29 |" << std::endl;
    game << "|     | 40 | 39 | 4  | 12 | 21 | 28 |" << std::endl;
    game << "| 47t | 38 | 35 | 3  | 11 | 20 | 27 |" << std::endl;
    game << "| 46  | 37 | 34 | 2  | 10 | 19 | 26 |" << std::endl;
    game << "| 45  | 36 | 33 | 1  | 9  | 18 | 17 |";

    ASSERT_TRUE(ValidateGame(CreatePlayersList(), 6u, game.str()));
}

TEST_F(HeightBySevenFourPlayersGameTestFixture, /*DISABLED_*/Handle_LeftVerticalTie5_ReturnsTrue)
{
    std::ostringstream game;
    game << "|     |    |    | 8  | 16 | 25 | 32 |" << std::endl;
    game << "|     | 44 |    | 7  | 15 | 24 | 31 |" << std::endl;
    game << "| 51t | 42 | 47 | 6  | 14 | 23 | 30 |" << std::endl;
    game << "| 50  | 41 | 43 | 5  | 13 | 22 | 29 |" << std::endl;
    game << "| 49  | 40 | 39 | 4  | 12 | 21 | 28 |" << std::endl;
    game << "| 48  | 38 | 35 | 3  | 11 | 20 | 27 |" << std::endl;
    game << "| 46  | 37 | 34 | 2  | 10 | 19 | 26 |" << std::endl;
    game << "| 45  | 36 | 33 | 1  | 9  | 18 | 17 |";

    ASSERT_TRUE(ValidateGame(CreatePlayersList(), 6u, game.str()));
}

TEST_F(HeightBySevenFourPlayersGameTestFixture, /*DISABLED_*/Handle_LeftVerticalTie6_ReturnsTrue)
{
    std::ostringstream game;
    game << "| 54 | 55t |    | 8  | 16 | 25 | 32 |" << std::endl;
    game << "| 53 | 44  | 51 | 7  | 15 | 24 | 31 |" << std::endl;
    game << "| 52 | 42  | 47 | 6  | 14 | 23 | 30 |" << std::endl;
    game << "| 50 | 41  | 43 | 5  | 13 | 22 | 29 |" << std::endl;
    game << "| 49 | 40  | 39 | 4  | 12 | 21 | 28 |" << std::endl;
    game << "| 48 | 38  | 35 | 3  | 11 | 20 | 27 |" << std::endl;
    game << "| 46 | 37  | 34 | 2  | 10 | 19 | 26 |" << std::endl;
    game << "| 45 | 36  | 33 | 1  | 9  | 18 | 17 |";

    ASSERT_TRUE(ValidateGame(CreatePlayersList(), 6u, game.str()));
}

TEST_F(HeightBySevenFourPlayersGameTestFixture, /*DISABLED_*/Handle_RightVerticalTie1_ReturnsTrue)
{
    std::ostringstream game;
    game << "| 32 | 25 | 16 | 8  |     |   |   |" << std::endl;
    game << "| 31 | 24 | 15 | 7  |     |   |   |" << std::endl;
    game << "| 30 | 23 | 14 | 6  |     |   |   |" << std::endl;
    game << "| 29 | 22 | 13 | 5  |     |   |   |" << std::endl;
    game << "| 28 | 21 | 12 | 4  | 36t |   |   |" << std::endl;
    game << "| 27 | 20 | 11 | 3  | 35  |   |   |" << std::endl;
    game << "| 26 | 19 | 10 | 2  | 34  |   |   |" << std::endl;
    game << "| 17 | 18 | 9  | 1  | 33  |   |   |";

    ASSERT_TRUE(ValidateGame(CreatePlayersList(), 6u, game.str()));
}

TEST_F(HeightBySevenFourPlayersGameTestFixture, /*DISABLED_*/Handle_RightVerticalTie2_ReturnsTrue)
{
    std::ostringstream game;
    game << "| 32 | 25 | 16 | 8  |    |     |   |" << std::endl;
    game << "| 31 | 24 | 15 | 7  |    |     |   |" << std::endl;
    game << "| 30 | 23 | 14 | 6  |    |     |   |" << std::endl;
    game << "| 29 | 22 | 13 | 5  |    |     |   |" << std::endl;
    game << "| 28 | 21 | 12 | 4  |    | 39t |   |" << std::endl;
    game << "| 27 | 20 | 11 | 3  | 35 | 38  |   |" << std::endl;
    game << "| 26 | 19 | 10 | 2  | 34 | 37  |   |" << std::endl;
    game << "| 17 | 18 | 9  | 1  | 33 | 36  |   |";

    ASSERT_TRUE(ValidateGame(CreatePlayersList(), 6u, game.str()));
}

TEST_F(HeightBySevenFourPlayersGameTestFixture, /*DISABLED_*/Handle_RightVerticalTie3_ReturnsTrue)
{
    std::ostringstream game;
    game << "| 32 | 25 | 16 | 8  |    |     |   |" << std::endl;
    game << "| 31 | 24 | 15 | 7  |    | 43t |   |" << std::endl;
    game << "| 30 | 23 | 14 | 6  |    | 42  |   |" << std::endl;
    game << "| 29 | 22 | 13 | 5  |    | 41  |   |" << std::endl;
    game << "| 28 | 21 | 12 | 4  | 39 | 40  |   |" << std::endl;
    game << "| 27 | 20 | 11 | 3  | 35 | 38  |   |" << std::endl;
    game << "| 26 | 19 | 10 | 2  | 34 | 37  |   |" << std::endl;
    game << "| 17 | 18 | 9  | 1  | 33 | 36  |   |";

    ASSERT_TRUE(ValidateGame(CreatePlayersList(), 6u, game.str()));
}

TEST_F(HeightBySevenFourPlayersGameTestFixture, /*DISABLED_*/Handle_RightVerticalTie4_ReturnsTrue)
{
    std::ostringstream game;
    game << "| 32 | 25 | 16 | 8  |    |    |     |" << std::endl;
    game << "| 31 | 24 | 15 | 7  |    | 44 |     |" << std::endl;
    game << "| 30 | 23 | 14 | 6  |    | 42 |     |" << std::endl;
    game << "| 29 | 22 | 13 | 5  | 43 | 41 |     |" << std::endl;
    game << "| 28 | 21 | 12 | 4  | 39 | 40 |     |" << std::endl;
    game << "| 27 | 20 | 11 | 3  | 35 | 38 | 47t |" << std::endl;
    game << "| 26 | 19 | 10 | 2  | 34 | 37 | 46  |" << std::endl;
    game << "| 17 | 18 | 9  | 1  | 33 | 36 | 45  |";

    ASSERT_TRUE(ValidateGame(CreatePlayersList(), 6u, game.str()));
}

TEST_F(HeightBySevenFourPlayersGameTestFixture, /*DISABLED_*/Handle_RightVerticalTie5_ReturnsTrue)
{
    std::ostringstream game;
    game << "| 32 | 25 | 16 | 8  |    |    |     |" << std::endl;
    game << "| 31 | 24 | 15 | 7  |    | 44 |     |" << std::endl;
    game << "| 30 | 23 | 14 | 6  | 47 | 42 | 51t |" << std::endl;
    game << "| 29 | 22 | 13 | 5  | 43 | 41 | 50  |" << std::endl;
    game << "| 28 | 21 | 12 | 4  | 39 | 40 | 49  |" << std::endl;
    game << "| 27 | 20 | 11 | 3  | 35 | 38 | 48  |" << std::endl;
    game << "| 26 | 19 | 10 | 2  | 34 | 37 | 46  |" << std::endl;
    game << "| 17 | 18 | 9  | 1  | 33 | 36 | 45  |";

    ASSERT_TRUE(ValidateGame(CreatePlayersList(), 6u, game.str()));
}

TEST_F(HeightBySevenFourPlayersGameTestFixture, /*DISABLED_*/Handle_RightVerticalTie6_ReturnsTrue)
{
    std::ostringstream game;
    game << "| 32 | 25 | 16 | 8  |    | 55t | 54 |" << std::endl;
    game << "| 31 | 24 | 15 | 7  | 51 | 44  | 53 |" << std::endl;
    game << "| 30 | 23 | 14 | 6  | 47 | 42  | 52 |" << std::endl;
    game << "| 29 | 22 | 13 | 5  | 43 | 41  | 50 |" << std::endl;
    game << "| 28 | 21 | 12 | 4  | 39 | 40  | 49 |" << std::endl;
    game << "| 27 | 20 | 11 | 3  | 35 | 38  | 48 |" << std::endl;
    game << "| 26 | 19 | 10 | 2  | 34 | 37  | 46 |" << std::endl;
    game << "| 17 | 18 | 9  | 1  | 33 | 36  | 45 |";

    ASSERT_TRUE(ValidateGame(CreatePlayersList(), 6u, game.str()));
}

TEST_F(HeightBySevenFourPlayersGameTestFixture, /*DISABLED_*/Handle_CenterVerticalTie1_ReturnsTrue)
{
    std::ostringstream game;
    game << "| 8  | 24 | 23 |   |   |     | 32 |" << std::endl;
    game << "| 7  | 21 | 22 |   |   |     | 31 |" << std::endl;
    game << "| 6  | 20 | 19 |   |   |     | 30 |" << std::endl;
    game << "| 5  | 17 | 18 |   |   |     | 29 |" << std::endl;
    game << "| 4  | 16 | 15 |   |   | 36t | 28 |" << std::endl;
    game << "| 3  | 13 | 14 |   |   | 35  | 27 |" << std::endl;
    game << "| 2  | 12 | 11 |   |   | 34  | 26 |" << std::endl;
    game << "| 1  | 9  | 10 |   |   | 33  | 25 |";

    ASSERT_TRUE(ValidateGame(CreatePlayersList(), 6u, game.str()));
}

TEST_F(HeightBySevenFourPlayersGameTestFixture, /*DISABLED_*/Handle_CenterVerticalTie2_ReturnsTrue)
{
    std::ostringstream game;
    game << "| 8  | 24 | 23 |    |   |     | 32 |" << std::endl;
    game << "| 7  | 21 | 22 |    |   |     | 31 |" << std::endl;
    game << "| 6  | 20 | 19 |    |   |     | 30 |" << std::endl;
    game << "| 5  | 17 | 18 |    |   |     | 29 |" << std::endl;
    game << "| 4  | 16 | 15 |    |   | 39t | 28 |" << std::endl;
    game << "| 3  | 13 | 14 | 35 |   | 38  | 27 |" << std::endl;
    game << "| 2  | 12 | 11 | 34 |   | 37  | 26 |" << std::endl;
    game << "| 1  | 9  | 10 | 33 |   | 36  | 25 |";

    ASSERT_TRUE(ValidateGame(CreatePlayersList(), 6u, game.str()));
}

TEST_F(HeightBySevenFourPlayersGameTestFixture, /*DISABLED_*/Handle_CenterVerticalTie3_ReturnsTrue)
{
    std::ostringstream game;
    game << "| 8  | 24 | 23 |    |   |     | 32 |" << std::endl;
    game << "| 7  | 21 | 22 |    |   | 43t | 31 |" << std::endl;
    game << "| 6  | 20 | 19 |    |   | 42  | 30 |" << std::endl;
    game << "| 5  | 17 | 18 |    |   | 41  | 29 |" << std::endl;
    game << "| 4  | 16 | 15 | 39 |   | 40  | 28 |" << std::endl;
    game << "| 3  | 13 | 14 | 35 |   | 38  | 27 |" << std::endl;
    game << "| 2  | 12 | 11 | 34 |   | 37  | 26 |" << std::endl;
    game << "| 1  | 9  | 10 | 33 |   | 36  | 25 |";

    ASSERT_TRUE(ValidateGame(CreatePlayersList(), 6u, game.str()));
}

TEST_F(HeightBySevenFourPlayersGameTestFixture, /*DISABLED_*/Handle_CenterVerticalTie4_ReturnsTrue)
{
    std::ostringstream game;
    game << "| 8  | 24 | 23 |    |     | 45 | 32 |" << std::endl;
    game << "| 7  | 21 | 22 |    |     | 44 | 31 |" << std::endl;
    game << "| 6  | 20 | 19 |    |     | 42 | 30 |" << std::endl;
    game << "| 5  | 17 | 18 | 43 |     | 41 | 29 |" << std::endl;
    game << "| 4  | 16 | 15 | 39 |     | 40 | 28 |" << std::endl;
    game << "| 3  | 13 | 14 | 35 |     | 38 | 27 |" << std::endl;
    game << "| 2  | 12 | 11 | 34 | 47t | 37 | 26 |" << std::endl;
    game << "| 1  | 9  | 10 | 33 | 46  | 36 | 25 |";

    ASSERT_TRUE(ValidateGame(CreatePlayersList(), 6u, game.str()));
}

TEST_F(HeightBySevenFourPlayersGameTestFixture, /*DISABLED_*/Handle_CenterVerticalTie5_ReturnsTrue)
{
    std::ostringstream game;
    game << "| 8  | 24 | 23 |    |     | 45 | 32 |" << std::endl;
    game << "| 7  | 21 | 22 |    |     | 44 | 31 |" << std::endl;
    game << "| 6  | 20 | 19 | 47 |     | 42 | 30 |" << std::endl;
    game << "| 5  | 17 | 18 | 43 | 51t | 41 | 29 |" << std::endl;
    game << "| 4  | 16 | 15 | 39 | 50  | 40 | 28 |" << std::endl;
    game << "| 3  | 13 | 14 | 35 | 49  | 38 | 27 |" << std::endl;
    game << "| 2  | 12 | 11 | 34 | 48  | 37 | 26 |" << std::endl;
    game << "| 1  | 9  | 10 | 33 | 46  | 36 | 25 |";

    ASSERT_TRUE(ValidateGame(CreatePlayersList(), 6u, game.str()));
}

TEST_F(HeightBySevenFourPlayersGameTestFixture, /*DISABLED_*/Handle_CenterVerticalTie6_ReturnsTrue)
{
    std::ostringstream game;
    game << "| 8  | 24 | 23 |    | 55t | 45 | 32 |" << std::endl;
    game << "| 7  | 21 | 22 | 51 | 54  | 44 | 31 |" << std::endl;
    game << "| 6  | 20 | 19 | 47 | 53  | 42 | 30 |" << std::endl;
    game << "| 5  | 17 | 18 | 43 | 52  | 41 | 29 |" << std::endl;
    game << "| 4  | 16 | 15 | 39 | 50  | 40 | 28 |" << std::endl;
    game << "| 3  | 13 | 14 | 35 | 49  | 38 | 27 |" << std::endl;
    game << "| 2  | 12 | 11 | 34 | 48  | 37 | 26 |" << std::endl;
    game << "| 1  | 9  | 10 | 33 | 46  | 36 | 25 |";

    ASSERT_TRUE(ValidateGame(CreatePlayersList(), 6u, game.str()));
}

TEST_F(HeightBySevenFourPlayersGameTestFixture, /*DISABLED_*/Handle_HorizontalTie1_ReturnsTrue)
{
    // The current algorithm only makes sure that:
    //
    //   1. There remains horizontal possibilities for a win according
    //      to the chips already dropped, the free positions and the
    //      in-a-row value.
    //   2. Players have enough moves left to possibly win.
    //
    // This means that some really early tie scenarios, such as the
    // following, are not detected:
    //
    //             |    |    |    |    |    |     |    |
    //             |    |    |    |    |    |     |    |
    //             |    |    |    |    |    |     |    |
    //             | 31 | 32 | 29 | 33 | 30 | 34t |    |
    //             | 28 | 27 | 26 | 25 | 24 | 23  | 22 |
    //             | 15 | 16 | 17 | 18 | 19 | 20  | 21 |
    //             | 8  | 9  | 10 | 11 | 12 | 13  | 14 |
    //             | 1  | 2  | 3  | 4  | 5  | 6   | 7  |
    //
    // Here all players still have enough moves left to win and there are
    // three empty rows in which six chips fit horizontally. However,
    // because of the board configuration, and the effect of gravity on
    // the chips as they are dropped, it is not possible for any player
    // to win here. Hence a tie should be detected.
    //
    // This limitation is not a no-go because ties are not detected too
    // early, but should still be addressed in time. See TG-215 for more
    // information.

    // At this point all players have 5 moves left, which is not
    // enough in any scenario to win here. This is why a tie
    // occurs:
    std::ostringstream game;
    game << "|    |     |    |    |    |    |    |" << std::endl;
    game << "|    |     |    |    |    |    |    |" << std::endl;
    game << "| 36 | 37t |    |    |    |    |    |" << std::endl;
    game << "| 31 | 32  | 29 | 33 | 30 | 34 | 35 |" << std::endl;
    game << "| 28 | 27  | 26 | 25 | 24 | 23 | 22 |" << std::endl;
    game << "| 15 | 16  | 17 | 18 | 19 | 20 | 21 |" << std::endl;
    game << "| 8  | 9   | 10 | 11 | 12 | 13 | 14 |" << std::endl;
    game << "| 1  | 2   | 3  | 4  | 5  | 6  | 7  |";

    ASSERT_TRUE(ValidateGame(CreatePlayersList(), 6u, game.str()));
}

TEST_F(HeightBySevenFourPlayersGameTestFixture, /*DISABLED_*/Handle_HorizontalTie2_ReturnsTrue)
{
    // At this point all players only have 1 or 0 move left, which is not
    // enough in any scenario to win here. This is why a tie occurs.
    // See TG-215.
    std::ostringstream game;
    game << "| 38 | 42 | 46 | 50 |     |    | 47 |" << std::endl;
    game << "| 37 | 41 | 45 | 49 |     |    | 43 |" << std::endl;
    game << "| 36 | 40 | 44 | 48 | 51t |    | 39 |" << std::endl;
    game << "| 31 | 32 | 29 | 33 | 30  | 34 | 35 |" << std::endl;
    game << "| 28 | 27 | 26 | 25 | 24  | 23 | 22 |" << std::endl;
    game << "| 15 | 16 | 17 | 18 | 19  | 20 | 21 |" << std::endl;
    game << "| 8  | 9  | 10 | 11 | 12  | 13 | 14 |" << std::endl;
    game << "| 1  | 2  | 3  | 4  | 5   | 6  | 7  |";

    ASSERT_TRUE(ValidateGame(CreatePlayersList(), 6u, game.str()));
}

TEST_F(HeightBySevenFourPlayersGameTestFixture, /*DISABLED_*/Handle_RightAscendingTie_ReturnsTrue)
{
    std::ostringstream game;
    game << "|    |    |    |    |    |     |    |" << std::endl;
    game << "|    |    |    |    |    | 43t |    |" << std::endl;
    game << "| 37 | 38 | 39 | 40 | 29 | 41  | 42 |" << std::endl;
    game << "| 32 | 33 | 34 | 25 | 23 | 35  | 36 |" << std::endl;
    game << "| 30 | 31 | 21 | 19 | 22 | 27  | 28 |" << std::endl;
    game << "| 15 | 17 | 16 | 18 | 20 | 24  | 26 |" << std::endl;
    game << "| 8  | 9  | 10 | 11 | 12 | 13  | 14 |" << std::endl;
    game << "| 1  | 2  | 3  | 4  | 5  | 6   | 7  |";

    ASSERT_TRUE(ValidateGame(CreatePlayersList(), 6u, game.str()));
}

TEST_F(HeightBySevenFourPlayersGameTestFixture, /*DISABLED_*/Handle_LeftDescendingTie_ReturnsTrue)
{
    std::ostringstream game;
    game << "|    |     |    |    |    |    |    |" << std::endl;
    game << "|    | 43t |    |    |    |    |    |" << std::endl;
    game << "| 42 | 41  | 29 | 40 | 39 | 38 | 37 |" << std::endl;
    game << "| 36 | 35  | 23 | 25 | 34 | 33 | 32 |" << std::endl;
    game << "| 28 | 27  | 22 | 19 | 21 | 31 | 30 |" << std::endl;
    game << "| 26 | 24  | 20 | 18 | 16 | 17 | 15 |" << std::endl;
    game << "| 14 | 13  | 12 | 11 | 10 | 9  | 8  |" << std::endl;
    game << "| 7  | 6   | 5  | 4  | 3  | 2  | 1  |";

    ASSERT_TRUE(ValidateGame(CreatePlayersList(), 6u, game.str()));
}

TEST_F(HeightBySevenFourPlayersGameTestFixture, /*DISABLED_*/Handle_AlmostFullBoardTie_ReturnsTrue)
{
    std::ostringstream game;
    game << "| 50 | 51 | 52 | 53 |    | 55t | 54 |" << std::endl;
    game << "| 49 | 48 | 47 | 46 | 44 | 45  | 43 |" << std::endl;
    game << "| 37 | 38 | 39 | 36 | 40 | 42  | 41 |" << std::endl;
    game << "| 30 | 31 | 28 | 32 | 33 | 34  | 35 |" << std::endl;
    game << "| 29 | 20 | 19 | 27 | 26 | 25  | 24 |" << std::endl;
    game << "| 16 | 15 | 17 | 18 | 21 | 22  | 23 |" << std::endl;
    game << "| 8  | 9  | 10 | 11 | 12 | 13  | 14 |" << std::endl;
    game << "| 1  | 2  | 3  | 4  | 5  | 6   | 7  |";

    ASSERT_TRUE(ValidateGame(CreatePlayersList(), 6u, game.str()));
}
