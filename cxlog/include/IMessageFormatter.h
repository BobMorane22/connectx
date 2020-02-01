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
 * @file IMessageFormatter.h
 * @date 2020
 *
 *************************************************************************************************/

#ifndef IMESSAGEFORMATTER_H_911F98FA_9452_4B67_845D_34FD824FDD3A
#define IMESSAGEFORMATTER_H_911F98FA_9452_4B67_845D_34FD824FDD3A

#include <string>

#include "VerbosityLevel.h"

namespace cxlog
{

/***********************************************************************************************//**
 * @brief Message formatter.
 *
 * Specifies a common interface that every message formatter for a logger must share.
 *
 **************************************************************************************************/
class IMessageFormatter
{

public:

    /*******************************************************************************************//**
     * @brief Default destructor.
     *
     **********************************************************************************************/
    virtual ~IMessageFormatter() = default;

    /*******************************************************************************************//**
     * @brief Format headers for logging.
     *
     * If a message is column-based (for example, in a spreadsheet), headers might be be required
     * to know wich data is in which column. Some other logger require a header stating different
     * informations about the system.
     *
     * @return A string containing the formatted headers.
     *
     **********************************************************************************************/
    virtual std::string FormatHeaders() const = 0;

    /*******************************************************************************************//**
     * @brief Formats a message entry according to different informations supplied by the logger.
     *
     * Takes different informations (including, of course, a message) supplied by the logger
     * and formats them to a specific format (ex.: text, CSV, HTML, etc.).
     *
     * @param p_verbosityLevel The message verbosity level.
     * @param p_fileName       The source file in which the logging occurred.
     * @param p_functionName   The function name in which the logging occurred.
     * @param p_lineNumber     The line number in the source file where the logging occurred.
     * @param p_message        The message to log.
     *
     * @return The formatted message.
     *
     **********************************************************************************************/
    virtual std::string FormatMessage(const VerbosityLevel p_verbosityLevel,
                                      const std::string&   p_fileName,
                                      const std::string&   p_functionName,
                                      const size_t         p_lineNumber,
                                      const std::string&   p_message) const = 0;

};

} // namespace cxlog

#endif // IMESSAGEFORMATTER_H_911F98FA_9452_4B67_845D_34FD824FDD3A
