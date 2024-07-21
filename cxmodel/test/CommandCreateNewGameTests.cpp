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
 * @file CommandCreateNewGameTests.cpp
 * @date 2020
 *
 *************************************************************************************************/

#include <gtest/gtest.h>

#include <cxunit/DisableStdStreamsRAII.h>
#include <cxmodel/Board.h>
#include <cxmodel/CommandCompletionStatus.h>
#include <cxmodel/CommandCreateNewGame.h>

class CommandCreateNewGameTestFixture : public ::testing::Test
{

public:

    cx::model::IConnectXLimits& ModelAsLimitsGet()
    {
        return m_model;
    }

private:

    class ModelMock final : public cx::model::IConnectXLimits
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

TEST_F(CommandCreateNewGameTestFixture, /*DISABLED_*/Execute_ValidNewGame_NewGameCreated)
{
    std::vector<std::shared_ptr<cx::model::IPlayer>> modelPlayers;
    std::unique_ptr<cx::model::IBoard> board;
    size_t modelInARowValue = 0u;

    cx::model::NewGameInformation newGameInformation;

    newGameInformation.m_gridHeight = 6u;
    newGameInformation.m_gridWidth = 7u;
    newGameInformation.m_inARowValue = 4u;
    newGameInformation.m_players.emplace_back(cx::model::CreatePlayer("John Doe", cx::model::MakeRed(), cx::model::PlayerType::HUMAN));
    newGameInformation.m_players.emplace_back(cx::model::CreatePlayer("Jane Doe", cx::model::MakeBlue(), cx::model::PlayerType::HUMAN));

    cx::model::CommandCreateNewGame cmd{ModelAsLimitsGet(), board, modelPlayers, modelInARowValue, std::move(newGameInformation)};
    ASSERT_TRUE(cmd.Execute() == cx::model::CommandCompletionStatus::SUCCESS);

    ASSERT_EQ(modelPlayers.size(), 2u);
    ASSERT_EQ(*modelPlayers[0], *cx::model::CreatePlayer("John Doe", cx::model::MakeRed(), cx::model::PlayerType::HUMAN));
    ASSERT_EQ(*modelPlayers[1], *cx::model::CreatePlayer("Jane Doe", cx::model::MakeBlue(), cx::model::PlayerType::HUMAN));

    ASSERT_TRUE(board);
    ASSERT_EQ(board->GetNbRows(), 6u);
    ASSERT_EQ(board->GetNbColumns(), 7u);
    ASSERT_EQ(modelInARowValue, 4u);
}

TEST_F(CommandCreateNewGameTestFixture, /*DISABLED_*/Undo_ValidNewGame_HasNoEffect)
{
    std::vector<std::shared_ptr<cx::model::IPlayer>> modelPlayers;
    std::unique_ptr<cx::model::IBoard> board;
    size_t modelInARowValue = 0u;

    cx::model::NewGameInformation newGameInformation;

    newGameInformation.m_gridHeight = 6u;
    newGameInformation.m_gridWidth = 7u;
    newGameInformation.m_inARowValue = 4u;
    newGameInformation.m_players.emplace_back(cx::model::CreatePlayer("John Doe", cx::model::MakeRed(), cx::model::PlayerType::HUMAN));
    newGameInformation.m_players.emplace_back(cx::model::CreatePlayer("Jane Doe", cx::model::MakeBlue(), cx::model::PlayerType::HUMAN));

    cx::model::CommandCreateNewGame cmd{ModelAsLimitsGet(), board, modelPlayers, modelInARowValue, std::move(newGameInformation)};
    ASSERT_TRUE(cmd.Execute() == cx::model::CommandCompletionStatus::SUCCESS);

    // For now, undoing should have no effect:
    {
        cx::unit::DisableStdStreamsRAII streamDisabler;
        cmd.Undo();
        ASSERT_ASSERTION_FAILED(streamDisabler);
    }

    ASSERT_EQ(modelPlayers.size(), 2u);
    ASSERT_EQ(*modelPlayers[0], *cx::model::CreatePlayer("John Doe", cx::model::MakeRed(), cx::model::PlayerType::HUMAN));
    ASSERT_EQ(*modelPlayers[1], *cx::model::CreatePlayer("Jane Doe", cx::model::MakeBlue(), cx::model::PlayerType::HUMAN));

    ASSERT_TRUE(board);
    ASSERT_EQ(board->GetNbRows(), 6u);
    ASSERT_EQ(board->GetNbColumns(), 7u);
    ASSERT_EQ(modelInARowValue, 4u);
}
