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
 * @file WinSquareBoardGameResolutionStrategyTests.cpp
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

TEST_F(SquareBoardThreePlayersGameTestFixture, /*DISABLED_*/Handle_DownLeftVerticalWin_ReturnsTrue)
{
    std::ostringstream gameStream;
    gameStream << "|     |    |    |   |   |   |   |" << std::endl;
    gameStream << "|     |    |    |   |   |   |   |" << std::endl;
    gameStream << "| 13w |    |    |   |   |   |   |" << std::endl;
    gameStream << "| 10  | 11 | 12 |   |   |   |   |" << std::endl;
    gameStream << "| 7   | 8  | 9  |   |   |   |   |" << std::endl;
    gameStream << "| 4   | 5  | 6  |   |   |   |   |" << std::endl;
    gameStream << "| 1   | 2  | 3  |   |   |   |   |";

    ASSERT_TRUE(ValidateGame(CreatePlayersList(), 5u, gameStream.str()));
}

TEST_F(SquareBoardThreePlayersGameTestFixture, /*DISABLED_*/Handle_UpLeftVerticalWin_ReturnsTrue)
{
    std::ostringstream gameStream;
    gameStream << "| 16w | 12 |    |   |   |   |   |" << std::endl;
    gameStream << "| 13  | 11 |    |   |   |   |   |" << std::endl;
    gameStream << "| 10  | 9  |    |   |   |   |   |" << std::endl;
    gameStream << "| 7   | 8  |    |   |   |   |   |" << std::endl;
    gameStream << "| 4   | 6  |    |   |   |   |   |" << std::endl;
    gameStream << "| 3   | 5  | 15 |   |   |   |   |" << std::endl;
    gameStream << "| 2   | 1  | 14 |   |   |   |   |";

    ASSERT_TRUE(ValidateGame(CreatePlayersList(), 5u, gameStream.str()));
}

TEST_F(SquareBoardThreePlayersGameTestFixture, /*DISABLED_*/Handle_DownRightVerticalWin_ReturnsTrue)
{
    std::ostringstream gameStream;
    gameStream << "|   |   |    |    |    |    |     |" << std::endl;
    gameStream << "|   |   |    |    |    |    |     |" << std::endl;
    gameStream << "|   |   |    |    |    |    | 15w |" << std::endl;
    gameStream << "|   |   |    |    | 10 | 11 | 12  |" << std::endl;
    gameStream << "|   |   |    |    | 7  | 8  | 9   |" << std::endl;
    gameStream << "|   |   |    |    | 4  | 5  | 6   |" << std::endl;
    gameStream << "|   |   | 13 | 14 | 1  | 2  | 3   |";

    ASSERT_TRUE(ValidateGame(CreatePlayersList(), 5u, gameStream.str()));
}

TEST_F(SquareBoardThreePlayersGameTestFixture, /*DISABLED_*/Handle_UpRightVerticalWin_ReturnsTrue)
{
    std::ostringstream gameStream;
    gameStream << "|   |   |   |   |    | 13 | 15w |" << std::endl;
    gameStream << "|   |   |   |   |    | 11 | 12  |" << std::endl;
    gameStream << "|   |   |   |   |    | 10 | 9   |" << std::endl;
    gameStream << "|   |   |   |   |    | 8  | 6   |" << std::endl;
    gameStream << "|   |   |   |   |    | 7  | 3   |" << std::endl;
    gameStream << "|   |   |   |   |    | 5  | 2   |" << std::endl;
    gameStream << "|   |   |   |   | 14 | 4  | 1   |";

    ASSERT_TRUE(ValidateGame(CreatePlayersList(), 5u, gameStream.str()));
}

TEST_F(SquareBoardThreePlayersGameTestFixture, /*DISABLED_*/Handle_DownCenterVerticalWin_ReturnsTrue)
{
    std::ostringstream gameStream;
    gameStream << "|   |   |    |     |    |    |   |" << std::endl;
    gameStream << "|   |   |    |     |    |    |   |" << std::endl;
    gameStream << "|   |   |    | 14w |    |    |   |" << std::endl;
    gameStream << "|   |   | 10 | 11  | 12 |    |   |" << std::endl;
    gameStream << "|   |   | 7  | 8   | 9  |    |   |" << std::endl;
    gameStream << "|   |   | 4  | 5   | 6  |    |   |" << std::endl;
    gameStream << "|   |   | 1  | 2   | 3  | 13 |   |";

    ASSERT_TRUE(ValidateGame(CreatePlayersList(), 5u, gameStream.str()));
}

TEST_F(SquareBoardThreePlayersGameTestFixture, /*DISABLED_*/Handle_UpCenterVerticalWin_ReturnsTrue)
{
    std::ostringstream gameStream;
    gameStream << "|   |   | 12 | 17w |    |   |   |" << std::endl;
    gameStream << "|   |   | 10 | 14  |    |   |   |" << std::endl;
    gameStream << "|   |   | 9  | 11  |    |   |   |" << std::endl;
    gameStream << "|   |   | 7  | 8   |    |   |   |" << std::endl;
    gameStream << "|   |   | 6  | 5   | 16 |   |   |" << std::endl;
    gameStream << "|   |   | 4  | 3   | 15 |   |   |" << std::endl;
    gameStream << "|   |   | 2  | 1   | 13 |   |   |";

    ASSERT_TRUE(ValidateGame(CreatePlayersList(), 5u, gameStream.str()));
}

TEST_F(SquareBoardThreePlayersGameTestFixture, /*DISABLED_*/Handle_DownLeftHorizontalWin_ReturnsTrue)
{
    std::ostringstream gameStream;
    gameStream << "|    |    |    |    |     |   |   |" << std::endl;
    gameStream << "|    |    |    |    |     |   |   |" << std::endl;
    gameStream << "|    |    |    |    |     |   |   |" << std::endl;
    gameStream << "|    |    |    |    |     |   |   |" << std::endl;
    gameStream << "| 3  | 6  | 9  | 12 |     |   |   |" << std::endl;
    gameStream << "| 2  | 5  | 8  | 11 |     |   |   |" << std::endl;
    gameStream << "| 1  | 4  | 7  | 10 | 13w |   |   |";

    ASSERT_TRUE(ValidateGame(CreatePlayersList(), 5u, gameStream.str()));
}

TEST_F(SquareBoardThreePlayersGameTestFixture, /*DISABLED_*/Handle_UpLeftHorizontalWin_ReturnsTrue)
{
    std::ostringstream gameStream;
    gameStream << "| 24 | 27 | 30 | 33 | 39w |    |   |" << std::endl;
    gameStream << "| 23 | 26 | 29 | 32 | 37  |    |   |" << std::endl;
    gameStream << "| 22 | 25 | 28 | 31 | 35  |    |   |" << std::endl;
    gameStream << "| 16 | 17 | 18 | 19 | 20  | 38 |   |" << std::endl;
    gameStream << "| 11 | 12 | 13 | 14 | 15  | 36 |   |" << std::endl;
    gameStream << "| 6  | 7  | 8  | 9  | 10  | 34 |   |" << std::endl;
    gameStream << "| 1  | 2  | 3  | 4  | 5   | 21 |   |";

    ASSERT_TRUE(ValidateGame(CreatePlayersList(), 5u, gameStream.str()));
}

TEST_F(SquareBoardThreePlayersGameTestFixture, /*DISABLED_*/Handle_DownRightHorizontalWin_ReturnsTrue)
{
    std::ostringstream gameStream;
    gameStream << "|   |    |    |    |    |    |     |" << std::endl;
    gameStream << "|   |    |    |    |    |    |     |" << std::endl;
    gameStream << "|   |    |    |    |    |    |     |" << std::endl;
    gameStream << "|   |    |    |    |    |    |     |" << std::endl;
    gameStream << "|   |    | 5  | 8  | 11 | 14 |     |" << std::endl;
    gameStream << "|   | 2  | 4  | 7  | 10 | 13 |     |" << std::endl;
    gameStream << "|   | 1  | 3  | 6  | 9  | 12 | 15w |";

    ASSERT_TRUE(ValidateGame(CreatePlayersList(), 5u, gameStream.str()));
}

TEST_F(SquareBoardThreePlayersGameTestFixture, /*DISABLED_*/Handle_UpRightHorizontalWin_ReturnsTrue)
{
    std::ostringstream gameStream;
    gameStream << "|    |   | 23 | 26 | 29 | 32 | 41w |" << std::endl;
    gameStream << "| 40 |   | 22 | 25 | 28 | 31 | 38  |" << std::endl;
    gameStream << "| 39 |   | 21 | 24 | 27 | 30 | 35  |" << std::endl;
    gameStream << "| 37 |   | 16 | 17 | 18 | 19 | 20  |" << std::endl;
    gameStream << "| 36 |   | 11 | 12 | 13 | 14 | 15  |" << std::endl;
    gameStream << "| 34 |   | 6  | 7  | 8  | 9  | 10  |" << std::endl;
    gameStream << "| 33 |   | 1  | 2  | 3  | 4  | 5   |";

    ASSERT_TRUE(ValidateGame(CreatePlayersList(), 5u, gameStream.str()));
}

TEST_F(SquareBoardThreePlayersGameTestFixture, /*DISABLED_*/Handle_DownCenterHorizontalWin_ReturnsTrue)
{
    std::ostringstream gameStream;
    gameStream << "|    |    |    |    |    |     |   |" << std::endl;
    gameStream << "|    |    |    |    |    |     |   |" << std::endl;
    gameStream << "|    |    |    |    |    |     |   |" << std::endl;
    gameStream << "|    |    |    |    |    |     |   |" << std::endl;
    gameStream << "|    | 4  | 7  | 10 | 13 |     |   |" << std::endl;
    gameStream << "|    | 3  | 6  | 9  | 12 |     |   |" << std::endl;
    gameStream << "| 1  | 2  | 5  | 8  | 11 | 14w |   |";

    ASSERT_TRUE(ValidateGame(CreatePlayersList(), 5u, gameStream.str()));
}

TEST_F(SquareBoardThreePlayersGameTestFixture, /*DISABLED_*/Handle_UpCenterHorizontalWin_ReturnsTrue)
{
    std::ostringstream gameStream;
    gameStream << "|   | 25 | 28 | 31 | 34 | 40w |    |" << std::endl;
    gameStream << "|   | 24 | 27 | 30 | 33 | 37  |    |" << std::endl;
    gameStream << "|   | 23 | 26 | 29 | 32 | 36  | 39 |" << std::endl;
    gameStream << "|   | 16 | 17 | 18 | 19 | 20  | 38 |" << std::endl;
    gameStream << "|   | 11 | 12 | 13 | 14 | 15  | 35 |" << std::endl;
    gameStream << "|   | 6  | 7  | 8  | 9  | 10  | 22 |" << std::endl;
    gameStream << "|   | 1  | 2  | 3  | 4  | 5   | 21 |";

    ASSERT_TRUE(ValidateGame(CreatePlayersList(), 5u, gameStream.str()));
}

TEST_F(SquareBoardThreePlayersGameTestFixture, /*DISABLED_*/Handle_DownLeftAscendingWin_ReturnsTrue)
{
    std::ostringstream gameStream;
    gameStream << "|    |    |    |    |     |    |   |" << std::endl;
    gameStream << "|    |    |    |    |     |    |   |" << std::endl;
    gameStream << "|    |    |    |    | 16w |    |   |" << std::endl;
    gameStream << "|    |    |    | 10 | 14  |    |   |" << std::endl;
    gameStream << "|    |    | 7  | 9  | 13  |    |   |" << std::endl;
    gameStream << "|    | 4  | 5  | 8  | 12  |    |   |" << std::endl;
    gameStream << "| 1  | 2  | 3  | 6  | 11  | 15 |   |";

    ASSERT_TRUE(ValidateGame(CreatePlayersList(), 5u, gameStream.str()));
}

TEST_F(SquareBoardThreePlayersGameTestFixture, /*DISABLED_*/Handle_UpLeftAscendingWin_ReturnsTrue)
{
    std::ostringstream gameStream;
    gameStream << "|    |    |    |    | 26w |    |   |" << std::endl;
    gameStream << "|    |    |    | 20 | 24  |    |   |" << std::endl;
    gameStream << "|    |    | 17 | 19 | 23  |    |   |" << std::endl;
    gameStream << "|    | 14 | 15 | 18 | 22  |    |   |" << std::endl;
    gameStream << "| 11 | 12 | 13 | 16 | 21  |    |   |" << std::endl;
    gameStream << "| 6  | 7  | 8  | 9  | 10  |    |   |" << std::endl;
    gameStream << "| 1  | 2  | 3  | 4  | 5   | 25 |   |";

    ASSERT_TRUE(ValidateGame(CreatePlayersList(), 5u, gameStream.str()));
}

TEST_F(SquareBoardThreePlayersGameTestFixture, /*DISABLED_*/Handle_DownRightAscendingWin_ReturnsTrue)
{
    std::ostringstream gameStream;
    gameStream << "|    |   |    |    |    |    |     |" << std::endl;
    gameStream << "|    |   |    |    |    |    |     |" << std::endl;
    gameStream << "|    |   |    |    |    |    | 17w |" << std::endl;
    gameStream << "|    |   |    |    |    | 11 | 16  |" << std::endl;
    gameStream << "|    |   |    |    | 8  | 9  | 13  |" << std::endl;
    gameStream << "| 15 |   |    | 5  | 4  | 7  | 12  |" << std::endl;
    gameStream << "| 14 |   | 2  | 1  | 3  | 6  | 10  |";

    ASSERT_TRUE(ValidateGame(CreatePlayersList(), 5u, gameStream.str()));
}

TEST_F(SquareBoardThreePlayersGameTestFixture, /*DISABLED_*/Handle_UpRightAscendingWin_ReturnsTrue)
{
    std::ostringstream gameStream;
    gameStream << "|    |   |    |    |    |    | 27w |" << std::endl;
    gameStream << "|    |   |    |    |    | 18 | 25  |" << std::endl;
    gameStream << "|    |   |    |    | 12 | 17 | 24  |" << std::endl;
    gameStream << "|    |   |    | 9  | 11 | 16 | 23  |" << std::endl;
    gameStream << "|    |   | 3  | 6  | 10 | 15 | 22  |" << std::endl;
    gameStream << "| 26 |   | 2  | 5  | 8  | 14 | 21  |" << std::endl;
    gameStream << "| 19 |   | 1  | 4  | 7  | 13 | 20  |";

    ASSERT_TRUE(ValidateGame(CreatePlayersList(), 5u, gameStream.str()));
}

TEST_F(SquareBoardThreePlayersGameTestFixture, /*DISABLED_*/Handle_DownCenterAscendingWin_ReturnsTrue)
{
    std::ostringstream gameStream;
    gameStream << "|   |    |    |    |    |     |   |" << std::endl;
    gameStream << "|   |    |    |    |    |     |   |" << std::endl;
    gameStream << "|   |    |    |    |    | 15w |   |" << std::endl;
    gameStream << "|   |    |    |    | 12 | 14  |   |" << std::endl;
    gameStream << "|   |    |    | 9  | 8  | 13  |   |" << std::endl;
    gameStream << "|   |    | 6  | 4  | 7  | 11  |   |" << std::endl;
    gameStream << "|   | 3  | 1  | 2  | 5  | 10  |   |";

    ASSERT_TRUE(ValidateGame(CreatePlayersList(), 5u, gameStream.str()));
}

TEST_F(SquareBoardThreePlayersGameTestFixture, /*DISABLED_*/Handle_UpCenterAscendingWin_ReturnsTrue)
{
    std::ostringstream gameStream;
    gameStream << "|   |    |    |    |    | 28w |    |" << std::endl;
    gameStream << "|   |    |    |    | 22 | 26  |    |" << std::endl;
    gameStream << "|   |    |    | 16 | 21 | 23  |    |" << std::endl;
    gameStream << "|   |    | 13 | 15 | 18 | 20  |    |" << std::endl;
    gameStream << "|   | 10 | 12 | 14 | 17 | 19  | 27 |" << std::endl;
    gameStream << "|   | 6  | 7  | 8  | 9  | 11  | 25 |" << std::endl;
    gameStream << "|   | 1  | 2  | 3  | 4  | 5   | 24 |";

    ASSERT_TRUE(ValidateGame(CreatePlayersList(), 5u, gameStream.str()));
}

TEST_F(SquareBoardThreePlayersGameTestFixture, /*DISABLED_*/Handle_DownLeftDescendingWin_ReturnsTrue)
{
    std::ostringstream gameStream;
    gameStream << "|     |    |    |    |    |   |    |" << std::endl;
    gameStream << "|     |    |    |    |    |   |    |" << std::endl;
    gameStream << "| 16w |    |    |    |    |   |    |" << std::endl;
    gameStream << "| 14  | 10 |    |    |    |   |    |" << std::endl;
    gameStream << "| 13  | 9  | 7  |    |    |   |    |" << std::endl;
    gameStream << "| 12  | 8  | 5  | 4  |    |   |    |" << std::endl;
    gameStream << "| 11  | 6  | 3  | 2  | 1  |   | 15 |";

    ASSERT_TRUE(ValidateGame(CreatePlayersList(), 5u, gameStream.str()));
}

TEST_F(SquareBoardThreePlayersGameTestFixture, /*DISABLED_*/Handle_UpLeftDescendingWin_ReturnsTrue)
{
    std::ostringstream gameStream;
    gameStream << "| 26w |    |    |    |    |   |    |" << std::endl;
    gameStream << "| 24  | 20 |    |    |    |   |    |" << std::endl;
    gameStream << "| 23  | 17 | 14 |    |    |   |    |" << std::endl;
    gameStream << "| 22  | 16 | 11 | 8  |    |   |    |" << std::endl;
    gameStream << "| 21  | 15 | 10 | 6  | 5  |   |    |" << std::endl;
    gameStream << "| 19  | 13 | 9  | 4  | 3  |   |    |" << std::endl;
    gameStream << "| 18  | 12 | 7  | 2  | 1  |   | 25 |";

    ASSERT_TRUE(ValidateGame(CreatePlayersList(), 5u, gameStream.str()));
}

TEST_F(SquareBoardThreePlayersGameTestFixture, /*DISABLED_*/Handle_DownRightDescendingWin_ReturnsTrue)
{
    std::ostringstream gameStream;
    gameStream << "|   |    |     |    |    |    |    |" << std::endl;
    gameStream << "|   |    |     |    |    |    |    |" << std::endl;
    gameStream << "|   |    | 17w |    |    |    |    |" << std::endl;
    gameStream << "|   |    | 14  | 11 |    |    |    |" << std::endl;
    gameStream << "|   |    | 13  | 9  | 8  |    |    |" << std::endl;
    gameStream << "|   | 16 | 12  | 7  | 4  | 5  |    |" << std::endl;
    gameStream << "|   | 15 | 10  | 6  | 3  | 1  | 2  |";

    ASSERT_TRUE(ValidateGame(CreatePlayersList(), 5u, gameStream.str()));
}

TEST_F(SquareBoardThreePlayersGameTestFixture, /*DISABLED_*/Handle_UpRightDescendingWin_ReturnsTrue)
{
    std::ostringstream gameStream;
    gameStream << "|   |    | 27w |    |    |    |    |" << std::endl;
    gameStream << "|   |    | 25  | 18 |    |    |    |" << std::endl;
    gameStream << "|   |    | 24  | 17 | 12 |    |    |" << std::endl;
    gameStream << "|   |    | 23  | 16 | 11 | 9  |    |" << std::endl;
    gameStream << "|   |    | 22  | 15 | 10 | 6  | 3  |" << std::endl;
    gameStream << "|   | 26 | 21  | 14 | 8  | 5  | 2  |" << std::endl;
    gameStream << "|   | 19 | 20  | 13 | 7  | 4  | 1  |";

    ASSERT_TRUE(ValidateGame(CreatePlayersList(), 5u, gameStream.str()));
}

TEST_F(SquareBoardThreePlayersGameTestFixture, /*DISABLED_*/Handle_DownCenterDescendingWin_ReturnsTrue)
{
    std::ostringstream gameStream;
    gameStream << "|   |     |    |    |    |    |   |" << std::endl;
    gameStream << "|   |     |    |    |    |    |   |" << std::endl;
    gameStream << "|   | 15w |    |    |    |    |   |" << std::endl;
    gameStream << "|   | 14  | 12 |    |    |    |   |" << std::endl;
    gameStream << "|   | 13  | 8  | 9  |    |    |   |" << std::endl;
    gameStream << "|   | 11  | 7  | 4  | 6  |    |   |" << std::endl;
    gameStream << "|   | 10  | 5  | 2  | 1  | 3  |   |";

    ASSERT_TRUE(ValidateGame(CreatePlayersList(), 5u, gameStream.str()));
}

TEST_F(SquareBoardThreePlayersGameTestFixture, /*DISABLED_*/Handle_UpCenterDescendingWin_ReturnsTrue)
{
    std::ostringstream gameStream;
    gameStream << "|   | 25w |    |    |    |    |   |" << std::endl;
    gameStream << "|   | 24  | 19 |    |    |    |   |" << std::endl;
    gameStream << "|   | 23  | 17 | 13 |    |    |   |" << std::endl;
    gameStream << "|   | 22  | 16 | 11 | 7  |    |   |" << std::endl;
    gameStream << "|   | 21  | 15 | 10 | 6  | 4  |   |" << std::endl;
    gameStream << "|   | 20  | 14 | 9  | 5  | 2  |   |" << std::endl;
    gameStream << "|   | 18  | 12 | 8  | 3  | 1  |   |";

    ASSERT_TRUE(ValidateGame(CreatePlayersList(), 5u, gameStream.str()));
}

TEST_F(SquareBoardThreePlayersGameTestFixture, /*DISABLED_*/Handle_HorizontalWinNotAtEndpoint_ReturnsTrue)
{
    std::ostringstream gameStream;
    gameStream << "|   |    |     |    |    |    |   |" << std::endl;
    gameStream << "|   |    |     |    |    |    |   |" << std::endl;
    gameStream << "|   |    |     |    |    |    |   |" << std::endl;
    gameStream << "|   |    |     |    |    |    |   |" << std::endl;
    gameStream << "|   | 3  |     | 6  | 9  | 12 |   |" << std::endl;
    gameStream << "|   | 2  |     | 5  | 8  | 11 |   |" << std::endl;
    gameStream << "|   | 1  | 13w | 4  | 7  | 10 |   |";

    ASSERT_TRUE(ValidateGame(CreatePlayersList(), 5u, gameStream.str()));
}

TEST_F(SquareBoardThreePlayersGameTestFixture, /*DISABLED_*/Handle_AscendingWinNotAtEndpoint_ReturnsTrue)
{
    std::ostringstream gameStream;
    gameStream << "|   |    |    |     |    |    |    |" << std::endl;
    gameStream << "|   |    |    |     |    |    |    |" << std::endl;
    gameStream << "|   |    |    |     |    | 14 |    |" << std::endl;
    gameStream << "|   |    |    |     | 11 | 13 |    |" << std::endl;
    gameStream << "|   |    |    | 17w | 8  | 12 |    |" << std::endl;
    gameStream << "|   |    | 5  | 4   | 7  | 10 | 16 |" << std::endl;
    gameStream << "|   | 2  | 1  | 3   | 6  | 9  | 15 |";

    ASSERT_TRUE(ValidateGame(CreatePlayersList(), 5u, gameStream.str()));
}

TEST_F(SquareBoardThreePlayersGameTestFixture, /*DISABLED_*/Handle_DescendingWinNotAtEndpoint_ReturnsTrue)
{
    std::ostringstream gameStream;
    gameStream << "|    |    |    |    |     |    |   |" << std::endl;
    gameStream << "| 20 |    |    |    |     |    |   |" << std::endl;
    gameStream << "| 19 | 18 |    |    |     |    |   |" << std::endl;
    gameStream << "| 17 | 11 | 15 |    |     |    |   |" << std::endl;
    gameStream << "| 16 | 10 | 6  | 12 |     |    |   |" << std::endl;
    gameStream << "| 14 | 8  | 5  | 3  | 21w |    |   |" << std::endl;
    gameStream << "| 13 | 7  | 4  | 2  | 1   | 9  |   |";

    ASSERT_TRUE(ValidateGame(CreatePlayersList(), 5u, gameStream.str()));
}

TEST_F(SquareBoardThreePlayersGameTestFixture, /*DISABLED_*/Handle_AlmostFullBoardWin_ReturnsTrue)
{
    std::ostringstream gameStream;
    gameStream << "| 43 | 44 | 48w |    | 47 | 46 | 45 |" << std::endl;
    gameStream << "| 42 | 41 | 40  | 39 | 38 | 37 | 36 |" << std::endl;
    gameStream << "| 29 | 30 | 31  | 32 | 33 | 34 | 35 |" << std::endl;
    gameStream << "| 28 | 27 | 26  | 25 | 23 | 24 | 22 |" << std::endl;
    gameStream << "| 15 | 16 | 17  | 18 | 19 | 20 | 21 |" << std::endl;
    gameStream << "| 14 | 13 | 12  | 11 | 10 | 9  | 8  |" << std::endl;
    gameStream << "| 1  | 2  | 3   | 4  | 5  | 6  | 7  |";

    ASSERT_TRUE(ValidateGame(CreatePlayersList(), 5u, gameStream.str()));
}
