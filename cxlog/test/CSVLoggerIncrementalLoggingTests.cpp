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
 * @file CSVLoggerIncrementalLoggingTests.cpp
 * @date 2020
 *
 *************************************************************************************************/

#include <gtest/gtest.h>

#include <cxlog/include/CSVMessageFormatter.h>
#include <cxlog/include/IncrementalChainedLogger.h>
#include <cxlog/include/StringStreamLogTarget.h>

#include "CSVLoggerUtil.h"

namespace
{

void LogAtAllLevels(std::unique_ptr<cxlog::ILogger> p_logger)
{
    p_logger->Log(cxlog::VerbosityLevel::NONE,    _FILE_, _FUNCTION_, _LINE_, GenerateLineToLog());
    p_logger->Log(cxlog::VerbosityLevel::FATAL,   _FILE_, _FUNCTION_, _LINE_, GenerateLineToLog());
    p_logger->Log(cxlog::VerbosityLevel::ERROR,   _FILE_, _FUNCTION_, _LINE_, GenerateLineToLog());
    p_logger->Log(cxlog::VerbosityLevel::WARNING, _FILE_, _FUNCTION_, _LINE_, GenerateLineToLog());
    p_logger->Log(cxlog::VerbosityLevel::INFO,    _FILE_, _FUNCTION_, _LINE_, GenerateLineToLog());
    p_logger->Log(cxlog::VerbosityLevel::DEBUG,   _FILE_, _FUNCTION_, _LINE_, GenerateLineToLog());
}

} // unamed namespace

TEST(CSVIncrementalLogging, CSVStringLogger_TargetNONE_VerbosityLevelRespected)
{
    std::ostringstream t_stream;
    auto t_logger{CreateCSVStringStreamLogger(t_stream)};

    t_logger->SetVerbosityLevel(cxlog::VerbosityLevel::NONE);

    LogAtAllLevels(std::move(t_logger));

    ASSERT_TRUE(t_stream.str().empty());
}

TEST(CSVIncrementalLogging, CSVStringLogger_TargetFATAL_VerbosityLevelRespected)
{
    std::ostringstream t_stream;
    auto t_logger{CreateCSVStringStreamLogger(t_stream)};

    t_logger->SetVerbosityLevel(cxlog::VerbosityLevel::FATAL);

    LogAtAllLevels(std::move(t_logger));

    const std::string result{t_stream.str()};

    ASSERT_EQ(result, FatalResult());
}

TEST(CSVIncrementalLogging, CSVStringLogger_TargetERROR_VerbosityLevelRespected)
{
    std::ostringstream t_stream;
    auto t_logger{CreateCSVStringStreamLogger(t_stream)};

    t_logger->SetVerbosityLevel(cxlog::VerbosityLevel::ERROR);

    LogAtAllLevels(std::move(t_logger));

    const std::string result{t_stream.str()};

    ASSERT_EQ(result, FatalResult() + ErrorResult());
}

TEST(CSVIncrementalLogging, CSVStringLogger_TargetWARNING_VerbosityLevelRespected)
{
    std::ostringstream t_stream;
    auto t_logger{CreateCSVStringStreamLogger(t_stream)};

    t_logger->SetVerbosityLevel(cxlog::VerbosityLevel::WARNING);

    LogAtAllLevels(std::move(t_logger));

    const std::string result{t_stream.str()};

    ASSERT_EQ(result, FatalResult() + ErrorResult() + WarningResult());
}

TEST(CSVIncrementalLogging, CSVStringLogger_TargetINFO_VerbosityLevelRespected)
{
    std::ostringstream t_stream;
    auto t_logger{CreateCSVStringStreamLogger(t_stream)};

    t_logger->SetVerbosityLevel(cxlog::VerbosityLevel::INFO);

    LogAtAllLevels(std::move(t_logger));

    const std::string result{t_stream.str()};

    ASSERT_EQ(result, FatalResult() + ErrorResult() + WarningResult() + InfoResult());
}

TEST(CSVIncrementalLogging, CSVStringLogger_TargetDEBUG_VerbosityLevelRespected)
{
    std::ostringstream t_stream;
    auto t_logger{CreateCSVStringStreamLogger(t_stream)};

    t_logger->SetVerbosityLevel(cxlog::VerbosityLevel::DEBUG);

    LogAtAllLevels(std::move(t_logger));

    const std::string result{t_stream.str()};

    ASSERT_EQ(result, FatalResult() + ErrorResult() + WarningResult() + InfoResult() + DebugResult());
}

TEST(CSVIncrementalLogging, CSVStringChainedLogger_TargetNONE_VerbosityLevelRespected)
{
    std::ostringstream t_stream;
    auto t_logger{CreateCSVStringStreamChainLogger(t_stream)};

    t_logger->SetVerbosityLevel(cxlog::VerbosityLevel::NONE);

    LogAtAllLevels(std::move(t_logger));

    ASSERT_TRUE(t_stream.str().empty());
}

TEST(CSVIncrementalLogging, CSVStringChainedLogger_TargetFATAL_VerbosityLevelRespected)
{
    std::ostringstream t_stream;
    auto t_logger{CreateCSVStringStreamChainLogger(t_stream)};

    t_logger->SetVerbosityLevel(cxlog::VerbosityLevel::FATAL);

    LogAtAllLevels(std::move(t_logger));

    const std::string result{t_stream.str()};

    ASSERT_EQ(result, FatalResult());
}

TEST(CSVIncrementalLogging, CSVStringChainedLogger_TargetERROR_VerbosityLevelRespected)
{
    std::ostringstream t_stream;
    auto t_logger{CreateCSVStringStreamChainLogger(t_stream)};

    t_logger->SetVerbosityLevel(cxlog::VerbosityLevel::ERROR);

    LogAtAllLevels(std::move(t_logger));

    const std::string result{t_stream.str()};

    ASSERT_EQ(result, FatalResult() + ErrorResult());
}

TEST(CSVIncrementalLogging, CSVStringChainedLogger_TargetWARNING_VerbosityLevelRespected)
{
    std::ostringstream t_stream;
    auto t_logger{CreateCSVStringStreamChainLogger(t_stream)};

    t_logger->SetVerbosityLevel(cxlog::VerbosityLevel::WARNING);

    LogAtAllLevels(std::move(t_logger));

    const std::string result{t_stream.str()};

    ASSERT_EQ(result, FatalResult() + ErrorResult() + WarningResult());
}

TEST(CSVIncrementalLogging, CSVStringChainedLogger_TargetINFO_VerbosityLevelRespected)
{
    std::ostringstream t_stream;
    auto t_logger{CreateCSVStringStreamChainLogger(t_stream)};

    t_logger->SetVerbosityLevel(cxlog::VerbosityLevel::INFO);

    LogAtAllLevels(std::move(t_logger));

    const std::string result{t_stream.str()};

    ASSERT_EQ(result, FatalResult() + ErrorResult() + WarningResult() + InfoResult());
}

TEST(CSVIncrementalLogging, CSVStringChainedLogger_TargetDEBUG_VerbosityLevelRespected)
{
    std::ostringstream t_stream;
    auto t_logger{CreateCSVStringStreamChainLogger(t_stream)};

    t_logger->SetVerbosityLevel(cxlog::VerbosityLevel::DEBUG);

    LogAtAllLevels(std::move(t_logger));

    const std::string result{t_stream.str()};

    ASSERT_EQ(result, FatalResult() + ErrorResult() + WarningResult() + InfoResult() + DebugResult());
}
