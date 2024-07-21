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
 * @file BoardTests.cpp
 * @date 2020
 *
 *************************************************************************************************/

#include <gtest/gtest.h>

#include <cxunit/StdStreamRedirector.h>

#include <cxmodel/Board.h>
#include <cxmodel/Disc.h>

#include "ConnectXLimitsModelMock.h"

class BoardTestFixture: public::testing::Test
{

public:

    size_t GetMinimumGridHeight() const {return m_model.GetMinimumGridHeight();};
    size_t GetMinimumGridWidth() const {return m_model.GetMinimumGridWidth();};
    size_t GetMinimumInARowValue() const {return m_model.GetMinimumInARowValue();};
    size_t GetMaximumGridHeight() const {return m_model.GetMaximumGridHeight();};
    size_t GetMaximumGridWidth() const {return m_model.GetMaximumGridWidth();};
    size_t GetMaximumInARowValue() const {return m_model.GetMaximumInARowValue();};
    size_t GetMinimumNumberOfPlayers() const {return m_model.GetMinimumNumberOfPlayers();};
    size_t GetMaximumNumberOfPlayers() const {return m_model.GetMaximumNumberOfPlayers();};

    std::unique_ptr<cx::model::IBoard> GetClassicBoard() const
    {
        std::unique_ptr<cx::model::IBoard> board = std::make_unique<cx::model::Board>(6u, 7u, m_model);
        EXPECT_TRUE(board);

        return board;
    }

private:

    ConnectXLimitsModelMock m_model;
};

ADD_STREAM_REDIRECTORS(BoardTestFixture);

TEST_F(BoardTestFixture, /*DISABLED_*/GetNbRows_ValidGameBoard_ReturnsNbRows)
{
    const auto board = GetClassicBoard();

    ASSERT_EQ(GetMinimumGridHeight(), board->GetNbRows());
}

TEST_F(BoardTestFixture, /*DISABLED_*/GetNbColumns_ValidGameBoard_ReturnsNbColumns)
{
    const auto board = GetClassicBoard();

    ASSERT_EQ(GetMinimumGridWidth(), board->GetNbColumns());
}

TEST_F(BoardTestFixture, /*DISABLED_*/GetNbPositions_ValidGameBoard_ReturnsNbPositions)
{
    const auto board = GetClassicBoard();

    ASSERT_EQ(GetMinimumGridHeight() * GetMinimumGridWidth(), board->GetNbPositions());
}

TEST_F(BoardTestFixture, /*DISABLED_*/DropChip_ValidDiscAsParameter_DiscInsertedInGameboard)
{
    const auto board = GetClassicBoard();
    const cx::model::Disc NO_CHIP{cx::model::MakeTransparent()};

    ASSERT_EQ(board->GetChip({0u, 0u}), NO_CHIP);

    cx::model::IBoard::Position dummy;
    const cx::model::Disc RED_CHIP{cx::model::MakeRed()};
    ASSERT_TRUE(board->DropChip(0u, RED_CHIP, dummy));

    ASSERT_EQ(board->GetChip({0u, 0u}), RED_CHIP);
}

TEST_F(BoardTestFixture, /*DISABLED_*/DropChip_ValidDiscAsParameter_DiscInsertedInGameboardOverPrevious)
{
    const auto board = GetClassicBoard();

    const cx::model::Disc NO_CHIP{cx::model::MakeTransparent()};
    const cx::model::Disc RED_CHIP{cx::model::MakeRed()};
    const cx::model::Disc BLUE_CHIP{cx::model::MakeBlue()};

    ASSERT_EQ(board->GetChip({0, 0}), NO_CHIP);
    ASSERT_EQ(board->GetChip({1, 0}), NO_CHIP);

    cx::model::IBoard::Position dummy;
    ASSERT_TRUE(board->DropChip(0, RED_CHIP, dummy));
    ASSERT_TRUE(board->DropChip(0, BLUE_CHIP, dummy));

    ASSERT_EQ(board->GetChip({0, 0}), RED_CHIP);
    ASSERT_EQ(board->GetChip({1, 0}), BLUE_CHIP);
}

TEST_F(BoardTestFixture, /*DISABLED_*/DropChip_ValidDiscAsParameter_DiscInsertedInGameboardOverPrevious3)
{
    const auto board = GetClassicBoard();

    const cx::model::Disc NO_CHIP{cx::model::MakeTransparent()};
    const cx::model::Disc RED_CHIP{cx::model::MakeRed()};
    const cx::model::Disc BLUE_CHIP{cx::model::MakeBlue()};

    ASSERT_EQ(board->GetChip({0, 0}), NO_CHIP);
    ASSERT_EQ(board->GetChip({1, 0}), NO_CHIP);
    ASSERT_EQ(board->GetChip({2, 0}), NO_CHIP);

    cx::model::IBoard::Position dummy;
    ASSERT_TRUE(board->DropChip(0, RED_CHIP, dummy));
    ASSERT_TRUE(board->DropChip(0, BLUE_CHIP, dummy));
    ASSERT_TRUE(board->DropChip(0, RED_CHIP, dummy));

    ASSERT_EQ(board->GetChip({0, 0}), RED_CHIP);
    ASSERT_EQ(board->GetChip({1, 0}), BLUE_CHIP);
    ASSERT_EQ(board->GetChip({2, 0}), RED_CHIP);
}

TEST_F(BoardTestFixture, /*DISABLED_*/DropChip_ValidDiscAsParameter_DiscInsertedInGameboardOverPrevious4)
{
    const auto board = GetClassicBoard();

    const cx::model::Disc NO_CHIP{cx::model::MakeTransparent()};
    const cx::model::Disc RED_CHIP{cx::model::MakeRed()};
    const cx::model::Disc BLUE_CHIP{cx::model::MakeBlue()};

    ASSERT_EQ(board->GetChip({0, 0}), NO_CHIP);
    ASSERT_EQ(board->GetChip({1, 0}), NO_CHIP);
    ASSERT_EQ(board->GetChip({2, 0}), NO_CHIP);
    ASSERT_EQ(board->GetChip({3, 0}), NO_CHIP);

    cx::model::IBoard::Position dummy;
    ASSERT_TRUE(board->DropChip(0, RED_CHIP, dummy));
    ASSERT_TRUE(board->DropChip(0, BLUE_CHIP, dummy));
    ASSERT_TRUE(board->DropChip(0, RED_CHIP, dummy));
    ASSERT_TRUE(board->DropChip(0, BLUE_CHIP, dummy));

    ASSERT_EQ(board->GetChip({0, 0}), RED_CHIP);
    ASSERT_EQ(board->GetChip({1, 0}), BLUE_CHIP);
    ASSERT_EQ(board->GetChip({2, 0}), RED_CHIP);
    ASSERT_EQ(board->GetChip({3, 0}), BLUE_CHIP);
}

TEST_F(BoardTestFixture, /*DISABLED_*/DropChip_ValidDiscAsParameter_DiscInsertedInGameboardOverPrevious5)
{
    const auto board = GetClassicBoard();

    const cx::model::Disc NO_CHIP{cx::model::MakeTransparent()};
    const cx::model::Disc RED_CHIP{cx::model::MakeRed()};
    const cx::model::Disc BLUE_CHIP{cx::model::MakeBlue()};

    ASSERT_EQ(board->GetChip({0, 0}), NO_CHIP);
    ASSERT_EQ(board->GetChip({1, 0}), NO_CHIP);
    ASSERT_EQ(board->GetChip({2, 0}), NO_CHIP);
    ASSERT_EQ(board->GetChip({3, 0}), NO_CHIP);
    ASSERT_EQ(board->GetChip({4, 0}), NO_CHIP);

    cx::model::IBoard::Position dummy;
    ASSERT_TRUE(board->DropChip(0, RED_CHIP, dummy));
    ASSERT_TRUE(board->DropChip(0, BLUE_CHIP, dummy));
    ASSERT_TRUE(board->DropChip(0, RED_CHIP, dummy));
    ASSERT_TRUE(board->DropChip(0, BLUE_CHIP, dummy));
    ASSERT_TRUE(board->DropChip(0, RED_CHIP, dummy));

    ASSERT_EQ(board->GetChip({0, 0}), RED_CHIP);
    ASSERT_EQ(board->GetChip({1, 0}), BLUE_CHIP);
    ASSERT_EQ(board->GetChip({2, 0}), RED_CHIP);
    ASSERT_EQ(board->GetChip({3, 0}), BLUE_CHIP);
    ASSERT_EQ(board->GetChip({4, 0}), RED_CHIP);
}

TEST_F(BoardTestFixture, /*DISABLED_*/DropChip_ValidDiscAsParameter_DiscInsertedInGameboardOverPrevious6)
{
    const auto board = GetClassicBoard();

    const cx::model::Disc NO_CHIP{cx::model::MakeTransparent()};
    const cx::model::Disc RED_CHIP{cx::model::MakeRed()};
    const cx::model::Disc BLUE_CHIP{cx::model::MakeBlue()};

    ASSERT_EQ(board->GetChip({0, 0}), NO_CHIP);
    ASSERT_EQ(board->GetChip({1, 0}), NO_CHIP);
    ASSERT_EQ(board->GetChip({2, 0}), NO_CHIP);
    ASSERT_EQ(board->GetChip({3, 0}), NO_CHIP);
    ASSERT_EQ(board->GetChip({4, 0}), NO_CHIP);
    ASSERT_EQ(board->GetChip({5, 0}), NO_CHIP);

    cx::model::IBoard::Position dummy;
    ASSERT_TRUE(board->DropChip(0, RED_CHIP, dummy));
    ASSERT_TRUE(board->DropChip(0, BLUE_CHIP, dummy));
    ASSERT_TRUE(board->DropChip(0, RED_CHIP, dummy));
    ASSERT_TRUE(board->DropChip(0, BLUE_CHIP, dummy));
    ASSERT_TRUE(board->DropChip(0, RED_CHIP, dummy));
    ASSERT_TRUE(board->DropChip(0, BLUE_CHIP, dummy));

    ASSERT_EQ(board->GetChip({0, 0}), RED_CHIP);
    ASSERT_EQ(board->GetChip({1, 0}), BLUE_CHIP);
    ASSERT_EQ(board->GetChip({2, 0}), RED_CHIP);
    ASSERT_EQ(board->GetChip({3, 0}), BLUE_CHIP);
    ASSERT_EQ(board->GetChip({4, 0}), RED_CHIP);
    ASSERT_EQ(board->GetChip({5, 0}), BLUE_CHIP);
}

TEST_F(BoardTestFixture, /*DISABLED_*/DropChip_ValidDiscAsParameter_DiscInsertedInGameboardOverPrevious7)
{
    const auto board = GetClassicBoard();

    const cx::model::Disc NO_CHIP{cx::model::MakeTransparent()};
    const cx::model::Disc RED_CHIP{cx::model::MakeRed()};
    const cx::model::Disc BLUE_CHIP{cx::model::MakeBlue()};

    ASSERT_EQ(board->GetChip({0, 0}), NO_CHIP);
    ASSERT_EQ(board->GetChip({1, 0}), NO_CHIP);
    ASSERT_EQ(board->GetChip({2, 0}), NO_CHIP);
    ASSERT_EQ(board->GetChip({3, 0}), NO_CHIP);
    ASSERT_EQ(board->GetChip({4, 0}), NO_CHIP);
    ASSERT_EQ(board->GetChip({5, 0}), NO_CHIP);

    cx::model::IBoard::Position dummy;
    ASSERT_TRUE(board->DropChip(0, RED_CHIP, dummy));
    ASSERT_TRUE(board->DropChip(0, BLUE_CHIP, dummy));
    ASSERT_TRUE(board->DropChip(0, RED_CHIP, dummy));
    ASSERT_TRUE(board->DropChip(0, BLUE_CHIP, dummy));
    ASSERT_TRUE(board->DropChip(0, RED_CHIP, dummy));
    ASSERT_TRUE(board->DropChip(0, BLUE_CHIP, dummy));

    // Add an extra disc:
    ASSERT_FALSE(board->DropChip(0, RED_CHIP, dummy));

    ASSERT_EQ(board->GetChip({0, 0}), RED_CHIP);
    ASSERT_EQ(board->GetChip({1, 0}), BLUE_CHIP);
    ASSERT_EQ(board->GetChip({2, 0}), RED_CHIP);
    ASSERT_EQ(board->GetChip({3, 0}), BLUE_CHIP);
    ASSERT_EQ(board->GetChip({4, 0}), RED_CHIP);
    ASSERT_EQ(board->GetChip({5, 0}), BLUE_CHIP);
}

TEST_F(BoardTestFixture, /*DISABLED_*/DropChip_ValidDiscAsParameter_ReturnedPositionIsGood)
{
    const auto board = GetClassicBoard();

    const cx::model::Disc NO_CHIP{cx::model::MakeTransparent()};
    const cx::model::Disc RED_CHIP{cx::model::MakeRed()};
    const cx::model::Disc BLUE_CHIP{cx::model::MakeBlue()};

    ASSERT_EQ(board->GetChip({0, 0}), NO_CHIP);
    ASSERT_EQ(board->GetChip({1, 0}), NO_CHIP);
    ASSERT_EQ(board->GetChip({2, 0}), NO_CHIP);
    ASSERT_EQ(board->GetChip({3, 0}), NO_CHIP);

    cx::model::IBoard::Position dummy;
    ASSERT_TRUE(board->DropChip(4, RED_CHIP, dummy));
    ASSERT_TRUE(board->DropChip(4, BLUE_CHIP, dummy));
    ASSERT_TRUE(board->DropChip(4, RED_CHIP, dummy));

    cx::model::IBoard::Position position;
    ASSERT_TRUE(board->DropChip(4, BLUE_CHIP, position));

    constexpr cx::model::IBoard::Position expected{3, 4};
    ASSERT_EQ(expected.m_row, position.m_row);
    ASSERT_EQ(expected.m_column, position.m_column);
}

TEST_F(BoardTestFixture, /*DISABLED_*/GetChip_ExistingPositionAsParameter_ReturnsPosition)
{
    const auto board = GetClassicBoard();

    const cx::model::Disc NO_CHIP{cx::model::MakeTransparent()};
    const cx::model::Disc BLUE_CHIP{cx::model::MakeBlue()};

    const cx::model::IBoard::Position position{0, 2};

    cx::model::IBoard::Position dummy;
    board->DropChip(2, BLUE_CHIP, dummy);

    ASSERT_EQ(BLUE_CHIP, board->GetChip(position));
}

TEST_F(BoardTestFixtureStdErrStreamRedirector, /*DISABLED_*/GetChip_InputPositionOutOfLimits_ReturnsFirstDiscAndAsserts)
{
    const auto board = GetClassicBoard();

    const cx::model::Disc RED_CHIP{cx::model::MakeRed()};

    cx::model::IBoard::Position dummy;
    ASSERT_TRUE(board->DropChip(0, RED_CHIP, dummy));
    ASSERT_EQ(board->GetChip({0, 0}), RED_CHIP);

    // Wrong height position:
    ASSERT_EQ(board->GetChip({board->GetNbRows(), 0}), RED_CHIP);
    ASSERT_PRECONDITION_FAILED(*this);

    // Wrong column position:
    ASSERT_EQ(board->GetChip({0, board->GetNbColumns()}), RED_CHIP);
    ASSERT_PRECONDITION_FAILED(*this);
}
