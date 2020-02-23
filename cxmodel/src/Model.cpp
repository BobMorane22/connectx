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
#include <NotificationContext.h>

cxmodel::Model::Model(std::unique_ptr<ICommandStack>&& p_cmdStack, cxlog::ILogger& p_logger)
 : m_cmdStack{std::move(p_cmdStack)}
 , m_logger{p_logger}
{
    PRECONDITION(m_cmdStack != nullptr);

    if(m_cmdStack != nullptr)
    {
        PRECONDITION(m_cmdStack->IsEmpty());
    }

    m_currentValue = m_INITIAL_VALUE;

    CheckInvariants();
}

cxmodel::Model::~Model() = default;

unsigned int cxmodel::Model::GetCurrentValue() const
{
    return m_currentValue;
}

void cxmodel::Model::Increment()
{
    const unsigned int old = m_currentValue;

    m_cmdStack->Execute(std::make_unique<CommandIncrementByOne>(m_currentValue));

    Notify(NotificationContext::INCREMENT);

    POSTCONDITION(m_currentValue - old == 1);

    Log(cxlog::VerbosityLevel::DEBUG, __FILE__, __FUNCTION__, __LINE__,
        "Incremented value.");

    CheckInvariants();
}

void cxmodel::Model::Reinitialize()
{

    m_cmdStack->Execute(std::make_unique<CommandReinitialize>(m_INITIAL_VALUE, m_currentValue, m_currentValue));

    Notify(NotificationContext::REINITIALIZE);

    POSTCONDITION(m_currentValue == m_INITIAL_VALUE);

    Log(cxlog::VerbosityLevel::DEBUG, __FILE__, __FUNCTION__, __LINE__,
        "Reinitialized value.");

    CheckInvariants();
}

void cxmodel::Model::Undo()
{
    m_cmdStack->Undo();

    Notify(NotificationContext::UNDO);

    Log(cxlog::VerbosityLevel::DEBUG, __FILE__, __FUNCTION__, __LINE__,
        "Last action undoed.");

    CheckInvariants();
}

void cxmodel::Model::Redo()
{
    m_cmdStack->Redo();

    Notify(NotificationContext::REDO);

    Log(cxlog::VerbosityLevel::DEBUG, __FILE__, __FUNCTION__, __LINE__,
        "Last action redoed.");

    CheckInvariants();
}

void cxmodel::Model::Log(const cxlog::VerbosityLevel p_verbosityLevel, const std::string& p_fileName, const std::string& p_functionName, const size_t p_lineNumber, const std::string& p_message)
{
    m_logger.Log(p_verbosityLevel, p_fileName, p_functionName, p_lineNumber, p_message);
}

void cxmodel::Model::SetVerbosityLevel(const cxlog::VerbosityLevel p_verbosityLevel)
{
    m_logger.SetVerbosityLevel(p_verbosityLevel);
}

cxlog::VerbosityLevel cxmodel::Model::GetVerbosityLevel() const
{
    return m_logger.GetVerbosityLevel();
}

void cxmodel::Model::CheckInvariants()
{
    INVARIANT(m_cmdStack != nullptr);
}
