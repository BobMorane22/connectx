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
 * @file IConnectXLimits.h
 * @date 2020
 *
 *************************************************************************************************/

#ifndef ICONNECTXLIMITS_H_9A371FB1_B191_4967_A1E0_171616A30DDA
#define ICONNECTXLIMITS_H_9A371FB1_B191_4967_A1E0_171616A30DDA

namespace cxmodel
{

/*********************************************************************************************//**
 * @brief Interface to query any Connect X game limit parameter.
 *
 ************************************************************************************************/
class IConnectXLimits
{

public:

    /******************************************************************************************//**
     * @brief Destructor.
     *
     ********************************************************************************************/
    virtual ~IConnectXLimits() = default;

    /******************************************************************************************//**
     * @brief Gets the minimum Connect X grid height.
     *
     * @return The minimum Connect X grid height.
     *
     ********************************************************************************************/
    virtual size_t GetMinimumGridHeight() const = 0;

    /******************************************************************************************//**
     * @brief Gets the minimum Connect X grid width.
     *
     * @return The minimum Connect X grid width.
     *
     ********************************************************************************************/
    virtual size_t GetMinimumGridWidth() const = 0;

    /******************************************************************************************//**
     * @brief Gets the minimum Connect X in-a-row value.
     *
     * @return The minimum Connect X grid width.
     *
     ********************************************************************************************/
    virtual size_t GetMinimumInARowValue() const = 0;

    /******************************************************************************************//**
     * @brief Gets the maximum Connect X grid height.
     *
     * @return The maximum Connect X grid height.
     *
     ********************************************************************************************/
    virtual size_t GetMaximumGridHeight() const = 0;

    /******************************************************************************************//**
     * @brief Gets the maximum Connect X grid width.
     *
     * @return The maximum Connect X grid width.
     *
     ********************************************************************************************/
    virtual size_t GetMaximumGridWidth() const = 0;

    /******************************************************************************************//**
     * @brief Gets the maximum Connect X in-a-row value.
     *
     * @return The maximum Connect X grid width.
     *
     ********************************************************************************************/
    virtual size_t GetMaximumInARowValue() const = 0;

    /******************************************************************************************//**
     * @brief Gets the minimum Connect X number of players.
     *
     * @return The minimum Connect X number of players.
     *
     ********************************************************************************************/
    virtual size_t GetMinimumNumberOfPlayers() const = 0;

    /******************************************************************************************//**
     * @brief Gets the maximum Connect X number of players.
     *
     * @return The maximum Connect X number of players.
     *
     ********************************************************************************************/
    virtual size_t GetMaximumNumberOfPlayers() const = 0;

};

} // namespace cxmodel

#endif // ICONNECTXLIMITS_H_9A371FB1_B191_4967_A1E0_171616A30DDA
