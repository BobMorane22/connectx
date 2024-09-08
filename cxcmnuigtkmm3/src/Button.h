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
 * @file Button.h
 * @date 2024
 *
 *************************************************************************************************/

#ifndef GTKMM3BUTTON_H_28BFEAFC_06B4_4950_A338_12355AA185D0
#define GTKMM3BUTTON_H_28BFEAFC_06B4_4950_A338_12355AA185D0

#include <string>

#include <gtkmm/button.h>

#include <cxcmnui/IButton.h>

//! [AWT - Button inheritance]
namespace cx::cmn::ui::gtkmm3
{

/**********************************************************************************************//**
 * @brief Gtkmm 3 implementation of the `cx::cmn::ui::gtkmm3::IButton` interface.
 *
 *************************************************************************************************/
class Button : public cx::cmn::ui::IButton,
               public Gtk::Button                                    
//! [AWT - Button inheritance]
{

public:

    /******************************************************************************************//**
     * @brief Default constructor.
     *
     * Creates a button with no contents.
     *
     *********************************************************************************************/
     Button();

    /******************************************************************************************//**
     * @brief Constructor.
     *
     * @param p_label
     *      The textual label to appear on the button. The label can be empty. In this case,
     *      nothing will show on the button.
     *
     *********************************************************************************************/
    explicit Button(const std::string& p_label);

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

    // cx::cmn::ui::IButton:
    void UpdateContents(const std::string& p_newContents) override;
    [[nodiscard]] std::string GetContents() const override;
    [[nodiscard]] std::unique_ptr<ISignal<void>> OnClicked() override;

    // cx::cmn::ui::IWidget:
    [[nodiscard]] size_t GetWidth() const override;
    [[nodiscard]] size_t GetHeight() const override;
    void SetEnabled(cx::cmn::ui::EnabledState p_enabled) override;
    void SetMargins(const cx::cmn::ui::Margins& p_newMarginSizes) override;
    void SetTooltip(const std::string& p_tooltipContents) override;
    [[nodiscard]] std::unique_ptr<cx::cmn::ui::ISignal<cx::cmn::ui::EventPropagation, cx::cmn::ui::KeyboardKeyPressedEvent>> OnKeyPressed() override;

private:

    std::unique_ptr<IWidget> m_delegate;

};

} // namespace cx::cmn::ui::gtkmm3

#endif // GTKMM3BUTTON_H_28BFEAFC_06B4_4950_A338_12355AA185D0
