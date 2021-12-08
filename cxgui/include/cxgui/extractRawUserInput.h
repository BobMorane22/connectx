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
 * @file extractRawUserInput.h
 * @date 2020
 *
 *************************************************************************************************/

#ifndef EXTRACTRAWUSERINPUT_H_E59E21D1_FC74_469C_9360_9ECC7EE8D51F
#define EXTRACTRAWUSERINPUT_H_E59E21D1_FC74_469C_9360_9ECC7EE8D51F

#include <cxmodel/Status.h>

namespace cxgui
{

/******************************************************************************************//**
 * @brief Extracts raw user input (as a string), into a unsigned long.
 *
 * @param p_raw       The raw user input (usually from a control).
 * @param p_extracted The extracted value.
 *
 * @return `Success` upon successful extraction, `Error` otherwise. Note that when an error
 *         is returned, the extracted value is invalid.
 *
 * Extracts a user input string (e.g. from an edit box) into an unsigned long, if possible.
 *
 ********************************************************************************************/
cxmodel::Status extractRawUserInput(const std::string& p_raw, unsigned long& p_extracted);

} // namespace cxgui

#endif // EXTRACTRAWUSERINPUT_H_E59E21D1_FC74_469C_9360_9ECC7EE8D51F
