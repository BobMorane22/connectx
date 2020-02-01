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
 * @file IncrementalChainedLogger.h
 * @date 2020
 *
 *************************************************************************************************/

#ifndef INCREMENTALCHAINEDLOGGER_H_25A9595F_2567_4CD1_9A36_B046CFCC8552
#define INCREMENTALCHAINEDLOGGER_H_25A9595F_2567_4CD1_9A36_B046CFCC8552

#include "ChainLogger.h"
#include "IMessageFormatter.h"

namespace cxlog
{

/***********************************************************************************************//**
 * @brief An incremental logger using a chain of responsability to forward log requests.
 *
 * The logger is incremental in the sense that is has many successive logging verbosity level. One
 * can increase the logger verbosity incrementally if needed.
 *
 **************************************************************************************************/
class IncrementalChainedLogger : public ChainLogger
{

public:

    /*******************************************************************************************//**
     * @brief Constructor.
     *
     * Constructs an incremental logger that might forward its log entry to another logger using
     * a chain of responsability. The logger is incremental in the sense that is has many
     * successive logging verbosity level.
     *
     * @param p_msgFormatter A message formatter to format the logging information into a
     *                       specific format.
     * @param p_logTarget    The target for logging (stdout, file, etc.).
     * @param p_addHeader    A flag indicationg is headers have to be added to the logging
     *                       medium before any entry is logged.
     *
     **********************************************************************************************/
    IncrementalChainedLogger(std::unique_ptr<IMessageFormatter>&& p_msgFormatter,
                             std::unique_ptr<ILogTarget>&&        p_logTarget,
                             bool                                 p_addHeader = false);

    /*******************************************************************************************//**
     * @brief Logs an entry.
     *
     * Logs an entry using the information injected as parameters.
     *
     * @param p_verbosityLevel The message verbosity level.
     * @param p_fileName       The source file in which the logging occured.
     * @param p_functionName   The function name in which the logging occured.
     * @param p_lineNumber     The line number in the source file where the logging occured.
     * @param p_message        The message to log.
     *
     **********************************************************************************************/
    void Log(const VerbosityLevel p_verbosityLevel,
             const std::string&   p_fileName,
             const std::string&   p_functionName,
             const size_t         p_lineNumber,
             const std::string&   p_message) override;


private:

    std::unique_ptr<IMessageFormatter> m_msgFormatter; ///< The message formatter.
    std::unique_ptr<ILogTarget>        m_logTarget;    ///< The log target.
};

} // namespace cxlog

#endif // INCREMENTALCHAINEDLOGGER_H_25A9595F_2567_4CD1_9A36_B046CFCC8552
