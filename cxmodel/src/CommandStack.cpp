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

#include <cxinv/include/assertion.h>

#include <CommandStack.h>

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

void cxmodel::CommandStack::Add(std::unique_ptr<cxmodel::ICommand>&& p_command)
{
    PRECONDITION(p_command != nullptr);

    if(!p_command)
    {
        return;
    }

    if(IsFull() && AreNoCommandUndoed())
    {
        m_commands.erase(m_commands.cbegin());
        m_commands.push_back(std::move(p_command));
    }
    else if(!IsFull() && AreNoCommandUndoed())
    {
        m_commands.push_back(std::move(p_command));

        // If this is the first added command, the current position
        // is still 0.
        if(m_commands.size() != 1)
        {
            ++m_currentPosition;
        }
    }
    else
    {
        // Strip all previously undoed commands:
        m_commands.erase(m_commands.cbegin() + m_currentPosition,
                         m_commands.cend());

        m_commands.shrink_to_fit();

        // Add the command:
        m_commands.push_back(std::move(p_command));
        ++m_currentPosition;
    }

    CheckInvariants();
}

void cxmodel::CommandStack::Clear()
{
    m_commands.clear();

    POSTCONDITION(m_commands.size() == 0);

    CheckInvariants();
}


void cxmodel::CommandStack::Undo()
{
    if(m_commands.empty())
    {
        return;
    }

    if(m_currentPosition != 0)
    {
        m_commands[m_currentPosition]->Undo();
        --m_currentPosition;
    }
    else if(m_currentPosition == 0 && !m_allCmdUndoed)
    {
        m_commands[m_currentPosition]->Undo();
        m_allCmdUndoed = true;
    }

    CheckInvariants();
}

void cxmodel::CommandStack::Redo()
{
    if(m_commands.empty())
    {
        return;
    }

    if(m_currentPosition == 0)
    {
        m_allCmdUndoed = false;
    }

    if(m_currentPosition < m_commands.size())
    {
        m_commands[m_currentPosition]->Execute();
        ++m_currentPosition;
    }

    CheckInvariants();
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

bool cxmodel::CommandStack::AreNoCommandUndoed() const
{
    if(m_commands.empty())
    {
        return true;
    }

    return m_currentPosition == GetLastCommandPosition();
}

size_t cxmodel::CommandStack::GetLastCommandPosition() const
{
    return m_commands.size() - 1;
}

void cxmodel::CommandStack::CheckInvariants()
{
    INVARIANT(m_endPosition > 1);
}
