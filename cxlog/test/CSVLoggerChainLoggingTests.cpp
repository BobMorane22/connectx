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
 * @file CSVLoggerChainLoggingTests.cpp
 * @date 2020
 *
 *************************************************************************************************/

#include <gtest/gtest.h>

#include <cxlog/include/CSVMessageFormatter.h>
#include <cxlog/include/IncrementalChainedLogger.h>
#include <cxlog/include/StringStreamLogTarget.h>

#include "CSVLoggerUtil.h"

TEST(ChainLogging, ChainLogging_TwoSuccessiveLoggers_FirstHasSuccessorSecondDoesNot)
{
    std::ostringstream t_stream;
    std::ostringstream t_streamSuccessor;

    auto t_logger{CreateCSVStringStreamChainLogger(t_stream)};
    auto t_loggerSuccessor{CreateCSVStringStreamChainLogger(t_streamSuccessor)};

    ASSERT_FALSE(t_logger->HasSucessor());

    t_logger->SetSucessor(std::move(t_loggerSuccessor));

    ASSERT_TRUE(t_logger->HasSucessor());
}


TEST(ChainLogging, ChainLogging_ValidStringAsInfo_AllLoggersLog)
{
    std::ostringstream t_stream;
    std::ostringstream t_streamSuccessor;

    auto t_logger{CreateCSVStringStreamChainLogger(t_stream)};
    auto t_loggerSuccessor{CreateCSVStringStreamChainLogger(t_streamSuccessor)};

    t_logger->SetSucessor(std::move(t_loggerSuccessor));

    // Log a string:
    t_logger->Log(cxlog::VerbosityLevel::INFO, _FILE_, _FUNCTION_, _LINE_, GenerateLineToLog());

    // Get log results:
    const std::string loggedLine{t_stream.str()};
    const std::string loggedLineSuccessor{t_streamSuccessor.str()};
    const std::string expectedLine{InfoResult()};

    ASSERT_EQ(loggedLine, InfoResult());
    ASSERT_EQ(loggedLineSuccessor, InfoResult());
}

TEST(ChainLogging, ChainLogging_ValidStringAsInfo_AllLoggersLogExceptNone)
{
    std::ostringstream t_stream,
                       t_streamFirstSuccessor,
                       t_streamSecondSuccessor;

    auto t_logger               {CreateCSVStringStreamChainLogger(t_stream)};
    auto t_loggerFirstSuccessor {CreateCSVStringStreamChainLogger(t_streamFirstSuccessor)};
    auto t_loggerSecondSuccessor{CreateCSVStringStreamChainLogger(t_streamSecondSuccessor)};

    // Middle successor is silenced:
    t_loggerFirstSuccessor->SetVerbosityLevel(cxlog::VerbosityLevel::NONE);

    // Set two successors:
    t_loggerFirstSuccessor->SetSucessor(std::move(t_loggerSecondSuccessor));
    t_logger->SetSucessor(std::move(t_loggerFirstSuccessor));

    // Log a string:
    t_logger->Log(cxlog::VerbosityLevel::INFO, _FILE_, _FUNCTION_, _LINE_, GenerateLineToLog());

    // Get log results:
    const std::string loggedLine               {t_stream.str()};
    const std::string loggedLineFirstSuccessor {t_streamFirstSuccessor.str()};
    const std::string loggedLineSecondSuccessor{t_streamSecondSuccessor.str()};

    const std::string expectedLine{InfoResult()};

    ASSERT_EQ(loggedLine,                InfoResult());
    ASSERT_EQ(loggedLineFirstSuccessor,  EMPTY_STRING);
    ASSERT_EQ(loggedLineSecondSuccessor, InfoResult());
}
