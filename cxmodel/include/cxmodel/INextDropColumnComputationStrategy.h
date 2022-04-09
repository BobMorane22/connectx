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
 * @file INextDropColumnComputationStrategy.h
 * @date 2022
 *
 *************************************************************************************************/

#ifndef INEXTDROPCOLUMNCOMPUTATIONSTRATEGY_H_7F40031F_E940_4D58_B90F_3D8888274306
#define INEXTDROPCOLUMNCOMPUTATIONSTRATEGY_H_7F40031F_E940_4D58_B90F_3D8888274306

#include <cstddef>
#include <memory>

namespace cxmodel
{
    class IBoard;
}

namespace cxmodel
{

/**********************************************************************************************//**
 * @brief Drop column Computation algorithms.
 *
 *************************************************************************************************/
enum class DropColumnComputation
{
    RANDOM, ///< Computes a random available column.
};

/**********************************************************************************************//**
 * @brief Strategy for computing a next possible drop column.
 *
 *************************************************************************************************/
class INextDropColumnComputationStrategy
{

public:

    /******************************************************************************************//**
     * @brief Destructor.
     *
     *********************************************************************************************/
    virtual ~INextDropColumnComputationStrategy() = default;

    /******************************************************************************************//**
     * @brief Computes a next available drop column.
     *
     * @param p_board The game board.
     *
     * @return The computed column.
     *
     *********************************************************************************************/
    [[nodiscard]] virtual size_t Compute(const cxmodel::IBoard& p_board) const = 0;
};

/**********************************************************************************************//**
 * @brief Creates a new drop column computation strategy.
 *
 * @param p_algorithm The computation algorithm used.
 *
 * @return The associated strategy.
 *
 *************************************************************************************************/
[[nodiscard]] std::unique_ptr<INextDropColumnComputationStrategy> NextDropColumnComputationStrategyCreate(DropColumnComputation p_algorithm);

} // namespace cxmodel

#endif // INEXTDROPCOLUMNCOMPUTATIONSTRATEGY_H_7F40031F_E940_4D58_B90F_3D8888274306
