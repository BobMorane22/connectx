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
 * @file Gtkmm3Chip.h
 * @date 2020
 *
 *************************************************************************************************/

#ifndef GTKMM3CHIP_H_1CEF1E8A_30D4_45E4_932A_B86F7A39371D
#define GTKMM3CHIP_H_1CEF1E8A_30D4_45E4_932A_B86F7A39371D

#include <gtkmm/drawingarea.h>

#include <cxui/IChip.h>

namespace cx::cmn::ui
{

/*********************************************************************************************//**
 * @brief Gtkmm3 implementation for a chip to drop in the Connect X game board.
 *
 * This abstract class gives access to shared chip functionalities without binding any shape
 * to the chip. It is the concrete class' job to specify a chip shape.
 *
 ************************************************************************************************/
class Gtkmm3Chip : public cx::ui::IChip,
                   public Gtk::DrawingArea
{

public:

    /******************************************************************************************//**
     * @brief Constructor.
     *
     * @param p_fillColor
     *     The color filling the center of the chip (inside its border).
     * @param p_backgroundColor
     *     The color around the chip (outside its border).
     * @param p_width
     *     The chip width (in pixels).
     * @param p_height
     *     The chip height (in pixels).
     *
     ********************************************************************************************/
    Gtkmm3Chip(const cx::model::ChipColor& p_fillColor,
               const cx::model::ChipColor& p_backgroundColor,
               int p_width,
               int p_height);

    /******************************************************************************************//**
     * @brief Sets the delegate for widget common facilities.
     *
     * The delegate is reponsible to carry the implementation for generic `cx::cmn::ui::IWidget` operations.
     * It is meant to avoid implementation duplication.
     *
     * @param p_delegate
     *      The widget delegate.
     *
     * @pre
     *      The widget delegate instance given as an argument is valid.
     * @post
     *      The registered widget delegate is valid.
     *
     *********************************************************************************************/
    void SetDelegate(std::unique_ptr<IWidget> p_delegate);

    // cx::cmn::ui::IChip:
    void ChangeColor(const cx::model::ChipColor& p_newFillColor) override final;
    [[nodiscard]] cx::model::ChipColor GetColor() const override final;
    void Highlight() override final;
    void UnHighlight() override final;

    // cx::cmn::ui::IWidget:
    [[nodiscard]] size_t GetWidth() const override final;
    [[nodiscard]] size_t GetHeight() const override final;
    void SetEnabled(EnabledState p_enabled) override final;
    void SetMargins(const Margins& p_newMarginSizes) override final;
    void SetTooltip(const std::string& p_tooltipContents) override final;
    [[nodiscard]] std::unique_ptr<ISignal<EventPropagation, KeyboardKeyPressedEvent>> OnKeyPressed() override;

private:

    void Redraw();

    /******************************************************************************************//**
     * @brief Draws the chip border.
     *
     * This methods has to be overloaded to specify how the chip border will look. You can give
     * it any shape you want.
     *
     * @param p_context
     *     The Cairo context to use to draw the chip.
     *
     ********************************************************************************************/
    virtual void DrawBorder(const Cairo::RefPtr<Cairo::Context>& p_context) const = 0;

    [[nodiscard]] bool on_draw(const Cairo::RefPtr<Cairo::Context>& p_context) override final;

    void Draw(const Cairo::RefPtr<Cairo::Context>& p_context) const;
    void DrawBackgroundColor(const Cairo::RefPtr<Cairo::Context>& p_context) const;
    void DrawFillColor(const Cairo::RefPtr<Cairo::Context>& p_context) const;

private:

    std::unique_ptr<IWidget> m_delegate;

    cx::model::ChipColor m_fillColor;
    cx::model::ChipColor m_backgroundColor;
    cx::model::ChipColor m_initialBackgroundColor;
};

} // namespace cx::cmn::ui

#endif // GTKMM3CHIP_H_1CEF1E8A_30D4_45E4_932A_B86F7A39371D
