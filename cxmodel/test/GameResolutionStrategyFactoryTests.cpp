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
 * @file GameResolutionStrategyFactoryTests.cpp
 * @date 2020
 *
 *************************************************************************************************/

#include <limits>

#include <gtest/gtest.h>

#include <cxunit/DisableStdStreamsRAII.h>
#include <cxmodel/Disc.h>
#include <cxmodel/GameResolutionStrategyFactory.h>
#include <cxmodel/WinGameResolutionStrategy.h>
#include <cxmodel/TieGameResolutionStrategy.h>

namespace
{

class BoardMock final : public cx::model::IBoard
{

public:

    size_t GetNbRows() const override {return 6u;}
    size_t GetNbColumns() const override {return 7u;}
    size_t GetNbPositions() const override {return 42u;}
    const cx::model::IChip& GetChip(const Position& /*p_position*/) const override {return m_disc;}
    bool DropChip(size_t /*p_column*/, const cx::model::IChip& /*p_chip*/, cx::model::IBoard::Position& /*p_droppedPosition*/) override {return true;}
    void ResetChip(Position& /*p_position*/) override {}
    bool IsColumnFull(size_t /*p_column*/) const override {return false;}

private:

    const cx::model::Disc m_disc{cx::model::MakeRed()};

};

} // namespace

TEST(GameResolutionStrategyFactory, Make_WinGameResolution_WinStrategyReturned)
{
    // Setup:
    BoardMock board;
    std::vector<std::shared_ptr<cx::model::IPlayer>> players{
        cx::model::CreatePlayer("First", cx::model::MakeRed(), cx::model::PlayerType::HUMAN),
        cx::model::CreatePlayer("Second", cx::model::MakeBlue(), cx::model::PlayerType::HUMAN)
    };
    std::vector<cx::model::IBoard::Position> positions;

    // We create the strategy:
    auto strategy = cx::model::GameResolutionStrategyFactory::Make(board, 4u, players, positions, cx::model::GameResolution::WIN);
    ASSERT_TRUE(strategy);

    ASSERT_TRUE(dynamic_cast<cx::model::WinGameResolutionStrategy*>(strategy.get()));
}

TEST(GameResolutionStrategyFactory, Make_TieGameResolution_TieStrategyReturned)
{
    // Setup:
    BoardMock board;
    std::vector<std::shared_ptr<cx::model::IPlayer>> players{
        cx::model::CreatePlayer("First", cx::model::MakeRed(), cx::model::PlayerType::HUMAN),
        cx::model::CreatePlayer("Second", cx::model::MakeBlue(), cx::model::PlayerType::HUMAN)
    };
    std::vector<cx::model::IBoard::Position> positions;

    // We create the strategy:
    auto strategy = cx::model::GameResolutionStrategyFactory::Make(board, 4u, players, positions, cx::model::GameResolution::TIE);
    ASSERT_TRUE(strategy);

    ASSERT_TRUE(dynamic_cast<cx::model::TieGameResolutionStrategy*>(strategy.get()));
}

TEST(GameResolutionStrategyFactory, Make_InARowTooSmall_AssertsAndNoStrategyReturned)
{
    cx::unit::DisableStdStreamsRAII streamDisabler;

    // Setup:
    BoardMock board;
    std::vector<std::shared_ptr<cx::model::IPlayer>> players{
        cx::model::CreatePlayer("First", cx::model::MakeRed(), cx::model::PlayerType::HUMAN),
        cx::model::CreatePlayer("Second", cx::model::MakeBlue(), cx::model::PlayerType::HUMAN)
    };
    std::vector<cx::model::IBoard::Position> positions;

    // We create the strategy:
    auto strategy = cx::model::GameResolutionStrategyFactory::Make(board, 0u, players, positions, cx::model::GameResolution::WIN);
    ASSERT_TRUE(strategy);
    ASSERT_FALSE(dynamic_cast<cx::model::WinGameResolutionStrategy*>(strategy.get()));
    ASSERT_FALSE(dynamic_cast<cx::model::TieGameResolutionStrategy*>(strategy.get()));
    ASSERT_PRECONDITION_FAILED(streamDisabler);
}

TEST(GameResolutionStrategyFactory, Make_InARowTooBig_AssertsAndNoStrategyReturned)
{
    cx::unit::DisableStdStreamsRAII streamDisabler;

    // Setup:
    BoardMock board;
    std::vector<std::shared_ptr<cx::model::IPlayer>> players{
        cx::model::CreatePlayer("First", cx::model::MakeRed(), cx::model::PlayerType::HUMAN),
        cx::model::CreatePlayer("Second", cx::model::MakeBlue(), cx::model::PlayerType::HUMAN)
    };
    std::vector<cx::model::IBoard::Position> positions;

    // We create the strategy:
    auto strategy = cx::model::GameResolutionStrategyFactory::Make(board, std::numeric_limits<size_t>::max() + 1u, players, positions, cx::model::GameResolution::WIN);
    ASSERT_TRUE(strategy);
    ASSERT_FALSE(dynamic_cast<cx::model::WinGameResolutionStrategy*>(strategy.get()));
    ASSERT_FALSE(dynamic_cast<cx::model::TieGameResolutionStrategy*>(strategy.get()));
    ASSERT_PRECONDITION_FAILED(streamDisabler);
}

TEST(GameResolutionStrategyFactory, Make_NotEnoughPlayers_AssertsAndNoStrategyReturned)
{
    cx::unit::DisableStdStreamsRAII streamDisabler;

    // Setup:
    BoardMock board;
    std::vector<std::shared_ptr<cx::model::IPlayer>> players{
        cx::model::CreatePlayer("First", cx::model::MakeRed(), cx::model::PlayerType::HUMAN),
    };
    std::vector<cx::model::IBoard::Position> positions;

    // We create the strategy:
    auto strategy = cx::model::GameResolutionStrategyFactory::Make(board, 4u, players, positions, cx::model::GameResolution::WIN);
    ASSERT_TRUE(strategy);
    ASSERT_FALSE(dynamic_cast<cx::model::WinGameResolutionStrategy*>(strategy.get()));
    ASSERT_FALSE(dynamic_cast<cx::model::TieGameResolutionStrategy*>(strategy.get()));
    ASSERT_PRECONDITION_FAILED(streamDisabler);
}
