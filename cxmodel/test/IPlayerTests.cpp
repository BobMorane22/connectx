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
 * @file IPlayerTests.cpp
 * @date 2022
 *
 *************************************************************************************************/

#include <cxunit/DisableStdStreamsRAII.h>
#include <cxmodel/IChip.h>
#include <cxmodel/IPlayer.h>

TEST(IPlayer, CreatePlayer_HumanPlayer_ValidUnmanagedPlayerCreated)
{
    const auto humanPlayer = CreatePlayer("John", cxmodel::MakeRed(), cxmodel::PlayerType::HUMAN);
    ASSERT_TRUE(humanPlayer);

    ASSERT_TRUE(humanPlayer->GetName() == "John");
    ASSERT_TRUE(humanPlayer->GetChip().GetColor() == cxmodel::MakeRed());
    ASSERT_FALSE(humanPlayer->IsManaged());
}

TEST(IPlayer, CreatePlayer_BotPlayer_ValidManagedPlayerCreated)
{
    const auto botPlayer = CreatePlayer("JohnBot", cxmodel::MakeRed(), cxmodel::PlayerType::BOT);
    ASSERT_TRUE(botPlayer);

    ASSERT_TRUE(botPlayer->GetName() == "JohnBot");
    ASSERT_TRUE(botPlayer->GetChip().GetColor() == cxmodel::MakeRed());
    ASSERT_TRUE(botPlayer->IsManaged());
}

TEST(IPlayer, CreatePlayer_InvalidPlayerType_InvalidPlayerCreated)
{
    const auto invalidPlayerType = static_cast<cxmodel::PlayerType>(-1);

    std::unique_ptr<cxmodel::IPlayer> invalidPlayer;
    {
        cxunit::DisableStdStreamsRAII streamDisabler;
        invalidPlayer = CreatePlayer("Invalid", cxmodel::MakeRed(), invalidPlayerType);
        ASSERT_ASSERTION_FAILED(streamDisabler);
    }

    ASSERT_TRUE(invalidPlayer);

    ASSERT_TRUE(invalidPlayer->GetName() == "");
    ASSERT_TRUE(invalidPlayer->GetChip().GetColor() == cxmodel::MakeTransparent());
    ASSERT_FALSE(invalidPlayer->IsManaged());
}

TEST(IPlayer, EqualToOperator_SameHumanPlayer_ReturnsTrue)
{
    const auto lhs = CreatePlayer("John", cxmodel::MakeRed(), cxmodel::PlayerType::HUMAN);
    ASSERT_TRUE(lhs);

    const auto rhs = CreatePlayer("John", cxmodel::MakeRed(), cxmodel::PlayerType::HUMAN);
    ASSERT_TRUE(lhs);

    ASSERT_TRUE(*lhs == *rhs);
}

TEST(IPlayer, EqualToOperator_SameHumanPlayerButDifferentName_ReturnsTrue)
{
    const auto lhs = CreatePlayer("John", cxmodel::MakeRed(), cxmodel::PlayerType::HUMAN);
    ASSERT_TRUE(lhs);

    const auto rhs = CreatePlayer("Doe", cxmodel::MakeRed(), cxmodel::PlayerType::HUMAN);
    ASSERT_TRUE(lhs);

    ASSERT_TRUE(*lhs == *rhs);
}

TEST(IPlayer, EqualToOperator_SameHumanPlayerButDifferentChipColor_ReturnsFalse)
{
    const auto lhs = CreatePlayer("John", cxmodel::MakeRed(), cxmodel::PlayerType::HUMAN);
    ASSERT_TRUE(lhs);

    const auto rhs = CreatePlayer("John", cxmodel::MakeBlue(), cxmodel::PlayerType::HUMAN);
    ASSERT_TRUE(lhs);

    ASSERT_FALSE(*lhs == *rhs);
}

TEST(IPlayer, EqualToOperator_SameBotPlayer_ReturnsTrue)
{
    const auto lhs = CreatePlayer("John", cxmodel::MakeRed(), cxmodel::PlayerType::BOT);
    ASSERT_TRUE(lhs);

    const auto rhs = CreatePlayer("John", cxmodel::MakeRed(), cxmodel::PlayerType::BOT);
    ASSERT_TRUE(lhs);

    ASSERT_TRUE(*lhs == *rhs);
}

TEST(IPlayer, EqualToOperator_SameBotPlayerButDifferentName_ReturnsTrue)
{
    const auto lhs = CreatePlayer("John", cxmodel::MakeRed(), cxmodel::PlayerType::BOT);
    ASSERT_TRUE(lhs);

    const auto rhs = CreatePlayer("Doe", cxmodel::MakeRed(), cxmodel::PlayerType::BOT);
    ASSERT_TRUE(lhs);

    ASSERT_TRUE(*lhs == *rhs);
}

TEST(IPlayer, EqualToOperator_SameBotPlayerButDifferentChipColor_ReturnsFalse)
{
    const auto lhs = CreatePlayer("John", cxmodel::MakeRed(), cxmodel::PlayerType::BOT);
    ASSERT_TRUE(lhs);

    const auto rhs = CreatePlayer("John", cxmodel::MakeBlue(), cxmodel::PlayerType::BOT);
    ASSERT_TRUE(lhs);

    ASSERT_FALSE(*lhs == *rhs);
}

TEST(IPlayer, EqualToOperator_BotAndHumanPlayers_ReturnsFalse)
{
    const auto lhs = CreatePlayer("John", cxmodel::MakeRed(), cxmodel::PlayerType::HUMAN);
    ASSERT_TRUE(lhs);

    const auto rhs = CreatePlayer("John", cxmodel::MakeRed(), cxmodel::PlayerType::BOT);
    ASSERT_TRUE(lhs);

    ASSERT_FALSE(*lhs == *rhs);
}

TEST(IPlayer, NotEqualToOperator_SameHumanPlayer_ReturnsFalse)
{
    const auto lhs = CreatePlayer("John", cxmodel::MakeRed(), cxmodel::PlayerType::HUMAN);
    ASSERT_TRUE(lhs);

    const auto rhs = CreatePlayer("John", cxmodel::MakeRed(), cxmodel::PlayerType::HUMAN);
    ASSERT_TRUE(lhs);

    ASSERT_FALSE(*lhs != *rhs);
}

TEST(IPlayer, NotEqualToOperator_SameHumanPlayerButDifferentName_ReturnsFalse)
{
    const auto lhs = CreatePlayer("John", cxmodel::MakeRed(), cxmodel::PlayerType::HUMAN);
    ASSERT_TRUE(lhs);

    const auto rhs = CreatePlayer("Doe", cxmodel::MakeRed(), cxmodel::PlayerType::HUMAN);
    ASSERT_TRUE(lhs);

    ASSERT_FALSE(*lhs != *rhs);
}

TEST(IPlayer, NotEqualToOperator_SameHumanPlayerButDifferentChipColor_ReturnsTrue)
{
    const auto lhs = CreatePlayer("John", cxmodel::MakeRed(), cxmodel::PlayerType::HUMAN);
    ASSERT_TRUE(lhs);

    const auto rhs = CreatePlayer("John", cxmodel::MakeBlue(), cxmodel::PlayerType::HUMAN);
    ASSERT_TRUE(lhs);

    ASSERT_TRUE(*lhs != *rhs);
}

TEST(IPlayer, NotEqualToOperator_SameBotPlayer_ReturnsFalse)
{
    const auto lhs = CreatePlayer("John", cxmodel::MakeRed(), cxmodel::PlayerType::BOT);
    ASSERT_TRUE(lhs);

    const auto rhs = CreatePlayer("John", cxmodel::MakeRed(), cxmodel::PlayerType::BOT);
    ASSERT_TRUE(lhs);

    ASSERT_FALSE(*lhs != *rhs);
}

TEST(IPlayer, NotEqualToOperator_SameBotPlayerButDifferentName_ReturnsFalse)
{
    const auto lhs = CreatePlayer("John", cxmodel::MakeRed(), cxmodel::PlayerType::BOT);
    ASSERT_TRUE(lhs);

    const auto rhs = CreatePlayer("Doe", cxmodel::MakeRed(), cxmodel::PlayerType::BOT);
    ASSERT_TRUE(lhs);

    ASSERT_FALSE(*lhs != *rhs);
}

TEST(IPlayer, NotEqualToOperator_SameBotPlayerButDifferentChipColor_ReturnsTrue)
{
    const auto lhs = CreatePlayer("John", cxmodel::MakeRed(), cxmodel::PlayerType::BOT);
    ASSERT_TRUE(lhs);

    const auto rhs = CreatePlayer("John", cxmodel::MakeBlue(), cxmodel::PlayerType::BOT);
    ASSERT_TRUE(lhs);

    ASSERT_TRUE(*lhs != *rhs);
}

TEST(IPlayer, NotEqualToOperator_BotAndHumanPlayers_ReturnsTrue)
{
    const auto lhs = CreatePlayer("John", cxmodel::MakeRed(), cxmodel::PlayerType::HUMAN);
    ASSERT_TRUE(lhs);

    const auto rhs = CreatePlayer("John", cxmodel::MakeRed(), cxmodel::PlayerType::BOT);
    ASSERT_TRUE(lhs);

    ASSERT_TRUE(*lhs != *rhs);
}
