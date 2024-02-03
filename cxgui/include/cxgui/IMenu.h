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
 * @file IMenu.h
 * @date 2024
 *
 *************************************************************************************************/

#ifndef IMENU_H_2C2DB70B_1417_447D_8614_8D237933B1FF
#define IMENU_H_2C2DB70B_1417_447D_8614_8D237933B1FF

#include <cxgui/IWidget.h>

namespace cxgui
{
    class IMenuItem;
}

namespace cxgui
{

/**********************************************************************************************//**
 * @brief A menu composed of actions that can be triggered by the user.
 *
 * Menus are meant to be used in a menubar. Each menu has a title, which is used to identify it in
 * the menu bar.
 *
 * @see cxgui::IMenuBar
 * @see cxgui::IMenuItem
 *
 *************************************************************************************************/
class IMenu : public IWidget
{

public:

    /******************************************************************************************//**
     * @brief Destructor.
     *
     *********************************************************************************************/
    virtual ~IMenu() = default;

    /******************************************************************************************//**
     * @brief Registers a menu item into the menu.
     *
     * @param p_item
     *      The menu item to register into the menu.
     *
     *********************************************************************************************/
    virtual void Register(IMenuItem& p_item) = 0;

};

} // namespace cxgui

#endif // IMENU_H_2C2DB70B_1417_447D_8614_8D237933B1FF
