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
 * @file WinEdgeCasesGameResolutionStrategyTests.cpp
 * @date 2021
 *
 *************************************************************************************************/

#include <sstream>

#include "GameResolutionStrategyTestFixture.h"

using EdgeCase7By7SevenPlayersGameTestFixture = GameResolutionStrategyTestFixture;

namespace
{

constexpr size_t SEVEN_IN_A_ROW = 7u;

std::vector<std::shared_ptr<cxmodel::IPlayer>> CreatePlayersList()
{
    using namespace cxmodel;

    return {
        cxmodel::CreatePlayer("Player 1", cxmodel::MakeRed(), cxmodel::PlayerType::HUMAN),
        cxmodel::CreatePlayer("Player 2", cxmodel::MakeBlue(), cxmodel::PlayerType::HUMAN),
        cxmodel::CreatePlayer("Player 3", cxmodel::MakeYellow(), cxmodel::PlayerType::HUMAN),
        cxmodel::CreatePlayer("Player 4", cxmodel::MakeGreen(), cxmodel::PlayerType::HUMAN),
        cxmodel::CreatePlayer("Player 5", ChipColor::MakePredefined(ChipColor::Predefined::AQUA), cxmodel::PlayerType::HUMAN),
        cxmodel::CreatePlayer("Player 6", ChipColor::MakePredefined(ChipColor::Predefined::LIME), cxmodel::PlayerType::HUMAN),
        cxmodel::CreatePlayer("Player 7", ChipColor::MakePredefined(ChipColor::Predefined::GRAY), cxmodel::PlayerType::HUMAN),
    };
}

} // namespace

TEST_F(EdgeCase7By7SevenPlayersGameTestFixture, /*DISABLED_*/Handle_LeftVerticalWin_ReturnsTrue)
{
    std::ostringstream game;
    game << "| 43w |    |    |    |    |    |    |" << std::endl;
    game << "| 36  | 37 | 38 | 39 | 40 | 41 | 42 |" << std::endl;
    game << "| 29  | 30 | 31 | 32 | 33 | 34 | 35 |" << std::endl;
    game << "| 22  | 23 | 24 | 25 | 26 | 27 | 28 |" << std::endl;
    game << "| 15  | 16 | 17 | 18 | 19 | 20 | 21 |" << std::endl;
    game << "| 8   | 9  | 10 | 11 | 12 | 13 | 14 |" << std::endl;
    game << "| 1   | 2  | 3  | 4  | 5  | 6  | 7  |";

    ASSERT_TRUE(ValidateGame(CreatePlayersList(), SEVEN_IN_A_ROW, game.str()));
}

TEST_F(EdgeCase7By7SevenPlayersGameTestFixture, /*DISABLED_*/Handle_CenterVerticalWin_ReturnsTrue)
{
    std::ostringstream game;
    game << "|    |    |    | 46w | 45 | 44 | 43 |" << std::endl;
    game << "| 36 | 37 | 38 | 39  | 40 | 41 | 42 |" << std::endl;
    game << "| 29 | 30 | 31 | 32  | 33 | 34 | 35 |" << std::endl;
    game << "| 22 | 23 | 24 | 25  | 26 | 27 | 28 |" << std::endl;
    game << "| 15 | 16 | 17 | 18  | 19 | 20 | 21 |" << std::endl;
    game << "| 8  | 9  | 10 | 11  | 12 | 13 | 14 |" << std::endl;
    game << "| 1  | 2  | 3  | 4   | 5  | 6  | 7  |";

    ASSERT_TRUE(ValidateGame(CreatePlayersList(), SEVEN_IN_A_ROW, game.str()));
}

TEST_F(EdgeCase7By7SevenPlayersGameTestFixture, /*DISABLED_*/Handle_RightVerticalWin_ReturnsTrue)
{
    std::ostringstream game;
    game << "| 43 | 44 | 45 | 46 | 47 | 48 | 49w |" << std::endl;
    game << "| 41 | 40 | 39 | 38 | 37 | 36 | 42  |" << std::endl;
    game << "| 29 | 30 | 31 | 32 | 33 | 34 | 35  |" << std::endl;
    game << "| 27 | 26 | 25 | 24 | 23 | 22 | 28  |" << std::endl;
    game << "| 15 | 16 | 17 | 18 | 19 | 20 | 21  |" << std::endl;
    game << "| 13 | 12 | 11 | 10 | 9  | 8  | 14  |" << std::endl;
    game << "| 1  | 2  | 3  | 4  | 5  | 6  | 7   |";

    ASSERT_TRUE(ValidateGame(CreatePlayersList(), SEVEN_IN_A_ROW, game.str()));
}

TEST_F(EdgeCase7By7SevenPlayersGameTestFixture, /*DISABLED_*/Handle_DownHorizontalWin_ReturnsTrue)
{
    std::ostringstream game;
    game << "| 7 | 14 | 21 | 28 | 35 | 42 |     |" << std::endl;
    game << "| 6 | 13 | 20 | 27 | 34 | 41 |     |" << std::endl;
    game << "| 5 | 12 | 19 | 26 | 33 | 40 |     |" << std::endl;
    game << "| 4 | 11 | 18 | 25 | 32 | 39 |     |" << std::endl;
    game << "| 3 | 10 | 17 | 24 | 31 | 38 |     |" << std::endl;
    game << "| 2 | 9  | 16 | 23 | 30 | 37 |     |" << std::endl;
    game << "| 1 | 8  | 15 | 22 | 29 | 36 | 43w |";

    ASSERT_TRUE(ValidateGame(CreatePlayersList(), SEVEN_IN_A_ROW, game.str()));
}

TEST_F(EdgeCase7By7SevenPlayersGameTestFixture, /*DISABLED_*/Handle_CenterHorizontalWin_ReturnsTrue)
{
    std::ostringstream game;
    game << "| 7 | 14 | 21 |     | 45 | 28 | 35 |" << std::endl;
    game << "| 6 | 13 | 20 |     | 44 | 27 | 34 |" << std::endl;
    game << "| 5 | 12 | 19 |     | 43 | 26 | 33 |" << std::endl;
    game << "| 4 | 11 | 18 | 46w | 39 | 25 | 32 |" << std::endl;
    game << "| 3 | 10 | 17 | 42  | 38 | 24 | 31 |" << std::endl;
    game << "| 2 | 9  | 16 | 41  | 37 | 23 | 30 |" << std::endl;
    game << "| 1 | 8  | 15 | 40  | 36 | 22 | 29 |";

    ASSERT_TRUE(ValidateGame(CreatePlayersList(), SEVEN_IN_A_ROW, game.str()));
}

TEST_F(EdgeCase7By7SevenPlayersGameTestFixture, /*DISABLED_*/Handle_Ascending_ReturnsTrue)
{
    std::ostringstream game;
    game << "| 31 | 37 | 42 | 45 | 47 |    | 48w |" << std::endl;
    game << "| 30 | 36 | 40 | 44 | 46 | 41 | 24  |" << std::endl;
    game << "| 29 | 35 | 39 | 43 | 34 | 17 | 23  |" << std::endl;
    game << "| 28 | 33 | 38 | 27 | 11 | 16 | 22  |" << std::endl;
    game << "| 26 | 32 | 20 | 7  | 10 | 15 | 21  |" << std::endl;
    game << "| 25 | 13 | 3  | 5  | 9  | 14 | 19  |" << std::endl;
    game << "| 6  | 1  | 2  | 4  | 8  | 12 | 18  |";

    ASSERT_TRUE(ValidateGame(CreatePlayersList(), SEVEN_IN_A_ROW, game.str()));
}

TEST_F(EdgeCase7By7SevenPlayersGameTestFixture, /*DISABLED_*/Handle_Descending_ReturnsTrue)
{
    std::ostringstream game;
    game << "| 45w |    |    |    | 42 | 37 | 32 |" << std::endl;
    game << "| 25  | 38 |    | 44 | 41 | 36 | 30 |" << std::endl;
    game << "| 23  | 18 | 31 | 43 | 40 | 35 | 29 |" << std::endl;
    game << "| 22  | 16 | 12 | 24 | 39 | 34 | 28 |" << std::endl;
    game << "| 21  | 15 | 11 | 7  | 17 | 33 | 27 |" << std::endl;
    game << "| 20  | 14 | 9  | 6  | 4  | 10 | 26 |" << std::endl;
    game << "| 19  | 13 | 8  | 5  | 2  | 1  | 3  |";

    ASSERT_TRUE(ValidateGame(CreatePlayersList(), SEVEN_IN_A_ROW, game.str()));
}
