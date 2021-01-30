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
 * @file MenuItem.cpp
 * @date 2020
 *
 *************************************************************************************************/

#include <string>

#include <MenuItem.h>

std::string cxgui::MakeLabel(MenuItem p_menuItem)
{
    switch(p_menuItem)
    {
        case MenuItem::GAME:
            return "Game";

        case MenuItem::NEW_GAME:
            return "New";

        case MenuItem::REINITIALIZE_GAME:
            return "Reinitialize";

        case MenuItem::QUIT:
            return "Quit";

        case MenuItem::HELP:
            return "Help";

        case MenuItem::ABOUT:
            return "About";

        case MenuItem::UNDO:
            return "Undo [Ctrl+z]";

        default:                   // LCOV_EXCL_LINE
            return "";             // LCOV_EXCL_LINE
    }
}
