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
 * @file Gtkmm3OnOffSwitch.cpp
 * @date 2022
 *
 *************************************************************************************************/ 

#include <cxinv/assertion.h>
#include <cxcmn/helpers.h>
#include <cxcmnui/EnabledState.h>
#include <cxcmnui/EventPropagation.h>
#include <cxcmnui/ISignal.h>
#include <cxcmnui/KeyboardKeyPressedEvent.h>
#include <cxcmnui/Margins.h>
#include <cxcmnui/OnOffState.h>
#include <cxcmnuigtkmm3/Gtkmm3Connection.h>
#include <cxcmnuigtkmm3/Gtkmm3OnOffSwitch.h>

namespace
{

class Gtkmm3OnStateChangedSignal : public cx::cmn::ui::ISignal<void>
{

public:

    explicit Gtkmm3OnStateChangedSignal(Gtk::Switch& p_switch)
    : m_switch{p_switch}
    {
    }

    [[nodiscard]] std::unique_ptr<cx::cmn::ui::IConnection> Connect(const std::function<void()>& p_slot) override
    {
        sigc::connection gtkConnection = m_switch.connect_property_changed_with_return("active", p_slot);
        IF_CONDITION_NOT_MET_DO(gtkConnection.connected(), return nullptr;);

        return std::make_unique<cx::cmn::ui::Gtkmm3Connection>(gtkConnection);
    }

private:

    Gtk::Switch& m_switch;
};

} // namespace

void cx::cmn::ui::Gtkmm3OnOffSwitch::SetDelegate(std::unique_ptr<cx::cmn::ui::IWidget> p_delegate)
{
    IF_PRECONDITION_NOT_MET_DO(p_delegate, return;);

    m_delegate = std::move(p_delegate);

    POSTCONDITION(m_delegate);
}

cx::cmn::ui::OnOffState cx::cmn::ui::Gtkmm3OnOffSwitch::GetState() const
{
    if(get_active())
    {
        return OnOffState::ON;
    }

    return OnOffState::OFF;
}

void cx::cmn::ui::Gtkmm3OnOffSwitch::SetState(cx::cmn::ui::OnOffState p_newState)
{
    if(p_newState == OnOffState::ON)
    {
        set_active(true);
    }
    else
    {
        set_active(false);
    }
}

std::unique_ptr<cx::cmn::ui::ISignal<void>> cx::cmn::ui::Gtkmm3OnOffSwitch::OnStateChanged()
{
    return std::make_unique<Gtkmm3OnStateChangedSignal>(*this);
}

size_t cx::cmn::ui::Gtkmm3OnOffSwitch::GetWidth() const
{
    IF_CONDITION_NOT_MET_DO(m_delegate, return 0u;);
    return m_delegate->GetWidth();
}

size_t cx::cmn::ui::Gtkmm3OnOffSwitch::GetHeight() const
{
    IF_CONDITION_NOT_MET_DO(m_delegate, return 0u;);
    return m_delegate->GetHeight();
}

void cx::cmn::ui::Gtkmm3OnOffSwitch::SetEnabled(EnabledState p_enabled)
{
    IF_CONDITION_NOT_MET_DO(m_delegate, return;);
    m_delegate->SetEnabled(p_enabled);
}

void cx::cmn::ui::Gtkmm3OnOffSwitch::SetMargins(const Margins& p_newMarginSizes)
{
    IF_CONDITION_NOT_MET_DO(m_delegate, return;);
    m_delegate->SetMargins(p_newMarginSizes);
}

void cx::cmn::ui::Gtkmm3OnOffSwitch::SetTooltip(const std::string& p_tooltipContents)
{
    IF_CONDITION_NOT_MET_DO(m_delegate, return;);
    m_delegate->SetTooltip(p_tooltipContents);
}

std::unique_ptr<cx::cmn::ui::ISignal<cx::cmn::ui::EventPropagation, cx::cmn::ui::KeyboardKeyPressedEvent>> cx::cmn::ui::Gtkmm3OnOffSwitch::OnKeyPressed()
{
    IF_CONDITION_NOT_MET_DO(m_delegate, return nullptr;);
    return m_delegate->OnKeyPressed();
}
