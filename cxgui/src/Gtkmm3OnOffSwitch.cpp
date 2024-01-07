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
#include <cxstd/helpers.h>
#include <cxgui/EnabledState.h>
#include <cxgui/Gtkmm3Connection.h>
#include <cxgui/Gtkmm3OnOffSwitch.h>
#include <cxgui/ISignal.h>
#include <cxgui/Margins.h>
#include <cxgui/OnOffState.h>

namespace
{

class Gtkmm3OnStateChangedSignal : public cxgui::ISignal<void>
{

public:

    explicit Gtkmm3OnStateChangedSignal(Gtk::Switch& p_switch)
    : m_switch{p_switch}
    {
    }

    [[nodiscard]] virtual std::unique_ptr<cxgui::IConnection> Connect(const std::function<void()>& p_slot) override
    {
        sigc::connection gtkConnection = m_switch.connect_property_changed_with_return("active", p_slot);
        IF_CONDITION_NOT_MET_DO(gtkConnection.connected(), return nullptr;);

        return std::make_unique<cxgui::Gtkmm3Connection>(gtkConnection);
    }

private:

    Gtk::Switch& m_switch;
};

} // namespace

void cxgui::Gtkmm3OnOffSwitch::SetDelegate(std::unique_ptr<cxgui::IWidget> p_delegate)
{
    IF_PRECONDITION_NOT_MET_DO(p_delegate, return;);

    m_delegate = std::move(p_delegate);

    POSTCONDITION(m_delegate);
}

cxgui::OnOffState cxgui::Gtkmm3OnOffSwitch::GetState() const
{
    if(get_active())
    {
        return OnOffState::ON;
    }

    return OnOffState::OFF;
}

void cxgui::Gtkmm3OnOffSwitch::SetState(cxgui::OnOffState p_newState)
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

std::unique_ptr<cxgui::ISignal<void>> cxgui::Gtkmm3OnOffSwitch::OnStateChanged()
{
    return std::make_unique<Gtkmm3OnStateChangedSignal>(*this);
}

size_t cxgui::Gtkmm3OnOffSwitch::GetWidth() const
{
    RETURN_IF(!m_delegate, 0u);
    return m_delegate->GetWidth();
}

size_t cxgui::Gtkmm3OnOffSwitch::GetHeight() const
{
    RETURN_IF(!m_delegate, 0u);
    return m_delegate->GetHeight();
}

void cxgui::Gtkmm3OnOffSwitch::SetEnabled(EnabledState p_enabled)
{
    RETURN_IF(!m_delegate,);
    m_delegate->SetEnabled(p_enabled);
}

void cxgui::Gtkmm3OnOffSwitch::SetMargins(const Margins& p_newMarginSizes)
{
    RETURN_IF(!m_delegate,);
    m_delegate->SetMargins(p_newMarginSizes);
}
