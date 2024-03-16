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
 * @file Gtkmm3DiscChip.h
 * @date 2020
 *
 *************************************************************************************************/

#ifndef GTKMM3DISCCHIP_H_62BF81A1_A9D1_400E_83C5_2B8FE8CF5B34
#define GTKMM3DISCCHIP_H_62BF81A1_A9D1_400E_83C5_2B8FE8CF5B34

#include <cxgui/Gtkmm3Chip.h>

namespace cxgui
{

/**********************************************************************************************//**
 * @brief Gtkmm3 implementation of a chip which has a disc shape.
 *
 *************************************************************************************************/
class Gtkmm3DiscChip : public Gtkmm3Chip
{

public:

    /******************************************************************************************//**
     * @brief Constructor.
     *
     * @param p_fillColor
     *      The color filling the center of the disc (inside its border).
     * @param p_backgroundColor
     *      The color around the disc (outside its border).
     * @param p_dimension
     *      The disc dimension (both width and height, in pixels).
     *
     ********************************************************************************************/
    Gtkmm3DiscChip(const cxmodel::ChipColor& p_fillColor,
                   const cxmodel::ChipColor& p_backgroundColor,
                   int p_dimension);

private:

    // cxgui::Gtkmm3Chip:
    void DrawBorder(const Cairo::RefPtr<Cairo::Context>& p_context) const override final;

};

} // namespace cxgui

#endif // GTKMM3DISCCHIP_H_62BF81A1_A9D1_400E_83C5_2B8FE8CF5B34
