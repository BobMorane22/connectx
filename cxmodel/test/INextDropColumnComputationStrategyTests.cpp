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
 * @file INextDropColumnComputationStrategyTests.cpp
 * @date 2022
 *
 *************************************************************************************************/

#include <gtest/gtest.h>

#include <cxunit/DisableStdStreamsRAII.h>
#include <cxmodel/Board.h>
#include <cxmodel/Disc.h>
#include <cxmodel/INextDropColumnComputationStrategy.h>

#include "ConnectXLimitsModelMock.h"

namespace
{

void FillColumn(size_t p_column, cxmodel::IBoard& p_board, const cxmodel::IChip& p_chip)
{
    for(size_t row = 0u; row < p_board.GetNbRows(); ++row)
    {
        cxmodel::IBoard::Position unused;
        p_board.DropChip(p_column, p_chip, unused);

    }

    ASSERT_TRUE(p_board.IsColumnFull(p_column));
}

void FillBoard(cxmodel::IBoard& p_board, const cxmodel::IChip& p_chip)
{
    for(size_t column = 0u; column < p_board.GetNbColumns(); ++column)
    {
        FillColumn(column, p_board, p_chip);
    }
}

size_t ComputeColumn()
{
    const auto strategy = cxmodel::NextDropColumnComputationStrategyCreate(cxmodel::DropColumnComputation::RANDOM);

    const ConnectXLimitsModelMock modelMock;
    const cxmodel::Board board{6u, 7u, modelMock};

    return strategy->Compute(board);
}

bool DoesIndexAppearEnough(size_t p_indexUnderTest,
                           const std::vector<size_t>& p_allIndexes,
                           const size_t p_nbOfRepetitions,
                           const size_t p_tolerance)
{
    const size_t nbOfIndexAppearance = std::count_if(p_allIndexes.cbegin(),
                                                     p_allIndexes.cend(),
                                                     [p_indexUnderTest](size_t p_columnIndex)
                                                     {
                                                        return p_columnIndex == p_indexUnderTest;
                                                     });

    return nbOfIndexAppearance >= p_nbOfRepetitions - p_tolerance ||
           nbOfIndexAppearance <= p_nbOfRepetitions + p_tolerance;
}

} // namespace

TEST(INextDropColumnComputationStrategy, /*DISABLED_*/NextDropColumnComputationStrategyCreate_Random_ReturnsValidStrategy)
{
    const auto strategy = cxmodel::NextDropColumnComputationStrategyCreate(cxmodel::DropColumnComputation::RANDOM);
    ASSERT_TRUE(strategy);
}

TEST(INextDropColumnComputationStrategy, /*DISABLED_*/NextDropColumnComputationStrategyCreate_Invalid_AssertsAndReturnsValidStrategy)
{
    // Create an invalid algorithm:
    cxmodel::DropColumnComputation invalid = static_cast<cxmodel::DropColumnComputation>(-1);

    cxunit::DisableStdStreamsRAII streamDisabler;

    const auto strategy = cxmodel::NextDropColumnComputationStrategyCreate(invalid);

    ASSERT_ASSERTION_FAILED(streamDisabler);
    ASSERT_TRUE(strategy);
}

// ************************************************************************************************
//                                             RANDOM
// ************************************************************************************************
TEST(INextDropColumnComputationStrategy, /*DISABLED_*/Compute_RandomAndAvailableColumn_ReturnsResultInBoardRange)
{
    const auto strategy = cxmodel::NextDropColumnComputationStrategyCreate(cxmodel::DropColumnComputation::RANDOM);

    ConnectXLimitsModelMock modelMock;
    cxmodel::Board board{6u, 7u, modelMock};

    const size_t result = strategy->Compute(board);

    ASSERT_TRUE(result < 7u);
}

TEST(INextDropColumnComputationStrategy, /*DISABLED_*/Compute_RandomAndOneAvailableColumn_ReturnsAvailableColumn)
{
    const auto strategy = cxmodel::NextDropColumnComputationStrategyCreate(cxmodel::DropColumnComputation::RANDOM);

    ConnectXLimitsModelMock modelMock;
    cxmodel::Board board{6u, 7u, modelMock};

    cxmodel::Disc chip{cxmodel::MakeRed()};
    cxmodel::IBoard::Position unused;
    FillColumn(0u, board, chip);
    FillColumn(2u, board, chip);
    FillColumn(3u, board, chip);
    FillColumn(4u, board, chip);
    FillColumn(5u, board, chip);
    FillColumn(6u, board, chip);

    const size_t result = strategy->Compute(board);

    ASSERT_TRUE(result == 1u);
}

TEST(INextDropColumnComputationStrategy, /*DISABLED_*/Compute_RandomAndNoAvailableColumn_AssertsAndReturnsZero)
{
    const auto strategy = cxmodel::NextDropColumnComputationStrategyCreate(cxmodel::DropColumnComputation::RANDOM);

    ConnectXLimitsModelMock modelMock;
    cxmodel::Board board{6u, 7u, modelMock};

    cxmodel::Disc chip{cxmodel::MakeRed()};
    cxmodel::IBoard::Position unused;
    FillBoard(board, chip);

    cxunit::DisableStdStreamsRAII streamDisabler;
    const size_t result = strategy->Compute(board);
    ASSERT_ASSERTION_FAILED(streamDisabler);

    ASSERT_TRUE(result == 0u);
}

// In this test, we want to make sure the user experience truly feels random by running the
// test multiple times and measuring the frequence of each occurence. In an ideal world,
// all columns would have equal frequences of occurence.
TEST(INextDropColumnComputationStrategy, /*DISABLED_*/Compute_Random_ReturnsWellDistributedResult)
{
    // We use a board with 7 columns. We will then run the computation 7*100 (700) times
    // and then divide into columns indexes. Because of the uniform distribution used to
    // randomize, we are expecting each columns to be be "randomly" computed about 100
    // times. We will use a tolerance of 1%:
    constexpr size_t COLUMN_NB_REPETITIONS = 100u;
    constexpr size_t TOTAL_NB_REPETITIONS = 7u * COLUMN_NB_REPETITIONS;
    constexpr size_t TOLERANCE_ON_RANDOM = COLUMN_NB_REPETITIONS / 100u;

    std::vector<size_t> allColumnIndexes;
    allColumnIndexes.resize(TOTAL_NB_REPETITIONS);
    for(size_t repetition = 0u; repetition < TOTAL_NB_REPETITIONS; ++repetition)
    {
        allColumnIndexes[repetition] = ComputeColumn();
    }

    // At this point, all our computations are completed. We count, for each column,
    // the number of times it has come up:
    ASSERT_TRUE(DoesIndexAppearEnough(0u, allColumnIndexes, COLUMN_NB_REPETITIONS, TOLERANCE_ON_RANDOM));
    ASSERT_TRUE(DoesIndexAppearEnough(1u, allColumnIndexes, COLUMN_NB_REPETITIONS, TOLERANCE_ON_RANDOM));
    ASSERT_TRUE(DoesIndexAppearEnough(2u, allColumnIndexes, COLUMN_NB_REPETITIONS, TOLERANCE_ON_RANDOM));
    ASSERT_TRUE(DoesIndexAppearEnough(3u, allColumnIndexes, COLUMN_NB_REPETITIONS, TOLERANCE_ON_RANDOM));
    ASSERT_TRUE(DoesIndexAppearEnough(4u, allColumnIndexes, COLUMN_NB_REPETITIONS, TOLERANCE_ON_RANDOM));
    ASSERT_TRUE(DoesIndexAppearEnough(5u, allColumnIndexes, COLUMN_NB_REPETITIONS, TOLERANCE_ON_RANDOM));
    ASSERT_TRUE(DoesIndexAppearEnough(6u, allColumnIndexes, COLUMN_NB_REPETITIONS, TOLERANCE_ON_RANDOM));
                
}
