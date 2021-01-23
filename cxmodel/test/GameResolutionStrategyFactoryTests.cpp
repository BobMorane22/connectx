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

#include <gtest/gtest.h>

#include <limits>

#include <Disc.h>
#include <GameResolutionStrategyFactory.h>
#include <WinGameResolutionStrategy.h>
#include <TieGameResolutionStrategy.h>

#include "DisableStdStreamsRAII.h"

namespace
{

class BoardMock final : public cxmodel::IBoard
{

public:

    size_t GetNbRows() const override {return 6u;}
    size_t GetNbColumns() const override {return 7u;}
    size_t GetNbPositions() const override {return 42u;}
    const cxmodel::IChip& GetChip(const Position& /*p_position*/) const override {return m_disc;}
    bool DropChip(size_t /*p_column*/, const cxmodel::IChip& /*p_chip*/, cxmodel::IBoard::Position& /*p_droppedPosition*/) override {return true;}
    void ResetChip(Position& /*p_position*/) override {}
    bool IsColumnFull(size_t /*p_column*/) const override {return false;}

private:

    const cxmodel::Disc m_disc{cxmodel::MakeRed()};

};

} // namespace

TEST(GameResolutionStrategyFactory, Make_WinGameResolution_WinStrategyReturned)
{
    // Setup:
    BoardMock board;
    std::vector<cxmodel::Player> players{
        {"First", cxmodel::MakeRed()},
        {"Second", cxmodel::MakeBlue()}
    };
    std::vector<cxmodel::IBoard::Position> positions;

    // We create the strategy:
    auto strategy = cxmodel::GameResolutionStrategyFactory::Make(board, 4u, players, positions, cxmodel::GameResolution::WIN);
    ASSERT_TRUE(strategy);

    ASSERT_TRUE(dynamic_cast<cxmodel::WinGameResolutionStrategy*>(strategy.get()));
}

TEST(GameResolutionStrategyFactory, Make_TieGameResolution_TieStrategyReturned)
{
    // Setup:
    BoardMock board;
    std::vector<cxmodel::Player> players{
        {"First", cxmodel::MakeRed()},
        {"Second", cxmodel::MakeBlue()}
    };
    std::vector<cxmodel::IBoard::Position> positions;

    // We create the strategy:
    auto strategy = cxmodel::GameResolutionStrategyFactory::Make(board, 4u, players, positions, cxmodel::GameResolution::TIE);
    ASSERT_TRUE(strategy);

    ASSERT_TRUE(dynamic_cast<cxmodel::TieGameResolutionStrategy*>(strategy.get()));
}

TEST(GameResolutionStrategyFactory, Make_InARowTooSmall_AssertsAndNoStrategyReturned)
{
    DisableStdStreamsRAII m_streamDisabler;

    // Setup:
    BoardMock board;
    std::vector<cxmodel::Player> players{
        {"First", cxmodel::MakeRed()},
        {"Second", cxmodel::MakeBlue()}
    };
    std::vector<cxmodel::IBoard::Position> positions;

    // We create the strategy:
    auto strategy = cxmodel::GameResolutionStrategyFactory::Make(board, 0u, players, positions, cxmodel::GameResolution::WIN);
    ASSERT_TRUE(strategy);
    ASSERT_FALSE(dynamic_cast<cxmodel::WinGameResolutionStrategy*>(strategy.get()));
    ASSERT_FALSE(dynamic_cast<cxmodel::TieGameResolutionStrategy*>(strategy.get()));

    const std::string errorStream = m_streamDisabler.GetStdErrContents();
    ASSERT_TRUE(errorStream.find("Precondition") != std::string::npos);
}

TEST(GameResolutionStrategyFactory, Make_InARowTooBig_AssertsAndNoStrategyReturned)
{
    DisableStdStreamsRAII m_streamDisabler;

    // Setup:
    BoardMock board;
    std::vector<cxmodel::Player> players{
        {"First", cxmodel::MakeRed()},
        {"Second", cxmodel::MakeBlue()}
    };
    std::vector<cxmodel::IBoard::Position> positions;

    // We create the strategy:
    auto strategy = cxmodel::GameResolutionStrategyFactory::Make(board, std::numeric_limits<int>::max() + 1u, players, positions, cxmodel::GameResolution::WIN);
    ASSERT_TRUE(strategy);
    ASSERT_FALSE(dynamic_cast<cxmodel::WinGameResolutionStrategy*>(strategy.get()));
    ASSERT_FALSE(dynamic_cast<cxmodel::TieGameResolutionStrategy*>(strategy.get()));

    const std::string errorStream = m_streamDisabler.GetStdErrContents();
    ASSERT_TRUE(errorStream.find("Precondition") != std::string::npos);
}

TEST(GameResolutionStrategyFactory, Make_NotEnoughPlayers_AssertsAndNoStrategyReturned)
{
    DisableStdStreamsRAII m_streamDisabler;

    // Setup:
    BoardMock board;
    std::vector<cxmodel::Player> players{
        {"First", cxmodel::MakeRed()},
    };
    std::vector<cxmodel::IBoard::Position> positions;

    // We create the strategy:
    auto strategy = cxmodel::GameResolutionStrategyFactory::Make(board, 4u, players, positions, cxmodel::GameResolution::WIN);
    ASSERT_TRUE(strategy);
    ASSERT_FALSE(dynamic_cast<cxmodel::WinGameResolutionStrategy*>(strategy.get()));
    ASSERT_FALSE(dynamic_cast<cxmodel::TieGameResolutionStrategy*>(strategy.get()));

    const std::string errorStream = m_streamDisabler.GetStdErrContents();
    ASSERT_TRUE(errorStream.find("Precondition") != std::string::npos);
}
