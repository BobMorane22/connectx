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
 * @file ISP8601TimestampFormatterTests.cpp
 * @date 2020
 *
 *************************************************************************************************/

#include <regex>

#include <gtest/gtest.h>

#include <ISO8601TimestampFormatter.h>

TEST(ISO8601TimestampFormatter, /*DISABLED_*/FormatTimestamp_Seconds_ReturnsCorrectFormattedTimestamp)
{
    using namespace cxlog;

    std::unique_ptr<ITimestampFormatter> formatter = std::make_unique<ISO8601TimestampFormatter>(TimePrecision::SECONDS);

    const std::string formatted = formatter->FormatTimestamp();

    const std::regex timestampRegex{"\\d\\d\\d\\d-\\d\\d-\\d\\dT\\d\\d:\\d\\d:\\d\\d"};

    ASSERT_TRUE(std::regex_match(formatted, timestampRegex));
}

TEST(ISO8601TimestampFormatter, /*DISABLED_*/FormatTimestamp_MilliSeconds_ReturnsCorrectFormattedTimestamp)
{
    using namespace cxlog;

    std::unique_ptr<ITimestampFormatter> formatter = std::make_unique<ISO8601TimestampFormatter>(TimePrecision::MILLISECONDS);

    const std::string formatted = formatter->FormatTimestamp();

    const std::regex timestampRegex{"\\d\\d\\d\\d-\\d\\d-\\d\\dT\\d\\d:\\d\\d:\\d\\d.\\d\\d\\d"};

    ASSERT_TRUE(std::regex_match(formatted, timestampRegex));
}

TEST(ISO8601TimestampFormatter, /*DISABLED_*/FormatTimestamp_MicroSeconds_ReturnsCorrectFormattedTimestamp)
{
    using namespace cxlog;

    std::unique_ptr<ITimestampFormatter> formatter = std::make_unique<ISO8601TimestampFormatter>(TimePrecision::MICROSECONDS);

    const std::string formatted = formatter->FormatTimestamp();

    const std::regex timestampRegex{"\\d\\d\\d\\d-\\d\\d-\\d\\dT\\d\\d:\\d\\d:\\d\\d.\\d\\d\\d\\d\\d\\d"};

    ASSERT_TRUE(std::regex_match(formatted, timestampRegex));
}

TEST(ISO8601TimestampFormatter, /*DISABLED_*/FormatTimestamp_NanoSeconds_ReturnsCorrectFormattedTimestamp)
{
    using namespace cxlog;

    std::unique_ptr<ITimestampFormatter> formatter = std::make_unique<ISO8601TimestampFormatter>(TimePrecision::NANOSECONDS);

    const std::string formatted = formatter->FormatTimestamp();

    const std::regex timestampRegex{"\\d\\d\\d\\d-\\d\\d-\\d\\dT\\d\\d:\\d\\d:\\d\\d.\\d\\d\\d\\d\\d\\d\\d\\d\\d"};

    ASSERT_TRUE(std::regex_match(formatted, timestampRegex));
}
