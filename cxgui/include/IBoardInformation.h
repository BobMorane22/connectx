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
 * @file IBoardInformation.h
 * @date 2021
 *
 *************************************************************************************************/

#ifndef IBOARDINFORMATION_H_363CE7FD_F741_40F0_829D_6868F6B77EFE
#define IBOARDINFORMATION_H_363CE7FD_F741_40F0_829D_6868F6B77EFE

#include <cstddef>

namespace cxgui
{
    class Chip;
}

namespace cxgui
{

/**********************************************************************************************//**
 * @brief Access information about the Connect X board.
 *
 *************************************************************************************************/
class IBoardInformation
{

public:

    /******************************************************************************************//**
     * @brief Destructor.
     *
     *********************************************************************************************/
     virtual ~IBoardInformation() = default;

    /******************************************************************************************//**
     * @brief Gets the column in which the chip in the next disc area is currently located.
     *
     * @return The column in which the chip currently is located.
     *
     *********************************************************************************************/
    [[nodiscard]] virtual size_t GetCurrentColumn() const = 0;

    /******************************************************************************************//**
     * @brief Gets the chip currently in the next disc area.
     *
     * @return The disc in the next disc area. If there is none, nullptr.
     *
     *********************************************************************************************/
    [[nodiscard]] virtual const cxgui::Chip* GetCurrentChip() const = 0;

};

} // namespace cxgui

#endif // IBOARDINFORMATION_H_363CE7FD_F741_40F0_829D_6868F6B77EFE
