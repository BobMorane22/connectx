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

namespace cxgui
{

enum class MenuItem
{
    GAME,
    NEW_GAME,
    REINITIALIZE_GAME,
    UNDO,
    QUIT,

    HELP,
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

} // namespace cxgui

#endif // MENUITEM_H_A0647363_208A_493B_A9B8_4C275516DCCC
