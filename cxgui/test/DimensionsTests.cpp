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
 * @file DimensionsTests.cpp
 * @date 2021
 *
 *************************************************************************************************/

#include <gtest/gtest.h>

#include <Dimensions.h>

TEST(Dimensions, /*DISABLED*/EqualToOperator_TwoSameDimensions_ReturnsTrue)
{
    using namespace cxgui;

    constexpr Dimensions lhs{Height{1.0}, Width{2.0}};
    constexpr Dimensions rhs{lhs.m_height, lhs.m_width};

    ASSERT_TRUE(lhs == rhs);
}

TEST(Dimensions, /*DISABLED*/EqualToOperator_TwoDifferentDimensions_ReturnsFalse)
{
    using namespace cxgui;

    const double height = 1.0;
    const double width = 2.0;
    constexpr Dimensions lhs{Height{height}, Width{width}};

    // Testing different height:
    constexpr Dimensions rhsDiffInHeight{Height{height + 1.0}, lhs.m_width};
    ASSERT_FALSE(lhs == rhsDiffInHeight);

    // Testing different width:
    constexpr Dimensions rhsDiffInWidth{lhs.m_height, Width{width + 1.0}};
    ASSERT_FALSE(lhs == rhsDiffInWidth);
}

TEST(Dimensions, /*DISABLED*/NotEqualToOperator_TwoSameDimensions_ReturnsFalse)
{
    using namespace cxgui;

    constexpr Dimensions lhs{Height{1.0}, Width{2.0}};
    constexpr Dimensions rhs{lhs.m_height, lhs.m_width};

    ASSERT_FALSE(lhs != rhs);
}

TEST(Dimensions, /*DISABLED*/NotEqualToOperator_TwoDifferentDimensions_ReturnsTrue)
{
    using namespace cxgui;

    const double height = 1.0;
    const double width = 2.0;
    constexpr Dimensions lhs{Height{height}, Width{width}};

    // Testing different height:
    constexpr Dimensions rhsDiffInHeight{Height{height + 1.0}, lhs.m_width};
    ASSERT_TRUE(lhs != rhsDiffInHeight);

    // Testing different width:
    constexpr Dimensions rhsDiffInWidth{lhs.m_height, Width{width + 1.0}};
    ASSERT_TRUE(lhs != rhsDiffInWidth);
}
