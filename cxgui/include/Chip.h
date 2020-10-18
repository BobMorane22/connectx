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
 * @file Chip.h
 * @date 2020
 *
 *************************************************************************************************/

#ifndef CHIP_H_59D669EE_B5E5_415C_B68C_9D683613A99C
#define CHIP_H_59D669EE_B5E5_415C_B68C_9D683613A99C

#include <gtkmm/drawingarea.h>

#include <cxmodel/include/ChipColor.h>

namespace cxgui
{

/*********************************************************************************************//**
 * @brief Chip for dropping in the Connect X game board.
 *
 * A chip is a piece with which Connect X players can fill the board. This abstract class gives
 * access to shared chip functionalities without binding any shape to the chip. It is the
 * concrete class' job to specify a chip shape.
 *
 ************************************************************************************************/
class Chip : public Gtk::DrawingArea
{

public:

    /******************************************************************************************//**
     * @brief Constructor.
     *
     * @param p_fillColor       The color filling the center of the chip (inside its border).
     * @param p_backgroundColor The color around the chip (outside its border).
     *
     ********************************************************************************************/
    Chip(const cxmodel::ChipColor& p_fillColor, const cxmodel::ChipColor& p_backgroundColor);

    /******************************************************************************************//**
     * @brief Changes the chip's fill color.
     *
     * @param p_newFillColor The new fill color.
     *
     ********************************************************************************************/
    void ChangeColor(const cxmodel::ChipColor& p_newFillColor);

    /******************************************************************************************//**
     * @brief Chip color accessor.
     *
     * @return The chip's color.
     *
     ********************************************************************************************/
    cxmodel::ChipColor GetColor() const;

private:

    void Redraw();

    // Specify shape by overloading this:
    virtual void DrawBorder(const Cairo::RefPtr<Cairo::Context>& p_context) const = 0;

    bool on_draw(const Cairo::RefPtr<Cairo::Context>& p_context) override;

    void Draw(const Cairo::RefPtr<Cairo::Context>& p_context) const;
    void DrawBackgroundColor(const Cairo::RefPtr<Cairo::Context>& p_context) const;
    void DrawFillColor(const Cairo::RefPtr<Cairo::Context>& p_context) const;

    cxmodel::ChipColor m_fillColor;
    cxmodel::ChipColor m_backgroundColor;

};

} // namespace cxgui

#endif // CHIP_H_59D669EE_B5E5_415C_B68C_9D683613A99C
