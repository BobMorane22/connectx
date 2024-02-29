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
 * @file Gtkmm3Dialog.cpp
 * @date 2024
 *
 *************************************************************************************************/

#include "gtkmm/messagedialog.h"
#include <gtkmm/enums.h>

#include <cxinv/assertion.h>
#include <cxgui/DialogRole.h>
#include <cxgui/Gtkmm3Dialog.h>

namespace
{

[[nodiscard]] Gtk::MessageType ToGtk(cxgui::DialogRole p_role)
{
    using namespace cxgui;

    switch(p_role)
    {
        case DialogRole::INFORMATION: return Gtk::MESSAGE_INFO;
        case DialogRole::QUESTION:    return Gtk::MESSAGE_QUESTION;
        case DialogRole::WARNING:     return Gtk::MESSAGE_WARNING;
        case DialogRole::ERROR:       return Gtk::MESSAGE_ERROR;
    }

    ASSERT_ERROR_MSG("Unknown role");
    return Gtk::MESSAGE_OTHER;
}

} //namespace

cxgui::Gtkmm3Dialog::Gtkmm3Dialog(cxgui::IWindow& p_parent, DialogRole p_role, const std::string& p_message)
: Gtk::MessageDialog(dynamic_cast<Gtk::Window&>(p_parent), p_message, true, ToGtk(p_role), Gtk::ButtonsType::BUTTONS_OK, true)
{
    PRECONDITION(!p_message.empty());
}

int cxgui::Gtkmm3Dialog::Show()
{
    return run();
}

void cxgui::Gtkmm3Dialog::ShrinkToContents(IWindow::Orientation /*p_orientation*/)
{
    // Nothing to do.
}

void cxgui::Gtkmm3Dialog::Update(cxmodel::ModelNotificationContext /*p_context*/, cxmodel::ModelSubject* /*p_subject*/)
{
    // Nothing to do.
}

void cxgui::Gtkmm3Dialog::SetDelegate(std::unique_ptr<IWidget> p_delegate)
{
    IF_PRECONDITION_NOT_MET_DO(p_delegate, return;);

    m_delegate = std::move(p_delegate);

    POSTCONDITION(m_delegate);
}

size_t cxgui::Gtkmm3Dialog::GetWidth() const 
{
    IF_CONDITION_NOT_MET_DO(m_delegate, return 0u;);
    return m_delegate->GetWidth();
}

size_t cxgui::Gtkmm3Dialog::GetHeight() const 
{
    IF_CONDITION_NOT_MET_DO(m_delegate, return 0u;);
    return m_delegate->GetHeight();
}

void cxgui::Gtkmm3Dialog::SetEnabled(EnabledState p_enabled) 
{
    IF_CONDITION_NOT_MET_DO(m_delegate, return;);
    m_delegate->SetEnabled(p_enabled);
}

void cxgui::Gtkmm3Dialog::SetMargins(const Margins& p_newMarginSizes) 
{
    IF_CONDITION_NOT_MET_DO(m_delegate, return;);
    m_delegate->SetMargins(p_newMarginSizes);
}

void cxgui::Gtkmm3Dialog::SetTooltip(const std::string& p_tooltipContents)
{
    IF_CONDITION_NOT_MET_DO(m_delegate, return;);
    m_delegate->SetTooltip(p_tooltipContents);
}
