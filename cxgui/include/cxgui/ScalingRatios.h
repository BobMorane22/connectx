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
 * @file ScalingRatios.h
 * @date 2021
 *
 *************************************************************************************************/

#ifndef SCALINGRATIOS_H_C98BAFA1_22F4_4A84_9345_AF318597FB2F
#define SCALINGRATIOS_H_C98BAFA1_22F4_4A84_9345_AF318597FB2F

#include <cxstd/StrongType.h>

namespace cxgui
{

/**********************************************************************************************//**
 * @brief Ratio for horizontal scaling.
 *
 *************************************************************************************************/
using HorizontalScalingRatio = cxstd::StrongType<double, struct HorizontalScalingRatioTag, cxstd::EqualityComparable>;

/**********************************************************************************************//**
 * @brief Ratio for vertical scaling.
 *
 *************************************************************************************************/
using VerticalScalingRatio = cxstd::StrongType<double, struct VerticalScalingRatioTag, cxstd::EqualityComparable>;

/**********************************************************************************************//**
 * @brief Two dimensional scaling ratios.
 *
 *************************************************************************************************/
struct ScalingRatios
{

    /******************************************************************************************//**
     * @brief Constructor.
     *
     * @param p_horizontalRatio
     *      An horizontal scaling ratio.
     * @param p_verticalRatio
     *      A vertical scaling ratio.
     *
     *********************************************************************************************/
    constexpr ScalingRatios(HorizontalScalingRatio p_horizontalRatio, VerticalScalingRatio p_verticalRatio);

    /******************************************************************************************//**
     * @brief Constructor.
     *
     * In this case, the vertical scaling ratio is automatically set to 1.0 (no scaling).
     *
     * @param p_horizontalRatio
     *      An horizontal scaling ratio.
     *
     *********************************************************************************************/
    explicit constexpr ScalingRatios(HorizontalScalingRatio p_horizontalRatio);

    /******************************************************************************************//**
     * @brief Constructor.
     *
     * In this case, the horizontal scaling ratio is automatically set to 1.0 (no scaling).
     *
     * @param p_verticalRatio
     *      A vertical scaling ratio.
     *
     *********************************************************************************************/
    explicit constexpr ScalingRatios(VerticalScalingRatio p_verticalRatio);

    /** The horizontal scaling ratio. */
    HorizontalScalingRatio m_horizontalRatio;

    /** The vertical scaling ration. */
    VerticalScalingRatio m_verticalRatio;

};

/******************************************************************************************//**
 * @brief Equal-to operator.
 *
 * @param p_lhs The left-hand side ratios to compare.
 * @param p_rhs The right-hand side ratios to compare.
 *
 * @return `true` if both ratios are equal, `false` otherwise.
 *
 *********************************************************************************************/
constexpr bool operator==(const ScalingRatios& p_lhs, const ScalingRatios& p_rhs);

/******************************************************************************************//**
 * @brief Not equal-to operator.
 *
 * @param p_lhs The left-hand side ratios to compare.
 * @param p_rhs The right-hand side ratios to compare.
 *
 * @return `true` if both ratios are not equal, `false` otherwise.
 *
 *********************************************************************************************/
constexpr bool operator!=(const ScalingRatios& p_lhs, const ScalingRatios& p_rhs);

} // namespace cxgui

constexpr cxgui::ScalingRatios::ScalingRatios(HorizontalScalingRatio p_horizontalRatio, VerticalScalingRatio p_verticalRatio)
: m_horizontalRatio{p_horizontalRatio}
, m_verticalRatio{p_verticalRatio}
{
}

constexpr cxgui::ScalingRatios::ScalingRatios(HorizontalScalingRatio p_horizontalRatio)
: m_horizontalRatio{p_horizontalRatio}
, m_verticalRatio{1.0}
{
}

constexpr cxgui::ScalingRatios::ScalingRatios(VerticalScalingRatio p_verticalRatio)
: m_horizontalRatio{1.0}
, m_verticalRatio{p_verticalRatio}
{
}

constexpr bool cxgui::operator==(const ScalingRatios& p_lhs, const ScalingRatios& p_rhs)
{
    return p_lhs.m_horizontalRatio == p_rhs.m_horizontalRatio &&
           p_lhs.m_verticalRatio == p_rhs.m_verticalRatio;
}

constexpr bool cxgui::operator!=(const ScalingRatios& p_lhs, const ScalingRatios& p_rhs)
{
    return !(p_lhs == p_rhs);
}

#endif // SCALINGRATIOS_H_C98BAFA1_22F4_4A84_9345_AF318597FB2F

