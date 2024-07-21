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
 * @file ScalingRatiosTests.cpp
 * @date 2021
 *
 *************************************************************************************************/

#include <gtest/gtest.h>

#include <cxgui/ScalingRatios.h>

namespace
{

constexpr cx::gui::HorizontalScalingRatio DEFAULT_HORIZONTAL_RATIO{1.0};
constexpr cx::gui::VerticalScalingRatio DEFAULT_VERTICAL_RATIO{1.0};

} // namespace

TEST(ScalingRatios, Constructor_TwoArguments_RatiosSet)
{
    constexpr cx::gui::HorizontalScalingRatio hRatioExpected{2.0};
    constexpr cx::gui::VerticalScalingRatio vRatioExpected{3.0};
    constexpr cx::gui::ScalingRatios ratios{hRatioExpected, vRatioExpected};

    ASSERT_TRUE(ratios.m_horizontalRatio == hRatioExpected);
    ASSERT_TRUE(ratios.m_verticalRatio == vRatioExpected);
}

TEST(ScalingRatios, Constructor_HorizontalArgumentOnly_RatiosSet)
{
    constexpr cx::gui::HorizontalScalingRatio hRatioExpected{2.0};
    constexpr cx::gui::ScalingRatios ratios{hRatioExpected};

    ASSERT_TRUE(ratios.m_horizontalRatio == hRatioExpected);
    ASSERT_TRUE(ratios.m_verticalRatio == DEFAULT_VERTICAL_RATIO);
}

TEST(ScalingRatios, Constructor_VerticalArgumentOnly_RatiosSet)
{
    constexpr cx::gui::VerticalScalingRatio vRatioExpected{3.0};
    constexpr cx::gui::ScalingRatios ratios{vRatioExpected};

    ASSERT_TRUE(ratios.m_horizontalRatio == DEFAULT_HORIZONTAL_RATIO);
    ASSERT_TRUE(ratios.m_verticalRatio == vRatioExpected);
}

TEST(ScalingRatios, OperatorEqual_TwoEqualRatiosSet_ReturnsTrue)
{
    constexpr cx::gui::HorizontalScalingRatio hSame{2.0};
    constexpr cx::gui::VerticalScalingRatio vSame{3.0};

    constexpr cx::gui::ScalingRatios lhs{hSame, vSame};
    constexpr cx::gui::ScalingRatios rhs{hSame, vSame};

    ASSERT_TRUE(lhs == rhs);
}

TEST(ScalingRatios, OperatorEqual_TwoDifferentRatiosSet_ReturnsFalse)
{
    constexpr cx::gui::HorizontalScalingRatio hSame{2.0};
    constexpr cx::gui::VerticalScalingRatio vSame{3.0};

    // Horizontal different:
    constexpr cx::gui::ScalingRatios lhsA{cx::gui::HorizontalScalingRatio{5.0}, vSame};
    constexpr cx::gui::ScalingRatios rhsA{hSame, vSame};

    ASSERT_FALSE(lhsA == rhsA);

    // Vertical different:
    constexpr cx::gui::ScalingRatios lhsB{hSame, cx::gui::VerticalScalingRatio{5.0}};
    constexpr cx::gui::ScalingRatios rhsB{hSame, vSame};

    ASSERT_FALSE(lhsB == rhsB);

    // Both different:
    constexpr cx::gui::ScalingRatios lhsC{cx::gui::HorizontalScalingRatio{5.0}, cx::gui::VerticalScalingRatio{6.0}};
    constexpr cx::gui::ScalingRatios rhsC{hSame, vSame};

    ASSERT_FALSE(lhsC == rhsC);
}

TEST(ScalingRatios, OperatorNotEqual_TwoEqualRatiosSet_ReturnsFalse)
{
    constexpr cx::gui::HorizontalScalingRatio hSame{2.0};
    constexpr cx::gui::VerticalScalingRatio vSame{3.0};

    constexpr cx::gui::ScalingRatios lhs{hSame, vSame};
    constexpr cx::gui::ScalingRatios rhs{hSame, vSame};

    ASSERT_FALSE(lhs != rhs);
}

TEST(ScalingRatios, OperatorNotEqual_TwoDifferentRatiosSet_ReturnsTrue)
{
    constexpr cx::gui::HorizontalScalingRatio hSame{2.0};
    constexpr cx::gui::VerticalScalingRatio vSame{3.0};

    // Horizontal different:
    constexpr cx::gui::ScalingRatios lhsA{cx::gui::HorizontalScalingRatio{5.0}, vSame};
    constexpr cx::gui::ScalingRatios rhsA{hSame, vSame};

    ASSERT_TRUE(lhsA != rhsA);

    // Vertical different:
    constexpr cx::gui::ScalingRatios lhsB{hSame, cx::gui::VerticalScalingRatio{5.0}};
    constexpr cx::gui::ScalingRatios rhsB{hSame, vSame};

    ASSERT_TRUE(lhsB != rhsB);

    // Both different:
    constexpr cx::gui::ScalingRatios lhsC{cx::gui::HorizontalScalingRatio{5.0}, cx::gui::VerticalScalingRatio{6.0}};
    constexpr cx::gui::ScalingRatios rhsC{hSame, vSame};

    ASSERT_TRUE(lhsC != rhsC);
}
