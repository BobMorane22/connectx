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

#include <Board.h>
#include <CommandDropChip.h>
#include <Disc.h>
#include <IConnectXLimits.h>

#include "DisableStdStreamsRAII.h"
#include "LoggerMock.h"

static const cxmodel::Disc NO_CHIP{cxmodel::MakeTransparent()};

class CommandDropChipTestFixture : public ::testing::Test
{

public:

    std::string GetStdErrContents() const
    {
        return m_disableStreamRAII.GetStdErrContents();
    }

    cxlog::ILogger& GetLogger()
    {
        return m_loggerMock;
    }

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

    LoggerMock m_loggerMock;
    DisableStdStreamsRAII m_disableStreamRAII;
    ModelMock m_model;

};

TEST_F(CommandDropChipTestFixture, Execute_EmptyRowAndTwoPlayers_AllDataUpdated)
{
    // Data setup:
    cxmodel::Board board{7u, 6u, ModelAsLimitsGet()};
    ASSERT_TRUE(board.GetChip({0u, 0u}) == NO_CHIP);

    std::vector<cxmodel::Player> players{
        {"John Doe", cxmodel::MakeRed()},
        {"Jane Doe", cxmodel::MakeBlue()}
    };

    size_t activePlayerIndex = 0u;
    size_t nextPlayerIndex = 1u;

    cxmodel::Disc droppedDisc{cxmodel::MakeRed()};

    ASSERT_TRUE(droppedDisc == players[activePlayerIndex].GetChip());

    // The command is created and executed:
    std::unique_ptr<cxmodel::ICommand> cmd = std::make_unique<cxmodel::CommandDropChip>(GetLogger(),
                                                                                        board,
                                                                                        players,
                                                                                        activePlayerIndex,
                                                                                        nextPlayerIndex,
                                                                                        droppedDisc,
                                                                                        0u);

    cmd->Execute();

    // Data is now checked for valid updates:
    ASSERT_TRUE(board.GetChip({0u, 0u}) == cxmodel::Disc(cxmodel::MakeRed()));
    ASSERT_TRUE(activePlayerIndex == 1u);
    ASSERT_TRUE(nextPlayerIndex == 0u);
}

TEST_F(CommandDropChipTestFixture, Execute_EmptyRowAndThreePlayers_AllDataUpdated)
{
    // Data setup:
    cxmodel::Board board{7u, 6u, ModelAsLimitsGet()};
    ASSERT_TRUE(board.GetChip({0u, 0u}) == NO_CHIP);

    std::vector<cxmodel::Player> players{
        {"John Doe", cxmodel::MakeRed()},
        {"Jane Doe", cxmodel::MakeBlue()},
        {"Stacy Cooper", cxmodel::MakeYellow()}
    };

    size_t activePlayerIndex = 0u;
    size_t nextPlayerIndex = 1u;

    cxmodel::Disc droppedDisc{cxmodel::MakeRed()};

    ASSERT_TRUE(droppedDisc == players[activePlayerIndex].GetChip());

    // The command is created and executed:
    std::unique_ptr<cxmodel::ICommand> cmd = std::make_unique<cxmodel::CommandDropChip>(GetLogger(),
                                                                                        board,
                                                                                        players,
                                                                                        activePlayerIndex,
                                                                                        nextPlayerIndex,
                                                                                        droppedDisc,
                                                                                        0u);

    cmd->Execute();

    // Data is now checked for valid updates:
    ASSERT_TRUE(board.GetChip({0u, 0u}) == cxmodel::Disc(cxmodel::MakeRed()));
    ASSERT_TRUE(activePlayerIndex == 1u);
    ASSERT_TRUE(nextPlayerIndex == 2u);
}

TEST_F(CommandDropChipTestFixture, Execute_RowNotFull_AllDataUpdated)
{
    // Data setup:
    cxmodel::Board board{7u, 6u, ModelAsLimitsGet()};
    cxmodel::Disc firstDisc{cxmodel::MakeRed()};
    cxmodel::IBoard::Position dummy;
    ASSERT_TRUE(board.DropChip(5u, firstDisc, dummy));

    ASSERT_TRUE(board.GetChip({0u, 5u}) == firstDisc);
    ASSERT_TRUE(board.GetChip({1u, 5u}) == NO_CHIP);

    std::vector<cxmodel::Player> players{
        {"John Doe", cxmodel::MakeRed()},
        {"Jane Doe", cxmodel::MakeBlue()}
    };

    size_t activePlayerIndex = 1u;
    size_t nextPlayerIndex = 0u;

    cxmodel::Disc droppedDisc{cxmodel::MakeBlue()};

    ASSERT_TRUE(droppedDisc == players[activePlayerIndex].GetChip());

    // The command is created and executed:
    std::unique_ptr<cxmodel::ICommand> cmd = std::make_unique<cxmodel::CommandDropChip>(GetLogger(),
                                                                                        board,
                                                                                        players,
                                                                                        activePlayerIndex,
                                                                                        nextPlayerIndex,
                                                                                        droppedDisc,
                                                                                        5u);

    cmd->Execute();

    // Data is now checked for valid updates:
    ASSERT_TRUE(board.GetChip({1u, 5u}) == cxmodel::Disc(cxmodel::MakeBlue()));
    ASSERT_TRUE(activePlayerIndex == 0u);
    ASSERT_TRUE(nextPlayerIndex == 1u);
}

TEST_F(CommandDropChipTestFixture, Execute_RowFull_NoDataUpdated)
{
    // Data setup:
    cxmodel::Board board{7u, 6u, ModelAsLimitsGet()};
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

    std::vector<cxmodel::Player> players{
        {"John Doe", cxmodel::MakeRed()},
        {"Jane Doe", cxmodel::MakeBlue()}
    };

    size_t activePlayerIndex = 0u;
    size_t nextPlayerIndex = 1u;

    cxmodel::Disc droppedDisc{cxmodel::MakeRed()};

    ASSERT_TRUE(droppedDisc == players[activePlayerIndex].GetChip());

    // The command is created and executed:
    std::unique_ptr<cxmodel::ICommand> cmd = std::make_unique<cxmodel::CommandDropChip>(GetLogger(),
                                                                                        board,
                                                                                        players,
                                                                                        activePlayerIndex,
                                                                                        nextPlayerIndex,
                                                                                        droppedDisc,
                                                                                        6u);

    cmd->Execute();

    // Data is now checked, no update should have occured:
    ASSERT_TRUE(board.GetChip({5u, 6u}) == cxmodel::Disc(cxmodel::MakeBlue()));
    ASSERT_TRUE(activePlayerIndex == 0u);
    ASSERT_TRUE(nextPlayerIndex == 1u);
}

TEST_F(CommandDropChipTestFixture, Undo_Whatever_Asserts)
{
    // Data setup:
    cxmodel::Board board{7u, 6u, ModelAsLimitsGet()};
    ASSERT_TRUE(board.GetChip({0u, 0u}) == NO_CHIP);

    std::vector<cxmodel::Player> players{
        {"John Doe", cxmodel::MakeRed()},
        {"Jane Doe", cxmodel::MakeBlue()}
    };

    size_t activePlayerIndex = 0u;
    size_t nextPlayerIndex = 1u;

    cxmodel::Disc droppedDisc{cxmodel::MakeRed()};

    ASSERT_TRUE(droppedDisc == players[activePlayerIndex].GetChip());

    // The command is created and executed:
    std::unique_ptr<cxmodel::ICommand> cmd = std::make_unique<cxmodel::CommandDropChip>(GetLogger(),
                                                                                        board,
                                                                                        players,
                                                                                        activePlayerIndex,
                                                                                        nextPlayerIndex,
                                                                                        droppedDisc,
                                                                                        0u);

    ASSERT_TRUE(GetStdErrContents().empty());

    cmd->Undo();

    ASSERT_FALSE(GetStdErrContents().empty());

    const std::string assertToken = "Assertion";
    ASSERT_TRUE(GetStdErrContents().find(assertToken) != std::string::npos);
}
