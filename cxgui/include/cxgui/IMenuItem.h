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
 * @file IMenuItem.h
 * @date 2024
 *
 *************************************************************************************************/

#ifndef IMENUITEM_H_6ADCF292_5D13_4DC8_8DE9_542AD2F0602B
#define IMENUITEM_H_6ADCF292_5D13_4DC8_8DE9_542AD2F0602B

#include <functional>
#include <memory>

#include <cxgui/ISignal.h>
#include <cxgui/IWidget.h>

namespace cxgui
{

class KeyboardShortcut;

}

namespace cxgui
{

/**********************************************************************************************//**
 * @brief Menu items are items in a menu that can be triggered.
 *
 * Menu items can be triggered (either by clicking on them or by hitting a keyboard shortcut) to
 * carry out actions. Note that if registered, the keyboard shortcut will appear to the right of
 * the menu item.
 *
 * @see cxgui::IMenuBar
 * @see cxgui::IMenu
 *
 *************************************************************************************************/
class IMenuItem : public IWidget
{

public:

    /******************************************************************************************//**
     * @brief Destructor.
     *
     *********************************************************************************************/
    virtual ~IMenuItem() = default;
    
    /******************************************************************************************//**
     * @brief Signal when the menu item is triggerred.
     *
     * A menu item can be triggered by either clicking on it or by hitting its registered
     * keyboard shortcut).
     *
     * @return
     *      The triggered signal.
     *
     *********************************************************************************************/
    [[nodiscard]] virtual std::unique_ptr<ISignal<void>> OnTriggered() = 0;

    /******************************************************************************************//**
     * @brief Adds a keyboard shortcut.
     *
     * @param p_shortcut
     *      The keyboard shortcut to bind to the menu item. There can only be one keyboard
     *      shortcut by menu items. If a keyboard shortcut had already been registered for
     *      the menu item, it is replaced.
     *
     *********************************************************************************************/
    virtual void RegisterKeyboardShortcut(const KeyboardShortcut& p_shortcut) = 0;

};

} // namespace cxgui

#endif // IMENUITEM_H_6ADCF292_5D13_4DC8_8DE9_542AD2F0602B
