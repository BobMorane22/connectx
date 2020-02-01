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
 * @file CSVMessageFormatter.cpp
 * @date 2020
 *
 *************************************************************************************************/

#include <cxinv/include/assertion.h>

#include <CSVMessageFormatter.h>

namespace
{

const std::string NEWLINE  {"\n"}; // CSV end of line character.
const std::string SEPARATOR{", "}; // CSV separator character.

std::string MakeCSV(const std::string& p_timestamp,
                    const std::string& p_verbosityLevel,
                    const std::string& p_fileName,
                    const std::string& p_functionName,
                    const size_t       p_lineNumber,
                    const std::string& p_message)
{
    return p_timestamp                  + SEPARATOR +
           p_verbosityLevel             + SEPARATOR +
           p_fileName                   + SEPARATOR +
           p_functionName               + SEPARATOR +
           std::to_string(p_lineNumber) + SEPARATOR +
           p_message                    + NEWLINE;
}

} // unamed namespace

cxlog::CSVMessageFormatter::CSVMessageFormatter(std::unique_ptr<cxlog::ITimestampFormatter>&& p_timeFormatter)
 : m_timeFormatter{std::move(p_timeFormatter)}
{
    PRECONDITION(m_timeFormatter != nullptr);
}

std::string cxlog::CSVMessageFormatter::FormatHeaders() const
{
    return "Timestamp"       + SEPARATOR +
           "File name"       + SEPARATOR +
           "Function name"   + SEPARATOR +
           "Line number"     + SEPARATOR +
           "Verbosity level" + SEPARATOR +
           "Message"         + NEWLINE;
}

std::string cxlog::CSVMessageFormatter::FormatMessage(const VerbosityLevel p_verbosityLevel,
                                                      const std::string&   p_fileName,
                                                      const std::string&   p_functionName,
                                                      const size_t         p_lineNumber,
                                                      const std::string&   p_message) const
{
    switch(p_verbosityLevel)
    {
        case cxlog::VerbosityLevel::NONE:
        {
            ASSERT_ERROR_MSG("Do this check in higher level functions.");
            return {};
        }
        case cxlog::VerbosityLevel::FATAL:
        {
            return MakeCSV(m_timeFormatter->FormatTimestamp(), "FATAL", p_fileName, p_functionName, p_lineNumber, p_message);
        }
        case cxlog::VerbosityLevel::ERROR:
        {
            return MakeCSV(m_timeFormatter->FormatTimestamp(), "ERROR", p_fileName, p_functionName, p_lineNumber, p_message);
        }
        case cxlog::VerbosityLevel::WARNING:
        {
            return MakeCSV(m_timeFormatter->FormatTimestamp(), "WARNING", p_fileName, p_functionName, p_lineNumber, p_message);
        }
        case cxlog::VerbosityLevel::INFO:
        {
            return MakeCSV(m_timeFormatter->FormatTimestamp(), "INFO", p_fileName, p_functionName, p_lineNumber, p_message);
        }
        case cxlog::VerbosityLevel::DEBUG:
        {
            return MakeCSV(m_timeFormatter->FormatTimestamp(), "DEBUG", p_fileName, p_functionName, p_lineNumber, p_message);
        }
    }

    ASSERT_ERROR_MSG("Unknown verbosity level");
    return {};
}
