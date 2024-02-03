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
 * @file IMenuBar.h
 * @date 2024
 *
 *************************************************************************************************/

#ifndef IMENUBAR_H_7283BF86_D1E9_4A7D_8935_A46FD2DAC73F
#define IMENUBAR_H_7283BF86_D1E9_4A7D_8935_A46FD2DAC73F

#include <cxgui/IWidget.h>

namespace cxgui
{

class IMenu;

}

namespace cxgui
{

/**********************************************************************************************//**
 * @brief Widgets for displaying menus.
 *
 * @see cxgui::IMenu
 * @see cxgui::IMenuItem
 *
 *************************************************************************************************/
class IMenuBar : public IWidget
{

public:

    /******************************************************************************************//**
     * @brief Destructor.
     *
     *********************************************************************************************/
    virtual ~IMenuBar() = default;

    /******************************************************************************************//**
     * @brief Registers a new menu.
     *
     * Once a menu is registered in the menu bar, it will be displayed as part of it.
     *
     * @param p_menu
     *      The menu to register to the menubar.
     *
     *********************************************************************************************/
    virtual void Register(IMenu& p_menu) = 0;

};

} // namespace cxgui

#endif // IMENUBAR_H_7283BF86_D1E9_4A7D_8935_A46FD2DAC73F
