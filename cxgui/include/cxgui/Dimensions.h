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
 * @file Dimensions.h
 * @date 2021
 *
 *************************************************************************************************/

#ifndef DIMENSIONS_H_DED7FF0E_07A9_4626_B744_8A3EAAC92B7B
#define DIMENSIONS_H_DED7FF0E_07A9_4626_B744_8A3EAAC92B7B

#include <cxmodel/StrongType.h>

namespace cxgui
{

using Height = cxstd::StrongType<double, struct HeightTag>;
using Width = cxstd::StrongType<double, struct WidthTag>;

/**********************************************************************************************//**
 * @brief 2D dimensions (in pixels) for widgets.
 *
 *************************************************************************************************/
struct Dimensions
{
    constexpr Dimensions(const Height& p_height, const Width& p_width)
    : m_height(p_height)
    , m_width(p_width)
    {
    }

    Height m_height;
    Width m_width;
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
bool operator==(const cxgui::Dimensions& p_lhs, const cxgui::Dimensions& p_rhs);

/**********************************************************************************************//**
 * @brief Not equal-to operator.
 *
 * @param p_lhs
 *      The left-hand value to use for the comparison.
 * @param p_rhs
 *      The right-hand value to use for the comparison.
 *
 *************************************************************************************************/
bool operator!=(const cxgui::Dimensions& p_lhs, const cxgui::Dimensions& p_rhs);

} // namespace cxgui

#endif // DIMENSIONS_H_DED7FF0E_07A9_4626_B744_8A3EAAC92B7B
