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
 * @file EnabledState.h
 * @date 2022
 *
 *************************************************************************************************/

namespace cx::cmn::ui
{

/**********************************************************************************************//**
 * @brief Widget enabled state.
 *
 * A widget can be enabled or disabled. A user can interract directly on an enabled widget. With
 * a disabled widget, interaction can also occur, but it has to be indirectly. On most toolkits,
 * diabled widgets are "greyed out".
 *
 *************************************************************************************************/
enum class EnabledState
{
    /** The user can interract with the widget. */
    Enabled,  

    /** The user cannot interract with the widget. */
    Disabled
};

} // namespace cx::cmn::ui
