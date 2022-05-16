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
 * @file ApplicationTests.cpp
 * @date 2019
 *
 *************************************************************************************************/

#include <cstdlib>
#include <memory>

#include <gtest/gtest.h>

#include <cxexec/Application.h>

#include "ApplicationTestFixture.h"

TEST_F(ApplicationTestFixtureStdErrStreamRedirector, /*DISABLED_*/Run_BadArgumentCount_ExitFailure)
{
    const int argc = 0;
    const char *argv[] = {"connectx"};

    auto modelRefs = GetModelReferences();
    auto app = std::make_unique<cx::Application>(argc, (char**)argv, modelRefs, GetLogger());

    EXPECT_EQ(app->Run(), EXIT_FAILURE);
}

TEST_F(ApplicationTestFixtureStdErrStreamRedirector, /*DISABLED_*/Run_BadArgument_ExitFailure)
{
    const int argc = 2;
    const char *argv[] = {"connectx", "--bad"};

    auto modelRefs = GetModelReferences();
    auto app = std::make_unique<cx::Application>(argc, (char**)argv, modelRefs, GetLogger());

    EXPECT_EQ(app->Run(), EXIT_FAILURE);
}

TEST_F(ApplicationTestFixtureStdOutStreamRedirector, /*DISABLED_*/Run_Help_ExitSuccess)
{
    const int argc = 2;
    const char *argv[] = {"connectx", "--help"};

    auto modelRefs = GetModelReferences();
    auto app = std::make_unique<cx::Application>(argc, (char**)argv, modelRefs, GetLogger());

    EXPECT_EQ(app->Run(), EXIT_SUCCESS);
}

TEST_F(ApplicationTestFixtureStdOutStreamRedirector, /*DISABLED_*/Run_Version_ExitSuccess)
{
    const int argc = 2;
    const char *argv[] = {"connectx", "--version"};

    auto modelRefs = GetModelReferences();
    auto app = std::make_unique<cx::Application>(argc, (char**)argv, modelRefs, GetLogger());
                                                                              
    EXPECT_EQ(app->Run(), EXIT_SUCCESS);
}

TEST_F(ApplicationTestFixtureStdOutStreamRedirector, /*DISABLED_*/Run_HelpAndVersion_ExitSuccess)
{
    const int argc = 3;
    const char *argv[] = {"connectx", "--help", "--version"};

    auto modelRefs = GetModelReferences();
    auto app = std::make_unique<cx::Application>(argc, (char**)argv, modelRefs, GetLogger());
                                                                              
    EXPECT_EQ(app->Run(), EXIT_SUCCESS);
}

TEST_F(ApplicationTestFixtureStdOutStreamRedirector, /*DISABLED_*/Run_VersionAndHelp_ExitSuccess)
{
    const int argc = 3;
    const char *argv[] = {"connectx", "--version", "--help"};

    auto modelRefs = GetModelReferences();
    auto app = std::make_unique<cx::Application>(argc, (char**)argv, modelRefs, GetLogger());

    EXPECT_EQ(app->Run(), EXIT_SUCCESS);
}

TEST_F(ApplicationTestFixtureStdOutStreamRedirector, /*DISABLED_*/Run_TwoManyValidArguments_ExitSuccess)
{
    const int argc = 4;
    const char *argv[] = {"connectx", "--help", "--version", "--help"};

    auto modelRefs = GetModelReferences();
    auto app = std::make_unique<cx::Application>(argc, (char**)argv, modelRefs, GetLogger());

    EXPECT_EQ(app->Run(), EXIT_SUCCESS);
}

TEST_F(ApplicationTestFixtureStdErrStreamRedirector, /*DISABLED_*/Run_MixedArguments_ExitFailure)
{
    const int argc = 4;
    const char *argv[] = {"connectx", "--version", "--bad", "--help"};

    auto modelRefs = GetModelReferences();
    auto app = std::make_unique<cx::Application>(argc, (char**)argv, modelRefs, GetLogger());

    EXPECT_EQ(app->Run(), EXIT_FAILURE);
}
