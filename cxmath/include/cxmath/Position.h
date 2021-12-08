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
 * @file Position.h
 * @date 2021
 *
 *************************************************************************************************/

#ifndef POSITION_H_0AF4F7DC_2C60_4E04_9AEF_7CDA286A9B0E
#define POSITION_H_0AF4F7DC_2C60_4E04_9AEF_7CDA286A9B0E

namespace cxmath
{

/**********************************************************************************************//**
 * @brief Represents a 2D position in cartesian coordinates.
 *
 *************************************************************************************************/
struct Position
{
    constexpr Position()
    : m_x{0.0}
    , m_y{0.0}
    {
    }

    constexpr Position(double p_x, double p_y)
    : m_x{p_x}
    , m_y{p_y}
    {
    }

    double m_x;
    double m_y;
};

/**********************************************************************************************//**
 * @brief Equal-to operator.
 *
 * @param p_lhs
 *      The left-hand value to use for the comparison.
 * @param p_rhs
 *      The right-hand value to use for the comparison.
 *
 *************************************************************************************************/
bool operator==(const cxmath::Position& p_lhs, const cxmath::Position& p_rhs);

/**********************************************************************************************//**
 * @brief Not equal-to operator.
 *
 * @param p_lhs
 *      The left-hand value to use for the comparison.
 * @param p_rhs
 *      The right-hand value to use for the comparison.
 *
 *************************************************************************************************/
bool operator!=(const cxmath::Position& p_lhs, const cxmath::Position& p_rhs);

} // namespace cxmath

#endif // POSITION_H_0AF4F7DC_2C60_4E04_9AEF_7CDA286A9B0E

