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
 * @file common.h
 * @date 2020
 *
 *************************************************************************************************/

#ifndef COMMON_H_E38DC86D_677A_4508_9D75_1B9C3C899679
#define COMMON_H_E38DC86D_677A_4508_9D75_1B9C3C899679

#include <cxmodel/ChipColor.h>

namespace cxgui
{

/******************************************************************************************//**
 * @brief Color depth used in the cxgui library.
 *
 ********************************************************************************************/
using Color = cxmodel::Color<unsigned short int>;

static_assert(sizeof(cxgui::Color) == sizeof(cxmodel::ChipColor));

// Dialog global margin (on each sides):
constexpr int DIALOG_SIDE_MARGIN = 10;

// Dialog titles bottom margin space:
constexpr int TITLE_BOTTOM_MARGIN = 20;

// Section titles bottom margin space:
constexpr int SECTION_BOTTOM_MARGIN = 10;

// Controls botton margin space:
constexpr int CONTROL_BOTTOM_MARGIN = 5;

// Indentation space in a dialog. For example, add this to control text to indent it once.
constexpr char INDENT_MARK[] = "    ";

// Default chip size, in pixels:
constexpr int DEFAULT_CHIP_SIZE = 40;

// Handler event propagation:
constexpr bool STOP_EVENT_PROPAGATION = true;
constexpr bool PROPAGATE_EVENT = false;


} // namespace cxgui

#endif // COMMON_H_E38DC86D_677A_4508_9D75_1B9C3C899679
