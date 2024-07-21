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

#include <gtkmm/enums.h>
#include <gtkmm/messagedialog.h>

#include <cxinv/assertion.h>
#include <cxgui/DialogRole.h>
#include <cxgui/gtkmmConversions.h>
#include <cxgui/Gtkmm3Dialog.h>


cx::gui::Gtkmm3Dialog::Gtkmm3Dialog(cx::gui::IWindow& p_parent, DialogRole p_role, const std::string& p_message)
: Gtk::MessageDialog(dynamic_cast<Gtk::Window&>(p_parent), p_message, true, Gtk::MESSAGE_INFO, Gtk::ButtonsType::BUTTONS_OK, true)
{
    PRECONDITION(!p_message.empty());

    const auto messageTypeConversion = cx::gui::ToGtk<Gtk::MessageType>(p_role);
    Glib::PropertyProxy<Gtk::MessageType> messageType = property_message_type();
    messageType.set_value(messageTypeConversion.value_or(Gtk::MESSAGE_OTHER));
}

int cx::gui::Gtkmm3Dialog::Show()
{
    return run();
}

void cx::gui::Gtkmm3Dialog::ShrinkToContents(IWindow::Orientation /*p_orientation*/)
{
    // Nothing to do.
}

void cx::gui::Gtkmm3Dialog::Update(cx::model::ModelNotificationContext /*p_context*/, cx::model::ModelSubject* /*p_subject*/)
{
    // Nothing to do.
}

void cx::gui::Gtkmm3Dialog::SetDelegate(std::unique_ptr<IWidget> p_delegate)
{
    IF_PRECONDITION_NOT_MET_DO(p_delegate, return;);

    m_delegate = std::move(p_delegate);

    POSTCONDITION(m_delegate);
}

size_t cx::gui::Gtkmm3Dialog::GetWidth() const 
{
    IF_CONDITION_NOT_MET_DO(m_delegate, return 0u;);
    return m_delegate->GetWidth();
}

size_t cx::gui::Gtkmm3Dialog::GetHeight() const 
{
    IF_CONDITION_NOT_MET_DO(m_delegate, return 0u;);
    return m_delegate->GetHeight();
}

void cx::gui::Gtkmm3Dialog::SetEnabled(EnabledState p_enabled) 
{
    IF_CONDITION_NOT_MET_DO(m_delegate, return;);
    m_delegate->SetEnabled(p_enabled);
}

void cx::gui::Gtkmm3Dialog::SetMargins(const Margins& p_newMarginSizes) 
{
    IF_CONDITION_NOT_MET_DO(m_delegate, return;);
    m_delegate->SetMargins(p_newMarginSizes);
}

void cx::gui::Gtkmm3Dialog::SetTooltip(const std::string& p_tooltipContents)
{
    IF_CONDITION_NOT_MET_DO(m_delegate, return;);
    m_delegate->SetTooltip(p_tooltipContents);
}

std::unique_ptr<cx::gui::ISignal<cx::gui::EventPropagation, cx::gui::KeyboardKeyPressedEvent>> cx::gui::Gtkmm3Dialog::OnKeyPressed()
{
    IF_CONDITION_NOT_MET_DO(m_delegate, return nullptr;);
    return m_delegate->OnKeyPressed();
}
