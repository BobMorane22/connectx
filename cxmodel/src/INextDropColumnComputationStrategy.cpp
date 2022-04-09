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
 * @file INextDropColumnComputationStrategy.cpp
 * @date 2022
 *
 *************************************************************************************************/

#include <algorithm>
#include <random>

#include <cxinv/assertion.h>
#include <cxmodel/IBoard.h>
#include <cxmodel/INextDropColumnComputationStrategy.h>

/**************************************************************************************************
 * @brief No next drop column computation strategy.
 *
 *************************************************************************************************/
class NoNextDropColumnComputationStrategy : public cxmodel::INextDropColumnComputationStrategy
{

public:

    /**********************************************************************************************
     * @brief Computes a next available drop column.
     *
     * @return The computed column.
     *
     *********************************************************************************************/
    [[nodiscard]] size_t Compute(const cxmodel::IBoard& /*p_board*/) const override
    {
        return 0u;
    }
};

/**************************************************************************************************
 * @brief Random next drop column strategy.
 *
 * A random column is chosen amongst the available columns in the board.
 *
 *************************************************************************************************/
class RandomNextDropColumnComputationStrategy : public cxmodel::INextDropColumnComputationStrategy
{

public:

    /**********************************************************************************************
     * @brief Constructor.
     *
     *********************************************************************************************/
    RandomNextDropColumnComputationStrategy() = default;

    /**********************************************************************************************
     * @brief Computes a next available drop column.
     *
     * @param p_board The game board.
     *
     * @return The computed column.
     *
     *********************************************************************************************/
    [[nodiscard]] size_t Compute(const cxmodel::IBoard& p_board) const override;
};

size_t RandomNextDropColumnComputationStrategy::Compute(const cxmodel::IBoard& p_board) const
{
    // List all the available column indexes:
    std::vector<size_t> allColumnIndexes;
    for(size_t column = 0u; column < p_board.GetNbColumns(); ++column)
    {
        allColumnIndexes.push_back(column);
    }

    // Filter to get only the remaining columns:
    std::vector<size_t> availableColumnIndexes;
    std::copy_if(allColumnIndexes.cbegin(),
                 allColumnIndexes.cend(),
                 std::back_inserter(availableColumnIndexes),
                 [&p_board](size_t p_index)
                 {
                     return !p_board.IsColumnFull(p_index);
                 });

    IF_CONDITION_NOT_MET_DO(availableColumnIndexes.size() > 0u, return 0u;);

    // From this set of available column indexes, pick one at random:
    std::random_device randomDevice;
    std::mt19937 randomNumberGenerator(randomDevice());
    std::uniform_int_distribution<size_t> distribution(0u, availableColumnIndexes.size() - 1u);

    const size_t columnIndex = distribution(randomNumberGenerator);
    IF_CONDITION_NOT_MET_DO(columnIndex < availableColumnIndexes.size(), return 0u;);

    return availableColumnIndexes[columnIndex];
}

std::unique_ptr<cxmodel::INextDropColumnComputationStrategy> cxmodel::NextDropColumnComputationStrategyCreate(DropColumnComputation p_algorithm)
{
    switch(p_algorithm)
    {
        case DropColumnComputation::RANDOM:
            return std::make_unique<RandomNextDropColumnComputationStrategy>();

        default:
            break;
    }

    ASSERT_ERROR_MSG("Unknown next drop column computation algorithm");
    return std::make_unique<NoNextDropColumnComputationStrategy>();
}
