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
 * @file PlayerTests.cpp
 * @date 2020
 *
 *************************************************************************************************/

#include <gtest/gtest.h>

#include <cxmodel/Disc.h>
#include <cxmodel/IPlayer.h>

TEST(Player, /*DISABLED_*/GetName_ValidName_NameReturned)
{
    const auto player = cxmodel::CreatePlayer("John Doe", cxmodel::MakeRed(), cxmodel::PlayerType::HUMAN);

    ASSERT_EQ(player->GetName(), "John Doe");
}

TEST(Player, /*DISABLED_*/GetChip_ValidChip_ChipReturned)
{
    const auto player = cxmodel::CreatePlayer("John Doe", cxmodel::MakeRed(), cxmodel::PlayerType::HUMAN);
    const cxmodel::Disc disc{cxmodel::MakeRed()};

    ASSERT_EQ(player->GetChip(), disc);
}

TEST(Player, /*DISABLED_*/EqualToOperator_TwoSameNamesAndColors_TrueReturned)
{
    const auto lhs = cxmodel::CreatePlayer("John Doe", cxmodel::MakeRed(), cxmodel::PlayerType::HUMAN);
    const auto rhs = cxmodel::CreatePlayer("John Doe", cxmodel::MakeRed(), cxmodel::PlayerType::HUMAN);

    ASSERT_TRUE(*lhs == *rhs);
}

TEST(Player, /*DISABLED_*/EqualToOperator_TwoDifferentNamesButSameColors_TrueReturned)
{
    const auto lhs = cxmodel::CreatePlayer("John Doe", cxmodel::MakeRed(), cxmodel::PlayerType::HUMAN);
    const auto rhs = cxmodel::CreatePlayer("Jane Doe", cxmodel::MakeRed(), cxmodel::PlayerType::HUMAN);

    ASSERT_TRUE(*lhs == *rhs);
}

TEST(Player, /*DISABLED_*/EqualToOperator_TwoDifferentNamesAndColors_FalseReturned)
{
    const auto lhs = cxmodel::CreatePlayer("John Doe", cxmodel::MakeRed(), cxmodel::PlayerType::HUMAN);
    const auto rhs = cxmodel::CreatePlayer("Jane Doe", cxmodel::MakeBlue(), cxmodel::PlayerType::HUMAN);

    ASSERT_FALSE(*lhs == *rhs);
}

TEST(Player, /*DISABLED_*/EqualToOperator_TwoSameNamesButDifferentColors_FalseReturned)
{
    const auto lhs = cxmodel::CreatePlayer("John Doe", cxmodel::MakeRed(), cxmodel::PlayerType::HUMAN);
    const auto rhs = cxmodel::CreatePlayer("John Doe", cxmodel::MakeBlue(), cxmodel::PlayerType::HUMAN);

    ASSERT_FALSE(*lhs == *rhs);
}

TEST(Player, /*DISABLED_*/NotEqualToOperator_TwoSameNamesAndColors_FalseReturned)
{
    const auto lhs = cxmodel::CreatePlayer("John Doe", cxmodel::MakeRed(), cxmodel::PlayerType::HUMAN);
    const auto rhs = cxmodel::CreatePlayer("John Doe", cxmodel::MakeRed(), cxmodel::PlayerType::HUMAN);

    ASSERT_FALSE(*lhs != *rhs);
}

TEST(Player, /*DISABLED_*/NotEqualToOperator_TwoDifferentNamesButSameColors_FalseReturned)
{
    const auto lhs = cxmodel::CreatePlayer("John Doe", cxmodel::MakeRed(), cxmodel::PlayerType::HUMAN);
    const auto rhs = cxmodel::CreatePlayer("Jane Doe", cxmodel::MakeRed(), cxmodel::PlayerType::HUMAN);

    ASSERT_FALSE(*lhs != *rhs);
}

TEST(Player, /*DISABLED_*/NotEqualToOperator_TwoDifferentNamesAndColors_TrueReturned)
{
    const auto lhs = cxmodel::CreatePlayer("John Doe", cxmodel::MakeRed(), cxmodel::PlayerType::HUMAN);
    const auto rhs = cxmodel::CreatePlayer("Jane Doe", cxmodel::MakeBlue(), cxmodel::PlayerType::HUMAN);

    ASSERT_TRUE(*lhs != *rhs);
}

TEST(Player, /*DISABLED_*/NotEqualToOperator_TwoSameNamesButDifferentColors_TrueReturned)
{
    const auto lhs = cxmodel::CreatePlayer("John Doe", cxmodel::MakeRed(), cxmodel::PlayerType::HUMAN);
    const auto rhs = cxmodel::CreatePlayer("John Doe", cxmodel::MakeBlue(), cxmodel::PlayerType::HUMAN);

    ASSERT_TRUE(*lhs != *rhs);
}
