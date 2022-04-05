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

#include <cxinv/assertion.h>
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
    [[nodiscard]] size_t Compute() const override
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
     * @return The computed column.
     *
     *********************************************************************************************/
    [[nodiscard]] size_t Compute() const override;
};

size_t RandomNextDropColumnComputationStrategy::Compute() const
{
    return 0u;
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
