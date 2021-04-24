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
 * @file TieEdgeCasesGameResolutionStrategyTests.cpp
 * @date 2021
 *
 *************************************************************************************************/

#include <sstream>

#include "GameResolutionStrategyTestFixture.h"

using EdgeCase7By7SevenPlayersGameTestFixture = GameResolutionStrategyTestFixture;

namespace
{

constexpr size_t SEVEN_IN_A_ROW = 7u;

std::vector<cxmodel::Player> CreatePlayersList()
{
    using namespace cxmodel;
    return {
        {"Player 1", MakeRed()},
        {"Player 2", MakeBlue()},
        {"Player 3", MakeYellow()},
        {"Player 4", MakeGreen()},
        {"Player 5", ChipColor::MakePredefined(ChipColor::Predefined::AQUA)},
        {"Player 6", ChipColor::MakePredefined(ChipColor::Predefined::LIME)},
        {"Player 7", ChipColor::MakePredefined(ChipColor::Predefined::GRAY)},
    };
}

} // namespace

TEST_F(EdgeCase7By7SevenPlayersGameTestFixture, /*DISABLED_*/Handle_LeftVertical_ReturnsTrue)
{
    std::ostringstream game;
    game << "| 7 | 14 |     |    |   |   |   |" << std::endl;
    game << "| 6 | 13 | 21t |    |   |   |   |" << std::endl;
    game << "| 5 | 12 | 20  |    |   |   |   |" << std::endl;
    game << "| 4 | 11 | 19  |    |   |   |   |" << std::endl;
    game << "| 3 | 10 | 18  |    |   |   |   |" << std::endl;
    game << "| 2 | 9  | 17  |    |   |   |   |" << std::endl;
    game << "| 1 | 8  | 16  | 15 |   |   |   |";

    ASSERT_TRUE(ValidateGame(CreatePlayersList(), SEVEN_IN_A_ROW, game.str()));
}

TEST_F(EdgeCase7By7SevenPlayersGameTestFixture, /*DISABLED_*/Handle_RightVertical_ReturnsTrue)
{
    std::ostringstream game;
    game << "|   |   |   |    |     | 14 | 7 |" << std::endl;
    game << "|   |   |   |    | 21t | 13 | 6 |" << std::endl;
    game << "|   |   |   |    | 20  | 12 | 5 |" << std::endl;
    game << "|   |   |   |    | 19  | 11 | 4 |" << std::endl;
    game << "|   |   |   |    | 18  | 10 | 3 |" << std::endl;
    game << "|   |   |   |    | 17  | 9  | 2 |" << std::endl;
    game << "|   |   |   | 15 | 16  | 8  | 1 |";

    ASSERT_TRUE(ValidateGame(CreatePlayersList(), SEVEN_IN_A_ROW, game.str()));
}

TEST_F(EdgeCase7By7SevenPlayersGameTestFixture, /*DISABLED_*/Handle_Horizontal_ReturnsTrue)
{
    std::ostringstream game;
    game << "|    |    |     |    |    |    |    |" << std::endl;
    game << "|    |    |     |    |    |    |    |" << std::endl;
    game << "|    |    |     |    |    |    |    |" << std::endl;
    game << "|    |    |     |    |    |    |    |" << std::endl;
    game << "|    |    |     |    |    |    |    |" << std::endl;
    game << "|    |    | 11t |    | 10 | 9  | 8  |" << std::endl;
    game << "| 1  | 2  | 3   | 4  | 5  | 6  | 7  |";

    ASSERT_TRUE(ValidateGame(CreatePlayersList(), SEVEN_IN_A_ROW, game.str()));
}
