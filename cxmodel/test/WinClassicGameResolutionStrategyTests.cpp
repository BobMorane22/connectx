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

TEST_F(ClassicGameFixture, WinFirstTest)
{
    // Game setup:
    std::ostringstream game;
    game << "|    |   |   |   |   |   |   |" << std::endl; 
    game << "|    |   |   |   |   |   |   |" << std::endl;
    game << "| 7w |   |   |   |   |   |   |" << std::endl;
    game << "| 5  | 6 |   |   |   |   |   |" << std::endl;
    game << "| 3  | 4 |   |   |   |   |   |" << std::endl;
    game << "| 1  | 2 |   |   |   |   |   |";

    ASSERT_TRUE(ValidateGame(MakeTwoPlayersList(), 4u, game.str())); 
}

TEST_F(ClassicGameFixture, WinSecondTest)
{
    // Game setup:
    std::ostringstream game;
    game << "|   |   |   |   |   |   |    |" << std::endl; 
    game << "|   |   |   |   |   |   |    |" << std::endl;
    game << "|   |   |   |   |   |   | 7w |" << std::endl;
    game << "|   |   |   |   |   | 6 | 5  |" << std::endl;
    game << "|   |   |   |   |   | 4 | 3  |" << std::endl;
    game << "|   |   |   |   |   | 2 | 1  |";

    ASSERT_TRUE(ValidateGame(MakeTwoPlayersList(), 4u, game.str())); 
}
