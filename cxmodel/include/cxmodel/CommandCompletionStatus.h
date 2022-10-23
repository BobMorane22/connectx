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
 * @file CommandStatus.h
 * @date 2022
 *
 *************************************************************************************************/

#ifndef COMMANDCOMPLETIONSTATUS_H_D8E68D1D_1790_4070_AE58_CF186972A190
#define COMMANDCOMPLETIONSTATUS_H_D8E68D1D_1790_4070_AE58_CF186972A190

namespace cxmodel
{

/*********************************************************************************************//**
 * @brief Command completion status.
 *
 * Incidates with which degree of success a command was executes. The higher the value, the more
 * critical the error (if any).
 *
 ************************************************************************************************/
enum class CommandCompletionStatus
{
    /** Command completed successfully. */
    SUCCESS,

    /** Command failed in an expected way. As far as the program is concerned,
        this failure is an accetable outcome and was predictable. This type
        of failure should not result in a bug.*/
    FAILED_EXPECTED,

    /** Command failed in an unexpected way. As far as the program is concerned,
        this failure is unacceptable and is the result of an internal error which
        could not have been predicted. Such errors include preconditions and
        postconditions fails. This type of failure will typically result in a bug.*/
    FAILED_UNEXPECTED,
};

static_assert(CommandCompletionStatus::SUCCESS < CommandCompletionStatus::FAILED_EXPECTED);
static_assert(CommandCompletionStatus::FAILED_EXPECTED < CommandCompletionStatus::FAILED_UNEXPECTED);

} // namespace cxmodel

#endif // COMMANDCOMPLETIONSTATUS_H_D8E68D1D_1790_4070_AE58_CF186972A190
