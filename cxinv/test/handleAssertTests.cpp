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
 * @file handleAssertTests.cpp
 * @date 2019
 *
 *************************************************************************************************/

#ifndef NDEBUG

#include <gtest/gtest.h>

#include <cxinv/assertion.h>

#include "HandleAssertTestFixture.h"

TEST_F(HandleAssertTestFixture, /*DISABLED_*/HandleAssert_TrueCondition_ReturnsTrue)
{
    ASSERT_TRUE(cx::inv::HandleAssert(cx::inv::AssertLabel::ASSERTION,
                                    (5 > 3),
                                    m_CONDITION_EXPRESSION,
                                    m__FILE_,
                                    m__FUNCTION_,
                                    m__LINE_));
}


TEST_F(HandleAssertTestFixture, /*DISABLED_*/HandleAssert_FalseCondition_ReturnsFalse)
{
    ASSERT_FALSE(cx::inv::HandleAssert(cx::inv::AssertLabel::ASSERTION,
                                    (3 > 5),
                                     m_CONDITION_EXPRESSION,
                                     m__FILE_,
                                     m__FUNCTION_,
                                     m__LINE_));
}

TEST_F(HandleAssertTestFixture, /*DISABLED_*/HandleAssert_AllValidInputsNoMessageAssertion_ValidMessages)
{
    cx::inv::HandleAssert(cx::inv::AssertLabel::ASSERTION,
                        (3 > 5),
                        m_CONDITION_EXPRESSION,
                        m__FILE_,
                        m__FUNCTION_,
                        m__LINE_);

    const std::string result = GetStdErrContents();
    const std::string expected = MakeExpectedMessage(cx::inv::AssertLabel::ASSERTION);

    ASSERT_EQ(result, expected);

    const std::string stdoutContents = GetStdOutContents();
    ASSERT_TRUE(stdoutContents.empty());
}

TEST_F(HandleAssertTestFixture, /*DISABLED_*/HandleAssert_AllValidInputsNoMessagePrecondition_ValidMessages)
{
    cx::inv::HandleAssert(cx::inv::AssertLabel::PRECONDITION,
                        (3 > 5),
                        m_CONDITION_EXPRESSION,
                        m__FILE_,
                        m__FUNCTION_,
                        m__LINE_);

    const std::string result = GetStdErrContents();
    const std::string expected = MakeExpectedMessage(cx::inv::AssertLabel::PRECONDITION);

    ASSERT_EQ(result, expected);

    const std::string stdoutContents = GetStdOutContents();
    ASSERT_TRUE(stdoutContents.empty());
}

TEST_F(HandleAssertTestFixture, /*DISABLED_*/HandleAssert_AllValidInputsNoMessagePostcondition_ValidMessages)
{
    cx::inv::HandleAssert(cx::inv::AssertLabel::POSTCONDITION,
                        (3 > 5),
                        m_CONDITION_EXPRESSION,
                        m__FILE_,
                        m__FUNCTION_,
                        m__LINE_);

    const std::string result = GetStdErrContents();
    const std::string expected = MakeExpectedMessage(cx::inv::AssertLabel::POSTCONDITION);

    ASSERT_EQ(result, expected);

    const std::string stdoutContents = GetStdOutContents();
    ASSERT_TRUE(stdoutContents.empty());
}

TEST_F(HandleAssertTestFixture, /*DISABLED_*/HandleAssert_AllValidInputsNoMessageInvariant_ValidMessages)
{
    cx::inv::HandleAssert(cx::inv::AssertLabel::INVARIANT,
                        (3 > 5),
                        m_CONDITION_EXPRESSION,
                        m__FILE_,
                        m__FUNCTION_,
                        m__LINE_);

    const std::string result = GetStdErrContents();
    const std::string expected = MakeExpectedMessage(cx::inv::AssertLabel::INVARIANT);

    ASSERT_EQ(result, expected);

    const std::string stdoutContents = GetStdOutContents();
    ASSERT_TRUE(stdoutContents.empty());
}

TEST_F(HandleAssertTestFixture, /*DISABLED_*/HandleAssert_AllValidInputsWithMessageAssertion_ValidMessages)
{
    cx::inv::HandleAssert(cx::inv::AssertLabel::ASSERTION,
                        (3 > 5),
                        m_CONDITION_EXPRESSION,
                        m__FILE_,
                        m__FUNCTION_,
                        m__LINE_,
                        m_VALID_MESSAGE);

    const std::string result = GetStdErrContents();
    const std::string expected = MakeExpectedMessage(cx::inv::AssertLabel::ASSERTION, m_VALID_MESSAGE);

    ASSERT_EQ(result, expected);

    const std::string stdoutContents = GetStdOutContents();
    ASSERT_TRUE(stdoutContents.empty());
}

TEST_F(HandleAssertTestFixture, /*DISABLED_*/HandleAssert_AllValidInputsWithMessagePrecondition_ValidMessages)
{
    cx::inv::HandleAssert(cx::inv::AssertLabel::PRECONDITION,
                        (3 > 5),
                        m_CONDITION_EXPRESSION,
                        m__FILE_,
                        m__FUNCTION_,
                        m__LINE_,
                        m_VALID_MESSAGE);

    const std::string result = GetStdErrContents();
    const std::string expected = MakeExpectedMessage(cx::inv::AssertLabel::PRECONDITION, m_VALID_MESSAGE);

    ASSERT_EQ(result, expected);

    const std::string stdoutContents = GetStdOutContents();
    ASSERT_TRUE(stdoutContents.empty());
}

TEST_F(HandleAssertTestFixture, /*DISABLED_*/HandleAssert_AllValidInputsWithMessagePostcondition_ValidMessages)
{
    cx::inv::HandleAssert(cx::inv::AssertLabel::POSTCONDITION,
                        (3 > 5),
                        m_CONDITION_EXPRESSION,
                        m__FILE_,
                        m__FUNCTION_,
                        m__LINE_,
                        m_VALID_MESSAGE);

    const std::string result = GetStdErrContents();
    const std::string expected = MakeExpectedMessage(cx::inv::AssertLabel::POSTCONDITION, m_VALID_MESSAGE);

    ASSERT_EQ(result, expected);

    const std::string stdoutContents = GetStdOutContents();
    ASSERT_TRUE(stdoutContents.empty());
}

TEST_F(HandleAssertTestFixture, /*DISABLED_*/HandleAssert_AllValidInputsWithMessageInvariant_ValidMessages)
{
    cx::inv::HandleAssert(cx::inv::AssertLabel::INVARIANT,
                        (3 > 5),
                        m_CONDITION_EXPRESSION,
                        m__FILE_,
                        m__FUNCTION_,
                        m__LINE_,
                        m_VALID_MESSAGE);

    const std::string result = GetStdErrContents();
    const std::string expected = MakeExpectedMessage(cx::inv::AssertLabel::INVARIANT, m_VALID_MESSAGE);

    ASSERT_EQ(result, expected);

    const std::string stdoutContents = GetStdOutContents();
    ASSERT_TRUE(stdoutContents.empty());
}

TEST_F(HandleAssertTestFixture, /*DISABLED_*/HandleAssert_invalidConditionExpression_ExecutionAborted)
{
    ASSERT_DEATH(cx::inv::HandleAssert(cx::inv::AssertLabel::INVARIANT,
                                     (3 > 5),
                                     nullptr,
                                     m__FILE_,
                                     m__FUNCTION_,
                                     m__LINE_),
                                     GetStdErrContents());
}

TEST_F(HandleAssertTestFixture, /*DISABLED_*/HandleAssert_invalidFileName_ExecutionAborted)
{
    ASSERT_DEATH(cx::inv::HandleAssert(cx::inv::AssertLabel::INVARIANT,
                                     (3 > 5),
                                     m_CONDITION_EXPRESSION,
                                     nullptr,
                                     m__FUNCTION_,
                                     m__LINE_),
                                     GetStdErrContents());
}

TEST_F(HandleAssertTestFixture, /*DISABLED_*/HandleAssert_invalidFunctionName_ExecutionAborted)
{
    ASSERT_DEATH(cx::inv::HandleAssert(cx::inv::AssertLabel::INVARIANT,
                                     (3 > 5),
                                     m_CONDITION_EXPRESSION,
                                     m__FILE_,
                                     nullptr,
                                     m__LINE_),
                                     GetStdErrContents());
}

TEST(HandleAssertTest, /*DISABLED_*/HandleAssert_UniquePtrAssertCheckForNullptr_NotExplcitCheckNeeded)
{
    struct A {};

    std::unique_ptr<A> uPtr = std::make_unique<A>();

    if(INL_ASSERT(uPtr))
    {
        ASSERT_TRUE(true);
    }
    else
    {
        ASSERT_TRUE(false);
    }
}

TEST(HandleAssertTest, /*DISABLED_*/HandleAssert_SharedPtrAssertCheckForNullptr_NotExplcitCheckNeeded)
{
    struct A {};

    std::shared_ptr<A> sPtr = std::make_shared<A>();

    if(INL_ASSERT(sPtr))
    {
        ASSERT_TRUE(true);
    }
    else
    {
        ASSERT_TRUE(false);
    }
}

#endif // NDEBUG
