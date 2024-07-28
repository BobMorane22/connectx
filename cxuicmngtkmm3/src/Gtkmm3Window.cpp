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
 * @file Gtkmm3Window.cpp
 * @date 2024
 *
 *************************************************************************************************/

#include <glibmm/fileutils.h>

#include <cxuicmn/EventPropagation.h>
#include <cxuicmn/Gtkmm3Window.h>
#include <cxuicmn/IAbstractWidgetsFactory.h>
#include <cxuicmn/ILayout.h>
#include <cxuicmn/KeyboardKeyPressedEvent.h>
#include <cxuicmn/WidgetsFactories.h>

void cx::ui::cmn::Gtkmm3Window::ConfigureWindowIcon()
{
    try
    {
        set_icon_from_file(cx::ui::cmn::RESSOURCE_ICONS_PATH + std::string{"/cxicon16.png"});
    }
    catch(const Glib::FileError& p_exception)
    {
        const std::string errorMsg = p_exception.what();
        ASSERT_ERROR_MSG(errorMsg.c_str());

        return;
    }
}

cx::ui::cmn::Gtkmm3Window::Gtkmm3Window(WidgetsFactories& p_widgetsFactories)
: m_widgetsFactories{p_widgetsFactories}
{
    const IAbstractWidgetsFactory& standardWidgetsFactory = m_widgetsFactories.GetStandardWidgetsFactory();
    m_mainLayout = standardWidgetsFactory.CreateLayout();

    Gtk::Widget* mainLayoutAsGtk = dynamic_cast<Gtk::Widget*>(m_mainLayout.get());
    if(INL_ASSERT(mainLayoutAsGtk))
    {
        add(*mainLayoutAsGtk);
    }

    POSTCONDITION(m_mainLayout);
}

int cx::ui::cmn::Gtkmm3Window::Show()
{
    show_all();

    return EXIT_SUCCESS;
}

void cx::ui::cmn::Gtkmm3Window::ShrinkToContents(IWindow::Orientation p_orientation)
{
    if(p_orientation == IWindow::Orientation::VERTICAL)
    {
        resize(get_width(), 1);
    }
    else if(p_orientation == IWindow::Orientation::VERTICAL)
    {
        resize(1, get_height());
    }
    else
    {
        ASSERT_ERROR_MSG("Not yet implemented");
    }
}

void cx::ui::cmn::Gtkmm3Window::Init()
{
    ConfigureWindowIcon();
    InitializeWidgets();
    ConfigureWindow();
    RegisterLayouts();
    RegisterWidgets();
    ConfigureLayouts();
    ConfigureWidgets();
    ConfigureSignalHandlers();
}

void cx::ui::cmn::Gtkmm3Window::SetDelegate(std::unique_ptr<IWidget> p_delegate)
{
    IF_PRECONDITION_NOT_MET_DO(p_delegate, return;);

    m_delegate = std::move(p_delegate);

    POSTCONDITION(m_delegate);
}

size_t cx::ui::cmn::Gtkmm3Window::GetWidth() const 
{
    IF_CONDITION_NOT_MET_DO(m_delegate, return 0u;);
    return m_delegate->GetWidth();
}

size_t cx::ui::cmn::Gtkmm3Window::GetHeight() const 
{
    IF_CONDITION_NOT_MET_DO(m_delegate, return 0u;);
    return m_delegate->GetHeight();
}

void cx::ui::cmn::Gtkmm3Window::SetEnabled(EnabledState p_enabled) 
{
    IF_CONDITION_NOT_MET_DO(m_delegate, return;);
    m_delegate->SetEnabled(p_enabled);
}

void cx::ui::cmn::Gtkmm3Window::SetMargins(const Margins& p_newMarginSizes) 
{
    IF_CONDITION_NOT_MET_DO(m_delegate, return;);
    m_delegate->SetMargins(p_newMarginSizes);
}

void cx::ui::cmn::Gtkmm3Window::SetTooltip(const std::string& p_tooltipContents)
{
    IF_CONDITION_NOT_MET_DO(m_delegate, return;);
    m_delegate->SetTooltip(p_tooltipContents);
}

std::unique_ptr<cx::ui::cmn::ISignal<cx::ui::cmn::EventPropagation, cx::ui::cmn::KeyboardKeyPressedEvent>> cx::ui::cmn::Gtkmm3Window::OnKeyPressed()
{
    IF_CONDITION_NOT_MET_DO(m_delegate, return nullptr;);
    return m_delegate->OnKeyPressed();
}
