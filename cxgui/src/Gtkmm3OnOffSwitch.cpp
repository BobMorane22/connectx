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
    const int width = get_width();
    IF_CONDITION_NOT_MET_DO(width >= 0, return 0u;);

    return width;
}

size_t cxgui::Gtkmm3OnOffSwitch::GetHeight() const
{
    const int height = get_height();
    IF_CONDITION_NOT_MET_DO(height >= 0, return 0u;);

    return height;
}

void cxgui::Gtkmm3OnOffSwitch::SetEnabled(EnabledState p_enabled)
{
    set_sensitive(p_enabled == EnabledState::Enabled ? true : false);
}

void cxgui::Gtkmm3OnOffSwitch::SetMargins(const Margins& p_newMarginSizes)
{
    const int start = p_newMarginSizes.m_left.Get();
    const int end = p_newMarginSizes.m_right.Get();
    const int top = p_newMarginSizes.m_top.Get();
    const int bottom = p_newMarginSizes.m_bottom.Get();

    set_margin_start(start);
    set_margin_end(end);
    set_margin_top(top);
    set_margin_bottom(bottom);
}
