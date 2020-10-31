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
 * @file StatusTests.cpp
 * @date 2020
 *
 *************************************************************************************************/

#include <gtest/gtest.h>

#include <Status.h>

#include "DisableStdStreamsRAII.h"

TEST(Status, MakeSuccess_ValidContext_SuccessReturned)
{
    const auto status = cxmodel::MakeSuccess();

    ASSERT_TRUE(status.IsSuccess());
}

TEST(Status, MakeError_WithErrorMessage_ErrorReturned)
{
    const auto status = cxmodel::MakeError("An error message");

    ASSERT_FALSE(status.IsSuccess());
}

TEST(Status, GetMessage_ErrorWithMessage_MessageReturned)
{
    const std::string expected = "An error message";

    const auto status = cxmodel::MakeError("An error message");

    ASSERT_EQ(expected, status.GetMessage());
}

TEST(Status, GetMessage_Success_EmptyMessageReturned)
{
    DisableStdStreamsRAII streamDisabler;

    const auto status = cxmodel::MakeSuccess();

    ASSERT_EQ("", status.GetMessage());
}

TEST(Status, MakeError_WithoutErrorMessage_EmptyMessageReturned)
{
    DisableStdStreamsRAII streamDisabler;

    const auto status = cxmodel::MakeError("");

    ASSERT_EQ("", status.GetMessage());
}

TEST(Status, GetMessage_Success_Asserts)
{
    DisableStdStreamsRAII streamDisabler;

    const auto status = cxmodel::MakeSuccess();
    const std::string message = status.GetMessage();

    const std::string streamContents = streamDisabler.GetStdErrContents();

    ASSERT_TRUE(streamContents.find("Precondition") != std::string::npos);
}

TEST(Status, MakeError_WithoutErrorMessage_Asserts)
{
    DisableStdStreamsRAII streamDisabler;

    const auto status = cxmodel::MakeError("");

    const std::string streamContents = streamDisabler.GetStdErrContents();

    ASSERT_TRUE(streamContents.find("Precondition") != std::string::npos);
}

TEST(Status, OnError_WithSuccess_DoesNotReturn)
{
    const auto runner = [](const cxmodel::Status& p_status, bool& p_didItReturn)
                        {
                            ON_ERROR(p_status, return;);

                            p_didItReturn = true;
                        };

    bool didNotReturn = false;
    runner(cxmodel::MakeSuccess(), didNotReturn);

    ASSERT_TRUE(didNotReturn);
}

TEST(Status, OnError_WithError_Returns)
{
    const auto runner = [](const cxmodel::Status& p_status, bool& p_didItReturn)
                        {
                            ON_ERROR(p_status, return;);

                            p_didItReturn = true;
                        };

    bool didReturn = false;
    runner(cxmodel::MakeError("An error message"), didReturn);

    ASSERT_FALSE(didReturn);
}
