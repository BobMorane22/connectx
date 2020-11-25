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
 * @file NotificationContext.h
 * @date 2020
 *
 *************************************************************************************************/

#ifndef NOTIFICATIONCONTEXT_H_3B763656_2127_4F2A_B522_85ECBA656CB8
#define NOTIFICATIONCONTEXT_H_3B763656_2127_4F2A_B522_85ECBA656CB8

namespace cxmodel
{

/**********************************************************************************************//**
 * @brief Connect X model notification context.
 *
 * Describes all the contexts from which the Connect X model may notify.
 *
 ************************************************************************************************/
enum class NotificationContext
{
    // User operations:
    CREATE_NEW_GAME,
    CHIP_DROPPED,
    REDO,
    UNDO,

    // Game states:
    GAME_WON,
    GAME_ENDED,
    GAME_REINITIALIZED
};

} // namespace cxmodel

#endif // NOTIFICATIONCONTEXT_H_3B763656_2127_4F2A_B522_85ECBA656CB8
