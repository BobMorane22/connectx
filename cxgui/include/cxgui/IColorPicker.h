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
 * @file IColorPicker.h
 * @date 2024
 *
 *************************************************************************************************/

#ifndef ICOLORPICKER_H_FC678E04_F896_472E_A3A9_769E584E01FF
#define ICOLORPICKER_H_FC678E04_F896_472E_A3A9_769E584E01FF

#include <cxgui/common.h>
#include <cxgui/ISignal.h>
#include <cxgui/IWidget.h>

namespace cxgui
{

class IColorPicker : public IWidget
{

public:

    /******************************************************************************************//**
     * @brief Sets the current selected color.
     *
     * @param p_color
     *      The color to make visible in the combo box.
     *
     ********************************************************************************************/
    [[nodiscard]] virtual Color GetCurrentSelection() const = 0;

    /******************************************************************************************//**
     * @brief Sets the current selected color.
     *
     * @param p_color
     *      The color to make visible in the combo box.
     *
     ********************************************************************************************/
    virtual void SetCurrentSelection(const cxgui::Color& p_color) = 0;

    /******************************************************************************************//**
     * @brief Get the signal for when the color selection is changed by the user.
     *
     * @return
     *      A signal to connect to for when the color selection is changed.
     *
     ********************************************************************************************/
    [[nodiscard]] virtual std::unique_ptr<ISignal<void>> OnSelectionChanged() = 0;
};

} // namespace cxgui

#endif // ICOLORPICKER_H_FC678E04_F896_472E_A3A9_769E584E01FF
