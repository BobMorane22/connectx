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
 * @file PositionTests.cpp
 * @date 2021
 *
 *************************************************************************************************/

#include <gtest/gtest.h>

#include <Position.h>

TEST(Position, /*DISABLED_*/DefaultConstructor_ValidPosition_IsOrigin)
{
    constexpr cxmath::Position position;

    ASSERT_EQ(position.m_x, 0.0);
    ASSERT_EQ(position.m_y, 0.0);
}

TEST(Position, /*DISABLED_*/Constructor_ValidPosition_GivenCoordinates)
{
    constexpr double x = 1.2345;
    constexpr double y = 2.3456;
    cxmath::Position position{x, y};

    ASSERT_EQ(position.m_x, x);
    ASSERT_EQ(position.m_y, y);
}

TEST(Position, /*DISABLED_*/EqualToOperator_TwoSamePositions_ReturnsTrue)
{
    constexpr cxmath::Position lhs{1.0, 2.0};
    constexpr cxmath::Position rhs{lhs.m_x, lhs.m_y};

    ASSERT_TRUE(lhs == rhs);
}

TEST(Position, /*DISABLED_*/EqualToOperator_TwoDifferentPositions_ReturnsFalse)
{
    const cxmath::Position lhs{1.0, 2.0};

    // Testing a difference in x:
    constexpr cxmath::Position rhsDiffInX{lhs.m_x + 1.0, lhs.m_y};
    ASSERT_FALSE(lhs == rhsDiffInX);

    // Testing a difference in y:
    constexpr cxmath::Position rhsDiffInY{lhs.m_x, lhs.m_y + 1.0};
    ASSERT_FALSE(lhs == rhsDiffInY);
}

TEST(Position, /*DISABLED_*/NotEqualToOperator_TwoSamePositions_ReturnsFalse)
{
    constexpr cxmath::Position lhs{1.0, 2.0};
    constexpr cxmath::Position rhs{lhs.m_x, lhs.m_y};

    ASSERT_FALSE(lhs != rhs);
}

TEST(Position, /*DISABLED_*/NotEqualToOperator_TwoDifferentPositions_ReturnsTrue)
{
    constexpr cxmath::Position lhs{1.0, 2.0};

    // Testing a difference in x:
    constexpr cxmath::Position rhsDiffInX{lhs.m_x + 1.0, lhs.m_y};
    ASSERT_TRUE(lhs != rhsDiffInX);

    // Testing a difference in y:
    constexpr cxmath::Position rhsDiffInY{lhs.m_x, lhs.m_y + 1.0};
    ASSERT_TRUE(lhs != rhsDiffInY);
}

