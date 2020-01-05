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
 * @file CommandStackTests.cpp
 * @date 2020
 *
 *************************************************************************************************/

#include <gtest/gtest.h>

#include "CommandAddTwoMock.h"
#include "CommandStackTestFixture.h"
#include "CommandTimesThreeMock.h"

TEST_F(CommandStackTestFixture, Add_ValidCommand_CommandAdded)
{
    double result{0.0};

    std::unique_ptr<cxmodel::ICommand> cmd{new CommandAddTwoMock{result}};
    GetCommandStack()->Add(std::move(cmd));

    ASSERT_FALSE(GetCommandStack()->IsEmpty());
    ASSERT_EQ(GetCommandStack()->GetNbCommands(), 1);
}

TEST_F(CommandStackTestFixture, Add_InvalidCommand_CommandNotAdded)
{
    double result{0.0};
    (void)result; // unused

    std::unique_ptr<cxmodel::ICommand> cmd;
    ASSERT_FALSE(cmd);

    GetCommandStack()->Add(std::move(cmd));

    ASSERT_TRUE(GetCommandStack()->IsEmpty());
}

TEST_F(CommandStackTestFixture, Add_ManyValidCommands_CommandsAdded)
{
    double result{0.0};

    for(size_t index = 0; index < 5; ++index)
    {
        std::unique_ptr<cxmodel::ICommand> cmd{new CommandAddTwoMock{result}};
        GetCommandStack()->Add(std::move(cmd));
    }

    ASSERT_FALSE(GetCommandStack()->IsEmpty());
    ASSERT_EQ(GetCommandStack()->GetNbCommands(), 5);
}

TEST_F(CommandStackTestFixture, Add_TooManyValidCommands_LastCommandIsLastInStack)
{
    double result{0.0};

    for(size_t index = 0; index < GetCommandStackSize(); ++index)
    {
        std::unique_ptr<cxmodel::ICommand> cmd{new CommandAddTwoMock{result}};
        cmd->Execute();
        GetCommandStack()->Add(std::move(cmd));
    }

    ASSERT_TRUE(GetCommandStack()->IsFull());
    ASSERT_EQ(GetCommandStack()->GetNbCommands(), GetCommandStackSize());
    ASSERT_EQ(result, 400.0);

    // Add one too many:
    std::unique_ptr<cxmodel::ICommand> cmd{new CommandTimesThreeMock{result}};
    cmd->Execute();
    GetCommandStack()->Add(std::move(cmd));

    ASSERT_TRUE(GetCommandStack()->IsFull());
    ASSERT_EQ(GetCommandStack()->GetNbCommands(), GetCommandStackSize());
    ASSERT_EQ(result, 1200.0);

    GetCommandStack()->Undo();

    ASSERT_TRUE(GetCommandStack()->IsFull());
    ASSERT_EQ(GetCommandStack()->GetNbCommands(), GetCommandStackSize());
    ASSERT_EQ(result, 400.0);
}

TEST_F(CommandStackTestFixture, Clear_SingleCommand_CommandCleared)
{
    double result{0.0};

    std::unique_ptr<cxmodel::ICommand> cmd{new CommandAddTwoMock{result}};
    GetCommandStack()->Add(std::move(cmd));

    ASSERT_FALSE(GetCommandStack()->IsEmpty());

    GetCommandStack()->Clear();

    ASSERT_TRUE(GetCommandStack()->IsEmpty());
}

TEST_F(CommandStackTestFixture, Clear_ManyCommands_CommandsCleared)
{
    double result{0.0};

    for(size_t index = 0; index < 5; ++index)
    {
        std::unique_ptr<cxmodel::ICommand> cmd{new CommandAddTwoMock{result}};
        GetCommandStack()->Add(std::move(cmd));
    }

    ASSERT_FALSE(GetCommandStack()->IsEmpty());

    GetCommandStack()->Clear();

    ASSERT_TRUE(GetCommandStack()->IsEmpty());
}

TEST_F(CommandStackTestFixture, Clear_NoCommand_NothingHappens)
{
    GetCommandStack()->Clear();

    ASSERT_TRUE(GetCommandStack()->IsEmpty());
}


TEST_F(CommandStackTestFixture, Undo_SingleCommand_CommandUndoed)
{
    double result{0.0};

    std::unique_ptr<cxmodel::ICommand> cmd{new CommandAddTwoMock{result}};
    cmd->Execute();

    ASSERT_EQ(result, 2.0);

    GetCommandStack()->Add(std::move(cmd));
    GetCommandStack()->Undo();

    ASSERT_EQ(result, 0.0);
}

TEST_F(CommandStackTestFixture, Undo_MultipleCommands_AllCommandsUndoed)
{
    double result{0.0};

    std::unique_ptr<cxmodel::ICommand> cmd1{new CommandAddTwoMock{result}};
    std::unique_ptr<cxmodel::ICommand> cmd2{new CommandTimesThreeMock{result}};
    std::unique_ptr<cxmodel::ICommand> cmd3{new CommandAddTwoMock{result}};
    cmd1->Execute();
    cmd2->Execute();
    cmd3->Execute();

    ASSERT_EQ(result, 8.0);

    GetCommandStack()->Add(std::move(cmd1));
    GetCommandStack()->Add(std::move(cmd2));
    GetCommandStack()->Add(std::move(cmd3));

    GetCommandStack()->Undo();
    GetCommandStack()->Undo();
    GetCommandStack()->Undo();

    ASSERT_EQ(result, 0.0);
}

TEST_F(CommandStackTestFixture, Undo_NoCommand_NothingHappens)
{
    GetCommandStack()->Undo();

    ASSERT_TRUE(GetCommandStack()->IsEmpty());
}

TEST_F(CommandStackTestFixture, DISABLED_Undo_TooManyUndoes_AllCommandsUndoed)
{
    ASSERT_TRUE(false);
}

TEST_F(CommandStackTestFixture, Redo_SingleCommand_CommandRedoed)
{
    double result{0.0};

    std::unique_ptr<cxmodel::ICommand> cmd{new CommandAddTwoMock{result}};
    cmd->Execute();

    ASSERT_EQ(result, 2.0);

    GetCommandStack()->Add(std::move(cmd));
    GetCommandStack()->Undo();
    GetCommandStack()->Redo();

    ASSERT_EQ(result, 2.0);
}

TEST_F(CommandStackTestFixture, Redo_MultipleCommands_AllCommandsRedoed)
{
    double result{0.0};

    std::unique_ptr<cxmodel::ICommand> cmd1{new CommandAddTwoMock{result}};
    std::unique_ptr<cxmodel::ICommand> cmd2{new CommandTimesThreeMock{result}};
    std::unique_ptr<cxmodel::ICommand> cmd3{new CommandAddTwoMock{result}};
    cmd1->Execute();
    cmd2->Execute();
    cmd3->Execute();

    ASSERT_EQ(result, 8.0);

    GetCommandStack()->Add(std::move(cmd1));
    GetCommandStack()->Add(std::move(cmd2));
    GetCommandStack()->Add(std::move(cmd3));

    GetCommandStack()->Undo();
    GetCommandStack()->Undo();
    GetCommandStack()->Undo();

    GetCommandStack()->Redo();
    GetCommandStack()->Redo();
    GetCommandStack()->Redo();

    ASSERT_EQ(result, 8.0);
}

TEST_F(CommandStackTestFixture, Redo_NoCommand_NothingHappens)
{
    GetCommandStack()->Redo();

    ASSERT_TRUE(GetCommandStack()->IsEmpty());
}


TEST_F(CommandStackTestFixture, DISABLED_Redo_TooManyRedoes_AllCommandsRedoed)
{
    ASSERT_TRUE(false);
}

TEST_F(CommandStackTestFixture, DISABLED_UndoRedo_SingleCommand_StateIsUnchaged)
{
    ASSERT_TRUE(false);
}

TEST_F(CommandStackTestFixture, DISABLED_UndoRedo_MultipleCommands_StateIsUnchaged)
{
    ASSERT_TRUE(false);
}
