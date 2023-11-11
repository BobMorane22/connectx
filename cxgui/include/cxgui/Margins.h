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
 * @file Margins.h
 * @date 2023
 *
 *************************************************************************************************/

#ifndef MARGINS_H_D69C1309_AC7D_4008_8139_04EE2888BFF6
#define MARGINS_H_D69C1309_AC7D_4008_8139_04EE2888BFF6

#include <cxstd/StrongType.h>

namespace cxgui
{

/******************************************************************************************//**
 * @brief Margin size of the top.
 *
 ********************************************************************************************/
using TopMargin = cxstd::StrongType<int, struct TopMarginTag, cxstd::Addable, cxstd::Comparable>;

/******************************************************************************************//**
 * @brief Margin size of the bottom.
 *
 ********************************************************************************************/
using BottomMargin = cxstd::StrongType<int, struct BottomMarginTag, cxstd::Addable, cxstd::Comparable>;

/******************************************************************************************//**
 * @brief Margin size of the left side.
 *
 ********************************************************************************************/
using LeftMargin = cxstd::StrongType<int, struct LeftMarginTag, cxstd::Addable, cxstd::Comparable>;

/******************************************************************************************//**
 * @brief Margin size of the right side.
 *
 ********************************************************************************************/
using RightMargin = cxstd::StrongType<int, struct RightMarginTag, cxstd::Addable, cxstd::Comparable>;

/******************************************************************************************//**
 * @brief Widget margin sizes.
 *
 ********************************************************************************************/
struct Margins
{

    /**************************************************************************************//**
     * @brief Constructor.
     *
     * @param p_top
     *      The top margin size.
     * @param p_bottom
     *      The bottom margin size.
     * @param p_left
     *      The left side margin size.
     * @param p_right
     *      The right side margin size.
     *
     ****************************************************************************************/
    constexpr Margins(const TopMargin& p_top,
                      const BottomMargin& p_bottom,
                      const LeftMargin& p_left,
                      const RightMargin& p_right)
    : m_top{p_top}, m_bottom{p_bottom}
    , m_left{p_left}, m_right{p_right}
    {
    }

    TopMargin m_top;
    BottomMargin m_bottom;
    LeftMargin m_left;
    RightMargin m_right;
};

} // namespace cxgui

#endif // MARGINS_H_D69C1309_AC7D_4008_8139_04EE2888BFF6
