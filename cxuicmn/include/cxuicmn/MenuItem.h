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
 * @file MenuItem.h
 * @date 2020
 *
 *************************************************************************************************/

#ifndef MENUITEM_H_A0647363_208A_493B_A9B8_4C275516DCCC
#define MENUITEM_H_A0647363_208A_493B_A9B8_4C275516DCCC

namespace cx::cmn::ui
{

/**********************************************************************************************//**
 * @brief Items found in the Connect X application menu.
 *
 *************************************************************************************************/
enum class MenuItem
{
    /** Game menu in the menu bar. */
    GAME,

    /** Shows the "New game" window. */
    NEW_GAME,

    /** Reinitializes the game, keeping the same parameters. */
    REINITIALIZE_GAME,

    /** Undo the last action. */
    UNDO,

    /** Redo the last action. */
    REDO,

    /** Quits Connect X. */
    QUIT,

    /** Help menu in the menu bar. */
    HELP,

    /** Shows the user help documentation. */
    CONTENTS,

    /** Lauches the "About" window.  */
    ABOUT,
};

/******************************************************************************************//**
 * @brief Creates a label associated to a menu item.
 *
 * @param p_menuItem The menu item to get the label for.
 *
 * @return The associated label.
 *
 ********************************************************************************************/
std::string MakeLabel(MenuItem p_menuItem);

} // namespace cx::cmn::ui

#endif // MENUITEM_H_A0647363_208A_493B_A9B8_4C275516DCCC
