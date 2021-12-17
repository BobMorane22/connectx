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
 * @file CSVMessageFormatterTests.cpp
 * @date 2020
 *
 *************************************************************************************************/

#include <gtest/gtest.h>

#include <cxlog/CSVMessageFormatter.h>

#include "CSVLoggerUtil.h"
#include "TimestampFormatterMock.h"

TEST(CSVMessageFormatter, /*DISABLED_*/FormatHeaders_ValidMessageFormatter_FormatsHeadersAccordingly)
{
    std::unique_ptr<TimestampFormatterMock> tsmpFormatter= std::make_unique<TimestampFormatterMock>();
    std::unique_ptr<cxlog::IMessageFormatter> formatter = std::make_unique<cxlog::CSVMessageFormatter>(std::move(tsmpFormatter));

    const std::string result  {formatter->FormatHeaders()};
    const std::string expected{HeaderLine()};

    ASSERT_EQ(result, expected);
}

TEST(CSVMessageFormatter, /*DISABLED_*/FormatMessage_ValidLineAsFatal_FormatsCSVMessageAccordingly)
{
    std::unique_ptr<TimestampFormatterMock> tsmpFormatter= std::make_unique<TimestampFormatterMock>();
    std::unique_ptr<cxlog::IMessageFormatter> formatter = std::make_unique<cxlog::CSVMessageFormatter>(std::move(tsmpFormatter));

    const std::string result{formatter->FormatMessage(cxlog::VerbosityLevel::FATAL,
                                                      _FILE_,
                                                      _FUNCTION_,
                                                      _LINE_,
                                                      GenerateLineToLog())};
    const std::string expected{FatalResult()};

    ASSERT_EQ(result, expected);
}

TEST(CSVMessageFormatter, /*DISABLED_*/FormatMessage_ValidLineAsError_FormatsCSVMessageAccordingly)
{
    std::unique_ptr<TimestampFormatterMock> tsmpFormatter= std::make_unique<TimestampFormatterMock>();
    std::unique_ptr<cxlog::IMessageFormatter> formatter = std::make_unique<cxlog::CSVMessageFormatter>(std::move(tsmpFormatter));

    const std::string result{formatter->FormatMessage(cxlog::VerbosityLevel::ERROR,
                                                      _FILE_,
                                                      _FUNCTION_,
                                                      _LINE_,
                                                      GenerateLineToLog())};
    const std::string expected{ErrorResult()};

    ASSERT_EQ(result, expected);
}

TEST(CSVMessageFormatter, /*DISABLED_*/FormatMessage_ValidLineAsWarning_FormatsCSVMessageAccordingly)
{
    std::unique_ptr<TimestampFormatterMock> tsmpFormatter= std::make_unique<TimestampFormatterMock>();
    std::unique_ptr<cxlog::IMessageFormatter> formatter = std::make_unique<cxlog::CSVMessageFormatter>(std::move(tsmpFormatter));

    const std::string result{formatter->FormatMessage(cxlog::VerbosityLevel::WARNING,
                                                      _FILE_,
                                                      _FUNCTION_,
                                                      _LINE_,
                                                      GenerateLineToLog())};
    const std::string expected{WarningResult()};

    ASSERT_EQ(result, expected);
}

TEST(CSVMessageFormatter, /*DISABLED_*/FormatMessage_ValidLineAsInfo_FormatsCSVMessageAccordingly)
{
    std::unique_ptr<TimestampFormatterMock> tsmpFormatter= std::make_unique<TimestampFormatterMock>();
    std::unique_ptr<cxlog::IMessageFormatter> formatter = std::make_unique<cxlog::CSVMessageFormatter>(std::move(tsmpFormatter));

    const std::string result{formatter->FormatMessage(cxlog::VerbosityLevel::INFO,
                                                      _FILE_,
                                                      _FUNCTION_,
                                                      _LINE_,
                                                      GenerateLineToLog())};
    const std::string expected{InfoResult()};

    ASSERT_EQ(result, expected);
}

TEST(CSVMessageFormatter, /*DISABLED_*/FormatMessage_ValidLineAsDebug_FormatsCSVMessageAccordingly)
{
    std::unique_ptr<TimestampFormatterMock> tsmpFormatter= std::make_unique<TimestampFormatterMock>();
    std::unique_ptr<cxlog::IMessageFormatter> formatter = std::make_unique<cxlog::CSVMessageFormatter>(std::move(tsmpFormatter));

    const std::string result{formatter->FormatMessage(cxlog::VerbosityLevel::DEBUG,
                                                      _FILE_,
                                                      _FUNCTION_,
                                                      _LINE_,
                                                      GenerateLineToLog())};
    const std::string expected{DebugResult()};

    ASSERT_EQ(result, expected);
}
