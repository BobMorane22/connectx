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
 * @file Win8By7BoardGameResolutionStrategyTests.cpp
 * @date 2021
 *
 *************************************************************************************************/

#include <sstream>

#include "GameResolutionStrategyTestFixture.h"

using HeightBySevenFourPlayersGameTestFixture = GameResolutionStrategyTestFixture;

namespace
{

std::vector<std::shared_ptr<cxmodel::IPlayer>> CreatePlayersList()
{
    return {
        cxmodel::CreatePlayer("Player 1", cxmodel::MakeRed(), cxmodel::PlayerType::HUMAN),
        cxmodel::CreatePlayer("Player 2", cxmodel::MakeBlue(), cxmodel::PlayerType::HUMAN),
        cxmodel::CreatePlayer("Player 3", cxmodel::MakeYellow(), cxmodel::PlayerType::HUMAN),
        cxmodel::CreatePlayer("Player 4", cxmodel::MakeGreen(), cxmodel::PlayerType::HUMAN),
    };
}

} // namespace

TEST_F(HeightBySevenFourPlayersGameTestFixture, /*DISABLED_*/Handle_DownLeftVerticalWin_ReturnsTrue)
{
    std::ostringstream game;
    game << "|     |    |    |    |   |   |   |" << std::endl;
    game << "|     |    |    |    |   |   |   |" << std::endl;
    game << "| 21w |    |    |    |   |   |   |" << std::endl;
    game << "| 17  | 18 | 19 | 20 |   |   |   |" << std::endl;
    game << "| 13  | 14 | 15 | 16 |   |   |   |" << std::endl;
    game << "| 9   | 10 | 11 | 12 |   |   |   |" << std::endl;
    game << "| 5   | 6  | 7  | 8  |   |   |   |" << std::endl;
    game << "| 1   | 2  | 3  | 4  |   |   |   |";

    ASSERT_TRUE(ValidateGame(CreatePlayersList(), 6u, game.str()));
}

TEST_F(HeightBySevenFourPlayersGameTestFixture, /*DISABLED_*/Handle_UpLeftVerticalWin_ReturnsTrue)
{
    std::ostringstream game;
    game << "|    |    | 31w |    |    |   |   |" << std::endl;
    game << "| 25 | 26 | 27  | 28 |    |   |   |" << std::endl;
    game << "| 21 | 22 | 23  | 24 |    |   |   |" << std::endl;
    game << "| 17 | 18 | 19  | 20 |    |   |   |" << std::endl;
    game << "| 13 | 14 | 15  | 16 |    |   |   |" << std::endl;
    game << "| 9  | 10 | 11  | 12 |    |   |   |" << std::endl;
    game << "| 8  | 7  | 6   | 5  | 30 |   |   |" << std::endl;
    game << "| 4  | 3  | 2   | 1  | 29 |   |   |";

    ASSERT_TRUE(ValidateGame(CreatePlayersList(), 6u, game.str()));
}

TEST_F(HeightBySevenFourPlayersGameTestFixture, /*DISABLED_*/Handle_DownRightVerticalWin_ReturnsTrue)
{
    std::ostringstream game;
    game << "|   |   |    |    |    |    |     |" << std::endl;
    game << "|   |   |    |    |    |    |     |" << std::endl;
    game << "|   |   |    |    |    |    | 24w |" << std::endl;
    game << "|   |   |    | 17 | 18 | 19 | 20  |" << std::endl;
    game << "|   |   |    | 13 | 14 | 15 | 16  |" << std::endl;
    game << "|   |   | 23 | 9  | 10 | 11 | 12  |" << std::endl;
    game << "|   |   | 22 | 5  | 6  | 7  | 8   |" << std::endl;
    game << "|   |   | 21 | 1  | 2  | 3  | 4   |";

    ASSERT_TRUE(ValidateGame(CreatePlayersList(), 6u, game.str()));
}

TEST_F(HeightBySevenFourPlayersGameTestFixture, /*DISABLED_*/Handle_UpRightVerticalWin_ReturnsTrue)
{
    std::ostringstream game;
    game << "|   |   |    |    |    |    | 30w |" << std::endl;
    game << "|   |   |    | 28 | 27 | 25 | 26  |" << std::endl;
    game << "|   |   |    | 24 | 23 | 21 | 22  |" << std::endl;
    game << "|   |   |    | 20 | 19 | 17 | 18  |" << std::endl;
    game << "|   |   |    | 16 | 15 | 13 | 14  |" << std::endl;
    game << "|   |   |    | 12 | 11 | 9  | 10  |" << std::endl;
    game << "|   |   |    | 5  | 6  | 7  | 8   |" << std::endl;
    game << "|   |   | 29 | 1  | 2  | 3  | 4   |";

    ASSERT_TRUE(ValidateGame(CreatePlayersList(), 6u, game.str()));
}

TEST_F(HeightBySevenFourPlayersGameTestFixture, /*DISABLED_*/Handle_DownCenterVerticalWin_ReturnsTrue)
{
    std::ostringstream game;
    game << "|   |    |     |    |    |    |   |" << std::endl;
    game << "|   |    |     |    |    |    |   |" << std::endl;
    game << "|   |    | 22w |    |    |    |   |" << std::endl;
    game << "|   | 17 | 18  | 19 | 20 |    |   |" << std::endl;
    game << "|   | 13 | 14  | 15 | 16 |    |   |" << std::endl;
    game << "|   | 9  | 10  | 11 | 12 |    |   |" << std::endl;
    game << "|   | 5  | 6   | 7  | 8  |    |   |" << std::endl;
    game << "|   | 1  | 2   | 3  | 4  | 21 |   |";

    ASSERT_TRUE(ValidateGame(CreatePlayersList(), 6u, game.str()));
}

TEST_F(HeightBySevenFourPlayersGameTestFixture, /*DISABLED_*/Handle_UpCenterVerticalWin_ReturnsTrue)
{
    std::ostringstream game;
    game << "|   |   | 29w |    |    |    |   |" << std::endl;
    game << "|   |   | 25  | 26 | 27 | 28 |   |" << std::endl;
    game << "|   |   | 21  | 22 | 23 | 24 |   |" << std::endl;
    game << "|   |   | 17  | 18 | 19 | 20 |   |" << std::endl;
    game << "|   |   | 13  | 14 | 15 | 16 |   |" << std::endl;
    game << "|   |   | 9   | 10 | 11 | 12 |   |" << std::endl;
    game << "|   |   | 8   | 7  | 6  | 5  |   |" << std::endl;
    game << "|   |   | 4   | 3  | 2  | 1  |   |";

    ASSERT_TRUE(ValidateGame(CreatePlayersList(), 6u, game.str()));
}

TEST_F(HeightBySevenFourPlayersGameTestFixture, /*DISABLED_*/Handle_DownLeftHorizontalWin_ReturnsTrue)
{
    std::ostringstream game;
    game << "|    |    |    |    |    |     |    |" << std::endl;
    game << "|    |    |    |    |    |     |    |" << std::endl;
    game << "|    |    |    |    |    |     |    |" << std::endl;
    game << "|    |    |    |    |    |     |    |" << std::endl;
    game << "| 8  | 12 | 16 | 20 |    |     |    |" << std::endl;
    game << "| 6  | 10 | 14 | 18 | 22 |     | 4  |" << std::endl;
    game << "| 5  | 9  | 13 | 17 | 21 |     | 2  |" << std::endl;
    game << "| 3  | 7  | 11 | 15 | 19 | 23w | 1  |";

    ASSERT_TRUE(ValidateGame(CreatePlayersList(), 6u, game.str()));
}

TEST_F(HeightBySevenFourPlayersGameTestFixture, /*DISABLED_*/Handle_UpLeftHorizontalWin_ReturnsTrue)
{
    std::ostringstream game;
    game << "| 30 | 34 | 38 | 42 | 46 | 50w |    |" << std::endl;
    game << "| 27 | 31 | 35 | 39 | 43 | 49  |    |" << std::endl;
    game << "| 26 | 29 | 33 | 37 | 41 | 45  |    |" << std::endl;
    game << "| 25 | 28 | 32 | 36 | 40 | 44  |    |" << std::endl;
    game << "| 19 | 20 | 21 | 22 | 23 | 24  |    |" << std::endl;
    game << "| 13 | 14 | 15 | 16 | 17 | 18  |    |" << std::endl;
    game << "| 7  | 8  | 9  | 10 | 11 | 12  | 48 |" << std::endl;
    game << "| 1  | 2  | 3  | 4  | 5  | 6   | 47 |";

    ASSERT_TRUE(ValidateGame(CreatePlayersList(), 6u, game.str()));
}

TEST_F(HeightBySevenFourPlayersGameTestFixture, /*DISABLED_*/Handle_DownRightHorizontalWin_ReturnsTrue)
{
    std::ostringstream game;
    game << "|    |    |    |    |    |    |     |" << std::endl;
    game << "|    |    |    |    |    |    |     |" << std::endl;
    game << "|    |    |    |    |    |    |     |" << std::endl;
    game << "|    |    |    |    |    |    |     |" << std::endl;
    game << "|    | 7  | 11 | 15 | 19 | 23 |     |" << std::endl;
    game << "| 3  | 6  | 10 | 14 | 18 | 22 |     |" << std::endl;
    game << "| 2  | 5  | 9  | 13 | 17 | 21 |     |" << std::endl;
    game << "| 1  | 4  | 8  | 12 | 16 | 20 | 24w |";

    ASSERT_TRUE(ValidateGame(CreatePlayersList(), 6u, game.str()));
}

TEST_F(HeightBySevenFourPlayersGameTestFixture, /*DISABLED_*/Handle_UpRightHorizontalWin_ReturnsTrue)
{
    std::ostringstream game;
    game << "|    | 31 | 35 | 39 | 43 | 47 | 51w |" << std::endl;
    game << "|    | 27 | 30 | 34 | 38 | 42 | 46  |" << std::endl;
    game << "|    | 26 | 29 | 33 | 37 | 41 | 45  |" << std::endl;
    game << "|    | 25 | 28 | 32 | 36 | 40 | 44  |" << std::endl;
    game << "|    | 19 | 20 | 21 | 22 | 23 | 24  |" << std::endl;
    game << "| 50 | 13 | 14 | 15 | 16 | 17 | 18  |" << std::endl;
    game << "| 49 | 7  | 8  | 9  | 10 | 11 | 12  |" << std::endl;
    game << "| 48 | 1  | 2  | 3  | 4  | 5  | 6   |";

    ASSERT_TRUE(ValidateGame(CreatePlayersList(), 6u, game.str()));
}

TEST_F(HeightBySevenFourPlayersGameTestFixture, /*DISABLED_*/Handle_DownLeftAscendingWin_ReturnsTrue)
{
    std::ostringstream game;
    game << "|   |   |    |    |    |     |    |" << std::endl;
    game << "|   |   |    |    |    |     |    |" << std::endl;
    game << "|   |   |    |    |    | 24w |    |" << std::endl;
    game << "|   |   |    |    | 20 | 19  |    |" << std::endl;
    game << "|   |   |    | 16 | 13 | 18  |    |" << std::endl;
    game << "|   |   | 12 | 7  | 11 | 17  | 23 |" << std::endl;
    game << "|   | 8 | 3  | 6  | 10 | 15  | 22 |" << std::endl;
    game << "| 4 | 1 | 2  | 5  | 9  | 14  | 21 |";

    ASSERT_TRUE(ValidateGame(CreatePlayersList(), 6u, game.str()));
}

TEST_F(HeightBySevenFourPlayersGameTestFixture, /*DISABLED_*/Handle_UpLeftAscendingWin_ReturnsTrue)
{
    std::ostringstream game;
    game << "|    |    |    |    |    | 33w |   |" << std::endl;
    game << "|    |    |    |    | 29 | 32  |   |" << std::endl;
    game << "|    |    |    | 25 | 26 | 31  |   |" << std::endl;
    game << "|    |    | 21 | 20 | 24 | 30  |   |" << std::endl;
    game << "|    | 17 | 16 | 19 | 23 | 28  |   |" << std::endl;
    game << "| 13 | 14 | 15 | 18 | 22 | 27  |   |" << std::endl;
    game << "| 7  | 8  | 9  | 10 | 11 | 12  |   |" << std::endl;
    game << "| 1  | 2  | 3  | 4  | 5  | 6   |   |";

    ASSERT_TRUE(ValidateGame(CreatePlayersList(), 6u, game.str()));
}

TEST_F(HeightBySevenFourPlayersGameTestFixture, /*DISABLED_*/Handle_DownRightAscendingWin_ReturnsTrue)
{
    std::ostringstream game;
    game << "|    |   |   |    |    |    |     |" << std::endl;
    game << "|    |   |   |    |    |    |     |" << std::endl;
    game << "|    |   |   |    |    |    | 22w |" << std::endl;
    game << "|    |   |   |    |    | 18 | 20  |" << std::endl;
    game << "|    |   |   |    | 14 | 13 | 19  |" << std::endl;
    game << "|    |   |   | 10 | 8  | 12 | 17  |" << std::endl;
    game << "|    |   | 6 | 4  | 7  | 11 | 16  |" << std::endl;
    game << "| 21 | 2 | 1 | 3  | 5  | 9  | 15  |";

    ASSERT_TRUE(ValidateGame(CreatePlayersList(), 6u, game.str()));
}

TEST_F(HeightBySevenFourPlayersGameTestFixture, /*DISABLED_*/Handle_UpRightAscendingWin_ReturnsTrue)
{
    std::ostringstream game;
    game << "|    |    |    |    |    |    | 35w |" << std::endl;
    game << "|    |    |    |    |    | 31 | 32  |" << std::endl;
    game << "|    |    |    |    | 27 | 25 | 30  |" << std::endl;
    game << "|    |    |    | 23 | 20 | 24 | 29  |" << std::endl;
    game << "|    |    | 19 | 16 | 18 | 22 | 28  |" << std::endl;
    game << "|    | 15 | 13 | 14 | 17 | 21 | 26  |" << std::endl;
    game << "| 34 | 7  | 8  | 9  | 10 | 11 | 12  |" << std::endl;
    game << "| 33 | 1  | 2  | 3  | 4  | 5  | 6   |";

    ASSERT_TRUE(ValidateGame(CreatePlayersList(), 6u, game.str()));
}

TEST_F(HeightBySevenFourPlayersGameTestFixture, /*DISABLED_*/Handle_DownLeftDescendingWin_ReturnsTrue)
{
    std::ostringstream game;
    game << "|     |    |    |    |   |   |    |" << std::endl;
    game << "|     |    |    |    |   |   |    |" << std::endl;
    game << "| 22w |    |    |    |   |   |    |" << std::endl;
    game << "| 20  | 18 |    |    |   |   |    |" << std::endl;
    game << "| 19  | 13 | 14 |    |   |   |    |" << std::endl;
    game << "| 17  | 12 | 8  | 10 |   |   |    |" << std::endl;
    game << "| 16  | 11 | 7  | 4  | 6 |   |    |" << std::endl;
    game << "| 15  | 9  | 5  | 3  | 1 | 2 | 21 |";

    ASSERT_TRUE(ValidateGame(CreatePlayersList(), 6u, game.str()));
}

TEST_F(HeightBySevenFourPlayersGameTestFixture, /*DISABLED_*/Handle_UpLeftDescendingWin_ReturnsTrue)
{
    std::ostringstream game;
    game << "| 35w |    |    |    |    |    |    |" << std::endl;
    game << "| 32  | 31 |    |    |    |    |    |" << std::endl;
    game << "| 30  | 25 | 27 |    |    |    |    |" << std::endl;
    game << "| 29  | 24 | 20 | 23 |    |    |    |" << std::endl;
    game << "| 28  | 22 | 18 | 16 | 19 |    |    |" << std::endl;
    game << "| 26  | 21 | 17 | 14 | 13 | 15 |    |" << std::endl;
    game << "| 12  | 11 | 10 | 9  | 8  | 7  | 34 |" << std::endl;
    game << "| 6   | 5  | 4  | 3  | 2  | 1  | 33 |";

    ASSERT_TRUE(ValidateGame(CreatePlayersList(), 6u, game.str()));
}

TEST_F(HeightBySevenFourPlayersGameTestFixture, /*DISABLED_*/Handle_DownRightDescendingWin_ReturnsTrue)
{
    std::ostringstream game;
    game << "|    |     |    |    |    |   |   |" << std::endl;
    game << "|    |     |    |    |    |   |   |" << std::endl;
    game << "|    | 24w |    |    |    |   |   |" << std::endl;
    game << "|    | 19  | 20 |    |    |   |   |" << std::endl;
    game << "|    | 18  | 13 | 16 |    |   |   |" << std::endl;
    game << "| 23 | 17  | 11 | 7  | 12 |   |   |" << std::endl;
    game << "| 22 | 15  | 10 | 6  | 3  | 8 |   |" << std::endl;
    game << "| 21 | 14  | 9  | 5  | 2  | 1 | 4 |";

    ASSERT_TRUE(ValidateGame(CreatePlayersList(), 6u, game.str()));
}

TEST_F(HeightBySevenFourPlayersGameTestFixture, /*DISABLED_*/Handle_UpRightDescendingWin_ReturnsTrue)
{
    std::ostringstream game;
    game << "|   | 33w |    |    |    |    |    |" << std::endl;
    game << "|   | 32  | 29 |    |    |    |    |" << std::endl;
    game << "|   | 31  | 26 | 25 |    |    |    |" << std::endl;
    game << "|   | 30  | 24 | 20 | 21 |    |    |" << std::endl;
    game << "|   | 28  | 23 | 19 | 16 | 17 |    |" << std::endl;
    game << "|   | 27  | 22 | 18 | 15 | 14 | 13 |" << std::endl;
    game << "|   | 12  | 11 | 10 | 9  | 8  | 7  |" << std::endl;
    game << "|   | 6   | 5  | 4  | 3  | 2  | 1  |";

    ASSERT_TRUE(ValidateGame(CreatePlayersList(), 6u, game.str()));
}

TEST_F(HeightBySevenFourPlayersGameTestFixture, /*DISABLED_*/Handle_HorizontalWinNotAtEndpoint_ReturnsTrue)
{
    std::ostringstream game;
    game << "|    |    |     |    |    |    |   |" << std::endl;
    game << "|    |    |     |    |    |    |   |" << std::endl;
    game << "|    |    |     |    |    |    |   |" << std::endl;
    game << "|    |    |     |    |    |    |   |" << std::endl;
    game << "| 4  | 8  |     | 12 | 16 | 20 |   |" << std::endl;
    game << "| 3  | 7  |     | 11 | 15 | 19 |   |" << std::endl;
    game << "| 2  | 6  |     | 10 | 14 | 18 |   |" << std::endl;
    game << "| 1  | 5  | 21w | 9  | 13 | 17 |   |";

    ASSERT_TRUE(ValidateGame(CreatePlayersList(), 6u, game.str()));
}

TEST_F(HeightBySevenFourPlayersGameTestFixture, /*DISABLED_*/Handle_AscendingWinNotAtEndpoint_ReturnsTrue)
{
    std::ostringstream game;
    game << "|    |    |     |    |    |    |    |" << std::endl;
    game << "|    |    |     |    |    |    |    |" << std::endl;
    game << "|    |    |     |    |    | 22 |    |" << std::endl;
    game << "|    |    |     |    | 14 | 19 | 25 |" << std::endl;
    game << "|    |    |     | 10 | 13 | 18 | 24 |" << std::endl;
    game << "|    |    | 26w | 8  | 12 | 17 | 23 |" << std::endl;
    game << "|    | 6  | 4   | 7  | 11 | 16 | 21 |" << std::endl;
    game << "| 2  | 1  | 3   | 5  | 9  | 15 | 20 |";

    ASSERT_TRUE(ValidateGame(CreatePlayersList(), 6u, game.str()));
}

TEST_F(HeightBySevenFourPlayersGameTestFixture, /*DISABLED_*/Handle_DescendingWinNotAtEndpoint_ReturnsTrue)
{
    std::ostringstream game;
    game << "|    |    |     |    |    |    |    |" << std::endl;
    game << "|    |    |     |    |    |    |    |" << std::endl;
    game << "| 23 |    |     |    |    |    |    |" << std::endl;
    game << "| 19 | 15 |     |    |    |    |    |" << std::endl;
    game << "| 18 | 14 | 27w |    |    | 26 |    |" << std::endl;
    game << "| 17 | 13 | 10  | 11 |    | 25 | 22 |" << std::endl;
    game << "| 16 | 12 | 9   | 8  | 7  | 24 | 21 |" << std::endl;
    game << "| 1  | 2  | 4   | 5  | 6  | 3  | 20 |";

    ASSERT_TRUE(ValidateGame(CreatePlayersList(), 6u, game.str()));
}

TEST_F(HeightBySevenFourPlayersGameTestFixture, /*DISABLED_*/Handle_AlmostFullBoardWin_ReturnsTrue)
{
    std::ostringstream game;
    game << "| 50 | 51 | 52 | 53 | 54 | 55w |    |" << std::endl;
    game << "| 43 | 44 | 45 | 46 | 47 | 48  | 49 |" << std::endl;
    game << "| 36 | 37 | 38 | 39 | 41 | 42  | 40 |" << std::endl;
    game << "| 34 | 33 | 35 | 32 | 31 | 30  | 29 |" << std::endl;
    game << "| 22 | 23 | 24 | 25 | 26 | 27  | 28 |" << std::endl;
    game << "| 15 | 16 | 17 | 18 | 19 | 20  | 21 |" << std::endl;
    game << "| 8  | 9  | 10 | 11 | 12 | 13  | 14 |" << std::endl;
    game << "| 1  | 2  | 3  | 4  | 5  | 6   | 7  |";

    ASSERT_TRUE(ValidateGame(CreatePlayersList(), 6u, game.str()));
}
