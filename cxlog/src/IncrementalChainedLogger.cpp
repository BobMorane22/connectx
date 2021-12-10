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
 * @file IncrementalChainedLogger.cpp
 * @date 2020
 *
 *************************************************************************************************/

#include <cxinv/assertion.h>
#include <cxlog/IncrementalChainedLogger.h>

cxlog::IncrementalChainedLogger::IncrementalChainedLogger(std::unique_ptr<IMessageFormatter>&& p_msgFormatter,
                                                          std::unique_ptr<ILogTarget>&&        p_logTarget,
                                                          bool                                 p_addHeader)
 : m_msgFormatter{std::move(p_msgFormatter)}
 , m_logTarget{std::move(p_logTarget)}
{
    // We take member variables as preconditions because parameters
    // have been moved away:
    PRECONDITION(m_msgFormatter);
    PRECONDITION(m_logTarget);

    if(m_msgFormatter && m_logTarget && p_addHeader)
    {
        // Log the header:
        m_logTarget->Log(m_msgFormatter->FormatHeaders());
    }

    INVARIANT(m_msgFormatter);
    INVARIANT(m_logTarget);
}

void cxlog::IncrementalChainedLogger::Log(const VerbosityLevel p_verbosityLevel,
                                          const std::string&   p_fileName,
                                          const std::string&   p_functionName,
                                          const size_t         p_lineNumber,
                                          const std::string&   p_message)
{
    IF_CONDITION_NOT_MET_DO(m_msgFormatter, return;);

    if(p_verbosityLevel > GetVerbosityLevel() ||
       p_verbosityLevel == VerbosityLevel::NONE ||
       GetVerbosityLevel() == VerbosityLevel::NONE)
    {
        if(HasSucessor())
        {
            // Forward message to next logger:
            m_successor->Log(p_verbosityLevel, p_fileName, p_functionName, p_lineNumber, p_message);
        }

        return;
    }

    // Create well formatted message:
    const std::string msg{m_msgFormatter->FormatMessage(p_verbosityLevel, p_fileName, p_functionName, p_lineNumber, p_message)};

    if(!INL_ASSERT(m_logTarget))
    {
        // Release formatter, no logging will be done after all:
        m_msgFormatter.reset(nullptr);

        return;
    }

    // Log it to the target:
    m_logTarget->Log(msg);

    if(HasSucessor())
    {
        // Forward message to next logger:
        m_successor->Log(p_verbosityLevel, p_fileName, p_functionName, p_lineNumber, p_message);
    }

    INVARIANT(m_msgFormatter);
    INVARIANT(m_logTarget);
}
