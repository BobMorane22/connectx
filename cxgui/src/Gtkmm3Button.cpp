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
 * @file Gtkmm3Button.cpp
 * @date 2024
 *
 *************************************************************************************************/

#include <cxinv/assertion.h>
#include <cxcmn/helpers.h>
#include <cxgui/Gtkmm3Button.h>
#include <cxgui/Gtkmm3Connection.h>
#include <cxgui/Margins.h>

namespace
{

class Gtkmm3OnClickedSignal : public cx::gui::ISignal<void>
{

public:

    explicit Gtkmm3OnClickedSignal(Gtk::Button& p_button)
    : m_button{p_button}
    {
    }

    [[nodiscard]] std::unique_ptr<cx::gui::IConnection> Connect(const std::function<void()>& p_slot) override
    {
        sigc::connection gtkConnection = m_button.signal_clicked().connect(p_slot);
        IF_CONDITION_NOT_MET_DO(gtkConnection.connected(), return nullptr;);

        return std::make_unique<cx::gui::Gtkmm3Connection>(gtkConnection);
    }

private:

    Gtk::Button& m_button;

};

} // namespace

cx::gui::Gtkmm3Button::Gtkmm3Button()
: cx::gui::Gtkmm3Button("")
{
}

cx::gui::Gtkmm3Button::Gtkmm3Button(const std::string& p_label)
{
    set_label(p_label);
}

void cx::gui::Gtkmm3Button::SetDelegate(std::unique_ptr<IWidget> p_delegate)
{
    IF_PRECONDITION_NOT_MET_DO(p_delegate, return;);

    m_delegate = std::move(p_delegate);

    POSTCONDITION(m_delegate);
}

void cx::gui::Gtkmm3Button::UpdateContents(const std::string& p_newContents)
{
    set_label(p_newContents);
}

std::string cx::gui::Gtkmm3Button::GetContents() const
{
    return get_label();
}

std::unique_ptr<cx::gui::ISignal<void>> cx::gui::Gtkmm3Button::OnClicked()
{
    return std::make_unique<Gtkmm3OnClickedSignal>(*this);
}

size_t cx::gui::Gtkmm3Button::GetWidth() const 
{
    IF_CONDITION_NOT_MET_DO(m_delegate, return 0u;);
    return m_delegate->GetWidth();
}

size_t cx::gui::Gtkmm3Button::GetHeight() const 
{
    IF_CONDITION_NOT_MET_DO(m_delegate, return 0u;);
    return m_delegate->GetHeight();
}

void cx::gui::Gtkmm3Button::SetEnabled(EnabledState p_enabled) 
{
    IF_CONDITION_NOT_MET_DO(m_delegate, return;);
    m_delegate->SetEnabled(p_enabled);
}

void cx::gui::Gtkmm3Button::SetMargins(const Margins& p_newMarginSizes) 
{
    IF_CONDITION_NOT_MET_DO(m_delegate, return;);
    m_delegate->SetMargins(p_newMarginSizes);
}

void cx::gui::Gtkmm3Button::SetTooltip(const std::string& p_tooltipContents)
{
    IF_CONDITION_NOT_MET_DO(m_delegate, return;);
    m_delegate->SetTooltip(p_tooltipContents);
}

std::unique_ptr<cx::gui::ISignal<cx::gui::EventPropagation, cx::gui::KeyboardKeyPressedEvent>> cx::gui::Gtkmm3Button::OnKeyPressed()
{
    IF_CONDITION_NOT_MET_DO(m_delegate, return nullptr;);
    return m_delegate->OnKeyPressed();
}
