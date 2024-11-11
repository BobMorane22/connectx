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
 * @file Window.h
 * @date 2024
 *
 *************************************************************************************************/

#ifndef WINDOW_H_450385E3_F251_4E91_ADE7_5457E7CFF128
#define WINDOW_H_450385E3_F251_4E91_ADE7_5457E7CFF128

#include <gtkmm/application.h>
#include <gtkmm/window.h>

#include <cxcmnui/IWindow.h>

namespace cx::cmn::ui::gtkmm3
{

/***********************************************************************************************//**
 * @brief Gtkmm3 window implementation.
 *
 **************************************************************************************************/
class Window : public Gtk::Window,
               public cx::cmn::ui::IWindow
{

public:

    /*******************************************************************************************//**
     * @brief Constructor.
     *
     * @param p_gtkApplication
     *      The underlying GTK application.
     *
     * @pre
     *      The supplied GTK application is valid.
     * @post
     *      The stored GTK application reference is valid.
     *
     **********************************************************************************************/
    Window(
        Glib::RefPtr<Gtk::Application> p_gtkApplication);

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

    // cx::cmn::ui::IWindow:
    [[nodiscard]] int Show() override;
    void ShrinkToContents(
        Orientation p_orientation) override;
    void RegisterLayout(
        cx::cmn::ui::ILayout& p_layout) override;

    // cx::cmn::ui::IWidget:
    [[nodiscard]] size_t GetWidth() const override;
    [[nodiscard]] size_t GetHeight() const override;
    void SetEnabled(cx::cmn::ui::EnabledState p_enabled) override;
    void SetMargins(const cx::cmn::ui::Margins& p_newMarginSizes) override;
    void SetTooltip(const std::string& p_tooltipContents) override;
    [[nodiscard]] std::unique_ptr<cx::cmn::ui::ISignal<cx::cmn::ui::EventPropagation, cx::cmn::ui::KeyboardKeyPressedEvent>> OnKeyPressed() override;

private:

    Glib::RefPtr<Gtk::Application> m_gtkApplication;
    std::unique_ptr<IWidget> m_delegate;

};

} // namespace cx::cmn::ui::gtkmm3

#endif // WINDOW_H_450385E3_F251_4E91_ADE7_5457E7CFF128
