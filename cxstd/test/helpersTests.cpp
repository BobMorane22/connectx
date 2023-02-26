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
 * @file helpersTests.cpp
 * @date 2023
 *
 *************************************************************************************************/

#include <gtest/gtest.h>

#include <cxstd/helpers.h>

namespace
{

constexpr int CONDITIONAL_RETURN = 0;
constexpr int NO_CONDITIONAL_RETURN = 1;

[[nodiscard]] int f(bool p_condition)
{
    RETURN_IF(p_condition, CONDITIONAL_RETURN);
    return NO_CONDITIONAL_RETURN;
}

[[nodiscard]] int g(bool p_conditionA, bool p_conditionB)
{
    RETURN_IF(p_conditionA && p_conditionB, CONDITIONAL_RETURN);
    return NO_CONDITIONAL_RETURN;
}

[[nodiscard]] int h(bool p_condition)
{
    RETURN_IF(p_condition, 1 - 1);
    return NO_CONDITIONAL_RETURN;
}

[[nodiscard]] int i(bool p_conditionA, bool p_conditionB)
{
    RETURN_IF(p_conditionA && p_conditionB, 1 - 1);
    return NO_CONDITIONAL_RETURN;
}

void k(bool p_condition, bool& conditionalReturn)
{
    conditionalReturn = true;
    RETURN_IF(p_condition,);

    conditionalReturn = false;
}

void l(bool p_condition, bool& conditionalReturn)
{
    conditionalReturn = true;
    RETURN_IF(p_condition ? true : false,);

    conditionalReturn = false;
}

} // namespace

TEST(ReturnIf, RETURN_IF_SimpleConditionNoConditionalReturn)
{
    ASSERT_TRUE(f(false) == NO_CONDITIONAL_RETURN);
}

TEST(ReturnIf, RETURN_IF_ComplexConditionNoConditionalReturn)
{
    ASSERT_TRUE(g(true, false) == NO_CONDITIONAL_RETURN);
}

TEST(ReturnIf, RETURN_IF_SimpleConditionConditionalReturnWithValue)
{
    ASSERT_TRUE(f(true) == CONDITIONAL_RETURN);
}

TEST(ReturnIf, RETURN_IF_ComplexConditionReturnWithValue)
{
    ASSERT_TRUE(g(true, true) == CONDITIONAL_RETURN);
}

TEST(ReturnIf, RETURN_IF_SimpleConditionReturnWithExpression)
{
    ASSERT_TRUE(h(true) == CONDITIONAL_RETURN);
}

TEST(ReturnIf, RETURN_IF_ComplexConditionReturnWithExpression)
{
    ASSERT_TRUE(i(true, true) == CONDITIONAL_RETURN);
}

TEST(ReturnIf, RETURN_IF_SimpleConditionReturnVoid)
{
    bool conditionalReturn = false;
    k(true, conditionalReturn);
    ASSERT_TRUE(conditionalReturn);

    conditionalReturn = false;
    k(false, conditionalReturn);
    ASSERT_TRUE(!conditionalReturn);
}

TEST(ReturnIf, RETURN_IF_ComplexConditionReturnVoid)
{
    bool conditionalReturn = false;
    l(true, conditionalReturn);
    ASSERT_TRUE(conditionalReturn);

    conditionalReturn = false;
    l(false, conditionalReturn);
    ASSERT_TRUE(!conditionalReturn);
}
