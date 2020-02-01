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
 * @file CSVLoggerUtil.cpp
 * @date 2020
 *
 *************************************************************************************************/

#include <cxlog/include/CSVMessageFormatter.h>
#include <cxlog/include/IMessageFormatter.h>
#include <cxlog/include/IncrementalChainedLogger.h>
#include <cxlog/include/IncrementalLogger.h>
#include <cxlog/include/StringStreamLogTarget.h>

#include "CSVLoggerUtil.h"
#include "TimestampFormatterMock.h"

std::string GenerateLineToLog()
{
    return BASIC_STRING_TO_LOG;
}

std::string GenerateResult(const std::string p_prefix)
{
    return "AAAA:MM:JJTHH:MM:SS:mm"   + SEPARATOR +
           p_prefix                   +
           _FILE_                     + SEPARATOR +
           _FUNCTION_                 + SEPARATOR +
           std::to_string(_LINE_)     + SEPARATOR +
           BASIC_STRING_TO_LOG        + END_OF_LINE;
}

std::string FatalResult()
{
    return GenerateResult(FATAL_PREFIX);
}

std::string ErrorResult()
{
    return GenerateResult(ERROR_PREFIX);
}

std::string WarningResult()
{
    return GenerateResult(WARNING_PREFIX);
}

std::string InfoResult()
{
    return GenerateResult(INFO_PREFIX);
}

std::string DebugResult()
{
    return GenerateResult(DEBUG_PREFIX);
}

std::string HeaderLine()
{
    return "Timestamp"       + SEPARATOR +
           "File name"       + SEPARATOR +
           "Function name"   + SEPARATOR +
           "Line number"     + SEPARATOR +
           "Verbosity level" + SEPARATOR +
           "Message"         + END_OF_LINE;
}

std::unique_ptr<cxlog::ILogger> CreateCVSStringStreamLogger(std::ostringstream& p_stream,
                                                            const bool          p_generateHeader)
{
    // Creating logger dependencies:
    std::unique_ptr<cxlog::ITimestampFormatter> t_timeFormatter{new TimestampFormatterMock};
    std::unique_ptr<cxlog::IMessageFormatter> t_msgFormatter{new cxlog::CSVMessageFormatter{std::move(t_timeFormatter)}};

    std::unique_ptr<cxlog::ILogTarget> t_target{new cxlog::StringStreamLogTarget{p_stream}};

    // Creating CSV string logger:
    std::unique_ptr<cxlog::ILogger> t_logger{new cxlog::IncrementalLogger{std::move(t_msgFormatter),
                                             std::move(t_target),
                                             p_generateHeader}};

    t_logger->SetVerbosityLevel(cxlog::VerbosityLevel::DEBUG);

    return std::move(t_logger);
}

std::unique_ptr<cxlog::ChainLogger> CreateCVSStringStreamChainLogger(std::ostringstream& p_stream,
                                                                     const bool          p_generateHeader)
{
    // Creating logger dependencies:
    std::unique_ptr<cxlog::ITimestampFormatter> t_timeFormatter{new TimestampFormatterMock};
    std::unique_ptr<cxlog::IMessageFormatter> t_msgFormatter{new cxlog::CSVMessageFormatter{std::move(t_timeFormatter)}};

    std::unique_ptr<cxlog::ILogTarget> t_target{new cxlog::StringStreamLogTarget{p_stream}};

    // Creating CSV string logger:
    std::unique_ptr<cxlog::ChainLogger> t_logger{new cxlog::IncrementalChainedLogger{std::move(t_msgFormatter),
                                                                                     std::move(t_target),
                                                                                     p_generateHeader}};

    t_logger->SetVerbosityLevel(cxlog::VerbosityLevel::DEBUG);

    return std::move(t_logger);
}
