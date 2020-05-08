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

#include <gtest/gtest.h>

#include <assertion.h>

#include <HandleAssertTestFixture.h>

TEST_F(HandleAssertTestFixture, /*DISABLED_*/HandleAssert_AllValidInputsNoMessageAssertion_ValidMessages)
{
    cxinv::HandleAssert(cxinv::AssertLabel::ASSERTION,
                        (3 > 5),
                        m_CONDITION_EXPRESSION,
                        m__FILE_,
                        m__FUNCTION_,
                        m__LINE_);

    const std::string result = GetStdErrContents();
    const std::string expected = MakeExpectedMessage(cxinv::AssertLabel::ASSERTION);

    ASSERT_EQ(result, expected);

    const std::string stdoutContents = GetStdOutContents();
    ASSERT_TRUE(stdoutContents.empty());
}

TEST_F(HandleAssertTestFixture, /*DISABLED_*/HandleAssert_AllValidInputsNoMessagePrecondition_ValidMessages)
{
    cxinv::HandleAssert(cxinv::AssertLabel::PRECONDITION,
                        (3 > 5),
                        m_CONDITION_EXPRESSION,
                        m__FILE_,
                        m__FUNCTION_,
                        m__LINE_);

    const std::string result = GetStdErrContents();
    const std::string expected = MakeExpectedMessage(cxinv::AssertLabel::PRECONDITION);

    ASSERT_EQ(result, expected);

    const std::string stdoutContents = GetStdOutContents();
    ASSERT_TRUE(stdoutContents.empty());
}

TEST_F(HandleAssertTestFixture, /*DISABLED_*/HandleAssert_AllValidInputsNoMessagePostcondition_ValidMessages)
{
    cxinv::HandleAssert(cxinv::AssertLabel::POSTCONDITION,
                        (3 > 5),
                        m_CONDITION_EXPRESSION,
                        m__FILE_,
                        m__FUNCTION_,
                        m__LINE_);

    const std::string result = GetStdErrContents();
    const std::string expected = MakeExpectedMessage(cxinv::AssertLabel::POSTCONDITION);

    ASSERT_EQ(result, expected);

    const std::string stdoutContents = GetStdOutContents();
    ASSERT_TRUE(stdoutContents.empty());
}

TEST_F(HandleAssertTestFixture, /*DISABLED_*/HandleAssert_AllValidInputsNoMessageInvariant_ValidMessages)
{
    cxinv::HandleAssert(cxinv::AssertLabel::INVARIANT,
                        (3 > 5),
                        m_CONDITION_EXPRESSION,
                        m__FILE_,
                        m__FUNCTION_,
                        m__LINE_);

    const std::string result = GetStdErrContents();
    const std::string expected = MakeExpectedMessage(cxinv::AssertLabel::INVARIANT);

    ASSERT_EQ(result, expected);

    const std::string stdoutContents = GetStdOutContents();
    ASSERT_TRUE(stdoutContents.empty());
}

TEST_F(HandleAssertTestFixture, /*DISABLED_*/HandleAssert_AllValidInputsWithMessageAssertion_ValidMessages)
{
    cxinv::HandleAssert(cxinv::AssertLabel::ASSERTION,
                        (3 > 5),
                        m_CONDITION_EXPRESSION,
                        m__FILE_,
                        m__FUNCTION_,
                        m__LINE_,
                        m_VALID_MESSAGE);

    const std::string result = GetStdErrContents();
    const std::string expected = MakeExpectedMessage(cxinv::AssertLabel::ASSERTION, m_VALID_MESSAGE);

    ASSERT_EQ(result, expected);

    const std::string stdoutContents = GetStdOutContents();
    ASSERT_TRUE(stdoutContents.empty());
}

TEST_F(HandleAssertTestFixture, /*DISABLED_*/HandleAssert_AllValidInputsWithMessagePrecondition_ValidMessages)
{
    cxinv::HandleAssert(cxinv::AssertLabel::PRECONDITION,
                        (3 > 5),
                        m_CONDITION_EXPRESSION,
                        m__FILE_,
                        m__FUNCTION_,
                        m__LINE_,
                        m_VALID_MESSAGE);

    const std::string result = GetStdErrContents();
    const std::string expected = MakeExpectedMessage(cxinv::AssertLabel::PRECONDITION, m_VALID_MESSAGE);

    ASSERT_EQ(result, expected);

    const std::string stdoutContents = GetStdOutContents();
    ASSERT_TRUE(stdoutContents.empty());
}

TEST_F(HandleAssertTestFixture, /*DISABLED_*/HandleAssert_AllValidInputsWithMessagePostcondition_ValidMessages)
{
    cxinv::HandleAssert(cxinv::AssertLabel::POSTCONDITION,
                        (3 > 5),
                        m_CONDITION_EXPRESSION,
                        m__FILE_,
                        m__FUNCTION_,
                        m__LINE_,
                        m_VALID_MESSAGE);

    const std::string result = GetStdErrContents();
    const std::string expected = MakeExpectedMessage(cxinv::AssertLabel::POSTCONDITION, m_VALID_MESSAGE);

    ASSERT_EQ(result, expected);

    const std::string stdoutContents = GetStdOutContents();
    ASSERT_TRUE(stdoutContents.empty());
}

TEST_F(HandleAssertTestFixture, /*DISABLED_*/HandleAssert_AllValidInputsWithMessageInvariant_ValidMessages)
{
    cxinv::HandleAssert(cxinv::AssertLabel::INVARIANT,
                        (3 > 5),
                        m_CONDITION_EXPRESSION,
                        m__FILE_,
                        m__FUNCTION_,
                        m__LINE_,
                        m_VALID_MESSAGE);

    const std::string result = GetStdErrContents();
    const std::string expected = MakeExpectedMessage(cxinv::AssertLabel::INVARIANT, m_VALID_MESSAGE);

    ASSERT_EQ(result, expected);

    const std::string stdoutContents = GetStdOutContents();
    ASSERT_TRUE(stdoutContents.empty());
}

TEST_F(HandleAssertTestFixture, /*DISABLED_*/HandleAssert_invalidConditionExpression_ExecutionAborted)
{
    ASSERT_DEATH(cxinv::HandleAssert(cxinv::AssertLabel::INVARIANT,
                                     (3 > 5),
                                     nullptr,
                                     m__FILE_,
                                     m__FUNCTION_,
                                     m__LINE_),
                                     GetStdErrContents());
}

TEST_F(HandleAssertTestFixture, /*DISABLED_*/HandleAssert_invalidFileName_ExecutionAborted)
{
    ASSERT_DEATH(cxinv::HandleAssert(cxinv::AssertLabel::INVARIANT,
                                     (3 > 5),
                                     m_CONDITION_EXPRESSION,
                                     nullptr,
                                     m__FUNCTION_,
                                     m__LINE_),
                                     GetStdErrContents());
}

TEST_F(HandleAssertTestFixture, /*DISABLED_*/HandleAssert_invalidFunctionName_ExecutionAborted)
{
    ASSERT_DEATH(cxinv::HandleAssert(cxinv::AssertLabel::INVARIANT,
                                     (3 > 5),
                                     m_CONDITION_EXPRESSION,
                                     m__FILE_,
                                     nullptr,
                                     m__LINE_),
                                     GetStdErrContents());
}
