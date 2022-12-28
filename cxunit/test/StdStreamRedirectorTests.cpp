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
 * @file StdStreamRedirectorTests.cpp
 * @date 2021
 *
 * @note For some of these tests, some stream output will pollute the test report, which is
 *       wanted. It proves that stream redirection(s) did not occur.
 *
 *************************************************************************************************/

#include <iostream>

#include <gtest/gtest.h>

#include <cxunit/StdStreamRedirector.h>

class StdStreamWriter : public ::testing::Test
{

public:

    void TestBody() override {}

    void WriteToStdOut() {std::cout << "STDOUT";}
    void WriteToStdErr() {std::cerr << "STDERR";}
};

TEST(StreamRedirector, /*DISABLED_*/RedirectNone_ContentsOutput_NothingIsRedirected)
{
    cxunit::StdStreamRedirector<StdStreamWriter, cxunit::Redirection::NONE> redirector;

    redirector.WriteToStdOut(); // Should be printed to the console.
    // Will not compile:
    //   ASSERT_EQ(redirector.GetStdOutContents(), "STDOUT");

    redirector.WriteToStdErr(); // Should be printed to the console.
    // Will not compile:
    //   ASSERT_EQ(redirector.GetStdErrContents(), "STDERR");
}

TEST(StreamRedirector, /*DISABLED_*/RedirectStdOutOnly_ContentsOutput_OnlyStdOutRedirected)
{
    cxunit::StdStreamRedirector<StdStreamWriter, cxunit::Redirection::STDOUT> redirector;

    redirector.WriteToStdOut();
    ASSERT_EQ(redirector.GetStdOutContents(), "STDOUT");

    redirector.WriteToStdErr(); // Should be printed to the console.
    // Will not compile:
    //   ASSERT_EQ(redirector.GetStdErrContents(), "STDERR");
}

TEST(StreamRedirector, /*DISABLED_*/RedirectStdErrOnly_ContentsOutput_OnlyStdErrOutRedirected)
{
    cxunit::StdStreamRedirector<StdStreamWriter, cxunit::Redirection::STDERR> redirector;

    redirector.WriteToStdOut(); // Should be printed to the console.
    // Will not compile:
    //   ASSERT_EQ(redirector.GetStdOutContents(), "STDOUT");

    redirector.WriteToStdErr();
    ASSERT_EQ(redirector.GetStdErrContents(), "STDERR");
}

TEST(StreamRedirector, /*DISABLED_*/RedirectBoth_ContentsOutput_AllIsRedirected)
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

TEST_F(SomeFixtureNoStreamRedirector, /*DISABLED_*/NoStreamRedirector_Alias_TestCompiles)
{
    ASSERT_TRUE(true);
}

TEST_F(SomeFixtureStdOutStreamRedirector, /*DISABLED_*/StdOutStreamRedirector_Alias_TestCompiles)
{
    ASSERT_TRUE(true);
}

TEST_F(SomeFixtureStdErrStreamRedirector, /*DISABLED_*/StdErrStreamRedirector_Alias_TestCompiles)
{
    ASSERT_TRUE(true);
}

TEST_F(SomeFixtureBothStreamsRedirector, /*DISABLED_*/BothStreamRedirector_Alias_TestCompiles)
{
    ASSERT_TRUE(true);
}
