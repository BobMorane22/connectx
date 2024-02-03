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
 * @file Gtkmm3Button.h
 * @date 2024
 *
 *************************************************************************************************/

#ifndef GTKMM3BUTTON_H_28BFEAFC_06B4_4950_A338_12355AA185D0
#define GTKMM3BUTTON_H_28BFEAFC_06B4_4950_A338_12355AA185D0

#include <string>

#include <gtkmm/button.h>

#include <cxgui/IButton.h>

namespace cxgui
{

/**********************************************************************************************//**
 * @brief Gtkmm 3 implementation of the `cxgui::IButton` interface.
 *
 *************************************************************************************************/
class Gtkmm3Button : public IButton,
                     public Gtk::Button

{

public:

    /******************************************************************************************//**
     * @brief Constructor.
     *
     * @param p_label
     *      The textual label to appear on the button. The label can be empty. In this case,
     *      nothing will show on the button.
     *
     *********************************************************************************************/
    explicit Gtkmm3Button(const std::string& p_label);

    /*******************************************************************************************//**
     * @brief Sets the delegate for widget common facilities.
     *
     * The delegate is reponsible to carry the implementation for generic `cxgui::IWidget` operations.
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

    // cxgui::IButton:
    [[nodiscard]] std::unique_ptr<ISignal<void>> OnClicked() override;

    // cxgui::IWidget:
    [[nodiscard]] size_t GetWidth() const override;
    [[nodiscard]] size_t GetHeight() const override;
    void SetEnabled(EnabledState p_enabled) override;
    void SetMargins(const Margins& p_newMarginSizes) override;
    void SetTooltip(const std::string& p_tooltipContents) override;

private:

    std::unique_ptr<IWidget> m_delegate;

};

} // namespace cxgui

#endif // GTKMM3BUTTON_H_28BFEAFC_06B4_4950_A338_12355AA185D0
