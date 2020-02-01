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
 * @file IncrementalLogger.h
 * @date 2020
 *
 *************************************************************************************************/

#ifndef INCREMENTALLOGGER_H_8B296618_F3FB_4858_B8B3_845E261A3B9F
#define INCREMENTALLOGGER_H_8B296618_F3FB_4858_B8B3_845E261A3B9F

#include "IMessageFormatter.h"

#include "Logger.h"

namespace cxlog
{

/***********************************************************************************************//**
 * @brief A simple incremental logger.
 *
 * The logger is incremental in the sense that is has many successive logging verbosity level.
 * One can increase the logger verbosity incrementally if needed.
 *
 **************************************************************************************************/
class IncrementalLogger : public Logger
{

public:

    /*******************************************************************************************//**
     * Constructor.
     *
     * @param p_msgFormatter An address to a unique message formatter.
     * @param p_logTarget    An address to a unique log target.
     * @param p_addHeader    A flag indicating if the logger needs a header to be added on first
     *                       log event.
     *
     **********************************************************************************************/
    IncrementalLogger(std::unique_ptr<IMessageFormatter>&& p_msgFormatter,
                      std::unique_ptr<ILogTarget>&&        p_logTarget,
                      bool                                 p_addHeader = false);

    /*******************************************************************************************//**
     * @brief Logs an entry.
     *
     * Logs an entry using the information injected as parameters.
     *
     * @param p_verbosityLevel The message verbosity level.
     * @param p_fileName       The source file in which the logging occurred.
     * @param p_functionName   The function name in which the logging occurred.
     * @param p_lineNumber     The line number in the source file where the logging occurred.
     * @param p_message        The message to log.
     *
     **********************************************************************************************/
    void Log(const VerbosityLevel p_verbosityLevel,
             const std::string&   p_fileName,
             const std::string&   p_functionName,
             const size_t         p_lineNumber,
             const std::string&   p_message) override;

private:

    std::unique_ptr<IMessageFormatter> m_msgFormatter;
    std::unique_ptr<ILogTarget>        m_logTarget;
};

} // namespace cxlog

#endif // INCREMENTALLOGGER_H_8B296618_F3FB_4858_B8B3_845E261A3B9F
