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
 * @file DialogRole.h
 * @date 2024
 *
 *************************************************************************************************/

#ifndef DIALOGROLE_H_8B81831F_B231_40D3_9D11_35BC694498EB
#define DIALOGROLE_H_8B81831F_B231_40D3_9D11_35BC694498EB

namespace cxgui
{

/**********************************************************************************************//**
 * @brief Available roles for dialogging with the users.
 *
 *************************************************************************************************/
enum class DialogRole
{
    /** Ask the user a question. */
    QUESTION,

    /** Inform the user on something. */
    INFORMATION,

    /** Warn the user about something. Warning should be about minor issues which are not impacting
        the software's integrity (ex.: bad user input which is handled by the software. The user is
        invited to try again with added recommendations). Otherwise, use the "ERROR" role. */
    WARNING,

    /** Warn the user about a situation which might affect the software's integrigy. */
    ERROR,
};

};

#endif // DIALOGROLE_H_8B81831F_B231_40D3_9D11_35BC694498EB
