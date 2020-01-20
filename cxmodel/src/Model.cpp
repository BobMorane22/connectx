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
 * @file Model.cpp
 * @date 2019
 *
 *************************************************************************************************/

#include <cxinv/include/assertion.h>

#include <CommandIncrementByOne.h>
#include <CommandReinitialize.h>
#include <CommandStack.h>
#include <Model.h>

cxmodel::Model::Model(std::unique_ptr<ICommandStack>&& p_cmdStack)
 : m_cmdStack{std::move(p_cmdStack)}
{
    PRECONDITION(m_cmdStack != nullptr);

    if(m_cmdStack != nullptr)
    {
        PRECONDITION(m_cmdStack->IsEmpty());
    }

    m_currentValue = m_INITIAL_VALUE;

    CheckInvariants();
}

unsigned int cxmodel::Model::GetCurrentValue() const
{
    return m_currentValue;
}

void cxmodel::Model::Increment()
{
    const unsigned int old = m_currentValue;

    m_cmdStack->Execute(std::make_unique<CommandIncrementByOne>(m_currentValue));

    Notify();

    POSTCONDITION(m_currentValue - old == 1);

    CheckInvariants();
}

void cxmodel::Model::Reinitialize()
{

    m_cmdStack->Execute(std::make_unique<CommandReinitialize>(m_INITIAL_VALUE, m_currentValue, m_currentValue));

    Notify();

    POSTCONDITION(m_currentValue == m_INITIAL_VALUE);

    CheckInvariants();
}

void cxmodel::Model::Undo()
{
    m_cmdStack->Undo();

    Notify();

    CheckInvariants();
}

void cxmodel::Model::Redo()
{
    m_cmdStack->Redo();

    Notify();

    CheckInvariants();
}

void cxmodel::Model::CheckInvariants()
{
    INVARIANT(m_cmdStack != nullptr);
}
