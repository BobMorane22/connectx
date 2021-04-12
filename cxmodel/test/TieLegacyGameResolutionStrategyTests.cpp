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
 * @file TieLegacyGameResolutionStrategyTests.cpp
 * @date 2021
 *
 * These are the unit tests 'as-is' from the previous Connect X projet. They have been converted
 * to the new testing syntax, for more readability.
 *
 *************************************************************************************************/

#include <sstream>

#include "GameResolutionStrategyTestFixture.h"

using Legacy9By8ThreePlayersGameTestFixture = GameResolutionStrategyTestFixture;

namespace
{

std::vector<cxmodel::Player> CreatePlayersList()
{
    return {
        {"Player 1", cxmodel::MakeRed()},
        {"Player 2", cxmodel::MakeBlue()},
        {"Player 3", cxmodel::MakeYellow()},
    };
}

} // namespace

TEST_F(Legacy9By8ThreePlayersGameTestFixture, /*DISABLED_*/Handle_HorizontalTie_ReturnsTrue)
{
    std::ostringstream game;
    game << "|    |    |    |    |    |     |    |    |" << std::endl;
    game << "|    |    |    |    |    |     |    |    |" << std::endl;
    game << "| 49 | 50 | 51 | 52 | 53 | 54t |    |    |" << std::endl;
    game << "| 41 | 42 | 43 | 44 | 45 | 46  | 47 | 48 |" << std::endl;
    game << "| 33 | 34 | 35 | 36 | 37 | 38  | 39 | 40 |" << std::endl;
    game << "| 27 | 28 | 21 | 29 | 30 | 24  | 31 | 32 |" << std::endl;
    game << "| 19 | 20 | 15 | 22 | 23 | 18  | 25 | 26 |" << std::endl;
    game << "| 10 | 11 | 9  | 13 | 14 | 12  | 16 | 17 |" << std::endl;
    game << "| 1  | 2  | 3  | 4  | 5  | 6   | 7  | 8  |";

    ASSERT_TRUE(ValidateGame(CreatePlayersList(), 7u, game.str()));
}

TEST_F(Legacy9By8ThreePlayersGameTestFixture, /*DISABLED_*/Handle_VerticalTie_ReturnsTrue)
{
    std::ostringstream game;
    game << "| 17 | 18 | 35 | 36 | 45 |     |    |    |" << std::endl;
    game << "| 15 | 16 | 33 | 34 | 44 |     |    |    |" << std::endl;
    game << "| 13 | 14 | 31 | 32 | 43 |     |    |    |" << std::endl;
    game << "| 11 | 12 | 29 | 30 | 42 |     |    |    |" << std::endl;
    game << "| 9  | 10 | 27 | 28 | 41 |     |    |    |" << std::endl;
    game << "| 7  | 8  | 25 | 26 | 40 | 56t |    | 55 |" << std::endl;
    game << "| 5  | 6  | 23 | 24 | 39 | 52  | 53 | 54 |" << std::endl;
    game << "| 3  | 4  | 21 | 22 | 38 | 50  | 51 | 49 |" << std::endl;
    game << "| 1  | 2  | 19 | 20 | 37 | 46  | 47 | 48 |";

    ASSERT_TRUE(ValidateGame(CreatePlayersList(), 7u, game.str()));
}

TEST_F(Legacy9By8ThreePlayersGameTestFixture, /*DISABLED_*/Handle_DiagonalUpwardTie_ReturnsTrue)
{
    std::ostringstream game;
    game << "| 9  | 18 |    |    |    | 56t |    |    |" << std::endl;
    game << "| 8  | 17 | 33 |    |    | 55  |    |    |" << std::endl;
    game << "| 7  | 16 | 32 | 31 |    | 54  |    |    |" << std::endl;
    game << "| 6  | 15 | 29 | 30 | 44 | 53  |    |    |" << std::endl;
    game << "| 5  | 14 | 28 | 27 | 43 | 42  |    |    |" << std::endl;
    game << "| 4  | 13 | 25 | 26 | 40 | 41  | 51 | 52 |" << std::endl;
    game << "| 3  | 12 | 24 | 23 | 39 | 38  | 49 | 50 |" << std::endl;
    game << "| 2  | 11 | 21 | 22 | 36 | 37  | 48 | 47 |" << std::endl;
    game << "| 1  | 10 | 20 | 19 | 35 | 34  | 45 | 46 |";

    ASSERT_TRUE(ValidateGame(CreatePlayersList(), 7u, game.str()));
}

TEST_F(Legacy9By8ThreePlayersGameTestFixture, /*DISABLED_*/Handle_DiagonalDownwardTie_ReturnsTrue)
{
    std::ostringstream game;
    game << "|    |    | 56t |    |    |    | 18 | 9  |" << std::endl;
    game << "|    |    | 55  |    |    | 33 | 17 | 8  |" << std::endl;
    game << "|    |    | 54  |    | 31 | 32 | 16 | 7  |" << std::endl;
    game << "|    |    | 53  | 44 | 30 | 29 | 15 | 6  |" << std::endl;
    game << "|    |    | 42  | 43 | 27 | 28 | 14 | 5  |" << std::endl;
    game << "| 52 | 51 | 41  | 40 | 26 | 25 | 13 | 4  |" << std::endl;
    game << "| 50 | 49 | 38  | 39 | 23 | 24 | 12 | 3  |" << std::endl;
    game << "| 47 | 48 | 37  | 36 | 22 | 21 | 11 | 2  |" << std::endl;
    game << "| 46 | 45 | 34  | 35 | 19 | 20 | 10 | 1  |";

    ASSERT_TRUE(ValidateGame(CreatePlayersList(), 7u, game.str()));
}
