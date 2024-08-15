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
 * @date 2023
 *
 *************************************************************************************************/

#ifndef GTKMM3MENUITEM_H_C4184C81_A135_45A6_A70F_71CDA081E9F2
#define GTKMM3MENUITEM_H_C4184C81_A135_45A6_A70F_71CDA081E9F2

#include <memory>
#include <optional>

#include <gtkmm/image.h>
#include <gtkmm/menuitem.h>

#include <cxcmnui/IMenuItem.h>

namespace Gtk
{
    class Grid;
}

namespace cx::cmn::ui::FreeDesktop
{
    enum class StdActionIcon;
}

namespace cx::cmn::ui::gtkmm3
{

/**********************************************************************************************//**
 * @brief Gtkmm 3 implementation for the `cx::cmn::ui::gtkmm3::IMenuItem` interface.
 *
 *************************************************************************************************/
class MenuItem : public cx::cmn::ui::IMenuItem,
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
     * @pre
     *      The text is not empty.
     *
     *********************************************************************************************/
    MenuItem(
        const std::string& p_label,
        const std::optional<cx::cmn::ui::FreeDesktop::StdActionIcon>& p_icon = std::nullopt);

    /******************************************************************************************//**
     * @brief Destructor.
     *
     *********************************************************************************************/
    ~MenuItem() override;

    /*******************************************************************************************//**
     * @brief Sets the delegate for widget common facilities.
     *
     * The delegate is reponsible to carry the implementation for generic `cx::cmn::ui::gtkmm3::IWidget` operations.
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
    void SetDelegate(std::unique_ptr<cx::cmn::ui::IWidget> p_delegate);

    // cx::cmn::ui::IMenuItem:
    [[nodiscard]] std::unique_ptr<cx::cmn::ui::ISignal<void>> OnTriggered() override;
    void RegisterKeyboardShortcut(const cx::cmn::ui::KeyboardShortcut& p_shortcut) override;

    // cx::cmn::ui::IWidget:
    [[nodiscard]] size_t GetWidth() const override;
    [[nodiscard]] size_t GetHeight() const override;
    void SetEnabled(cx::cmn::ui::EnabledState p_enabled) override;
    void SetMargins(const cx::cmn::ui::Margins& p_newMarginSizes) override;
    void SetTooltip(const std::string& p_tooltipContents) override;
    [[nodiscard]] std::unique_ptr<ISignal<cx::cmn::ui::EventPropagation, cx::cmn::ui::KeyboardKeyPressedEvent>> OnKeyPressed() override;

private:

    std::unique_ptr<Gtk::Grid> m_layout;
    std::unique_ptr<Gtk::Image> m_icon;
    std::unique_ptr<Gtk::AccelLabel> m_accelerator;

    std::unique_ptr<cx::cmn::ui::IWidget> m_delegate;

};

} // namespace cx::cmn::ui::gtkmm3

#endif // GTKMM3MENUITEM_H_C4184C81_A135_45A6_A70F_71CDA081E9F2
