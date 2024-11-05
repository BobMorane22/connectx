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

#ifndef WIDGETSFACTORY_H_5926A0C8_0487_4398_8AD7_027927FEF81A
#define WIDGETSFACTORY_H_5926A0C8_0487_4398_8AD7_027927FEF81A

#include <memory>

namespace cx::cmn::ui
{
    class IAbstractWidgetsFactory;
}

namespace cx::ui
{
    class IAbstractConnectXWidgetsFactory;
}

namespace cx::ui::gtkmm3
{

/**********************************************************************************************//**
 * @brief Creates a factory instance for Connect X specific widgets.
 *
 * @param p_stdWidgetsFactory
 *      A standard widgets factory. Useful for reusing standard widgets in Connect X specific
 *      widgets, which makes porting easier.
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
    cx::cmn::ui::IAbstractWidgetsFactory& p_stdAbstractWidgetsFactory);

} // namespace cx::ui::gtkmm3

#endif // WIDGETSFACTORY_H_5926A0C8_0487_4398_8AD7_027927FEF81A
