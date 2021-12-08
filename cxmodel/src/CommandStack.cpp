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
 * @file CommandStack.cpp
 * @date 2020
 *
 *************************************************************************************************/

#include <iostream>

#include <cxinv/assertion.h>
#include <cxmodel/CommandStack.h>

cxmodel::CommandStack::CommandStack(const size_t p_capacity)
 : m_endPosition{p_capacity - 1}
 , m_currentPosition{0}
 , m_allCmdUndoed{false}
{
    PRECONDITION(p_capacity > 1);

    m_commands.reserve(p_capacity);

    POSTCONDITION(m_endPosition > 1);

    CheckInvariants();
}

void cxmodel::CommandStack::Execute(std::unique_ptr<cxmodel::ICommand>&& p_newCommand)
{
    PRECONDITION(p_newCommand != nullptr);

    if(!p_newCommand)
    {
        return;
    }

    if(NoCommandUndoed())
    {
        if(IsFull())
        {
            // We remove the oldest command (front) and add the new one
            // at the end (back):
            m_commands.erase(m_commands.cbegin());
            m_commands.push_back(std::move(p_newCommand));

            // We remove one to make sure the new command can be executed:
            m_currentPosition = m_commands.size() - 1;
        }
        else
        {
            m_commands.push_back(std::move(p_newCommand));
        }
    }
    else if(SomeCommandUndoed())
    {
        // Some commands were undoed and never redoed before new ones
        // were added. In this case, we strip all previously undoed commands.
        // We will forget about them and replace them by the new addedcommand:
        m_commands.erase(m_commands.cbegin() + m_currentPosition,
                         m_commands.cend());

        m_currentPosition = m_commands.size();

        // Add the new command:
        m_commands.push_back(std::move(p_newCommand));
    }

    // At this point a new command was added. We execute it:
    if(m_currentPosition < m_commands.size())
    {
        ++m_currentPosition;
        m_commands.back()->Execute();
    }

    CheckInvariants();
}

void cxmodel::CommandStack::Clear()
{
    m_commands.clear();
    m_currentPosition = 0;
    m_allCmdUndoed = false;

    POSTCONDITION(m_commands.size() == 0);

    CheckInvariants();
}

void cxmodel::CommandStack::Undo()
{
    if(m_commands.empty())
    {
        return;
    }

    if(m_currentPosition == 0)
    {
        return;
    }

    if(m_currentPosition > 0)
    {
        --m_currentPosition;
        m_commands[m_currentPosition]->Undo();
    }

    CheckInvariants();
}

void cxmodel::CommandStack::Redo()
{
    if(m_commands.empty())
    {
        return;
    }

    if(m_currentPosition == m_commands.size())
    {
        return;
    }

    if(m_currentPosition < m_commands.size())
    {
        ++m_currentPosition;
        m_commands[m_currentPosition - 1]->Execute();
    }

    CheckInvariants();
}

bool cxmodel::CommandStack::CanUndo() const
{
    return !IsEmpty() && m_currentPosition > 0;
}

bool cxmodel::CommandStack::CanRedo() const
{
    return !IsEmpty() && m_currentPosition < GetLastCommandPosition() + 1;
}

bool cxmodel::CommandStack::IsEmpty() const
{
    return m_commands.empty();
}

bool cxmodel::CommandStack::IsFull() const
{
    return m_endPosition == GetLastCommandPosition();
}

size_t cxmodel::CommandStack::GetNbCommands() const
{
    return m_commands.size();
}

size_t cxmodel::CommandStack::GetLastCommandPosition() const
{
    return m_commands.size() - 1;
}

bool cxmodel::CommandStack::NoCommandUndoed() const
{
    return m_currentPosition == m_commands.size();
}

bool cxmodel::CommandStack::SomeCommandUndoed() const
{
    return m_currentPosition < m_commands.size();
}

void cxmodel::CommandStack::CheckInvariants()
{
    INVARIANT(m_endPosition > 1);
}
