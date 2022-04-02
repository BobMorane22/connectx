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
 * @file IConnectXAI.h
 * @date 2022
 *
 *************************************************************************************************/

#ifndef ICONNECTXAI_H_362BB63A_6179_4ADE_BE2B_42ACD69F9888
#define ICONNECTXAI_H_362BB63A_6179_4ADE_BE2B_42ACD69F9888

namespace cxmodel
{

/**********************************************************************************************//**
 * @brief Drop column Computation algorithms.
 *
 *************************************************************************************************/
enum class DropColumnComputation
{
    BEST_POSSIBLE, ///< Computes the best possible column the the active player.
    RANDOM,        ///< Computes a random available column.
};

/**********************************************************************************************//**
 * @brief Interface to implement Connect X AI specific computations.
 *
 *************************************************************************************************/
class IConnectXAI
{

public:

    /******************************************************************************************//**
     * @brief Destructor.
     *
     *********************************************************************************************/
    virtual ~IConnectXAI() = default;

    /******************************************************************************************//**
     * @brief Automatically computes the next best drop colum.
     *
     * This computation is usually used to get a drop location for managed players.
     *
     * @param p_algorithm The algorithm to use for computation.
     *
     * @return An available drop column.
     *
     *********************************************************************************************/
    [[nodiscard]] virtual size_t ComputeNextDropColumn(DropColumnComputation p_algorithm) const = 0;

};

} // namespace cxmodel

#endif // ICONNECTXAI_H_362BB63A_6179_4ADE_BE2B_42ACD69F9888
