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
 * @file DiscChip.h
 * @date 2020
 *
 *************************************************************************************************/

#ifndef DISCCHIP_H_E87685D6_F889_4EC1_982F_1496DBD37A28
#define DISCCHIP_H_E87685D6_F889_4EC1_982F_1496DBD37A28

#include "Chip.h"

namespace cxgui
{

/*********************************************************************************************//**
 * @brief A disc shaped chip.
 *
 ************************************************************************************************/
class DiscChip : public cxgui::Chip
{

public:

    /******************************************************************************************//**
     * @brief Constructor.
     *
     * @param p_fillColor       The color filling the center of the chip (inside its border).
     * @param p_backgroundColor The color around the chip (outside its border).
     *
     ********************************************************************************************/
    DiscChip(const cxmodel::ChipColor& p_fillColor, const cxmodel::ChipColor& p_backgroundColor);

private:

    // Disc shape:
    virtual void DrawBorder(const Cairo::RefPtr<Cairo::Context>& p_context) const override;

};

} // namespace cxgui

#endif // DISCCHIP_H_E87685D6_F889_4EC1_982F_1496DBD37A28
