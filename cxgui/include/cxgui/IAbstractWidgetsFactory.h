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
#include <string>

// Can't forward declare because the interfaces contains nested classes used by this factory.
#include <cxgui/ISpinBox.h>

namespace cxgui
{
    class IButton;
    class ILabel;
    class IMenu;
    class IMenuBar;
    class IMenuItem;

    class IStatusBar;
    class IStatusBarPresenter;

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
///@{ @name Common widgets
// ================================================================================================

    /******************************************************************************************//**
     * @brief Creates a button instance with no initial contents.
     *
     * Buttons show contents and can be clicked on.
     *
     * @post
     *      The returned button instance is valid.
     *
     * @return
     *      A button instance.
     *
     *********************************************************************************************/
    [[nodiscard]] virtual std::unique_ptr<IButton> CreateButton() const = 0;

    /******************************************************************************************//**
     * @brief Creates a button instance with initial contents.
     *
     * Buttons show contents and can be clicked on.
     *
     * @param p_contents
     *      The button's intial contents.
     *
     * @post
     *      The returned button instance is valid.
     *
     * @return
     *      A button instance.
     *
     *********************************************************************************************/
    [[nodiscard]] virtual std::unique_ptr<IButton> CreateButton(const std::string& p_contents) const = 0;

    /******************************************************************************************//**
     * @brief Creates a label instance with no initial contents.
     *
     * Labels show contents.
     *
     * @post
     *      The returned label instance is valid.
     *
     * @return
     *      A label instance.
     *
     *********************************************************************************************/
    [[nodiscard]] virtual std::unique_ptr<ILabel> CreateLabel() const = 0;

    /******************************************************************************************//**
     * @brief Creates a label instance with initial contents.
     *
     * Labels show contents.
     *
     * @param p_contents
     *      The label's intial contents.
     *
     * @post
     *      The returned label instance is valid.
     *
     * @return
     *      A label instance.
     *
     *********************************************************************************************/
    [[nodiscard]] virtual std::unique_ptr<ILabel> CreateLabel(const std::string& p_contents) const = 0;

    /******************************************************************************************//**
     * @brief Creates a spin box instance.
     *
     * @param p_initialValue
     *      The initialValue for the spin box.
     *
     * @param p_climbRate
     *      The spin box's climb rate. The climb rate is the amount added of subsracted to the
     *      current value when the user interacts with the spin box's spin buttons.
     *
     * @param p_range
     *      The spin box's valid value range.
     *
     *********************************************************************************************/
    [[nodiscard]] virtual std::unique_ptr<ISpinBox> CreateSpinBox(
        int p_initialValue,
        const ISpinBox::ClimbRate& p_climbRate,
        const ISpinBox::Range& p_range) const = 0;

///@}

// ================================================================================================
///@{ @name Menu bar
// ================================================================================================

    /******************************************************************************************//**
     * @brief Creates a menu bar instance.
     *
     * Menu bars hold different `IMenu` elements, often divided into thematics. Each menu
     * contains one or more `IMenuItem`, which the user can use to activate features by
     * clicking on them.
     *
     * @post
     *      The returned menu bar instance is valid.
     *
     * @return
     *      A menu bar instance.
     *
     *********************************************************************************************/
    [[nodiscard]] virtual std::unique_ptr<IMenuBar> CreateMenuBar() const = 0;

    /******************************************************************************************//**
     * Creates a menu instance.
     *
     * Menus are used in a `IMenuBar`. They hold `IMenuItem`, which are the elements
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
    [[nodiscard]] virtual std::unique_ptr<IMenu> CreateMenu(const std::string p_title) const = 0;

    /******************************************************************************************//**
     * Creates a menu item instance.
     *
     * Menu items are used in a `IMenu`, which compose a `IMenuBar`. They are the
     * elements with which the user interacts to activate features.
     *
     * Menu items have a mandatory textual label and an optional icon representing the feature
     * the menu item activates. If present, the icon is drawn to the left of the textual label.
     * Items with and without icons can be mixed in a single `IMenu`. In this case, all
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
    [[nodiscard]] virtual std::unique_ptr<IMenuItem> CreateMenuItem(
        const std::string p_label,
        const std::optional<FreeDesktop::StdActionIcon>& p_icon = std::nullopt) const = 0;

///@}


// ================================================================================================
///@{ @name Status bar
// ================================================================================================

    /******************************************************************************************//**
     * Creates a status bar instance.
     *
     * Status bars are typically used at the bottom of windows to print information about the
     * application's status.
     *
     * @param p_presenter
     *      A status bar presenter.
     *
     * @post
     *      The returned status bar instance is valid.
     *
     * @return
     *      A status bar instance.
     *
     *********************************************************************************************/
    [[nodiscard]] virtual std::unique_ptr<IStatusBar> CreateStatusBar(IStatusBarPresenter& p_presenter) const = 0;

///@}

};

} // namespace cxgui

#endif // IABSTRACTWIDGETSFACTORY_H_FE309A25_8E9C_4F60_852F_0ADD5750890F
