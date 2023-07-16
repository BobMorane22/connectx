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
 * @file Gtkmm3WidgetsFactory.cpp
 * @date 2023
 *
 *************************************************************************************************/

#include <gtkmm.h>

#include "Gtkmm3WidgetsFactory.h"
#include "Gtkmm3Button.h"
#include "Gtkmm3EditBox.h"
#include "Gtkmm3Layout.h"

std::unique_ptr<IButton> Gtkmm3WidgetsFactory::CreateButton() const
{
    return std::make_unique<Gtkmm3Button>();
}

std::unique_ptr<IEditBox> Gtkmm3WidgetsFactory::CreateEditBox() const
{
    return std::make_unique<Gtkmm3EditBox>();
}

std::unique_ptr<ILayout> Gtkmm3WidgetsFactory::CreateLayout() const
{
    return std::make_unique<Gtkmm3Layout>();
}
