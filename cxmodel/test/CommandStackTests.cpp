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

TEST_F(CommandStackTestFixture, /*DISABLED_*/Execute_ValidCommand_CommandAdded)
{
    double result{0.0};

    GetCommandStack()->Execute(std::make_unique<CommandAddTwoMock>(result));

    ASSERT_FALSE(GetCommandStack()->IsEmpty());
    ASSERT_EQ(GetCommandStack()->GetNbCommands(), 1);
}

TEST_F(CommandStackTestFixture, /*DISABLED_*/Execute_InvalidCommand_CommandNotAdded)
{
    double result{0.0};
    (void)result; // unused

    std::unique_ptr<cxmodel::ICommand> cmd;
    ASSERT_FALSE(cmd);

    GetCommandStack()->Execute(std::move(cmd));

    ASSERT_TRUE(GetCommandStack()->IsEmpty());
}

TEST_F(CommandStackTestFixture, /*DISABLED_*/Execute_ManyValidCommands_CommandsAdded)
{
    double result{0.0};

    for(size_t index = 0; index < 5; ++index)
    {
        GetCommandStack()->Execute(std::make_unique<CommandAddTwoMock>(result));
    }

    ASSERT_FALSE(GetCommandStack()->IsEmpty());
    ASSERT_EQ(GetCommandStack()->GetNbCommands(), 5);
}

TEST_F(CommandStackTestFixture, /*DISABLED_*/Execute_TooManyValidCommands_LastCommandIsLastInStack)
{
    double result{0.0};

    for(size_t index = 0; index < GetCommandStackSize(); ++index)
    {
        GetCommandStack()->Execute(std::make_unique<CommandAddTwoMock>(result));
    }

    ASSERT_TRUE(GetCommandStack()->IsFull());
    ASSERT_EQ(GetCommandStack()->GetNbCommands(), GetCommandStackSize());
    ASSERT_EQ(result, 400.0);

    // Add one too many:
    GetCommandStack()->Execute(std::make_unique<CommandTimesThreeMock>(result));

    ASSERT_TRUE(GetCommandStack()->IsFull());
    ASSERT_EQ(GetCommandStack()->GetNbCommands(), GetCommandStackSize());
    ASSERT_EQ(result, 1200.0);

    GetCommandStack()->Undo();

    ASSERT_TRUE(GetCommandStack()->IsFull());
    ASSERT_EQ(GetCommandStack()->GetNbCommands(), GetCommandStackSize());
    ASSERT_EQ(result, 400.0);
}

TEST_F(CommandStackTestFixture, /*DISABLED_*/Clear_SingleCommand_CommandCleared)
{
    double result{0.0};

    GetCommandStack()->Execute(std::make_unique<CommandAddTwoMock>(result));

    ASSERT_FALSE(GetCommandStack()->IsEmpty());

    GetCommandStack()->Clear();

    ASSERT_TRUE(GetCommandStack()->IsEmpty());
}

TEST_F(CommandStackTestFixture, /*DISABLED_*/Clear_ManyCommands_CommandsCleared)
{
    double result{0.0};

    for(size_t index = 0; index < 5; ++index)
    {
        GetCommandStack()->Execute(std::make_unique<CommandAddTwoMock>(result));
    }

    ASSERT_FALSE(GetCommandStack()->IsEmpty());
    GetCommandStack()->Clear();
    ASSERT_TRUE(GetCommandStack()->IsEmpty());
}

TEST_F(CommandStackTestFixture, /*DISABLED_*/Clear_NoCommand_NothingHappens)
{
    ASSERT_TRUE(GetCommandStack()->IsEmpty());
    GetCommandStack()->Clear();
    ASSERT_TRUE(GetCommandStack()->IsEmpty());
}


TEST_F(CommandStackTestFixture, /*DISABLED_*/Undo_SingleCommand_CommandUndoed)
{
    double result{0.0};

    GetCommandStack()->Execute(std::make_unique<CommandAddTwoMock>(result));

    ASSERT_EQ(result, 2.0);

    GetCommandStack()->Undo();

    ASSERT_EQ(result, 0.0);
}

TEST_F(CommandStackTestFixture, /*DISABLED_*/Undo_MultipleCommands_AllCommandsUndoed)
{
    double result{0.0};

    GetCommandStack()->Execute(std::make_unique<CommandAddTwoMock>(result));
    GetCommandStack()->Execute(std::make_unique<CommandTimesThreeMock>(result));
    GetCommandStack()->Execute(std::make_unique<CommandAddTwoMock>(result));

    ASSERT_EQ(result, 8.0);

    GetCommandStack()->Undo();
    GetCommandStack()->Undo();
    GetCommandStack()->Undo();

    ASSERT_EQ(result, 0.0);
}

TEST_F(CommandStackTestFixture, /*DISABLED_*/Undo_NoCommand_NothingHappens)
{
    ASSERT_TRUE(GetCommandStack()->IsEmpty());
    GetCommandStack()->Undo();
    ASSERT_TRUE(GetCommandStack()->IsEmpty());
}

TEST_F(CommandStackTestFixture, /*DISABLED_*/Undo_TooManyUndoes_AllCommandsUndoed)
{
    double result{0.0};

    GetCommandStack()->Execute(std::make_unique<CommandAddTwoMock>(result));
    GetCommandStack()->Execute(std::make_unique<CommandTimesThreeMock>(result));

    ASSERT_EQ(result, 6.0);

    GetCommandStack()->Undo();
    GetCommandStack()->Undo();
    GetCommandStack()->Undo();

    ASSERT_EQ(result, 0.0);
}

TEST_F(CommandStackTestFixture, /*DISABLED_*/Redo_SingleCommand_CommandRedoed)
{
    double result{0.0};

    GetCommandStack()->Execute(std::make_unique<CommandAddTwoMock>(result));

    ASSERT_EQ(result, 2.0);

    GetCommandStack()->Undo();
    GetCommandStack()->Redo();

    ASSERT_EQ(result, 2.0);
}

TEST_F(CommandStackTestFixture, /*DISABLED_*/Redo_MultipleCommands_AllCommandsRedoed)
{
    double result{0.0};

    GetCommandStack()->Execute(std::make_unique<CommandAddTwoMock>(result));
    GetCommandStack()->Execute(std::make_unique<CommandTimesThreeMock>(result));
    GetCommandStack()->Execute(std::make_unique<CommandAddTwoMock>(result));

    ASSERT_EQ(result, 8.0);

    GetCommandStack()->Undo();
    GetCommandStack()->Undo();
    GetCommandStack()->Undo();

    GetCommandStack()->Redo();
    GetCommandStack()->Redo();
    GetCommandStack()->Redo();

    ASSERT_EQ(result, 8.0);
}

TEST_F(CommandStackTestFixture, /*DISABLED_*/Redo_NoCommand_NothingHappens)
{
    ASSERT_TRUE(GetCommandStack()->IsEmpty());
    GetCommandStack()->Redo();
    ASSERT_TRUE(GetCommandStack()->IsEmpty());
}

TEST_F(CommandStackTestFixture, /*DISABLED_*/Redo_TooManyRedoes_AllCommandsRedoed)
{
    double result{0.0};

    GetCommandStack()->Execute(std::make_unique<CommandAddTwoMock>(result));
    GetCommandStack()->Execute(std::make_unique<CommandTimesThreeMock>(result));

    ASSERT_EQ(result, 6.0);

    GetCommandStack()->Undo();
    GetCommandStack()->Undo();
    GetCommandStack()->Redo();
    GetCommandStack()->Redo();
    GetCommandStack()->Redo();

    ASSERT_EQ(result, 6.0);
}

TEST_F(CommandStackTestFixture, /*DISABLED_*/UndoRedo_SingleCommand_StateIsUnchaged)
{
    double result{0.0};

    GetCommandStack()->Execute(std::make_unique<CommandAddTwoMock>(result));

    ASSERT_EQ(result, 2.0);

    GetCommandStack()->Undo();
    GetCommandStack()->Redo();

    ASSERT_EQ(result, 2.0);
}

TEST_F(CommandStackTestFixture, /*DISABLED_*/UndoRedo_CommandExecuteedInBetween_RedoHasNoEffect)
{
    double result{0.0};

    GetCommandStack()->Execute(std::make_unique<CommandAddTwoMock>(result));
    GetCommandStack()->Execute(std::make_unique<CommandTimesThreeMock>(result));
    GetCommandStack()->Execute(std::make_unique<CommandAddTwoMock>(result));

    // Undo last command
    GetCommandStack()->Undo();

    ASSERT_EQ(GetCommandStack()->GetNbCommands(), 3);
    ASSERT_EQ(result, 6.0);

    // Overwrite it with a new command:
    GetCommandStack()->Execute(std::make_unique<CommandTimesThreeMock>(result));

    ASSERT_EQ(GetCommandStack()->GetNbCommands(), 3);
    ASSERT_EQ(result, 18.0);
}
