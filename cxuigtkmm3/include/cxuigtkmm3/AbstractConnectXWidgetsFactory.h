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
 * @file AbstractConnectXWidgetsFactory.h
 * @date 2024
 *
 *************************************************************************************************/

#ifndef GTKMM3ABSTRACTCONNECTXWIDGETSFACTORY_H_B3944DEE_5157_44D5_91D7_B238464FDD05
#define GTKMM3ABSTRACTCONNECTXWIDGETSFACTORY_H_B3944DEE_5157_44D5_91D7_B238464FDD05

#include <gtkmm/application.h>

#include <cxui/IAbstractConnectXWidgetsFactory.h>

namespace cx::cmn::ui
{
    class IAbstractWidgetsFactory;
}

namespace cx::ui::gtkmm3
{

/**********************************************************************************************//**
 * @brief Creates a factory instance for Connect X specific widgets.
 *
 * @param p_gtkApplication
 *      The `Gtk::Application` instance representing the current application the factory
 *      is used for. Without it, widgets cannot be rendered on the screen.
 *
 * @param p_stdWidgetsFactory
 *      A standard widgets factory. Useful for reusing standard widgets in Connect X specific
 *      widgets, which makes porting easier.
 *
 * @pre
 *      The `Gtk::Application` instance given as an argument is valid.
 *
 * @post
 *      The returned factory is valid.
 *
 * @return
 *      A factory instance which is to be used to create Connect X specific widgets. The widgets
 *      are created by using Gtkmm version 3.24.5.
 *
 *************************************************************************************************/
[[nodiscard]] std::unique_ptr<cx::ui::IAbstractConnectXWidgetsFactory> CreateFactory(
    Glib::RefPtr<Gtk::Application> p_gtkApplication,
    cx::cmn::ui::IAbstractWidgetsFactory& p_stdAbstractWidgetsFactory);

} // namespace cx::ui::gtkmm3

#endif // GTKMM3ABSTRACTCONNECTXWIDGETSFACTORY_H_B3944DEE_5157_44D5_91D7_B238464FDD05
