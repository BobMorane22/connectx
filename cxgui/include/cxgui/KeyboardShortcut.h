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
 * @file KeyboardShortcut.h
 * @date 2024
 *
 *************************************************************************************************/

#ifndef KEYBOARDSHORTCUT_H_D28AD8FB_B8CC_47FD_BE0F_C7F60C5BF3BC
#define KEYBOARDSHORTCUT_H_D28AD8FB_B8CC_47FD_BE0F_C7F60C5BF3BC

#include <optional>

#include <cxgui/Keys.h>

namespace cxgui
{

/**********************************************************************************************//**
 * @brief Keyboard shortcut.
 *
 * Keyboard shortcut which can be made of a simple key (e.g. `F1`) or two keys to be hit
 * in sequential order (e.g. `Ctrl + Q`). In this last example, `Ctrl` must be hit firts,
 * then `Q`.
 *
 * Keyboard shortcut are used to trigger events using the keyboard.
 *
 *************************************************************************************************/
struct KeyboardShortcut final
{

    /******************************************************************************************//**
     * @brief Constructor.
     *
     * Creates a single key keyboard shortcut.
     *
     * @param p_first
     *      The key to hit.
     *
     *********************************************************************************************/
    explicit KeyboardShortcut(Key p_first);

    /******************************************************************************************//**
     * @brief Copy constructor.
     *
     * Creates a two keys keyboard shortcut.
     *
     * @param p_shortcut
     *      The keyboard shortcut to copy.
     *
     *********************************************************************************************/
    KeyboardShortcut(const KeyboardShortcut& p_shortcut);

    /** The key to hit to activate the keyboard shortcut. If a second key is registered, this
        key must be hit first for the keyboard shortcut to work properly. */
    Key m_first;

    /** The (optional) second key to hit to activate the keyboard shortcut. Must be hit
        after the first key. */
    std::optional<Key> m_second;
};

/**********************************************************************************************//**
 * @brief From two distinct keys, create a keyboard shortcut.
 *
 * @param p_first
 *      The first key to hit.
 * @param p_second
 *      The second key to hit.
 *
 * @pre Both keys are different.
 * @post The second key is valid.
 *
 * @return
 *      A keyboard shortcut with `p_first` as the first key and `p_second` as the second key.
 *
 *************************************************************************************************/
[[nodiscard]] KeyboardShortcut operator+(Key p_first, Key p_second);

} // namespace cxgui

#endif // KEYBOARDSHORTCUT_H_D28AD8FB_B8CC_47FD_BE0F_C7F60C5BF3BC
