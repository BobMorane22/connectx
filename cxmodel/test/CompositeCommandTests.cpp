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
class ErrorLeafCommandMock : public cxmodel::ICommand
{

public:

    explicit ErrorLeafCommandMock(cxmodel::CommandCompletionStatus p_errorStatus)
    {
        EXPECT_TRUE(p_errorStatus != cxmodel::CommandCompletionStatus::SUCCESS);
        m_errorStatus = p_errorStatus;
    }

    [[nodiscard]] cxmodel::CommandCompletionStatus Execute() override
    {
        return m_errorStatus;
    }

    void Undo() override
    {
        FAIL() << "Should not be called.";
    }

private:

    cxmodel::CommandCompletionStatus m_errorStatus;

};

// Mocks a command that returns a success.
class SuccessLeafCommandMock : public cxmodel::ICommand
{

public:

    [[nodiscard]] cxmodel::CommandCompletionStatus Execute() override
    {
        return cxmodel::CommandCompletionStatus::SUCCESS;
    }

    void Undo() override
    {
        FAIL() << "Should not be called.";
    }

};

} // namespace 

TEST(CompositeCommand, EmptyComposite_ExecuteCalled_SuccessReturned)
{
    cxmodel::CompositeCommand composite;
    ASSERT_TRUE(composite.Execute() == cxmodel::CommandCompletionStatus::SUCCESS);
}

TEST(CompositeCommand, Add_OneLeafCommand_CommandAdded)
{
    double total = 0.0;

    cxmodel::CompositeCommand composite;
    composite.Add(std::make_unique<CommandAddTwoMock>(total));

    ASSERT_TRUE(composite.Execute() == cxmodel::CommandCompletionStatus::SUCCESS);
    ASSERT_TRUE(total == 2.0);
}

TEST(CompositeCommand, Add_TwoLeafCommands_CommandsAdded)
{
    double total = 0.0;

    cxmodel::CompositeCommand composite;
    composite.Add(std::make_unique<CommandAddTwoMock>(total));
    composite.Add(std::make_unique<CommandAddTwoMock>(total));

    ASSERT_TRUE(composite.Execute() == cxmodel::CommandCompletionStatus::SUCCESS);
    ASSERT_TRUE(total == 4.0);
}

TEST(CompositeCommand, Add_ALeafAndAComposite_CommandsAdded)
{
    double total = 0.0;

    cxmodel::CompositeCommand topLevelComposite;

    auto subComposite = std::make_unique<cxmodel::CompositeCommand>();
    ASSERT_TRUE(subComposite);
    subComposite->Add(std::make_unique<CommandAddTwoMock>(total));
    subComposite->Add(std::make_unique<CommandAddTwoMock>(total));

    topLevelComposite.Add(std::move(subComposite));
    topLevelComposite.Add(std::make_unique<CommandAddTwoMock>(total));

    ASSERT_TRUE(topLevelComposite.Execute() == cxmodel::CommandCompletionStatus::SUCCESS);
    ASSERT_TRUE(total == 6.0);
}

TEST(CompositeCommand, Add_InvalidChild_NothingAddedAndAssert)
{
    cxmodel::CompositeCommand topLevelComposite;

    {
        cxunit::DisableStdStreamsRAII streamDisabler;

        topLevelComposite.Add(nullptr); 
        ASSERT_PRECONDITION_FAILED(streamDisabler);
    }
}

TEST(CompositeCommand, Execute_LeafCommandFails_ReturnsError)
{
    // Expected fail:
    {
        cxmodel::CompositeCommand composite;
        composite.Add(std::make_unique<ErrorLeafCommandMock>(cxmodel::CommandCompletionStatus::FAILED_EXPECTED));

        ASSERT_TRUE(composite.Execute() == cxmodel::CommandCompletionStatus::FAILED_EXPECTED);
    }
    // Unexpected fail:
    {
        cxmodel::CompositeCommand composite;
        composite.Add(std::make_unique<ErrorLeafCommandMock>(cxmodel::CommandCompletionStatus::FAILED_UNEXPECTED));

        cxunit::DisableStdStreamsRAII streamDisabler;
        ASSERT_TRUE(composite.Execute() == cxmodel::CommandCompletionStatus::FAILED_UNEXPECTED);
        ASSERT_ASSERTION_FAILED(streamDisabler);
    }
}

TEST(CompositeCommand, Execute_CompositeCommandFails_ReturnsError)
{
    // Expected fail:
    {
        cxmodel::CompositeCommand topLevelComposite;

        auto subComposite = std::make_unique<cxmodel::CompositeCommand>();
        ASSERT_TRUE(subComposite);
        subComposite->Add(std::make_unique<SuccessLeafCommandMock>());
        subComposite->Add(std::make_unique<ErrorLeafCommandMock>(cxmodel::CommandCompletionStatus::FAILED_EXPECTED));

        topLevelComposite.Add(std::move(subComposite));

        ASSERT_TRUE(topLevelComposite.Execute() == cxmodel::CommandCompletionStatus::FAILED_EXPECTED);
    }
    // Unexpected fail:
    {
        cxmodel::CompositeCommand topLevelComposite;

        auto subComposite = std::make_unique<cxmodel::CompositeCommand>();
        ASSERT_TRUE(subComposite);
        subComposite->Add(std::make_unique<SuccessLeafCommandMock>());
        subComposite->Add(std::make_unique<ErrorLeafCommandMock>(cxmodel::CommandCompletionStatus::FAILED_UNEXPECTED));

        topLevelComposite.Add(std::move(subComposite));

        cxunit::DisableStdStreamsRAII streamDisabler;
        ASSERT_TRUE(topLevelComposite.Execute() == cxmodel::CommandCompletionStatus::FAILED_UNEXPECTED);
        ASSERT_ASSERTION_FAILED(streamDisabler);
    }
}
