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
 * @file IAnimatedBoard.h
 * @date 2024
 *
 *************************************************************************************************/

#ifndef IANIMATEDBOARD_H_138FF453_BD0C_423D_A57F_1C1834CB8749
#define IANIMATEDBOARD_H_138FF453_BD0C_423D_A57F_1C1834CB8749

#include <cxgui/IWidget.h>

#include <cxmodel/common.h>
#include <cxmodel/IObserver.h>
#include <cxmodel/Subject.h>
#include <cxmodel/ChipColor.h>
#include <cxgui/BoardAnimationNotificationContext.h>
#include <cxgui/IBoardInformation.h>

namespace cxgui
{

/**********************************************************************************************//**
 * @brief User events performed on the animated board widget.
 *
 *************************************************************************************************/
enum class UserAction
{
    /** The user clicked the mouse on the board. */
    MOUSE_CLICKED,
};

/**********************************************************************************************//**
 * @brief Subject on which user actions are performed.
 *
 * Observers react when this subject is acted upon.
 *
 *************************************************************************************************/
using UserActionSubject = cxmodel::Subject<UserAction>;

/**********************************************************************************************//**
 * @brief Observers for user actions.
 *
 *************************************************************************************************/
using IUserActionObserver = cxmodel::IObserver<UserAction>;

/**********************************************************************************************//**
 * @brief Game board widget supporting animations.
 *
 * Represents a customizable game board for Connect X. The game board is composed of the actual
 * board in which chips are dropped, but also an extra row, at the top, to visualize the chip
 * of the player that is currently playing.
 *
 * With this widget, chip movements are animated (moving left, right, etc). Board animation
 * events are handled through a subject/observer system in which a user can, for example,
 * start an animation and then be notified when the animation finishes to resume the game.
 *
 * Mouse clicks are also events that can be handled through a subject/observer system.
 *
 * For now, animations are assumed to be synchronous, which means that during animations, the
 * game must not go on and the user should not be able to interract with the board.
 *
 *************************************************************************************************/
class IAnimatedBoard : public IWidget,
                       public cxgui::IBoardInformation,
                       public cxgui::IBoardAnimationObserver,
                       public cxgui::BoardAnimationSubject,
                       public cxgui::UserActionSubject
{

public:

    /******************************************************************************************//**
     * @brief Destructor.
     *
     *********************************************************************************************/
    virtual ~IAnimatedBoard() = default;

    /******************************************************************************************//**
     * @brief Gets the column in which the chip in the next disc area is currently located.
     *
     * @return
     *      The column in which the chip currently is located.
     *
     *********************************************************************************************/
    [[nodiscard]] virtual const cxmodel::Column& GetCurrentColumn() const = 0;

    /******************************************************************************************//**
     * @brief Gets the color of the chip currently in the next disc area.
     *
     * @return
     *      The color of the disc in the next disc area. If there is none, transparent is returned.
     *
     *********************************************************************************************/
    [[nodiscard]] virtual cxmodel::ChipColor GetCurrentChipColor() const = 0;

};

} // namespace cxgui

#endif // IANIMATEDBOARD_H_138FF453_BD0C_423D_A57F_1C1834CB8749
