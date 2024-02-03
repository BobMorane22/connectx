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
 * @file Gtkmm3Menu.h
 * @date 2024
 *
 *************************************************************************************************/

#ifndef GTKMM3MENU_H_8F6908BA_083B_4C86_A927_97A375555E22
#define GTKMM3MENU_H_8F6908BA_083B_4C86_A927_97A375555E22

#include <gtkmm/menu.h>

#include <cxgui/IMenu.h>

namespace cxgui
{

/***********************************************************************************************//**
 * @brief Gtkmm 3 implementation of the `cxgui::IMenu` interface.
 *
 **************************************************************************************************/
class Gtkmm3Menu : public IMenu,
                   public Gtk::Menu
{

public:

    /*******************************************************************************************//**
     * @brief Constructor.
     *
     * @param p_title
     *      The menu title, as shown to the user.
     *
     * @pre
     *      The menu title is not empty.
     *
     **********************************************************************************************/
    explicit Gtkmm3Menu(const std::string& p_title);

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

    /*******************************************************************************************//**
     * @brief The Gtk menu item used to show the title.
     *
     * Sadly, Gtkmm 3 (at the time of writing: 3.24.5) does not offer the possibility to create
     * a menu and specify a title "on the spot". The call exists, but was deprecated in Gtkmm
     * 3.10. We have to go trough an extra menu item (of which the menu is a sub-menu of) to
     * add a title. This getter exposes this extra menu item.
     *
     * @return The menu item through which the title, and the menu, can be added.
     *
     **********************************************************************************************/
    [[nodiscard]] Gtk::MenuItem& GetTitleMenuItem();

    // cxgui::IMenu:
    void Register(IMenuItem& p_item) override;

    // cxgui::IWidget:
    [[nodiscard]] size_t GetWidth() const override;
    [[nodiscard]] size_t GetHeight() const override;
    void SetEnabled(EnabledState p_enabled) override;
    void SetMargins(const Margins& p_newMarginSizes) override;

private:

    Gtk::MenuItem m_titleMenuItem;
    std::unique_ptr<IWidget> m_delegate;

};

} // namespace cxgui

#endif // GTKMM3MENU_H_8F6908BA_083B_4C86_A927_97A375555E22
