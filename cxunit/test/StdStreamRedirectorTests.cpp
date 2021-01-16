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
 * @file StdStreamRedirectorTests.h
 * @date 2021
 *
 *************************************************************************************************/

#include <iostream>

#include <gtest/gtest.h>

#include <StdStreamRedirector.h>

class StdStreamWriter : public ::testing::Test
{

public:

    void TestBody() override {}

    void WriteToStdOut() {std::cout << "STDOUT";}
    void WriteToStdErr() {std::cerr << "STDERR";}
};

TEST(StreamRedirector, RedirectNone_ContentsOutput_NothingIsRedirected)
{
    cxunit::StdStreamRedirector<StdStreamWriter, cxunit::Redirection::NONE> redirector;

    // Will not compile:
    //   redirector.WriteToStdOut();
    //   ASSERT_EQ(redirector.GetStdOutContents(), "STDOUT");

    // Will not compile:
    //   redirector.WriteToStdErr();
    //   ASSERT_EQ(redirector.GetStdErrContents(), "STDERR");
}

TEST(StreamRedirector, RedirectStdOutOnly_ContentsOutput_OnlyStdOutRedirected)
{
    cxunit::StdStreamRedirector<StdStreamWriter, cxunit::Redirection::STDOUT> redirector;

    redirector.WriteToStdOut();
    ASSERT_EQ(redirector.GetStdOutContents(), "STDOUT");

    // Will not compile:
    //   redirector.WriteToStdErr();
    //   ASSERT_EQ(redirector.GetStdErrContents(), "STDERR");
}

TEST(StreamRedirector, RedirectStdErrOnly_ContentsOutput_OnlyStdErrOutRedirected)
{
    cxunit::StdStreamRedirector<StdStreamWriter, cxunit::Redirection::STDERR> redirector;

    // Will not compile:
    //   redirector.WriteToStdOut();
    //   ASSERT_EQ(redirector.GetStdOutContents(), "STDOUT");

    redirector.WriteToStdErr();
    ASSERT_EQ(redirector.GetStdErrContents(), "STDERR");
}

TEST(StreamRedirector, RedirectBoth_ContentsOutput_AllIsRedirected)
{
    cxunit::StdStreamRedirector<StdStreamWriter, cxunit::Redirection::BOTH> redirector;

    redirector.WriteToStdOut();
    ASSERT_EQ(redirector.GetStdOutContents(), "STDOUT");

    redirector.WriteToStdErr();
    ASSERT_EQ(redirector.GetStdErrContents(), "STDERR");
}

// The following is the usual use case for the `StdStreamRedirector` classes: creating aliases for
// fixtures according to different scenarios and writing tests using these aliases. We make sure it
// compiles:
class SomeFixture : public ::testing::Test
{
};

ADD_STREAM_REDIRECTORS(SomeFixture);

TEST_F(SomeFixtureNoStreamRedirector, NoStreamRedirector_Alias_TestCompiles)
{
    ASSERT_TRUE(true);
}

TEST_F(SomeFixtureStdOutStreamRedirector, StdOutStreamRedirector_Alias_TestCompiles)
{
    ASSERT_TRUE(true);
}

TEST_F(SomeFixtureStdErrStreamRedirector, StdErrStreamRedirector_Alias_TestCompiles)
{
    ASSERT_TRUE(true);
}

TEST_F(SomeFixtureBothStreamsRedirector, BothStreamRedirector_Alias_TestCompiles)
{
    ASSERT_TRUE(true);
}
