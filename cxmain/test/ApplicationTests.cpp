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

#include <Application.h>
#include <ApplicationTestFixture.h>


TEST_F(ApplicationTestFixture, Run_StandardCase_ExitSuccess)
{
    const int argc = 1;
    char const *argv[] = {"connectx"};

    std::unique_ptr<cx::IApplication> app = std::make_unique<cx::Application>(argc, argv);

    EXPECT_EQ(app->Run(), EXIT_SUCCESS);
}

TEST_F(ApplicationTestFixture, Run_BadArgumentCount_ExitFailure)
{
    const int argc = 0;
    char const *argv[] = {"connectx"};

    std::unique_ptr<cx::IApplication> app = std::make_unique<cx::Application>(argc, argv);

    EXPECT_EQ(app->Run(), EXIT_FAILURE);
}

TEST_F(ApplicationTestFixture, Run_BadArgument_ExitFailure)
{
    const int argc = 2;
    char const *argv[] = {"connectx", "--bad"};

    std::unique_ptr<cx::IApplication> app = std::make_unique<cx::Application>(argc, argv);

    EXPECT_EQ(app->Run(), EXIT_FAILURE);
}

TEST_F(ApplicationTestFixture, Run_Help_ExitSuccess)
{
    const int argc = 2;
    char const *argv[] = {"connectx", "--help"};

    std::unique_ptr<cx::IApplication> app = std::make_unique<cx::Application>(argc, argv);

    EXPECT_EQ(app->Run(), EXIT_SUCCESS);
}

TEST_F(ApplicationTestFixture, Run_Version_ExitSuccess)
{
    const int argc = 2;
    char const *argv[] = {"connectx", "--version"};

    std::unique_ptr<cx::IApplication> app = std::make_unique<cx::Application>(argc, argv);

    EXPECT_EQ(app->Run(), EXIT_SUCCESS);
}

TEST_F(ApplicationTestFixture, Run_HelpAndVersion_ExitSuccess)
{
    const int argc = 3;
    char const *argv[] = {"connectx", "--help", "--version"};

    std::unique_ptr<cx::IApplication> app = std::make_unique<cx::Application>(argc, argv);

    EXPECT_EQ(app->Run(), EXIT_SUCCESS);
}

TEST_F(ApplicationTestFixture, Run_VersionAndHelp_ExitSuccess)
{
    const int argc = 3;
    char const *argv[] = {"connectx", "--version", "--help"};

    std::unique_ptr<cx::IApplication> app = std::make_unique<cx::Application>(argc, argv);

    EXPECT_EQ(app->Run(), EXIT_SUCCESS);
}

TEST_F(ApplicationTestFixture, Run_TwoManyValidArguments_ExitSuccess)
{
    const int argc = 4;
    char const *argv[] = {"connectx", "--help", "--version", "--help"};

    std::unique_ptr<cx::IApplication> app = std::make_unique<cx::Application>(argc, argv);

    EXPECT_EQ(app->Run(), EXIT_SUCCESS);
}

TEST_F(ApplicationTestFixture, Run_MixedArguments_ExitFailure)
{
    const int argc = 4;
    char const *argv[] = {"connectx", "--version", "--bad", "--help"};

    std::unique_ptr<cx::IApplication> app = std::make_unique<cx::Application>(argc, argv);

    EXPECT_EQ(app->Run(), EXIT_FAILURE);
}
