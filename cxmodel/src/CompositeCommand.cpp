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
 * @file CompositeCommand.cpp
 * @date 2022
 *
 *************************************************************************************************/

#include <cxinv/assertion.h>
#include <cxmodel/CommandCompletionStatus.h>
#include <cxmodel/CompositeCommand.h>

void cxmodel::CompositeCommand::Add(std::unique_ptr<cxmodel::ICommand> p_child)
{
    IF_PRECONDITION_NOT_MET_DO(p_child, return;);

    const size_t sizeBefore = m_children.size();

    m_children.push_back(std::move(p_child));

    const size_t sizeAfter = m_children.size();

    POSTCONDITION(sizeAfter == sizeBefore + 1u);
}

cxmodel::CommandCompletionStatus cxmodel::CompositeCommand::Execute()
{
    for(auto& child : m_children)
    {
        IF_CONDITION_NOT_MET_DO(child, continue;);
        const auto executionResult = child->Execute();

        if(executionResult != cxmodel::CommandCompletionStatus::SUCCESS)
        {
            ASSERT(executionResult != cxmodel::CommandCompletionStatus::FAILED_UNEXPECTED);
            return executionResult;
        }
    }

    return cxmodel::CommandCompletionStatus::SUCCESS;
}

void cxmodel::CompositeCommand::Undo()
{
    for(auto& child : m_children)
    {
        IF_CONDITION_NOT_MET_DO(child, continue;);
        child->Undo();
    }
}
