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

/**********************************************************************************************//**
 * @brief The \f$\pi\f$ constant.
 *
 *************************************************************************************************/
template<typename T>
inline constexpr T pi = T(3.14159265358979323846264338327950288419716939937510);

/**********************************************************************************************//**
 * @brief Earth's standard gravitational acceleration constant (in m/s²).
 *
 * Earth's gravitational acceleration constant varies, in practice, from place to place. This
 * is the nominal average value at Earth's surface. We can use it to *approximate* Earth's true
 * gravitational constant at any place.
 *
 *************************************************************************************************/
template <typename T>
inline constexpr T g = T{9.80665};

/**********************************************************************************************//**
 * @brief Checks whether two values are equal.
 *
 * The equality check performed by this function is less strict that what one would expect with
 * the `==` operator implementation. While the `==` operator usually checks for binary equality,
 * this functions looks for *logical* equality.
 * 
 * To illustrate this, we can look at the classical case of the `double` type. With this type,
 * unwanted rounding errors can occur during calculations. For example, the value 0.1 (base 10)
 * cannot be represented exactly because in base 2, it has an infinite number of digits:
 *
 * \f[
 *     0.1_{10} = 0.\overline{00011}_{2}.
 * \f]
 * 
 * On some systems, this issue is "avoided" by using close enough values that do not have this
 * problem, such as:
 *
 * \f[
 *     0.10000000000000001_{10},
 * \f]
 * 
 * which are representable in base 2. These differences introduce rounding errors in calculations
 * which can result in the `==` operator failing because of some far away digits even if mathematically,
 * the comparison should work. The goal of this function is then to mimick the behavior of the
 * `==` operator, but in a less strict way, which does not fail for unimportant precision issues.
 *
 * For more information, read [this](https://docs.oracle.com/cd/E19957-01/806-3568/ncg_goldberg.html).
 *
 * @param p_lhs
 *      The left-hand value to use for the comparison.
 * @param p_rhs
 *      The right-hand value to use for the comparison.
 *
 * @return
 *      `true` if both values are considered logically equal, `false` otherwise.
 *
 *************************************************************************************************/
[[nodiscard]] bool AreLogicallyEqual(double p_lhs, double p_rhs);

} // cxmath

#endif // MATH_H_510D2F57_FB0C_4280_9992_BDD00936E001

