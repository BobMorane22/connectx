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
 * @file ModelNotificationContext.h
 * @date 2020
 *
 *************************************************************************************************/

#ifndef NOTIFICATIONCONTEXT_H_3B763656_2127_4F2A_B522_85ECBA656CB8
#define NOTIFICATIONCONTEXT_H_3B763656_2127_4F2A_B522_85ECBA656CB8

#include "IObserver.h"
#include "Subject.h"

namespace cxmodel
{

/**********************************************************************************************//**
 * @brief Connect X model notification context.
 *
 * Describes all the contexts from which the Connect X model may notify.
 *
 ************************************************************************************************/
enum class ModelNotificationContext
{
    /** A new game was created.*/
    CREATE_NEW_GAME,

    /** A chip was sucessfully dropped into the game board.*/
    CHIP_DROPPED,

    /** A chip failed to drop into the game board. Possible causes include a full column.*/
    CHIP_DROPPED_FAILED,

    /** A chip was moved left by one column in the New Disc Area.*/
    CHIP_MOVED_LEFT_ONE_COLUMN,

    /** A chip was moved right by one column in the New Disc Area.*/
    CHIP_MOVED_RIGHT_ONE_COLUMN,

    /** The last successful disc drop was undone.*/
    UNDO_CHIP_DROPPED,

    /** The last successful undone disc drop was redone.*/
    REDO_CHIP_DROPPED,

    /** The current game was won.*/
    GAME_WON,

    /** The current game resulted in a tie.*/
    GAME_TIED,

    /** The current game was ended by the user.*/
    GAME_ENDED,

    /** The current game was reinitialized by the user.*/
    GAME_REINITIALIZED,
};

using IModelObserver = IObserver<ModelNotificationContext>;
using ModelSubject = Subject<ModelNotificationContext>;


} // namespace cxmodel

#endif // NOTIFICATIONCONTEXT_H_3B763656_2127_4F2A_B522_85ECBA656CB8
