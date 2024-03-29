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
 * @file Gtkmm3Layout.cpp
 * @date 2023
 *
 *************************************************************************************************/

#include "Gtkmm3Layout.h"
#include "Gtkmm3Button.h"
#include "Gtkmm3EditBox.h"

void Gtkmm3Layout::Attach(IWidget& p_widget, int p_left, int p_top)
{
    auto* child = dynamic_cast<Gtk::Widget*>(&p_widget);
    attach(*child, p_left, p_top);
}

void Gtkmm3Layout::Attach(Gtk::Widget& p_widget, int p_left, int p_top)
{
    attach(p_widget, p_left, p_top);
}
