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
 * @file widgetUtilities.cpp
 * @date 2024
 *
 *************************************************************************************************/

#include <cxuicmn/EnabledState.h>
#include <cxuicmn/IWidget.h>
#include <cxuicmn/widgetUtilities.h>

cx::ui::cmn::EnabledState cx::ui::cmn::EnabledStateUpdate(cx::ui::cmn::IWidget& p_widget, bool p_condition)
{
    auto state = cx::ui::cmn::EnabledState::Disabled;
    if(p_condition)
    {
        state = cx::ui::cmn::EnabledState::Enabled;
    }

    p_widget.SetEnabled(state);

    return state;
}
