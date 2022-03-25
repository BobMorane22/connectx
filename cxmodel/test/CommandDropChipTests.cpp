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
 * @file CommandDropChipTests.cpp
 * @date 2020
 *
 *************************************************************************************************/

#include <memory>

#include <gtest/gtest.h>

#include <cxunit/DisableStdStreamsRAII.h>
#include <cxmodel/Board.h>
#include <cxmodel/CommandDropChip.h>
#include <cxmodel/Disc.h>
#include <cxmodel/IConnectXLimits.h>

static const cxmodel::Disc NO_CHIP{cxmodel::MakeTransparent()};

class CommandDropChipTestFixture : public ::testing::Test
{

public:

    cxmodel::IConnectXLimits& ModelAsLimitsGet()
    {
        return m_model;
    }

private:

    class ModelMock final : public cxmodel::IConnectXLimits
    {
        size_t GetMinimumGridHeight() const override {return 6u;};
        size_t GetMinimumGridWidth() const override {return 7u;};
        size_t GetMinimumInARowValue() const override {return 4u;};
        size_t GetMaximumGridHeight() const override {return 64u;};
        size_t GetMaximumGridWidth() const override {return 64u;};
        size_t GetMaximumInARowValue() const override {return 10u;};
        size_t GetMinimumNumberOfPlayers() const override {return 3u;};
        size_t GetMaximumNumberOfPlayers() const override {return 10u;};
    };

    ModelMock m_model;

};

TEST_F(CommandDropChipTestFixture, /*DISABLED_*/Execute_EmptyRowAndTwoPlayers_AllDataUpdated)
{
    // Data setup:
    cxmodel::Board board{6u, 7u, ModelAsLimitsGet()};
    ASSERT_TRUE(board.GetChip({0u, 0u}) == NO_CHIP);

    cxmodel::PlayerInformation playerInfo{
        {
            cxmodel::CreatePlayer("John Doe", cxmodel::MakeRed(), cxmodel::PlayerType::HUMAN),
            cxmodel::CreatePlayer("Jane Doe", cxmodel::MakeBlue(), cxmodel::PlayerType::HUMAN)
        },
        0u,
        1u
    };

    cxmodel::Disc droppedDisc{cxmodel::MakeRed()};

    ASSERT_TRUE(droppedDisc == playerInfo.m_players[playerInfo.m_activePlayerIndex]->GetChip());

    std::vector<cxmodel::IBoard::Position> takenPositions;
    ASSERT_TRUE(takenPositions.empty());

    // The command is created and executed:
    std::unique_ptr<cxmodel::ICommand> cmd = std::make_unique<cxmodel::CommandDropChip>(board,
                                                                                        playerInfo,
                                                                                        std::make_unique<cxmodel::Disc>(droppedDisc),
                                                                                        0u,
                                                                                        takenPositions);

    cmd->Execute();

    // Data is now checked for valid updates:
    ASSERT_TRUE(board.GetChip({0u, 0u}) == cxmodel::Disc(cxmodel::MakeRed()));
    ASSERT_TRUE(playerInfo.m_activePlayerIndex == 1u);
    ASSERT_TRUE(playerInfo.m_nextPlayerIndex == 0u);
    ASSERT_TRUE(takenPositions.size() == 1);
    ASSERT_TRUE(takenPositions[0] == cxmodel::IBoard::Position(0u, 0u));
}

TEST_F(CommandDropChipTestFixture, /*DISABLED_*/Execute_EmptyRowAndThreePlayers_AllDataUpdated)
{
    // Data setup:
    cxmodel::Board board{6u, 7u, ModelAsLimitsGet()};
    ASSERT_TRUE(board.GetChip({0u, 0u}) == NO_CHIP);

    cxmodel::PlayerInformation playerInfo{
        {
            cxmodel::CreatePlayer("John Doe", cxmodel::MakeRed(), cxmodel::PlayerType::HUMAN),
            cxmodel::CreatePlayer("Jane Doe", cxmodel::MakeBlue(), cxmodel::PlayerType::HUMAN),
            cxmodel::CreatePlayer("Stacy Cooper", cxmodel::MakeYellow(), cxmodel::PlayerType::HUMAN)
        },
        0u,
        1u
    };

    cxmodel::Disc droppedDisc{cxmodel::MakeRed()};

    ASSERT_TRUE(droppedDisc == playerInfo.m_players[playerInfo.m_activePlayerIndex]->GetChip());

    std::vector<cxmodel::IBoard::Position> takenPositions;
    ASSERT_TRUE(takenPositions.empty());

    // The command is created and executed:
    std::unique_ptr<cxmodel::ICommand> cmd = std::make_unique<cxmodel::CommandDropChip>(board,
                                                                                        playerInfo,
                                                                                        std::make_unique<cxmodel::Disc>(droppedDisc),
                                                                                        0u,
                                                                                        takenPositions);

    cmd->Execute();

    // Data is now checked for valid updates:
    ASSERT_TRUE(board.GetChip({0u, 0u}) == cxmodel::Disc(cxmodel::MakeRed()));
    ASSERT_TRUE(playerInfo.m_activePlayerIndex == 1u);
    ASSERT_TRUE(playerInfo.m_nextPlayerIndex == 2u);
    ASSERT_TRUE(takenPositions.size() == 1);
    ASSERT_TRUE(takenPositions[0] == cxmodel::IBoard::Position(0u, 0u));
}

TEST_F(CommandDropChipTestFixture, /*DISABLED_*/Execute_RowNotFull_AllDataUpdated)
{
    // Data setup:
    cxmodel::Board board{6u, 7u, ModelAsLimitsGet()};
    cxmodel::Disc firstDisc{cxmodel::MakeRed()};
    cxmodel::IBoard::Position dummy;
    ASSERT_TRUE(board.DropChip(5u, firstDisc, dummy));

    ASSERT_TRUE(board.GetChip({0u, 5u}) == firstDisc);
    ASSERT_TRUE(board.GetChip({1u, 5u}) == NO_CHIP);

    cxmodel::PlayerInformation playerInfo{
        {
            cxmodel::CreatePlayer("John Doe", cxmodel::MakeRed(), cxmodel::PlayerType::HUMAN),
            cxmodel::CreatePlayer("Jane Doe", cxmodel::MakeBlue(), cxmodel::PlayerType::HUMAN),
        },
        1u,
        0u
    };

    cxmodel::Disc droppedDisc{cxmodel::MakeBlue()};

    ASSERT_TRUE(droppedDisc == playerInfo.m_players[playerInfo.m_activePlayerIndex]->GetChip());

    std::vector<cxmodel::IBoard::Position> takenPositions;
    ASSERT_TRUE(takenPositions.empty());

    // The command is created and executed:
    std::unique_ptr<cxmodel::ICommand> cmd = std::make_unique<cxmodel::CommandDropChip>(board,
                                                                                        playerInfo,
                                                                                        std::make_unique<cxmodel::Disc>(droppedDisc),
                                                                                        5u,
                                                                                        takenPositions);

    cmd->Execute();

    // Data is now checked for valid updates:
    ASSERT_TRUE(board.GetChip({1u, 5u}) == cxmodel::Disc(cxmodel::MakeBlue()));
    ASSERT_TRUE(playerInfo.m_activePlayerIndex == 0u);
    ASSERT_TRUE(playerInfo.m_nextPlayerIndex == 1u);
    ASSERT_TRUE(takenPositions.size() == 1);
    ASSERT_TRUE(takenPositions[0] == cxmodel::IBoard::Position(1u, 5u));
}

TEST_F(CommandDropChipTestFixture, /*DISABLED_*/Execute_RowFull_NoDataUpdated)
{
    // Data setup:
    cxmodel::Board board{6u, 7u, ModelAsLimitsGet()};
    cxmodel::Disc firstDisc{cxmodel::MakeRed()};
    cxmodel::Disc secondDisc{cxmodel::MakeBlue()};

    cxmodel::IBoard::Position dummy;
    ASSERT_TRUE(board.DropChip(6u, firstDisc, dummy));
    ASSERT_TRUE(board.DropChip(6u, secondDisc, dummy));
    ASSERT_TRUE(board.DropChip(6u, firstDisc, dummy));
    ASSERT_TRUE(board.DropChip(6u, secondDisc, dummy));
    ASSERT_TRUE(board.DropChip(6u, firstDisc, dummy));
    ASSERT_TRUE(board.DropChip(6u, secondDisc, dummy));
    ASSERT_TRUE(board.GetChip({5u, 6u}) == secondDisc);

    cxmodel::PlayerInformation playerInfo{
        {
            cxmodel::CreatePlayer("John Doe", cxmodel::MakeRed(), cxmodel::PlayerType::HUMAN),
            cxmodel::CreatePlayer("Jane Doe", cxmodel::MakeBlue(), cxmodel::PlayerType::HUMAN),
        },
        0u,
        1u
    };

    cxmodel::Disc droppedDisc{cxmodel::MakeRed()};

    ASSERT_TRUE(droppedDisc == playerInfo.m_players[playerInfo.m_activePlayerIndex]->GetChip());

    std::vector<cxmodel::IBoard::Position> takenPositions;
    ASSERT_TRUE(takenPositions.empty());

    // The command is created and executed:
    std::unique_ptr<cxmodel::ICommand> cmd = std::make_unique<cxmodel::CommandDropChip>(board,
                                                                                        playerInfo,
                                                                                        std::make_unique<cxmodel::Disc>(droppedDisc),
                                                                                        6u,
                                                                                        takenPositions);

    {
        // In production code, the availability of a column should
        // always be checked before dropping a disc. Here, for testing
        // purposes, we call the command directly on a full column and
        // an assertion occurs. We silence it for testing purposes:
        cxunit::DisableStdStreamsRAII streamDisabler;
        cmd->Execute();
    }

    // Data is now checked, no update should have occured:
    ASSERT_TRUE(board.GetChip({5u, 6u}) == cxmodel::Disc(cxmodel::MakeBlue()));
    ASSERT_TRUE(playerInfo.m_activePlayerIndex == 0u);
    ASSERT_TRUE(playerInfo.m_nextPlayerIndex == 1u);
    ASSERT_TRUE(takenPositions.empty());
}
