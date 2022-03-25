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

#include <cxmodel/Board.h>
#include <cxmodel/CommandCreateNewGame.h>

class CommandCreateNewGameTestFixture : public ::testing::Test
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

TEST_F(CommandCreateNewGameTestFixture, /*DISABLED_*/Execute_ValidNewGame_NewGameCreated)
{
    std::vector<std::shared_ptr<cxmodel::IPlayer>> modelPlayers;
    std::unique_ptr<cxmodel::IBoard> board;
    size_t modelInARowValue = 0u;

    cxmodel::NewGameInformation newGameInformation;

    newGameInformation.m_gridHeight = 6u;
    newGameInformation.m_gridWidth = 7u;
    newGameInformation.m_inARowValue = 4u;
    newGameInformation.m_players.emplace_back(cxmodel::CreatePlayer("John Doe", cxmodel::MakeRed(), cxmodel::PlayerType::HUMAN));
    newGameInformation.m_players.emplace_back(cxmodel::CreatePlayer("Jane Doe", cxmodel::MakeBlue(), cxmodel::PlayerType::HUMAN));

    cxmodel::CommandCreateNewGame cmd{ModelAsLimitsGet(), board, modelPlayers, modelInARowValue, std::move(newGameInformation)};
    cmd.Execute();

    ASSERT_EQ(modelPlayers.size(), 2u);
    ASSERT_EQ(*modelPlayers[0], *cxmodel::CreatePlayer("John Doe", cxmodel::MakeRed(), cxmodel::PlayerType::HUMAN));
    ASSERT_EQ(*modelPlayers[1], *cxmodel::CreatePlayer("Jane Doe", cxmodel::MakeBlue(), cxmodel::PlayerType::HUMAN));

    ASSERT_TRUE(board);
    ASSERT_EQ(board->GetNbRows(), 6u);
    ASSERT_EQ(board->GetNbColumns(), 7u);
    ASSERT_EQ(modelInARowValue, 4u);
}

TEST_F(CommandCreateNewGameTestFixture, /*DISABLED_*/Undo_ValidNewGame_HasNoEffect)
{
    std::vector<std::shared_ptr<cxmodel::IPlayer>> modelPlayers;
    std::unique_ptr<cxmodel::IBoard> board;
    size_t modelInARowValue = 0u;

    cxmodel::NewGameInformation newGameInformation;

    newGameInformation.m_gridHeight = 6u;
    newGameInformation.m_gridWidth = 7u;
    newGameInformation.m_inARowValue = 4u;
    newGameInformation.m_players.emplace_back(cxmodel::CreatePlayer("John Doe", cxmodel::MakeRed(), cxmodel::PlayerType::HUMAN));
    newGameInformation.m_players.emplace_back(cxmodel::CreatePlayer("Jane Doe", cxmodel::MakeBlue(), cxmodel::PlayerType::HUMAN));

    cxmodel::CommandCreateNewGame cmd{ModelAsLimitsGet(), board, modelPlayers, modelInARowValue, std::move(newGameInformation)};
    cmd.Execute();

    // For now, undoing should have no effect:
    cmd.Undo();

    ASSERT_EQ(modelPlayers.size(), 2u);
    ASSERT_EQ(*modelPlayers[0], *cxmodel::CreatePlayer("John Doe", cxmodel::MakeRed(), cxmodel::PlayerType::HUMAN));
    ASSERT_EQ(*modelPlayers[1], *cxmodel::CreatePlayer("Jane Doe", cxmodel::MakeBlue(), cxmodel::PlayerType::HUMAN));

    ASSERT_TRUE(board);
    ASSERT_EQ(board->GetNbRows(), 6u);
    ASSERT_EQ(board->GetNbColumns(), 7u);
    ASSERT_EQ(modelInARowValue, 4u);
}
