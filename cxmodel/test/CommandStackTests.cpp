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

#include <cxmodel/CommandCompletionStatus.h>

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

    {
        // Usually, the validity of the command should be check before feeding
        // it to Execute. Here, we do not check it for unit testing purposes.
        // The call to execute will assert and we need to silence it.
        cxunit::DisableStdStreamsRAII streamDisabler;
        GetCommandStack()->Execute(std::move(cmd));
    }

    ASSERT_TRUE(GetCommandStack()->IsEmpty());
}

TEST_F(CommandStackTestFixture, /*DISABLED_*/Execute_CommandReturningSuccess_CommandAddedToStack)
{
    class SuccessCommand : public cxmodel::ICommand
    {
        [[nodiscard]] cxmodel::CommandCompletionStatus Execute() override {return cxmodel::CommandCompletionStatus::SUCCESS;}
        void Undo() override {}
    };

    ASSERT_TRUE(GetCommandStack()->IsEmpty());
    ASSERT_TRUE(GetCommandStack()->Execute(std::make_unique<SuccessCommand>()) == cxmodel::CommandCompletionStatus::SUCCESS);
    ASSERT_TRUE(GetCommandStack()->GetNbCommands() == 1u);
}

TEST_F(CommandStackTestFixture, /*DISABLED_*/Execute_CommandReturningExpectedError_CommandNotAddedToStack)
{
    class ExpectedErrorCommand : public cxmodel::ICommand
    {
        [[nodiscard]] cxmodel::CommandCompletionStatus Execute() override {return cxmodel::CommandCompletionStatus::FAILED_EXPECTED;}
        void Undo() override {}
    };

    ASSERT_TRUE(GetCommandStack()->IsEmpty());
    ASSERT_TRUE(GetCommandStack()->Execute(std::make_unique<ExpectedErrorCommand>()) == cxmodel::CommandCompletionStatus::FAILED_EXPECTED);
    ASSERT_TRUE(GetCommandStack()->IsEmpty());
}

TEST_F(CommandStackTestFixtureStdErrStreamRedirector, /*DISABLED_*/Execute_CommandReturningUnexpectedError_CommandNotAddedToStackAndAsserts)
{
    class UnexpectedErrorCommand : public cxmodel::ICommand
    {
        [[nodiscard]] cxmodel::CommandCompletionStatus Execute() override {return cxmodel::CommandCompletionStatus::FAILED_UNEXPECTED;}
        void Undo() override {}
    };

    ASSERT_TRUE(GetCommandStack()->IsEmpty());
    ASSERT_TRUE(GetCommandStack()->Execute(std::make_unique<UnexpectedErrorCommand>()) == cxmodel::CommandCompletionStatus::FAILED_UNEXPECTED);
    ASSERT_TRUE(GetCommandStack()->IsEmpty());

    ASSERT_ASSERTION_FAILED(*this);
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

TEST_F(CommandStackTestFixture, /*DISABLED_*/CanUndo_NoCommandExecuted_ReturnsFalse)
{
    ASSERT_FALSE(GetCommandStack()->CanUndo());
}

TEST_F(CommandStackTestFixture, /*DISABLED_*/CanUndo_SomeCommandExecuted_ReturnsTrue)
{
    double result{0.0};

    GetCommandStack()->Execute(std::make_unique<CommandAddTwoMock>(result));

    ASSERT_TRUE(GetCommandStack()->CanUndo());
}

TEST_F(CommandStackTestFixture, /*DISABLED_*/CanUndo_AllUndoed_ReturnsFalse)
{
    double result{0.0};

    GetCommandStack()->Execute(std::make_unique<CommandAddTwoMock>(result));
    GetCommandStack()->Undo();

    ASSERT_FALSE(GetCommandStack()->CanUndo());
}

TEST_F(CommandStackTestFixture, /*DISABLED_*/CanRedo_NoCommandUndoed_ReturnsFalse)
{
    double result{0.0};

    GetCommandStack()->Execute(std::make_unique<CommandAddTwoMock>(result));

    ASSERT_FALSE(GetCommandStack()->CanRedo());
}

TEST_F(CommandStackTestFixture, /*DISABLED_*/CanRedo_SomeCommandsUndoed_ReturnsTrue)
{
    double result{0.0};

    GetCommandStack()->Execute(std::make_unique<CommandAddTwoMock>(result));
    GetCommandStack()->Execute(std::make_unique<CommandAddTwoMock>(result));
    GetCommandStack()->Undo();

    ASSERT_TRUE(GetCommandStack()->CanRedo());
}

TEST_F(CommandStackTestFixture, /*DISABLED_*/CanRedo_SomeMoreCommandsUndoed_ReturnsTrue)
{
    double result{0.0};

    GetCommandStack()->Execute(std::make_unique<CommandAddTwoMock>(result));
    GetCommandStack()->Execute(std::make_unique<CommandAddTwoMock>(result));
    GetCommandStack()->Execute(std::make_unique<CommandAddTwoMock>(result));
    GetCommandStack()->Undo();

    ASSERT_TRUE(GetCommandStack()->CanRedo());
}

TEST_F(CommandStackTestFixture, /*DISABLED_*/CanRedo_AllCommandsUndoed_ReturnsTrue)
{
    double result{0.0};

    GetCommandStack()->Execute(std::make_unique<CommandAddTwoMock>(result));
    GetCommandStack()->Execute(std::make_unique<CommandAddTwoMock>(result));
    GetCommandStack()->Undo();
    GetCommandStack()->Undo();

    ASSERT_TRUE(GetCommandStack()->CanRedo());
}
