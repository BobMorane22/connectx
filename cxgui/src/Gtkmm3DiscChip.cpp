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
 * @file Gtkmm3DiscChip.cpp
 * @date 2020
 *
 *************************************************************************************************/

#include <cxgui/Gtkmm3DiscChip.h>

cxgui::Gtkmm3DiscChip::Gtkmm3DiscChip(const cxmodel::ChipColor& p_fillColor,
                                      const cxmodel::ChipColor& p_backgroundColor,
                                      int p_dimension)
: Gtkmm3Chip{p_fillColor,
             p_backgroundColor,
             p_dimension,
             p_dimension}
{
}

void cxgui::Gtkmm3DiscChip::DrawBorder(const Cairo::RefPtr<Cairo::Context>& p_context) const
{
    const Gtk::Allocation allocation{get_allocation()};

    const int width{allocation.get_width()};
    const int height{allocation.get_height()};
    const int smallestDimension{std::min(width, height)};

    const int xCenter{width / 2};
    const int yCenter{height / 2};

    p_context->arc(xCenter,
                   yCenter,
                   smallestDimension / 2.5,
                   0.0,
                   2.0 * M_PI); // Not standard C...
}
