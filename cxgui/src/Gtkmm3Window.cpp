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

#include <cxgui/Gtkmm3Window.h>

void cxgui::Gtkmm3Window::ConfigureWindowIcon()
{
    try
    {
        set_icon_from_file(cxgui::RESSOURCE_ICONS_PATH + std::string{"/cxicon16.png"});
    }
    catch(const Glib::FileError& p_exception)
    {
        const std::string errorMsg = p_exception.what();
        ASSERT_ERROR_MSG(errorMsg.c_str());

        return;
    }
}

cxgui::Gtkmm3Window::Gtkmm3Window()
{
    m_mainLayout = CreateWidget<Gtkmm3Layout>();
    ASSERT(m_mainLayout);

    Gtk::Widget* mainLayoutAsGtk = dynamic_cast<Gtk::Widget*>(m_mainLayout.get());
    if(INL_ASSERT(mainLayoutAsGtk))
    {
        add(*mainLayoutAsGtk);
    }
}

int cxgui::Gtkmm3Window::Show()
{
    show_all();

    return EXIT_SUCCESS;
}

void cxgui::Gtkmm3Window::Init()
{
    ConfigureWindowIcon();
    ConfigureWindow();
    RegisterLayouts();
    RegisterWidgets();
    ConfigureLayouts();
    ConfigureWidgets();
    ConfigureSignalHandlers();
}

void cxgui::Gtkmm3Window::SetDelegate(std::unique_ptr<IWidget> p_delegate)
{
    IF_PRECONDITION_NOT_MET_DO(p_delegate, return;);

    m_delegate = std::move(p_delegate);

    POSTCONDITION(m_delegate);
}

size_t cxgui::Gtkmm3Window::GetWidth() const 
{
    IF_CONDITION_NOT_MET_DO(m_delegate, return 0u;);
    return m_delegate->GetWidth();
}

size_t cxgui::Gtkmm3Window::GetHeight() const 
{
    IF_CONDITION_NOT_MET_DO(m_delegate, return 0u;);
    return m_delegate->GetHeight();
}

void cxgui::Gtkmm3Window::SetEnabled(EnabledState p_enabled) 
{
    IF_CONDITION_NOT_MET_DO(m_delegate, return;);
    m_delegate->SetEnabled(p_enabled);
}

void cxgui::Gtkmm3Window::SetMargins(const Margins& p_newMarginSizes) 
{
    IF_CONDITION_NOT_MET_DO(m_delegate, return;);
    m_delegate->SetMargins(p_newMarginSizes);
}

void cxgui::Gtkmm3Window::SetTooltip(const std::string& p_tooltipContents)
{
    IF_CONDITION_NOT_MET_DO(m_delegate, return;);
    m_delegate->SetTooltip(p_tooltipContents);
}
