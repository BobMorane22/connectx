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
 * @file CommandTests.cpp
 * @date 2020
 *
 *************************************************************************************************/

#include <memory>

#include <gtest/gtest.h>

#include <CommandIncrementByOne.h>
#include <CommandReinitialize.h>

TEST(Commands, CommandIncrementByOne_Execute_IncrementedByOne)
{
    unsigned int valueToIncrement = 0u;
    std::unique_ptr<cxmodel::ICommand> cmd = std::make_unique<cxmodel::CommandIncrementByOne>(valueToIncrement);
    ASSERT_TRUE(cmd);

    ASSERT_EQ(valueToIncrement, 0u);

    cmd->Execute();

    ASSERT_EQ(valueToIncrement, 1u);
}

TEST(Commands, CommandIncrementByOne_Undo_DecrementedByOne)
{
    unsigned int valueToIncrement = 0u;
    std::unique_ptr<cxmodel::ICommand> cmd = std::make_unique<cxmodel::CommandIncrementByOne>(valueToIncrement);
    ASSERT_TRUE(cmd);

    cmd->Execute();

    ASSERT_EQ(valueToIncrement, 1u);

    cmd->Undo();

    ASSERT_EQ(valueToIncrement, 0u);
}

TEST(Commands, CommandReinitialize_Execute_Reinitialized)
{
    unsigned int valueToReinitialize = 1u;
    constexpr unsigned int REINIT_VALUE = 0u;
    std::unique_ptr<cxmodel::ICommand> cmd = std::make_unique<cxmodel::CommandReinitialize>(REINIT_VALUE, valueToReinitialize, valueToReinitialize);
    ASSERT_TRUE(cmd);

    ASSERT_EQ(valueToReinitialize, 1u);

    cmd->Execute();

    ASSERT_EQ(valueToReinitialize, 0u);
}

TEST(Commands, CommandReinitialize_Undo_Unreinitialized)
{
    unsigned int valueToReinitialize = 1u;
    constexpr unsigned int REINIT_VALUE = 0u;
    std::unique_ptr<cxmodel::ICommand> cmd = std::make_unique<cxmodel::CommandReinitialize>(REINIT_VALUE, valueToReinitialize, valueToReinitialize);
    ASSERT_TRUE(cmd);

    cmd->Execute();

    ASSERT_EQ(valueToReinitialize, 0u);

    cmd->Undo();

    ASSERT_EQ(valueToReinitialize, 1u);
}
