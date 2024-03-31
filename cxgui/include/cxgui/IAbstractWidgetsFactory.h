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
 * @file IAbstractWidgetsFactory.h
 * @date 2024
 *
 *************************************************************************************************/

#ifndef IABSTRACTWIDGETSFACTORY_H_FE309A25_8E9C_4F60_852F_0ADD5750890F
#define IABSTRACTWIDGETSFACTORY_H_FE309A25_8E9C_4F60_852F_0ADD5750890F

#include <memory>
#include <optional>

namespace cxgui
{
    class IMenu;
    class IMenuBar;
    class IMenuItem;

    namespace FreeDesktop
    {
        enum class StdActionIcon;
    }
}

namespace cxgui
{

/**********************************************************************************************//**
 * @brief Abstract widgets factory.
 *
 * Create standard widgets (i.e. buttons, labels, textboxes, etc.) without dealing with the
 * underlying toolkit.
 *
 *************************************************************************************************/
class IAbstractWidgetsFactory
{

public:

    /******************************************************************************************//**
     * @brief Destructor.
     *
     *********************************************************************************************/
    virtual ~IAbstractWidgetsFactory() = default;

// ================================================================================================
///@{ @name Menu bar
// ================================================================================================

    /******************************************************************************************//**
     * @brief Creates a menu bar instance.
     *
     * Menu bars hold different `cxgui::IMenu` elements, often divided into thematics. Each menu
     * contains one or more `cxgui::IMenuItem`, which the user can use to activate features by
     * clicking on them.
     *
     * @post
     *      The returned menu bar instance is valid.
     *
     * @return
     *      A menu bar instance.
     *
     *********************************************************************************************/
    [[nodiscard]] virtual std::unique_ptr<cxgui::IMenuBar> CreateMenuBar() const = 0;

    /******************************************************************************************//**
     * Creates a menu instance.
     *
     * Menus are used in a `cxgui::IMenuBar`. They hold `cxgui::IMenuItem`, which are the elements
     * the user interacts with to activate features.
     *
     * @param p_title
     *      The menu title, as shown to the user.
     *
     * @pre
     *      The menu title is not empty.
     *
     * @post
     *      The returned menu instance is valid.
     *
     * @return
     *      A menu instance.
     *
     *********************************************************************************************/
    [[nodiscard]] virtual std::unique_ptr<cxgui::IMenu> CreateMenu(const std::string p_title) const = 0;

    /******************************************************************************************//**
     * Creates a menu item instance.
     *
     * Menu items are used in a `cxgui::IMenu`, which compose a `cxgui::IMenuBar`. They are the
     * elements with which the user interacts to activate features.
     *
     * Menu items have a mandatory textual label and an optional icon representing the feature
     * the menu item activates. If present, the icon is drawn to the left of the textual label.
     * Items with and without icons can be mixed in a single `cxgui::IMenu`. In this case, all
     * texual labels are aligned to the left.
     *
     * @param p_label
     *      The text to appear on the menu item.
     * @param p_icon
     *      The optional icon to appear on the menu item.
     *
     * @pre
     *      The label text is not empty.
     *
     * @post
     *      The returned menu item instance is valid.
     *
     * @return
     *      A menu item instance.
     *
     *********************************************************************************************/
    [[nodiscard]] virtual std::unique_ptr<cxgui::IMenuItem> CreateMenuItem(
        const std::string p_label,
        const std::optional<FreeDesktop::StdActionIcon>& p_icon = std::nullopt) const = 0;

///@}

};

} // namespace cxgui

#endif // IABSTRACTWIDGETSFACTORY_H_FE309A25_8E9C_4F60_852F_0ADD5750890F
