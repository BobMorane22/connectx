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
 * @file ISO8601TimestampFormatter.h
 * @date 2020
 *
 * Format timestamps to the ISO 8601 format (yyyy-mm-ddThh:mm:ss[.mmm]).
 *
 *************************************************************************************************/

#ifndef ISO8601TIMESTAMPFORMATTER_H_C98443B5_733A_46B9_8B0C_EF059B9701E3
#define ISO8601TIMESTAMPFORMATTER_H_C98443B5_733A_46B9_8B0C_EF059B9701E3

#include "ITimestampFormatter.h"

namespace cxlog
{

/***********************************************************************************************//**
 * @brief Time precisions.
 *
 * Different time precisions to feed to the formatter to control the output to the desired
 * format.
 *
 **************************************************************************************************/
enum class TimePrecision
{
    SECONDS      = 0, // Output up to seconds.
    MILLISECONDS = 3, // Output up to seconds and add the millisecond fraction of the next second.
    MICROSECONDS = 6, // Output up to seconds and add the microsecond fraction of the next second.
    NANOSECONDS  = 9  // Output up to seconds and add the nanosecond fraction of the next second.
};

/***********************************************************************************************//**
 * @brief Time precisions.
 *
 * Different time precisions to feed to the formatter to control the output to the desired
 * format.
 *
 **************************************************************************************************/
class ISO8601TimestampFormatter : public ITimestampFormatter
{

public:

    /*******************************************************************************************//**
     * @brief Constructor.
     *
     * @param p_precision The time precision to use with this formatter.
     *
     **********************************************************************************************/
    ISO8601TimestampFormatter(const TimePrecision p_precision);

    /*******************************************************************************************//**
     * @brief Format a timestamp to a string following the ISO 8601 standard. The resulting string,
     *        depending on the chosen time precision, is in the form
     *        <tt>yyyy-mm-ddThh:mm:ss[.mmm]</tt>.
     *
     * @return A string containing the formatted timestamp.
     *
     **********************************************************************************************/
    std::string FormatTimestamp() const override;


private:

    const bool m_precisionNeeded{false};

    const TimePrecision m_precision {TimePrecision::SECONDS};

};

} // namespace cxlog

#endif // ISO8601TIMESTAMPFORMATTER_H_C98443B5_733A_46B9_8B0C_EF059B9701E3
