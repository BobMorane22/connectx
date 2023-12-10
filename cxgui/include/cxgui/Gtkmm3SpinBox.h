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

#include <gtkmm/spinbutton.h>

#include <cxgui/ISpinBox.h>

namespace cxgui
{

/**********************************************************************************************//**
 * @brief Gtkmm 3 implementation for the `cxgui::ISpinBox` interface.
 *
 *************************************************************************************************/
class Gtkmm3SpinBox : public cxgui::ISpinBox,
                      public Gtk::SpinButton
{

public:

    // cxgui::IWidget:
    [[nodiscard]] size_t GetWidth() const override;
    [[nodiscard]] size_t GetHeight() const override;
    void SetEnabled(EnabledState p_enabled) override;
    void SetMargins(const Margins& p_newMarginSizes) override;

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
    Gtkmm3SpinBox(int p_initialValue,
                  const ClimbRate& p_climbRate,
                  const Range& p_range);

    // cxgui::ISpinBox:
    [[nodiscard]] int GetValue() const override;

private:

    cxgui::ISpinBox::Range m_limits;

};

} // namespace cxgui

#endif // GTKMM3SPINBOX_H_73AD5C68_A06C_4EFB_94EE_928437F83BA6
