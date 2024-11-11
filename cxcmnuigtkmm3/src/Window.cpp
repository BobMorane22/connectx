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
 * @file Window.cpp
 * @date 2024
 *
 *************************************************************************************************/

#include <cstdlib>

#include <gtkmm/grid.h>

#include <cxinv/assertion.h>
#include <cxcmnui/ILayout.h>

#include "Window.h"

cx::cmn::ui::gtkmm3::Window::Window(
    Glib::RefPtr<Gtk::Application> p_gtkApplication)
{
    PRECONDITION(bool(p_gtkApplication));

    m_gtkApplication = p_gtkApplication;

    POSTCONDITION(bool(m_gtkApplication));
}

void cx::cmn::ui::gtkmm3::Window::SetDelegate(
    std::unique_ptr<cx::cmn::ui::IWidget> p_delegate)
{
    IF_PRECONDITION_NOT_MET_DO(p_delegate, return;);

    m_delegate = std::move(p_delegate);

    POSTCONDITION(m_delegate);
}

int cx::cmn::ui::gtkmm3::Window::Show() 
{
    const Gtk::Window* const activeWindow = m_gtkApplication->get_active_window();

    if(!activeWindow)
    {
        // There are no active window. This means this is the first shown
        // window, and hence the main window. We run the Gtk::Application
        // instance with this window to make it the main window.
        show_all();
        return m_gtkApplication->run(*this);
    }

    // Not the main window. We simply show it.
    show_all();    
    return EXIT_SUCCESS;
}

void cx::cmn::ui::gtkmm3::Window::RegisterLayout(
    cx::cmn::ui::ILayout& p_layout)
{
    auto* gtkLayout = dynamic_cast<Gtk::Grid*>(&p_layout);
    IF_CONDITION_NOT_MET_DO(gtkLayout, return;);

    add(*gtkLayout);
}

void cx::cmn::ui::gtkmm3::Window::ShrinkToContents(
    cx::cmn::ui::IWindow::Orientation p_orientation) 
{
    using namespace cx::cmn::ui;

    switch(p_orientation)
    {
        case IWindow::Orientation::VERTICAL:
        {
            resize(get_width(), 1);
            return;
        }
        case IWindow::Orientation::HORIZONTAL:
        {
            resize(1, get_height());
            return;
        }
        case IWindow::Orientation::ALL:
        {
            resize(1,1);
            return;
        }
        default:
            break;
    }

    ASSERT_ERROR_MSG("Not yet implemented");
}

size_t cx::cmn::ui::gtkmm3::Window::GetWidth() const 
{
    IF_CONDITION_NOT_MET_DO(m_delegate, return 0u;);
    return m_delegate->GetWidth();
}

size_t cx::cmn::ui::gtkmm3::Window::GetHeight() const 
{
    IF_CONDITION_NOT_MET_DO(m_delegate, return 0u;);
    return m_delegate->GetHeight();
}

void cx::cmn::ui::gtkmm3::Window::SetEnabled(cx::cmn::ui::EnabledState p_enabled) 
{
    IF_CONDITION_NOT_MET_DO(m_delegate, return;);
    m_delegate->SetEnabled(p_enabled);
}

void cx::cmn::ui::gtkmm3::Window::SetMargins(const cx::cmn::ui::Margins& p_newMarginSizes) 
{
    IF_CONDITION_NOT_MET_DO(m_delegate, return;);
    m_delegate->SetMargins(p_newMarginSizes);
}

void cx::cmn::ui::gtkmm3::Window::SetTooltip(const std::string& p_tooltipContents) 
{
    IF_CONDITION_NOT_MET_DO(m_delegate, return;);
    m_delegate->SetTooltip(p_tooltipContents);
}

std::unique_ptr<cx::cmn::ui::ISignal<cx::cmn::ui::EventPropagation, cx::cmn::ui::KeyboardKeyPressedEvent>> cx::cmn::ui::gtkmm3::Window::OnKeyPressed() 
{
    IF_CONDITION_NOT_MET_DO(m_delegate, return nullptr;);
    return m_delegate->OnKeyPressed();
}
