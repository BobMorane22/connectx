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

#include <cxgui/ILayout.h>

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
class Gtkmm3MenuItem : public Gtk::MenuItem
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
    ~Gtkmm3MenuItem();

private:

    std::unique_ptr<cxgui::ILayout> m_layout;
    std::unique_ptr<Gtk::Image> m_icon;
    std::unique_ptr<Gtk::AccelLabel> m_accelerator;
};

} // namespace cxgui

#endif // GTKMM3MENUITEM_H_C4184C81_A135_45A6_A70F_71CDA081E9F2
