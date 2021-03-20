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
 * @file TieClassicGameResolutionStrategyTests.cpp
 * @date 2021
 *
 *************************************************************************************************/

#include <sstream>

#include "GameResolutionStrategyTestFixture.h"

using ClassicGameFixture = GameResolutionStrategyTestFixture;

TEST_F(ClassicGameFixture, /*DISABLED_*/Handle_LeftVerticalTie_ReturnsTrue)
{
    std::ostringstream game;
    game << "|    | 39t | 6  | 12 | 29 | 30 | 18 |" << std::endl;
    game << "|    | 38  | 5  | 11 | 28 | 27 | 17 |" << std::endl;
    game << "|    | 37  | 4  | 10 | 25 | 26 | 16 |" << std::endl;
    game << "| 35 | 36  | 3  | 9  | 24 | 23 | 15 |" << std::endl;
    game << "| 34 | 33  | 2  | 8  | 21 | 22 | 14 |" << std::endl;
    game << "| 31 | 32  | 1  | 7  | 20 | 19 | 13 |";

    ASSERT_TRUE(ValidateGame(MakeTwoPlayersList(), 4u, game.str())); 
}

TEST_F(ClassicGameFixture, /*DISABLED_*/Handle_CenterVerticalTie_ReturnsTrue)
{
    std::ostringstream game;
    game << "| 24 | 27 |     |    |    | 33 | 30 |" << std::endl;
    game << "| 23 | 26 | 37t |    | 35 | 32 | 29 |" << std::endl;
    game << "| 22 | 25 | 36  |    | 34 | 31 | 28 |" << std::endl;
    game << "| 14 | 17 | 16  | 19 | 18 | 21 | 20 |" << std::endl;
    game << "| 9  | 8  | 11  | 10 | 13 | 12 | 15 |" << std::endl;
    game << "| 1  | 2  | 3   | 4  | 5  | 6  | 7  |";

    ASSERT_TRUE(ValidateGame(MakeTwoPlayersList(), 4u, game.str())); 
}

TEST_F(ClassicGameFixture, /*DISABLED_*/Handle_RightVerticalTie_ReturnsTrue)
{
    std::ostringstream game;
    game << "| 18 | 30 | 29 | 12 | 6  | 39t |    |" << std::endl;
    game << "| 17 | 27 | 28 | 11 | 5  | 38  |    |" << std::endl;
    game << "| 16 | 26 | 25 | 10 | 4  | 37  |    |" << std::endl;
    game << "| 15 | 23 | 24 | 9  | 3  | 36  | 35 |" << std::endl;
    game << "| 14 | 22 | 21 | 8  | 2  | 33  | 34 |" << std::endl;
    game << "| 13 | 19 | 20 | 7  | 1  | 32  | 31 |";

    ASSERT_TRUE(ValidateGame(MakeTwoPlayersList(), 4u, game.str())); 
}

TEST_F(ClassicGameFixture, /*DISABLED_*/Handle_LeftHorizontalTie_ReturnsTrue)
{
    std::ostringstream game;
    game << "|    |    |    |    |    | 37t | 36 |" << std::endl;
    game << "| 35 | 34 | 33 | 32 | 31 | 30  | 29 |" << std::endl;
    game << "| 27 | 28 | 25 | 26 | 23 | 24  | 21 |" << std::endl;
    game << "| 22 | 19 | 20 | 17 | 18 | 15  | 16 |" << std::endl;
    game << "| 14 | 13 | 12 | 11 | 10 | 9   | 8  |" << std::endl;
    game << "| 7  | 6  | 5  | 4  | 3  | 2   | 1  |";

    ASSERT_TRUE(ValidateGame(MakeTwoPlayersList(), 4u, game.str())); 
}

TEST_F(ClassicGameFixture, /*DISABLED_*/Handle_CenterHorizontalTie_ReturnsTrue)
{
    std::ostringstream game;
    game << "| 36 |    |    |    |    | 38t | 37 |" << std::endl;
    game << "| 29 | 30 | 31 | 32 | 33 | 34  | 35 |" << std::endl;
    game << "| 21 | 24 | 23 | 26 | 25 | 28  | 27 |" << std::endl;
    game << "| 16 | 15 | 18 | 17 | 20 | 19  | 22 |" << std::endl;
    game << "| 8  | 9  | 10 | 11 | 12 | 13  | 14 |" << std::endl;
    game << "| 1  | 2  | 3  | 4  | 5  | 6   | 7  |";

    ASSERT_TRUE(ValidateGame(MakeTwoPlayersList(), 4u, game.str())); 
}

TEST_F(ClassicGameFixture, /*DISABLED_*/Handle_RightHorizontalTie_ReturnsTrue)
{
    std::ostringstream game;
    game << "| 36 | 37t |    |    |    |    |    |" << std::endl;
    game << "| 29 | 30  | 31 | 32 | 33 | 34 | 35 |" << std::endl;
    game << "| 21 | 24  | 23 | 26 | 25 | 28 | 27 |" << std::endl;
    game << "| 16 | 15  | 18 | 17 | 20 | 19 | 22 |" << std::endl;
    game << "| 8  | 9   | 10 | 11 | 12 | 13 | 14 |" << std::endl;
    game << "| 1  | 2   | 3  | 4  | 5  | 6  | 7  |";

    ASSERT_TRUE(ValidateGame(MakeTwoPlayersList(), 4u, game.str())); 
}

TEST_F(ClassicGameFixture, /*DISABLED_*/Handle_RightAscendingTie_ReturnsTrue)
{
    std::ostringstream game;
    game << "| 6 | 20 | 25 | 30 | 40t |    |    |" << std::endl;
    game << "| 5 | 19 | 24 | 29 | 37  | 38 | 39 |" << std::endl;
    game << "| 4 | 18 | 23 | 28 | 36  | 34 | 35 |" << std::endl;
    game << "| 3 | 17 | 22 | 27 | 33  | 31 | 16 |" << std::endl;
    game << "| 2 | 10 | 9  | 26 | 32  | 14 | 15 |" << std::endl;
    game << "| 1 | 7  | 8  | 21 | 11  | 12 | 13 |";

    ASSERT_TRUE(ValidateGame(MakeTwoPlayersList(), 4u, game.str())); 
}

TEST_F(ClassicGameFixture, /*DISABLED_*/Handle_LeftDescendingTie_ReturnsTrue)
{
    std::ostringstream game;
    game << "|    |    | 40t | 30 | 25 | 20 | 6  |" << std::endl;
    game << "| 39 | 38 | 37  | 29 | 24 | 19 | 5  |" << std::endl;
    game << "| 35 | 34 | 36  | 28 | 23 | 18 | 4  |" << std::endl;
    game << "| 16 | 31 | 33  | 27 | 22 | 17 | 3  |" << std::endl;
    game << "| 15 | 14 | 32  | 26 | 9  | 10 | 2  |" << std::endl;
    game << "| 13 | 12 | 11  | 21 | 8  | 7  | 1  |";

    ASSERT_TRUE(ValidateGame(MakeTwoPlayersList(), 4u, game.str())); 
}

TEST_F(ClassicGameFixture, /*DISABLED_*/Handle_AlmostFullBoardTie_ReturnsTrue)
{
    std::ostringstream game;
    game << "| 12 | 11 | 24 | 23 | 30 |    | 41t |" << std::endl;
    game << "| 10 | 9  | 22 | 21 | 29 | 39 | 40  |" << std::endl;
    game << "| 8  | 7  | 20 | 19 | 28 | 38 | 37  |" << std::endl;
    game << "| 5  | 6  | 17 | 18 | 27 | 36 | 35  |" << std::endl;
    game << "| 3  | 4  | 15 | 16 | 26 | 33 | 34  |" << std::endl;
    game << "| 1  | 2  | 13 | 14 | 25 | 31 | 32  |";

    ASSERT_TRUE(ValidateGame(MakeTwoPlayersList(), 4u, game.str())); 
}
