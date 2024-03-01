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
 * @file Gtkmm3MenuItem.h
 * @date 2023
 *
 *************************************************************************************************/

#ifndef GTKMM3MENUITEM_H_C4184C81_A135_45A6_A70F_71CDA081E9F2
#define GTKMM3MENUITEM_H_C4184C81_A135_45A6_A70F_71CDA081E9F2

#include <memory>
#include <optional>

#include <gtkmm/image.h>
#include <gtkmm/menuitem.h>

#include <cxgui/IMenuItem.h>

namespace Gtk
{
    class Grid;
}

namespace cxgui::FreeDesktop
{
    enum class StdActionIcon;
}

namespace cxgui
{

/**********************************************************************************************//**
 * @brief Gtkmm 3 implementation for the `cxgui::IMenuItem` interface.
 *
 *************************************************************************************************/
class Gtkmm3MenuItem : public IMenuItem,
                       public Gtk::MenuItem
{

public:

    /******************************************************************************************//**
     * @brief Constructor.
     *
     * @param p_label
     *      The text to appear on the menu item.
     * @param p_icon
     *      The optional icon to appear on the menu item.
     *
     * @precondition
     *      The text is not empty.
     *
     *********************************************************************************************/
    Gtkmm3MenuItem(const std::string& p_label,
                   const std::optional<FreeDesktop::StdActionIcon>& p_icon = std::nullopt);

    /******************************************************************************************//**
     * @brief Destructor.
     *
     *********************************************************************************************/
    ~Gtkmm3MenuItem() override;

    /*******************************************************************************************//**
     * @brief Sets the delegate for widget common facilities.
     *
     * The delegate is reponsible to carry the implementation for generic `cxgui::IWidget` operations.
     * It is meant to avoid implementation duplication.
     *
     * @param p_delegate
     *      The widget delegate.
     *
     * @pre
     *      The widget delegate instance given as an argument is valid.
     * @post
     *      The registered widget delegate is valid.
     *
     **********************************************************************************************/
    void SetDelegate(std::unique_ptr<IWidget> p_delegate);

    // cxgui::IMenuItem:
    [[nodiscard]] std::unique_ptr<ISignal<void>> OnTriggered() override;
    void RegisterKeyboardShortcut(const KeyboardShortcut& p_shortcut) override;

    // cxgui::IWidget:
    [[nodiscard]] size_t GetWidth() const override;
    [[nodiscard]] size_t GetHeight() const override;
    void SetEnabled(EnabledState p_enabled) override;
    void SetMargins(const Margins& p_newMarginSizes) override;
    void SetTooltip(const std::string& p_tooltipContents) override;

private:

    std::unique_ptr<Gtk::Grid> m_layout;
    std::unique_ptr<Gtk::Image> m_icon;
    std::unique_ptr<Gtk::AccelLabel> m_accelerator;

    std::unique_ptr<IWidget> m_delegate;

};

} // namespace cxgui

#endif // GTKMM3MENUITEM_H_C4184C81_A135_45A6_A70F_71CDA081E9F2
