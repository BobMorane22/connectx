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
 * @file math.h
 * @date 2021
 *
 *************************************************************************************************/

#ifndef MATH_H_510D2F57_FB0C_4280_9992_BDD00936E001
#define MATH_H_510D2F57_FB0C_4280_9992_BDD00936E001

namespace cxmath
{

template<typename T>
inline constexpr T pi = T(3.14159265358979323846264338327950288419716939937510);

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
 * @brief Checks whether two values are equal.
 *
 * The equality check performed by this function is less strict that what one would expect with
 * an `operator==()` implementation. While `operator==()` usually checks for binary equality,
 * this functions looks for "logical" equality.
 * 
 * To illustrate this, we can look at the classical case of the `double` type. With this type,
 * unwanted rounding errors can occur during calculations. For example, the value 0.1 (base 10)
 * cannot be represented exactly because in base 2, it has an infinite number of digits:
 *
 *                     0.1 (base 10) == 0.00011000110001100011... (base 2)
 * 
 *
 * On some systems, for example, this issue is "avoided" by using close enough values that do
 * not have this problem, such as:
 *
 *                                    0.10000000000000001
 * 
 * which are representable in base 2. These differences introduce rounding errors in calculations
 * which can result in `operator==()` failing because of some far away digits even if mathematically,
 * the comparison should work. The goal of this function is then to mimick the behavior of
 * `operator==()`, but in a less strict way, which does not fail for unimportant precision issues.
 *
 * For more information, read "What Every Computer Scientist Should Know About Floating-Point Arithmetic"
 * available here:
 *
 *                  https://docs.oracle.com/cd/E19957-01/806-3568/ncg_goldberg.html
 *
 * @param p_lhs
 *      The left-hand value to use for the comparison.
 * @param p_rhs
 *      The right-hand value to use for the comparison.
 *
 *************************************************************************************************/
bool AreLogicallyEqual(double p_lhs, double p_rhs);

} // cxmath

#endif // MATH_H_510D2F57_FB0C_4280_9992_BDD00936E001

