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
 * @file IBoardTests.cpp
 * @date 2020
 *
 *************************************************************************************************/

#include <gtest/gtest.h> 

#include <cxmodel/IBoard.h>

TEST(Position, OperatorEqual_TwoSamePositions_ReturnsTrue)
{
    const cxmodel::IBoard::Position lhs{1u, 2u};
    const cxmodel::IBoard::Position rhs = lhs;

    ASSERT_TRUE(lhs == rhs);
}

TEST(Position, OperatorEqual_TwoDifferentPositions_ReturnsTrue)
{
    const cxmodel::IBoard::Position lhs{1u, 2u};
    const cxmodel::IBoard::Position rhs{2u, 1u};

    ASSERT_FALSE(lhs == rhs);
}

TEST(Position, OperatorNotEqual_TwoSamePositions_ReturnsFalse)
{
    const cxmodel::IBoard::Position lhs{1u, 2u};
    const cxmodel::IBoard::Position rhs = lhs;

    ASSERT_FALSE(lhs != rhs);
}

TEST(Position, OperatorNotEqual_TwoDifferentPositions_ReturnsTrue)
{
    const cxmodel::IBoard::Position lhs{1u, 2u};
    const cxmodel::IBoard::Position rhs{2u, 1u};

    ASSERT_TRUE(lhs != rhs);
}
