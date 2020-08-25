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
 * @file StdLogTargetTests.cpp
 * @date 2020
 *
 *************************************************************************************************/

#include <gtest/gtest.h>

#include <StdLogTarget.h>

#include "DisableStdStreamsRAII.h"

TEST(StdLogTarget, /*DISABLED_*/Log_SomeString_StringLoggedToStdout)
{
    DisableStdStreamsRAII raii;

    const std::string before = raii.GetStdOutContents();
    ASSERT_TRUE(before.empty());

    std::unique_ptr<cxlog::ILogTarget> target = std::make_unique<cxlog::StdLogTarget>();

    const std::string someString = "Some string...";

    target->Log(someString);

    const std::string after = raii.GetStdOutContents();
    ASSERT_EQ(after, someString);
}
