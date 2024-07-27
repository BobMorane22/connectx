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
 * @file KeyboardKeyPressedEvent.h
 * @date 2024
 *
 *************************************************************************************************/

#ifndef KEYBOARDKEYPRESSEDEVENT_H_AF108023_81EE_4BB7_8267_3D08C10B7095
#define KEYBOARDKEYPRESSEDEVENT_H_AF108023_81EE_4BB7_8267_3D08C10B7095

namespace cx::cmn::ui
{

/**********************************************************************************************//**
 * @brief Keyboard key pressed event.
 *
 * The user has pressed a key on his keyboard.
 *
 *************************************************************************************************/
enum class KeyboardKeyPressedEvent
{
    /** Left arrow key pressed. */
    KEY_LEFT,

    /** Right arrow key pressed. */
    KEY_RIGHT,

    /** Down arrow key pressed. */
    KEY_DOWN,
};

} // namespace cx::cmn::ui

#endif // KEYBOARDKEYPRESSEDEVENT_H_AF108023_81EE_4BB7_8267_3D08C10B7095
