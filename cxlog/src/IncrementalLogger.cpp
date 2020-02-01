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
 * @file IncrementalLogger.cpp
 * @date 2020
 *
 *************************************************************************************************/

#include <cxinv/include/assertion.h>

#include <IncrementalLogger.h>

cxlog::IncrementalLogger::IncrementalLogger(std::unique_ptr<IMessageFormatter>&& p_msgFormatter,
                                            std::unique_ptr<ILogTarget>&&        p_logTarget,
                                            bool                                 p_addHeader)
 : m_msgFormatter{std::move(p_msgFormatter)}
 , m_logTarget{std::move(p_logTarget)}
{
    // We take member variables as preconditions because parameters
    // have been moved away:
    PRECONDITION(m_msgFormatter != nullptr);
    PRECONDITION(m_logTarget != nullptr);

    if(m_msgFormatter && m_logTarget && p_addHeader)
    {
        // Log the header:
        m_logTarget->Log(m_msgFormatter->FormatHeaders());
    }

    INVARIANT(m_msgFormatter != nullptr);
    INVARIANT(m_logTarget != nullptr);
}

void cxlog::IncrementalLogger::Log(const VerbosityLevel p_verbosityLevel,
                                   const std::string&   p_fileName,
                                   const std::string&   p_functionName,
                                   const size_t         p_lineNumber,
                                   const std::string&   p_message)
{
    if(!m_msgFormatter)
    {
        ASSERT_ERROR_MSG("No reference to a formatter.");

        return;
    }

    if(p_verbosityLevel > GetVerbosityLevel() ||
        p_verbosityLevel == VerbosityLevel::NONE ||
        GetVerbosityLevel() == VerbosityLevel::NONE)
    {
        return;
    }

    // Create well formatted message:
    const std::string msg{m_msgFormatter->FormatMessage(p_verbosityLevel, p_fileName, p_functionName, p_lineNumber, p_message)};

    std::cout << "Formatted : " << msg << std::endl;

    if(!m_logTarget)
    {
        ASSERT_ERROR_MSG("No reference to a log target.");

        // Release formatter, no logging will be done after all:
        m_msgFormatter.reset(nullptr);

        return;
    }

    // Log it to the target:
    m_logTarget->Log(msg);

    INVARIANT(m_msgFormatter != nullptr);
    INVARIANT(m_logTarget != nullptr);
}
