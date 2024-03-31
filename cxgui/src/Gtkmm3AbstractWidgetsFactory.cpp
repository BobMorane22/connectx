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
 * @file Gtkmm3AbstractWidgetsFactory.cpp
 * @date 2024
 *
 *************************************************************************************************/

#include <cxinv/assertion.h>
#include <cxgui/StdActionIcon.h>
#include <cxgui/Gtkmm3AbstractWidgetsFactory.h>
#include <cxgui/Gtkmm3Menu.h>
#include <cxgui/Gtkmm3MenuBar.h>
#include <cxgui/Gtkmm3MenuItem.h>
#include <cxgui/Gtkmm3WidgetDelegate.h>

cxgui::Gtkmm3AbstractWidgetsFactory::Gtkmm3AbstractWidgetsFactory(Glib::RefPtr<Gtk::Application> p_gtkApplication)
{
    PRECONDITION(bool(p_gtkApplication));

    m_gtkApplication = p_gtkApplication;

    POSTCONDITION(bool(m_gtkApplication));
}

std::unique_ptr<cxgui::IMenuBar> cxgui::Gtkmm3AbstractWidgetsFactory::CreateMenuBar() const
{
    auto menuBar = cxgui::CreateWidget<cxgui::Gtkmm3MenuBar>();
    POSTCONDITION(menuBar);

    return menuBar;
}

std::unique_ptr<cxgui::IMenu> cxgui::Gtkmm3AbstractWidgetsFactory::CreateMenu(const std::string p_title) const
{
    IF_PRECONDITION_NOT_MET_DO(!p_title.empty(), return nullptr;);

    auto menu = cxgui::CreateWidget<cxgui::Gtkmm3Menu>(p_title);
    POSTCONDITION(menu);

    return menu;
}

std::unique_ptr<cxgui::IMenuItem> cxgui::Gtkmm3AbstractWidgetsFactory::CreateMenuItem(
    const std::string p_label,
    const std::optional<FreeDesktop::StdActionIcon>& p_icon) const
{
    IF_PRECONDITION_NOT_MET_DO(!p_label.empty(), return nullptr;);

    auto menuItem = CreateWidget<Gtkmm3MenuItem>(p_label, p_icon);
    POSTCONDITION(menuItem);

    return menuItem;
}
