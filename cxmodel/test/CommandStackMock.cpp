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
 * @file CommandStackMock.cpp
 * @date 2020
 *
 *************************************************************************************************/

#include <gtest/gtest.h>

#include <cxunit/NotImplementedException.h>

#include "CommandStackMock.h"

bool CommandStackMock::IsRedoed() const
{
    return m_isRedoed;
}

bool CommandStackMock::IsUndoed() const
{
    return m_isUndoed;
}

void CommandStackMock::SetCanUndo(bool p_canUndo)
{
    m_canUndo = p_canUndo;
}

void CommandStackMock::SetCanRedo(bool p_canRedo)
{
    m_canRedo = p_canRedo;
}

void CommandStackMock::Execute(std::unique_ptr<cxmodel::ICommand>&& /*p_newCommand*/)
{
    // Does nothing.
}

void CommandStackMock::Clear()
{
    throw cxunit::NotImplementedException();
}

void CommandStackMock::Undo()
{
    m_isUndoed = true;
}

void CommandStackMock::Redo()
{
    m_isRedoed = true;
}

bool CommandStackMock::CanUndo() const
{
    return m_canUndo;
}

bool CommandStackMock::CanRedo() const
{
    return m_canRedo;
}

bool CommandStackMock::IsEmpty() const
{
    return true;
}

bool CommandStackMock::IsFull() const
{
    throw cxunit::NotImplementedException();
}

size_t CommandStackMock::GetNbCommands() const
{
    throw cxunit::NotImplementedException();
}
