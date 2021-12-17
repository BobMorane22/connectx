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
 * @file CSVLoggerTests.cpp
 * @date 2020
 *
 *************************************************************************************************/

#include <gtest/gtest.h>

#include <cxlog/CSVMessageFormatter.h>
#include <cxlog/IncrementalChainedLogger.h>
#include <cxlog/StringStreamLogTarget.h>

#include "CSVLoggerUtil.h"

TEST(CSVLogger, /*DISABLED_*/CSVStringLogger_ValidStringAsInfo_LoggingIsAdequate)
{
    std::ostringstream t_stream;
    auto t_logger{CreateCSVStringStreamLogger(t_stream)};

    // Log a string:
    t_logger->Log(cxlog::VerbosityLevel::INFO, _FILE_, _FUNCTION_, _LINE_, GenerateLineToLog());

    // Get log result:
    const std::string loggedLine{t_stream.str()};

    ASSERT_EQ(loggedLine, InfoResult());
}

TEST(CSVLogger, /*DISABLED_*/CSVStringLogger_ValidStringAsError_LoggingIsAdequate)
{
    std::ostringstream t_stream;
    auto t_logger{CreateCSVStringStreamLogger(t_stream)};

    // Log a string:
    t_logger->Log(cxlog::VerbosityLevel::ERROR, _FILE_, _FUNCTION_, _LINE_, GenerateLineToLog());

    // Get log result:
    const std::string loggedLine{t_stream.str()};

    ASSERT_EQ(loggedLine, ErrorResult());
}

TEST(CSVLogger, /*DISABLED_*/CSVStringLogger_ValidStringAsFatal_LoggingIsAdequate)
{
    std::ostringstream t_stream;
    auto t_logger{CreateCSVStringStreamLogger(t_stream)};

    // Log a string:
    t_logger->Log(cxlog::VerbosityLevel::FATAL, _FILE_, _FUNCTION_, _LINE_, GenerateLineToLog());

    // Get log result:
    const std::string loggedLine{t_stream.str()};

    ASSERT_EQ(loggedLine, FatalResult());
}

TEST(CSVLogger, /*DISABLED_*/CSVStringLogger_ValidStringAsDebug_LoggingIsAdequate)
{
    std::ostringstream t_stream;
    auto t_logger{CreateCSVStringStreamLogger(t_stream)};

    // Log a string:
    t_logger->Log(cxlog::VerbosityLevel::DEBUG, _FILE_, _FUNCTION_, _LINE_, GenerateLineToLog());

    // Get log result:
    const std::string loggedLine{t_stream.str()};

    ASSERT_EQ(loggedLine, DebugResult());
}

TEST(CSVLogger, /*DISABLED_*/CSVStringLogger_ValidStrings_AllLinesLoggued)
{
    std::ostringstream t_stream;
    auto t_logger{CreateCSVStringStreamLogger(t_stream)};

    // Log a string:
    t_logger->Log(cxlog::VerbosityLevel::INFO,  _FILE_, _FUNCTION_, _LINE_, GenerateLineToLog());
    t_logger->Log(cxlog::VerbosityLevel::ERROR, _FILE_, _FUNCTION_, _LINE_, GenerateLineToLog());
    t_logger->Log(cxlog::VerbosityLevel::FATAL, _FILE_, _FUNCTION_, _LINE_, GenerateLineToLog());

    // Get log result:
    const std::string loggedLines{t_stream.str()};

    const std::string expectedLines{InfoResult() + ErrorResult() + FatalResult()};

    ASSERT_EQ(loggedLines, expectedLines);
}

TEST(CSVLogger, /*DISABLED_*/CSVStringLogger_GenerateHeadersTrue_HeadersGenerated)
{
    std::ostringstream t_stream;
    auto t_logger{CreateCSVStringStreamLogger(t_stream, true)};

    // Get log result:
    const std::string loggedLines{t_stream.str()};

    ASSERT_EQ(loggedLines, HeaderLine());
}
