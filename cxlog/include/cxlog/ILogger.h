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
 * @file ILogger.h
 * @date 2020
 *
 *************************************************************************************************/

#ifndef ILOGGER_H_C23F1D75_6DA4_499E_A502_FBEC85D074DB
#define ILOGGER_H_C23F1D75_6DA4_499E_A502_FBEC85D074DB

#include <string>

#include "ILogTarget.h"
#include "VerbosityLevel.h"

namespace cxlog
{

/***********************************************************************************************//**
 * @brief Interface to implement loggers.
 *
 **************************************************************************************************/
class ILogger
{

public:

    /*******************************************************************************************//**
     * @brief Default destructor.
     *
     **********************************************************************************************/
    virtual ~ILogger() = default;

    /*******************************************************************************************//**
     * @brief Logs an entry.
     *
     * Logs an entry using the information injected as parameters.
     *
     * @param p_verbosityLevel
     *      The message verbosity level.
     * @param p_fileName
     *      The source file in which the logging occurred.
     * @param p_functionName
     *      The function name in which the logging occurred.
     * @param p_lineNumber
     *      The line number in the source file where the logging occurred.
     * @param p_message
     *      The message to log.
     *
     **********************************************************************************************/
    virtual void Log(const VerbosityLevel p_verbosityLevel,
                     const std::string&   p_fileName,
                     const std::string&   p_functionName,
                     const size_t         p_lineNumber,
                     const std::string&   p_message) = 0;

    /*******************************************************************************************//**
     * @brief Mutates the logger general verbosity level.
     *
     * @param p_verbosityLevel
     *      The new logger-wide verbosity level.
     *
     *********************************************************************************************/
    virtual void SetVerbosityLevel(const VerbosityLevel p_verbosityLevel) = 0;

    /*******************************************************************************************//**
     * @brief Indicates the logger general verbosity level.
     *
     * @return
     *      The logger-wide verbosity level.
     *
     *********************************************************************************************/
    [[nodiscard]] virtual VerbosityLevel GetVerbosityLevel() const = 0;

};

} // namespace cxlog

#endif // ILOGGER_H_C23F1D75_6DA4_499E_A502_FBEC85D074DB
