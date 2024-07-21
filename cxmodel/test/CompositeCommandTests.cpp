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
 * @file CompositeCommandTests.cpp
 * @date 2022
 *
 *************************************************************************************************/

#include <gtest/gtest.h>

#include <cxunit/DisableStdStreamsRAII.h>
#include <cxmodel/CommandCompletionStatus.h>
#include <cxmodel/CompositeCommand.h>

#include "CommandAddTwoMock.h"

namespace
{

// Mocks a command that returns an error.
class ErrorLeafCommandMock : public cx::model::ICommand
{

public:

    explicit ErrorLeafCommandMock(cx::model::CommandCompletionStatus p_errorStatus)
    {
        EXPECT_TRUE(p_errorStatus != cx::model::CommandCompletionStatus::SUCCESS);
        m_errorStatus = p_errorStatus;
    }

    [[nodiscard]] cx::model::CommandCompletionStatus Execute() override
    {
        return m_errorStatus;
    }

    void Undo() override
    {
        FAIL() << "Should not be called.";
    }

private:

    cx::model::CommandCompletionStatus m_errorStatus;
};

// Mocks a command that returns a success.
class SuccessLeafCommandMock : public cx::model::ICommand
{

public:

    [[nodiscard]] cx::model::CommandCompletionStatus Execute() override
    {
        return cx::model::CommandCompletionStatus::SUCCESS;
    }

    void Undo() override
    {
        FAIL() << "Should not be called.";
    }
};

// Mocks a command that appends a string to another on undo.
class StringAppenderCommandMock : public cx::model::ICommand
{

public:

    StringAppenderCommandMock(const std::string& p_stringToAppend, std::string& p_stringToAppendTo)
    : m_stringToAppend{p_stringToAppend}
    , m_stringToAppendTo{p_stringToAppendTo}
    {
    }

    [[nodiscard]] cx::model::CommandCompletionStatus Execute() override
    {
        return cx::model::CommandCompletionStatus::SUCCESS;
    }

    void Undo() override
    {
        m_stringToAppendTo += m_stringToAppend;
    }

private:

    std::string m_stringToAppend;
    std::string& m_stringToAppendTo;
};

} // namespace 

TEST(CompositeCommand, /*DISABLED_*/EmptyComposite_ExecuteCalled_SuccessReturned)
{
    cx::model::CompositeCommand composite;
    ASSERT_TRUE(composite.Execute() == cx::model::CommandCompletionStatus::SUCCESS);
}

TEST(CompositeCommand, /*DISABLED_*/Add_OneLeafCommand_CommandAdded)
{
    double total = 0.0;

    cx::model::CompositeCommand composite;
    composite.Add(std::make_unique<CommandAddTwoMock>(total));

    ASSERT_TRUE(composite.Execute() == cx::model::CommandCompletionStatus::SUCCESS);
    ASSERT_TRUE(total == 2.0);
}

TEST(CompositeCommand, /*DISABLED_*/Add_TwoLeafCommands_CommandsAdded)
{
    double total = 0.0;

    cx::model::CompositeCommand composite;
    composite.Add(std::make_unique<CommandAddTwoMock>(total));
    composite.Add(std::make_unique<CommandAddTwoMock>(total));

    ASSERT_TRUE(composite.Execute() == cx::model::CommandCompletionStatus::SUCCESS);
    ASSERT_TRUE(total == 4.0);
}

TEST(CompositeCommand, /*DISABLED_*/Add_ALeafAndAComposite_CommandsAdded)
{
    double total = 0.0;

    cx::model::CompositeCommand topLevelComposite;

    auto subComposite = std::make_unique<cx::model::CompositeCommand>();
    ASSERT_TRUE(subComposite);
    subComposite->Add(std::make_unique<CommandAddTwoMock>(total));
    subComposite->Add(std::make_unique<CommandAddTwoMock>(total));

    topLevelComposite.Add(std::move(subComposite));
    topLevelComposite.Add(std::make_unique<CommandAddTwoMock>(total));

    ASSERT_TRUE(topLevelComposite.Execute() == cx::model::CommandCompletionStatus::SUCCESS);
    ASSERT_TRUE(total == 6.0);
}

TEST(CompositeCommand, /*DISABLED_*/Add_InvalidChild_NothingAddedAndAssert)
{
    cx::model::CompositeCommand topLevelComposite;

    {
        cx::unit::DisableStdStreamsRAII streamDisabler;

        topLevelComposite.Add(nullptr); 
        ASSERT_PRECONDITION_FAILED(streamDisabler);
    }
}

TEST(CompositeCommand, /*DISABLED_*/Execute_LeafCommandFails_ReturnsError)
{
    // Expected fail:
    {
        cx::model::CompositeCommand composite;
        composite.Add(std::make_unique<ErrorLeafCommandMock>(cx::model::CommandCompletionStatus::FAILED_EXPECTED));

        ASSERT_TRUE(composite.Execute() == cx::model::CommandCompletionStatus::FAILED_EXPECTED);
    }
    // Unexpected fail:
    {
        cx::model::CompositeCommand composite;
        composite.Add(std::make_unique<ErrorLeafCommandMock>(cx::model::CommandCompletionStatus::FAILED_UNEXPECTED));

        cx::unit::DisableStdStreamsRAII streamDisabler;
        ASSERT_TRUE(composite.Execute() == cx::model::CommandCompletionStatus::FAILED_UNEXPECTED);
        ASSERT_ASSERTION_FAILED(streamDisabler);
    }
}

TEST(CompositeCommand, /*DISABLED_*/Execute_CompositeCommandFails_ReturnsError)
{
    // Expected fail:
    {
        cx::model::CompositeCommand topLevelComposite;

        auto subComposite = std::make_unique<cx::model::CompositeCommand>();
        ASSERT_TRUE(subComposite);
        subComposite->Add(std::make_unique<SuccessLeafCommandMock>());
        subComposite->Add(std::make_unique<ErrorLeafCommandMock>(cx::model::CommandCompletionStatus::FAILED_EXPECTED));

        topLevelComposite.Add(std::move(subComposite));

        ASSERT_TRUE(topLevelComposite.Execute() == cx::model::CommandCompletionStatus::FAILED_EXPECTED);
    }
    // Unexpected fail:
    {
        cx::model::CompositeCommand topLevelComposite;

        auto subComposite = std::make_unique<cx::model::CompositeCommand>();
        ASSERT_TRUE(subComposite);
        subComposite->Add(std::make_unique<SuccessLeafCommandMock>());
        subComposite->Add(std::make_unique<ErrorLeafCommandMock>(cx::model::CommandCompletionStatus::FAILED_UNEXPECTED));

        topLevelComposite.Add(std::move(subComposite));

        cx::unit::DisableStdStreamsRAII streamDisabler;
        ASSERT_TRUE(topLevelComposite.Execute() == cx::model::CommandCompletionStatus::FAILED_UNEXPECTED);
        ASSERT_ASSERTION_FAILED(streamDisabler);
    }
}

TEST(CompositeCommand, /*DISABLED_*/Undo_ValidCommand_UndoCompleted)
{
    double total = 0.0;

    cx::model::CompositeCommand composite;
    composite.Add(std::make_unique<CommandAddTwoMock>(total));

    ASSERT_TRUE(composite.Execute() == cx::model::CommandCompletionStatus::SUCCESS);
    ASSERT_TRUE(total == 2.0);

    composite.Undo();
    ASSERT_TRUE(total == 0.0);
}

TEST(CompositeCommand, /*DISABLED_*/Undo_ValidCommands_UndoCompletedInReverseOrder)
{
    std::string result;

    cx::model::CompositeCommand composite;
    composite.Add(std::make_unique<StringAppenderCommandMock>("One", result));
    composite.Add(std::make_unique<StringAppenderCommandMock>("Two", result));

    ASSERT_TRUE(result.empty());
    composite.Undo();
    ASSERT_TRUE(result == "TwoOne");
}
