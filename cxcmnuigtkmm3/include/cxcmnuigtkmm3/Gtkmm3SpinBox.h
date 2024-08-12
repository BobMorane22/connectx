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
 * @file Gtkmm3SpinBox.h
 * @date 2023
 *
 *************************************************************************************************/

#ifndef GTKMM3SPINBOX_H_73AD5C68_A06C_4EFB_94EE_928437F83BA6
#define GTKMM3SPINBOX_H_73AD5C68_A06C_4EFB_94EE_928437F83BA6

#include <memory>

#include <gtkmm/spinbutton.h>

#include <cxcmnui/ISpinBox.h>

namespace cx::cmn::ui::gtkmm3
{

/**********************************************************************************************//**
 * @brief Gtkmm 3 implementation for the `cx::cmn::ui::gtkmm3::ISpinBox` interface.
 *
 *************************************************************************************************/
class Gtkmm3SpinBox final : public cx::cmn::ui::ISpinBox,
                            public Gtk::SpinButton
{

public:

    /******************************************************************************************//**
     * @brief Constructor.
     *
     * @param p_initialValue
     *      The initialValue for the spin box.
     *
     * @param p_climbRate
     *      The spin box's climb rate.
     *
     * @param p_range
     *      The spin box's value range.
     *
     *********************************************************************************************/
    Gtkmm3SpinBox(
        int p_initialValue,
        const ClimbRate& p_climbRate,
        const Range& p_range);

    /*******************************************************************************************//**
     * @brief Sets the delegate for widget common facilities.
     *
     * The delegate is reponsible to carry the implementation for generic `cx::cmn::ui::gtkmm3::IWidget` operations.
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
     **********************************************************************************************/
    void SetDelegate(std::unique_ptr<IWidget> p_delegate);

    // cx::cmn::ui::gtkmm3::ISpinBox:
    [[nodiscard]] int GetValue() const override;

    // cx::cmn::ui::gtkmm3::IWidget:
    [[nodiscard]] size_t GetWidth() const override;
    [[nodiscard]] size_t GetHeight() const override;
    void SetEnabled(EnabledState p_enabled) override;
    void SetMargins(const Margins& p_newMarginSizes) override;
    void SetTooltip(const std::string& p_tooltipContents) override;
    [[nodiscard]] std::unique_ptr<ISignal<EventPropagation, KeyboardKeyPressedEvent>> OnKeyPressed() override;

private:

    std::unique_ptr<IWidget> m_delegate;

    cx::cmn::ui::ISpinBox::Range m_limits;

};

} // namespace cx::cmn::ui::gtkmm3

#endif // GTKMM3SPINBOX_H_73AD5C68_A06C_4EFB_94EE_928437F83BA6
