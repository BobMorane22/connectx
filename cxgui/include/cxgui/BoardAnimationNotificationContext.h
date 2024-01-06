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
 * @file BoardAnimationNotificationContext.h
 * @date 2021
 *
 *************************************************************************************************/

#ifndef BOARDANIMATIONNOTIFICATIONCONTEXT_H_6D195C5E_A7B3_4F4F_9BCA_8E42F897BCA4
#define BOARDANIMATIONNOTIFICATIONCONTEXT_H_6D195C5E_A7B3_4F4F_9BCA_8E42F897BCA4

#include <cxmodel/IObserver.h>
#include <cxmodel/Subject.h>

namespace cxgui
{

/**********************************************************************************************//**
 * @brief Board animation events.
 *
 * Use as the notifications contexts for board animations. Typically, they are used to program
 * actions that must come before, during and after the animation.
 *
 *************************************************************************************************/
enum class BoardAnimationNotificationContext
{
    /** The underlying animation model is now valid. From this point,
        one can safely request animations. */
    ANIMATION_MODEL_VALID,

    /** Move left one column animation notification. */
    ANIMATE_MOVE_LEFT_ONE_COLUMN,

    /** Move left one column animation completed notification. */
    POST_ANIMATE_MOVE_LEFT_ONE_COLUMN,

    /** Move right one column animation notification. */
    ANIMATE_MOVE_RIGHT_ONE_COLUMN,

    /** Move right one column animation completed notification. */
    POST_ANIMATE_MOVE_RIGHT_ONE_COLUMN,

    /** Move right to some target animation notification. */
    ANIMATE_MOVE_RIGHT_TO_TARGET,

    /** Move right to some target animation completed notification. */
    POST_ANIMATE_MOVE_RIGHT_TO_TARGET,

    /** Drop chip animation notification. */
    ANIMATE_MOVE_DROP_CHIP,

    /** Drop chip completed animation notification. */
    POST_ANIMATE_DROP_CHIP,

    /** Undo drop chip animation notification. */
    ANIMATE_UNDO_DROP_CHIP,

    /** Undo drop chip animation completed notification. */
    POST_ANIMATE_UNDO_DROP_CHIP,

    /** Redo drop chip animation notification. */
    ANIMATE_REDO_DROP_CHIP,

    /** Redo drop chip animation completed notification. */
    POST_ANIMATE_REDO_DROP_CHIP,

    /** Reinitialize board animation notification. */
    ANIMATE_REINITIALIZE_BOARD,

    /** Reinitialize board animation completed notification. */
    POST_ANIMATE_REINITIALIZE_BOARD,
};

/**********************************************************************************************//**
 * @brief Board animation notifications observer.
 *
 *************************************************************************************************/
using IBoardAnimationObserver = cxmodel::IObserver<cxgui::BoardAnimationNotificationContext>;

/**********************************************************************************************//**
 * @brief Board animation notifications subject.
 *
 *************************************************************************************************/
using BoardAnimationSubject = cxmodel::Subject<cxgui::BoardAnimationNotificationContext>;

} // namespace cxgui

#endif // BOARDANIMATIONNOTIFICATIONCONTEXT_H_6D195C5E_A7B3_4F4F_9BCA_8E42F897BCA4
