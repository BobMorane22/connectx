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
 * @file widgetsFactory.h
 * @date 2024
 *
 *************************************************************************************************/

#ifndef WIDGETSFACTORY_H_63877FD3_06FC_42A5_91CE_9B02B141F34C
#define WIDGETSFACTORY_H_63877FD3_06FC_42A5_91CE_9B02B141F34C

#include <memory>

namespace cx::cmn::ui
{
    class IAbstractWidgetsFactory;
}

namespace cx::cmn::ui::gtkmm3
{

/**********************************************************************************************//**
 * @brief Creates a factory instance for common widgets.
 *
 * @param p_gtkApplication
 *      The `Gtk::Application` instance representing the current application the factory is used for.
 *      Without it, widgets cannot be rendered on the screen.
 *
 * @post
 *      The returned factory is valid.
 *
 * @return
 *      A factory instance which is to be used to create common widgets. The widgets are
 *      created by using Gtkmm version 3.24.5.
 *
 *************************************************************************************************/
[[nodiscard]] std::unique_ptr<cx::cmn::ui::IAbstractWidgetsFactory> CreateFactory();

} // namespace cx::cmn::ui::gtkmm3

#endif // WIDGETSFACTORY_H_63877FD3_06FC_42A5_91CE_9B02B141F34C
