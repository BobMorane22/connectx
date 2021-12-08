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
 * @file ISO8601TimestampFormatter.cpp
 * @date 2020
 *
 *************************************************************************************************/

#include <chrono>
#include <iomanip>
#include <sstream>

#include <cxinv/assertion.h>
#include <cxlog/ISO8601TimestampFormatter.h>

using namespace std::chrono;

namespace
{

double CountFromPrecision(const system_clock::time_point& p_timePoint,
                          const cxlog::TimePrecision p_precision)

{
    switch(p_precision)
    {
        case cxlog::TimePrecision::MILLISECONDS:
        {
            const auto milli{duration_cast<milliseconds>(p_timePoint.time_since_epoch()) % 1000};

            return milli.count();
        }
        case cxlog::TimePrecision::MICROSECONDS:
        {
            const auto micro{duration_cast<microseconds>(p_timePoint.time_since_epoch()) % 1000000};

            return micro.count();
        }
        case cxlog::TimePrecision::NANOSECONDS:
        {
            const auto nano{duration_cast<nanoseconds>(p_timePoint.time_since_epoch()) % 1000000000};

            return nano.count();
        }
        // Unreachable code: removed from coverage.
        // LCOV_EXCL_START
        default:
            ASSERT_ERROR_MSG("Unknown precision!");
    }

    return 0.0;
    // LCOV_EXCL_STOP
}

} // namespace

cxlog::ISO8601TimestampFormatter::ISO8601TimestampFormatter(const cxlog::TimePrecision p_precision)
 : m_precisionNeeded{p_precision != TimePrecision::SECONDS ? true : false}
 , m_precision{p_precision}
{
}

// yyyy-mm-ddThh:mm:ss[.mmm]
std::string cxlog::ISO8601TimestampFormatter::FormatTimestamp() const
{
    // Get current time:
    const auto now{system_clock::now()};

    // Get broken down time:
    const auto timer{system_clock::to_time_t(system_clock::now())};
    const auto brokenTime{*(std::localtime(&timer))};

    // Format:
    std::ostringstream oss;

    oss << std::put_time(&brokenTime, "%Y-%m-%dT%H:%M:%S");

    if(m_precisionNeeded)
    {
        oss.precision(0);

        oss << '.'
            << std::setfill('0')
            << std::setw(static_cast<std::streamsize>(m_precision))
            << std::fixed
            << CountFromPrecision(now, m_precision);
    }

    return oss.str();
}
