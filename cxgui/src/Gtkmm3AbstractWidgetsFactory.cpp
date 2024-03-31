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
#include <cxgui/Gtkmm3AbstractWidgetsFactory.h>
#include <cxgui/Gtkmm3MenuBar.h>
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
