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
 * @file widgetUtilities.h
 * @date 2024
 *
 *************************************************************************************************/

#ifndef WIDGETUTILITIES_H_CAE6AA9C_9245_4128_9D61_28A6A021CE6E
#define WIDGETUTILITIES_H_CAE6AA9C_9245_4128_9D61_28A6A021CE6E

namespace cxgui
{
    enum class EnabledState;
    class IWidget;
}

namespace cxgui
{

/**********************************************************************************************//**
 * @brief Enables or disables a widget according to a condition.
 *
 * If the condition is `true`, the widget is enabled. If the condition is `false`, the widget is
 * disabled. The caller can optionnaly see the new widget state through the returned value.
 *
 * @param p_widget
 *      The widget for which to update the enabled state.
 * @param p_condition
 *      A boolean condition. If the condition is `true`, the widget is enabled. Otherwise, the
 *      widget is disabled.
 *
 * @return
 *      The new widget enabled state.
 *
 *************************************************************************************************/
EnabledState EnabledStateUpdate(IWidget& p_widget, bool p_condition);

}

#endif // WIDGETUTILITIES_H_CAE6AA9C_9245_4128_9D61_28A6A021CE6E
