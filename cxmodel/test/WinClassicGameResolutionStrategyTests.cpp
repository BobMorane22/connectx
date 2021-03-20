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
 * @file WinClassicGameResolutionStrategyTests.cpp
 * @date 2021
 *
 *************************************************************************************************/

#include <sstream>

#include "GameResolutionStrategyTestFixture.h"

using ClassicGameFixture = GameResolutionStrategyTestFixture;

TEST_F(ClassicGameFixture, /*DISABLED_*/Handle_DownLeftVerticalWin_ReturnsTrue)
{
    std::ostringstream gameStream;

    gameStream << "|    |   |   |   |   |   |   |" << std::endl;
    gameStream << "|    |   |   |   |   |   |   |" << std::endl;
    gameStream << "| 7w |   |   |   |   |   |   |" << std::endl;
    gameStream << "| 5  | 6 |   |   |   |   |   |" << std::endl;
    gameStream << "| 3  | 4 |   |   |   |   |   |" << std::endl;
    gameStream << "| 1  | 2 |   |   |   |   |   |";

    ASSERT_TRUE(ValidateGame(MakeTwoPlayersList(), 4u, gameStream.str()));
}

TEST_F(ClassicGameFixture, /*DISABLED_*/Handle_UpLeftVerticalWin_ReturnsTrue)
{
    std::ostringstream gameStream;

    gameStream << "|   | 12w |    |   |   |   |   |" << std::endl;
    gameStream << "| 9 | 10  |    |   |   |   |   |" << std::endl;
    gameStream << "| 7 | 8   |    |   |   |   |   |" << std::endl;
    gameStream << "| 5 | 6   |    |   |   |   |   |" << std::endl;
    gameStream << "| 4 | 3   |    |   |   |   |   |" << std::endl;
    gameStream << "| 1 | 2   | 11 |   |   |   |   |";

    ASSERT_TRUE(ValidateGame(MakeTwoPlayersList(), 4u, gameStream.str()));
}

TEST_F(ClassicGameFixture, /*DISABLED_*/Handle_DownRightVerticalWin_ReturnsTrue)
{
    std::ostringstream gameStream;

    gameStream << "|   |   |   |   |   |   |    |" << std::endl;
    gameStream << "|   |   |   |   |   |   |    |" << std::endl;
    gameStream << "|   |   |   |   |   |   | 7w |" << std::endl;
    gameStream << "|   |   |   |   |   | 6 | 5  |" << std::endl;
    gameStream << "|   |   |   |   |   | 4 | 3  |" << std::endl;
    gameStream << "|   |   |   |   |   | 2 | 1  |";

    ASSERT_TRUE(ValidateGame(MakeTwoPlayersList(), 4u, gameStream.str()));
}

TEST_F(ClassicGameFixture, /*DISABLED_*/Handle_UpRightVerticalWin_ReturnsTrue)
{
    std::ostringstream gameStream;

    gameStream << "|   |   |   |   |    | 12w |   |" << std::endl;
    gameStream << "|   |   |   |   |    | 10  | 9 |" << std::endl;
    gameStream << "|   |   |   |   |    | 8   | 7 |" << std::endl;
    gameStream << "|   |   |   |   |    | 6   | 5 |" << std::endl;
    gameStream << "|   |   |   |   |    | 3   | 4 |" << std::endl;
    gameStream << "|   |   |   |   | 11 | 2   | 1 |" << std::endl;

    ASSERT_TRUE(ValidateGame(MakeTwoPlayersList(), 4u, gameStream.str()));
}

TEST_F(ClassicGameFixture, /*DISABLED_*/Handle_DownCenterVerticalWin_ReturnsTrue)
{
    std::ostringstream gameStream;

    gameStream << "|   |   |    |   |   |   |   |" << std::endl;
    gameStream << "|   |   |    |   |   |   |   |" << std::endl;
    gameStream << "|   |   | 7w |   |   |   |   |" << std::endl;
    gameStream << "|   |   | 5  | 6 |   |   |   |" << std::endl;
    gameStream << "|   |   | 3  | 4 |   |   |   |" << std::endl;
    gameStream << "|   |   | 1  | 2 |   |   |   |" << std::endl;

    ASSERT_TRUE(ValidateGame(MakeTwoPlayersList(), 4u, gameStream.str()));
}

TEST_F(ClassicGameFixture, /*DISABLED_*/Handle_UpCenterVerticalWin_ReturnsTrue)
{
    std::ostringstream gameStream;

    gameStream << "|   |   |   |   | 12w |    |   |" << std::endl;
    gameStream << "|   |   |   | 9 | 10  |    |   |" << std::endl;
    gameStream << "|   |   |   | 7 | 8   |    |   |" << std::endl;
    gameStream << "|   |   |   | 5 | 6   |    |   |" << std::endl;
    gameStream << "|   |   |   | 4 | 3   |    |   |" << std::endl;
    gameStream << "|   |   |   | 1 | 2   | 11 |   |" << std::endl;

    ASSERT_TRUE(ValidateGame(MakeTwoPlayersList(), 4u, gameStream.str()));
}

TEST_F(ClassicGameFixture, /*DISABLED_*/Handle_DownLeftHorizontalWin_ReturnsTrue)
{
    std::ostringstream gameStream;

    gameStream << "|   |   |   |    |   |   |   |" << std::endl;
    gameStream << "|   |   |   |    |   |   |   |" << std::endl;
    gameStream << "|   |   |   |    |   |   |   |" << std::endl;
    gameStream << "|   |   |   |    |   |   |   |" << std::endl;
    gameStream << "| 2 | 4 | 6 |    |   |   |   |" << std::endl;
    gameStream << "| 1 | 3 | 5 | 7w |   |   |   |" << std::endl;

    ASSERT_TRUE(ValidateGame(MakeTwoPlayersList(), 4u, gameStream.str()));
}

TEST_F(ClassicGameFixture, /*DISABLED_*/Handle_UpLeftHorizontalWin_ReturnsTrue)
{
    std::ostringstream gameStream;

    gameStream << "| 18 | 20 | 22 | 26w |    |    |   |" << std::endl;
    gameStream << "| 17 | 19 | 21 | 24  |    |    |   |" << std::endl;
    gameStream << "| 13 | 14 | 15 | 16  |    |    |   |" << std::endl;
    gameStream << "| 10 | 9  | 12 | 11  |    |    |   |" << std::endl;
    gameStream << "| 5  | 6  | 7  | 8   |    |    |   |" << std::endl;
    gameStream << "| 1  | 2  | 3  | 4   | 23 | 25 |   |" << std::endl;

    ASSERT_TRUE(ValidateGame(MakeTwoPlayersList(), 4u, gameStream.str()));
}

TEST_F(ClassicGameFixture, /*DISABLED_*/Handle_DownRightHorizontalWin_ReturnsTrue)
{
    std::ostringstream gameStream;

    gameStream << "|   |   |   |    |   |   |   |" << std::endl;
    gameStream << "|   |   |   |    |   |   |   |" << std::endl;
    gameStream << "|   |   |   |    |   |   |   |" << std::endl;
    gameStream << "|   |   |   |    |   |   |   |" << std::endl;
    gameStream << "|   |   |   |    | 6 | 4 | 2 |" << std::endl;
    gameStream << "|   |   |   | 7w | 5 | 3 | 1 |" << std::endl;

    ASSERT_TRUE(ValidateGame(MakeTwoPlayersList(), 4u, gameStream.str()));
}

TEST_F(ClassicGameFixture, /*DISABLED_*/Handle_UpRightHorizontalWin_ReturnsTrue)
{
    std::ostringstream gameStream;

    gameStream << "|   |    |    | 26w | 22 | 20 | 18 |" << std::endl;
    gameStream << "|   |    |    | 24  | 21 | 19 | 17 |" << std::endl;
    gameStream << "|   |    |    | 16  | 15 | 14 | 13 |" << std::endl;
    gameStream << "|   |    |    | 11  | 12 | 9  | 10 |" << std::endl;
    gameStream << "|   |    |    | 8   | 7  | 6  | 5  |" << std::endl;
    gameStream << "|   | 25 | 23 | 4   | 3  | 2  | 1  |" << std::endl;

    ASSERT_TRUE(ValidateGame(MakeTwoPlayersList(), 4u, gameStream.str()));
}

TEST_F(ClassicGameFixture, /*DISABLED_*/Handle_DownCenterHorizontalWin_ReturnsTrue)
{
    std::ostringstream gameStream;

    gameStream << "|   |   |   |   |   |    |   |" << std::endl;
    gameStream << "|   |   |   |   |   |    |   |" << std::endl;
    gameStream << "|   |   |   |   |   |    |   |" << std::endl;
    gameStream << "|   |   |   |   |   |    |   |" << std::endl;
    gameStream << "|   |   | 3 | 5 | 7 |    |   |" << std::endl;
    gameStream << "|   | 1 | 2 | 4 | 6 | 8w |   |" << std::endl;

    ASSERT_TRUE(ValidateGame(MakeTwoPlayersList(), 4u, gameStream.str()));
}

TEST_F(ClassicGameFixture, /*DISABLED_*/Handle_UpCenterHorizontalWin_ReturnsTrue)
{
    std::ostringstream gameStream;

    gameStream << "|   | 18 | 20 | 22 | 26w |    |   |" << std::endl;
    gameStream << "|   | 17 | 19 | 21 | 24  |    |   |" << std::endl;
    gameStream << "|   | 14 | 13 | 16 | 15  |    |   |" << std::endl;
    gameStream << "|   | 10 | 9  | 12 | 11  |    |   |" << std::endl;
    gameStream << "|   | 5  | 6  | 7  | 8   | 25 |   |" << std::endl;
    gameStream << "|   | 1  | 2  | 3  | 4   | 23 |   |" << std::endl;

    ASSERT_TRUE(ValidateGame(MakeTwoPlayersList(), 4u, gameStream.str()));
}

TEST_F(ClassicGameFixture, /*DISABLED_*/Handle_DownLeftAscendingWin_ReturnsTrue)
{
    std::ostringstream gameStream;

    gameStream << "|    |   |   |     |   |   |   |" << std::endl;
    gameStream << "|    |   |   |     |   |   |   |" << std::endl;
    gameStream << "|    |   |   | 11w |   |   |   |" << std::endl;
    gameStream << "|    |   | 7 | 9   |   |   |   |" << std::endl;
    gameStream << "| 10 | 3 | 5 | 8   |   |   |   |" << std::endl;
    gameStream << "| 1  | 2 | 4 | 6   |   |   |   |" << std::endl;

    ASSERT_TRUE(ValidateGame(MakeTwoPlayersList(), 4u, gameStream.str()));
}

TEST_F(ClassicGameFixture, /*DISABLED_*/Handle_UpLeftAscendingWin_ReturnsTrue)
{
    std::ostringstream gameStream;

    gameStream << "|    |    |    | 20w |    |   |   |" << std::endl;
    gameStream << "|    |    | 16 | 18  |    |   |   |" << std::endl;
    gameStream << "| 13 | 14 | 15 | 17  |    |   |   |" << std::endl;
    gameStream << "| 10 | 9  | 12 | 11  |    |   |   |" << std::endl;
    gameStream << "| 5  | 6  | 7  | 8   |    |   |   |" << std::endl;
    gameStream << "| 1  | 2  | 3  | 4   | 19 |   |   |" << std::endl;

    ASSERT_TRUE(ValidateGame(MakeTwoPlayersList(), 4u, gameStream.str()));
}

TEST_F(ClassicGameFixture, /*DISABLED_*/Handle_DownRightAscendingWin_ReturnsTrue)
{
    std::ostringstream gameStream;

    gameStream << "|   |   |   |   |   |   |     |" << std::endl;
    gameStream << "|   |   |   |   |   |   |     |" << std::endl;
    gameStream << "|   |   |   |   |   |   | 11w |" << std::endl;
    gameStream << "|   |   |   |   |   | 7 | 10  |" << std::endl;
    gameStream << "|   |   |   |   | 3 | 5 | 8   |" << std::endl;
    gameStream << "|   |   | 9 | 1 | 2 | 4 | 6   |" << std::endl;

    ASSERT_TRUE(ValidateGame(MakeTwoPlayersList(), 4u, gameStream.str()));
}

TEST_F(ClassicGameFixture, /*DISABLED_*/Handle_UpRightAscendingWin_ReturnsTrue)
{
    std::ostringstream gameStream;

    gameStream << "|   |   |   |    |    |    | 20w |" << std::endl;
    gameStream << "|   |   |   |    |    | 18 | 19  |" << std::endl;
    gameStream << "|   |   |   |    | 14 | 16 | 17  |" << std::endl;
    gameStream << "|   |   |   | 12 | 11 | 13 | 15  |" << std::endl;
    gameStream << "|   |   | 7 | 6  | 8  | 9  | 10  |" << std::endl;
    gameStream << "|   |   | 1 | 2  | 3  | 4  | 5   |" << std::endl;

    ASSERT_TRUE(ValidateGame(MakeTwoPlayersList(), 4u, gameStream.str()));
}

TEST_F(ClassicGameFixture, /*DISABLED_*/Handle_DownCenterAscendingWin_ReturnsTrue)
{
    std::ostringstream gameStream;

    gameStream << "|   |   |   |   |     |    |   |" << std::endl;
    gameStream << "|   |   |   |   |     |    |   |" << std::endl;
    gameStream << "|   |   |   |   | 12w |    |   |" << std::endl;
    gameStream << "|   |   |   | 8 | 10  |    |   |" << std::endl;
    gameStream << "|   |   | 6 | 7 | 9   |    |   |" << std::endl;
    gameStream << "| 1 | 2 | 3 | 4 | 5   | 11 |   |" << std::endl;

    ASSERT_TRUE(ValidateGame(MakeTwoPlayersList(), 4u, gameStream.str()));
}

TEST_F(ClassicGameFixture, /*DISABLED_*/Handle_UpCenterAscendingWin_ReturnsTrue)
{
    std::ostringstream gameStream;

    gameStream << "|   |    |    |    | 20w |    |   |" << std::endl;
    gameStream << "|   |    |    | 18 | 17  |    |   |" << std::endl;
    gameStream << "|   |    | 14 | 15 | 16  |    |   |" << std::endl;
    gameStream << "|   | 10 | 11 | 12 | 13  |    |   |" << std::endl;
    gameStream << "|   | 6  | 7  | 8  | 9   |    |   |" << std::endl;
    gameStream << "| 1 | 2  | 3  | 4  | 5   | 19 |   |" << std::endl;

    ASSERT_TRUE(ValidateGame(MakeTwoPlayersList(), 4u, gameStream.str()));
}

TEST_F(ClassicGameFixture, /*DISABLED_*/Handle_DownLeftDescendingWin_ReturnsTrue)
{
    std::ostringstream gameStream;

    gameStream << "|     |   |   |   |   |   |   |" << std::endl;
    gameStream << "|     |   |   |   |   |   |   |" << std::endl;
    gameStream << "| 10w |   |   |   |   |   |   |" << std::endl;
    gameStream << "| 9   | 8 |   |   |   |   |   |" << std::endl;
    gameStream << "| 5   | 7 | 6 |   |   |   |   |" << std::endl;
    gameStream << "| 1   | 2 | 3 | 4 |   |   |   |" << std::endl;

    ASSERT_TRUE(ValidateGame(MakeTwoPlayersList(), 4u, gameStream.str()));
}

TEST_F(ClassicGameFixture, /*DISABLED_*/Handle_UpLeftDescendingWin_ReturnsTrue)
{
    std::ostringstream gameStream;

    gameStream << "| 19w |    |    |   |   |    |   |" << std::endl;
    gameStream << "| 17  | 15 |    |   |   |    |   |" << std::endl;
    gameStream << "| 16  | 14 | 11 |   |   |    |   |" << std::endl;
    gameStream << "| 12  | 13 | 10 | 9 |   |    |   |" << std::endl;
    gameStream << "| 5   | 6  | 7  | 8 |   |    |   |" << std::endl;
    gameStream << "| 1   | 2  | 3  | 4 |   | 18 |   |" << std::endl;

    ASSERT_TRUE(ValidateGame(MakeTwoPlayersList(), 4u, gameStream.str()));
}

TEST_F(ClassicGameFixture, /*DISABLED_*/Handle_DownRightDescendingWin_ReturnsTrue)
{
    std::ostringstream gameStream;

    gameStream << "|   |   |    |     |   |   |   |" << std::endl;
    gameStream << "|   |   |    |     |   |   |   |" << std::endl;
    gameStream << "|   |   |    | 11w |   |   |   |" << std::endl;
    gameStream << "|   |   |    | 9   | 7 |   |   |" << std::endl;
    gameStream << "|   |   |    | 8   | 6 | 5 |   |" << std::endl;
    gameStream << "|   |   | 10 | 4   | 3 | 2 | 1 |" << std::endl;

    ASSERT_TRUE(ValidateGame(MakeTwoPlayersList(), 4u, gameStream.str()));
}

TEST_F(ClassicGameFixture, /*DISABLED_*/Handle_UpRightDescendingWin_ReturnsTrue)
{
    std::ostringstream gameStream;

    gameStream << "|   |   |   | 18w |    |    |    |" << std::endl;
    gameStream << "|   |   |   | 17  | 16 |    |    |" << std::endl;
    gameStream << "|   |   |   | 15  | 13 | 14 |    |" << std::endl;
    gameStream << "|   |   |   | 12  | 9  | 11 | 10 |" << std::endl;
    gameStream << "|   |   |   | 5   | 6  | 7  | 8  |" << std::endl;
    gameStream << "|   |   |   | 1   | 2  | 3  | 4  |" << std::endl;

    ASSERT_TRUE(ValidateGame(MakeTwoPlayersList(), 4u, gameStream.str()));
}

TEST_F(ClassicGameFixture, /*DISABLED_*/Handle_DownCenterDescendingWin_ReturnsTrue)
{
    std::ostringstream gameStream;

    gameStream << "|   |   |     |   |   |   |   |" << std::endl;
    gameStream << "|   |   |     |   |   |   |   |" << std::endl;
    gameStream << "|   |   | 10w |   |   |   |   |" << std::endl;
    gameStream << "|   |   | 9   | 8 |   |   |   |" << std::endl;
    gameStream << "|   |   | 7   | 5 | 6 |   |   |" << std::endl;
    gameStream << "|   |   | 1   | 2 | 3 | 4 |   |" << std::endl;

    ASSERT_TRUE(ValidateGame(MakeTwoPlayersList(), 4u, gameStream.str()));
}

TEST_F(ClassicGameFixture, /*DISABLED_*/Handle_UpCenterDescendingWin_ReturnsTrue)
{
    std::ostringstream gameStream;

    gameStream << "|   |   | 19w |    |    |   |    |" << std::endl;
    gameStream << "|   |   | 17  | 15 |    |   |    |" << std::endl;
    gameStream << "|   |   | 16  | 13 | 11 |   |    |" << std::endl;
    gameStream << "|   |   | 14  | 12 | 10 | 9 |    |" << std::endl;
    gameStream << "|   |   | 5   | 6  | 7  | 8 |    |" << std::endl;
    gameStream << "|   |   | 1   | 2  | 3  | 4 | 18 |" << std::endl;

    ASSERT_TRUE(ValidateGame(MakeTwoPlayersList(), 4u, gameStream.str()));
}

TEST_F(ClassicGameFixture, /*DISABLED_*/Handle_AlmostFullBoardWin_ReturnsTrue)
{
    std::ostringstream game;
    game << "| 12 | 11 | 24 | 23 | 30 | 41w |    |" << std::endl;
    game << "| 10 | 9  | 22 | 21 | 29 | 39  | 40 |" << std::endl;
    game << "| 8  | 7  | 20 | 19 | 28 | 38  | 37 |" << std::endl;
    game << "| 5  | 6  | 17 | 18 | 27 | 36  | 35 |" << std::endl;
    game << "| 3  | 4  | 15 | 16 | 26 | 33  | 34 |" << std::endl;
    game << "| 1  | 2  | 13 | 14 | 25 | 31  | 32 |";

    ASSERT_TRUE(ValidateGame(MakeTwoPlayersList(), 4u, game.str())); 
}
