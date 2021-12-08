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
 * @file VerbosityLevel.h
 * @date 2020
 *
 *************************************************************************************************/

#ifndef VERBOSITYLEVEL_H_E308C91C_1203_4880_A4AD_1983D6680B59
#define VERBOSITYLEVEL_H_E308C91C_1203_4880_A4AD_1983D6680B59

namespace cxlog
{

/***********************************************************************************************//**
 * @enum A verbosity level characterizes how a logger or a log entry should respectively prioritize
 *       a log entry or itself.
 *
 **************************************************************************************************/
enum class VerbosityLevel
{
    NONE    = 0,   // Do no logging.

    FATAL   = 1,   // System can't recover.

    ERROR   = 2,   // System can recover, but something is wrong.

    WARNING = 3,   // Warn about something unexpected that is not an error
                   // but that could lead to errors.

    INFO    = 4,   // General information that has no impact on the system.

    DEBUG   = 5    // Debug information, for developers only.
};

/***********************************************************************************************//**
 * @brief Less-than operator.
 *
 * A first verbosity level is less than a second iff its logging scope is less than the second.
 *
 * @param p_first  The first verbosity level.
 * @param p_second The second verbosity level.
 *
 * @return @c true iff the logging scope of @c p_first is less than the logging scope of
 *         @c p_second.
 *
 * @see cxlog::VerbosityLevel
 *
 **************************************************************************************************/
bool operator<(VerbosityLevel p_first, VerbosityLevel p_second);

/***********************************************************************************************//**
 * @brief Less-than-or-equal-to operator.
 *
 * A first verbosity level is less than a second iff its logging scope is less than or equal to
 * the second.
 *
 * @param p_first  The first verbosity level.
 * @param p_second The second verbosity level.
 *
 * @return @c true iff the logging scope of @c p_first is less than or equal to the logging
 *         scope of @c p_second.
 *
 * @see cxlog::VerbosityLevel
 *
 **************************************************************************************************/
bool operator<=(VerbosityLevel p_first, VerbosityLevel p_second);

/***********************************************************************************************//**
 * @brief Greater-than operator.
 *
 * A first verbosity level is less than a second iff its logging scope is greater than the second.
 *
 * @param p_first  The first verbosity level.
 * @param p_second The second verbosity level.
 *
 * @return @c true iff the logging scope of @c p_first is greater than the logging scope of
 *         @c p_second.
 *
 * @see cxlog::VerbosityLevel
 *
 **************************************************************************************************/
bool operator>(VerbosityLevel p_first, VerbosityLevel p_second);

/***********************************************************************************************//**
 * @brief Greater-than-or-equal-to operator.
 *
 * A first verbosity level is less than a second iff its logging scope is greater than or equal to
 * the second.
 *
 * @param p_first  The first verbosity level.
 * @param p_second The second verbosity level.
 *
 * @return @c true iff the logging scope of @c p_first is greater than or equal to the logging
 *         scope of @c p_second.
 *
 * @see cxlog::VerbosityLevel
 *
 **************************************************************************************************/
bool operator>=(VerbosityLevel p_first, VerbosityLevel p_second);

} // namespace cxlog

#endif // VERBOSITYLEVEL_H_E308C91C_1203_4880_A4AD_1983D6680B59
