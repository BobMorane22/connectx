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
 * @file CmdArgStrategyTests.cpp
 * @date 2019
 *
 *************************************************************************************************/

#include <memory>
#include <regex>

#include <gtest/gtest.h>

#include <ApplicationTestFixture.h>

#include <CmdArgHelpStrategy.h>
#include <CmdArgInvalidStrategy.h>
#include <CmdArgNoStrategy.h>
#include <CmdArgVersionStrategy.h>


TEST_F(ApplicationTestFixture, Handle_NoStrategy_NothingPrinted)
{
    const std::unique_ptr<cx::ICmdArgWorkflowStrategy> strategy = std::make_unique<cx::CmdArgNoStrategy>();

    std::string stdOutContents, stdErrContents;

    ASSERT_EQ(std::string(), stdOutContents);
    ASSERT_EQ(std::string(), stdErrContents);

    strategy->Handle();

    stdOutContents = GetStdOutContents();
    stdErrContents = GetStdErrContents();

    const std::string expectedStdOutContents = "";
    const std::string expectedStdErrContents = "";

    ASSERT_EQ(expectedStdOutContents, stdOutContents);
    ASSERT_EQ(expectedStdErrContents, stdErrContents);
}

TEST_F(ApplicationTestFixture, Handle_HelpStrategy_HelpStringIsValid)
{
    const std::unique_ptr<cx::ICmdArgWorkflowStrategy> strategy = std::make_unique<cx::CmdArgHelpStrategy>();

    std::string stdOutContents, stdErrContents;

    ASSERT_EQ(std::string(), stdOutContents);
    ASSERT_EQ(std::string(), stdErrContents);

    strategy->Handle();

    stdOutContents = GetStdOutContents();
    stdErrContents = GetStdErrContents();

    const std::string expectedStdOutContents = "Usage: connectx [OPTION]...\n\n"
                                               "Possible arguments:\n"
                                               "--help        display this help and exit\n"
                                               "--version     output version information and exit\n"
                                               "\n"
                                               "Exit status:\n"
                                               " 0 if OK,\n"
                                               " 1 if problems.\n"
                                               "\n"
                                               "Connect X available at: <https://github.com/BobMorane22/connectx/>\n";

    const std::string expectedStdErrContents = "";

    ASSERT_EQ(expectedStdOutContents, stdOutContents);
    ASSERT_EQ(expectedStdErrContents, stdErrContents);
}

TEST_F(ApplicationTestFixture, Handle_VersionStrategy_VersionStringIsValid)
{
    const std::unique_ptr<cx::ICmdArgWorkflowStrategy> strategy = std::make_unique<cx::CmdArgVersionStrategy>();

    std::string stdOutContents, stdErrContents;

    ASSERT_EQ(std::string(), stdOutContents);
    ASSERT_EQ(std::string(), stdErrContents);

    strategy->Handle();

    stdOutContents = GetStdOutContents();
    stdErrContents = GetStdErrContents();

    // In this case we use a regex so that the test is independent of the version number. It only
    // depends on the syntax of the version number, which must remain constant across releases.
    const std::regex expectedStdOutContents{ "Connect X v\\d\\.\\d\\n"
                                             "\\n"
                                             "Copyright \\(C\\) 20\\d\\d Eric Poirier.\\n"
                                             "License GPLv3\\+: GNU GPL version 3 or later <gnu.org/licenses/gpl.html>.\\n"
                                             "This is free software: you are free to change and redistribute it.\\n"
                                             "There is NO WARRANTY, to the extent permitted by law.\\n"
                                             "\\n"
                                             "Written by Eric Poirier.\\n"};

    const std::string expectedStdErrContents = "";

    ASSERT_TRUE(std::regex_match(stdOutContents, expectedStdOutContents));
    ASSERT_EQ(expectedStdErrContents, stdErrContents);
}

TEST_F(ApplicationTestFixture, Handle_InvalidArgStrategy_ErrorPrinted)
{
    const std::unique_ptr<cx::ICmdArgWorkflowStrategy> strategy = std::make_unique<cx::CmdArgInvalidStrategy>("--invalid");

    std::string stdOutContents, stdErrContents;

    ASSERT_EQ(std::string(), stdOutContents);
    ASSERT_EQ(std::string(), stdErrContents);

    strategy->Handle();

    stdOutContents = GetStdOutContents();
    stdErrContents = GetStdErrContents();

    const std::string expectedStdOutContents = "";
    const std::string expectedStdErrContents = "Connect X: invalid option '--invalid'\n";

    ASSERT_EQ(expectedStdOutContents, stdOutContents);
    ASSERT_EQ(expectedStdErrContents, stdErrContents);
}
