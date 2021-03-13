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

TEST_F(ClassicGameFixture, TieFirstTest)
{
    // Game setup:
    std::ostringstream game;
    game << "| 12 | 11 | 24 | 23 | 30 |    | 41t |" << std::endl;
    game << "| 10 | 9  | 22 | 21 | 29 | 39 | 40  |" << std::endl;
    game << "| 8  | 7  | 20 | 19 | 28 | 38 | 37  |" << std::endl;
    game << "| 5  | 6  | 17 | 18 | 27 | 36 | 35  |" << std::endl;
    game << "| 3  | 4  | 15 | 16 | 26 | 33 | 34  |" << std::endl;
    game << "| 1  | 2  | 13 | 14 | 25 | 31 | 32  |";

    ASSERT_TRUE(ValidateGame(MakeTwoPlayersList(), 4u, game.str())); 
}
