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
 * @file OnOffSwitch.cpp
 * @date 2022
 *
 *************************************************************************************************/ 

#include <cxinv/assertion.h>

#include <cxgui/EnabledState.h>
#include <cxgui/Margins.h>
#include <cxgui/OnOffState.h>
#include <cxgui/OnOffSwitch.h>

cxgui::OnOffSwitch::OnOffSwitch()
{
    GetUnderlying().signal_state_flags_changed().connect(
        [this](Gtk::StateFlags  /*p_previousState*/)
        {
            IF_CONDITION_NOT_MET_DO(bool(m_stateChangedSlot), return;);
            m_stateChangedSlot();
        },
        false
    );
}

cxgui::OnOffState cxgui::OnOffSwitch::GetState() const
{
    if(m_underlying.get_active())
    {
        return OnOffState::ON;
    }

    return OnOffState::OFF;
}

void cxgui::OnOffSwitch::SetState(cxgui::OnOffState p_newState)
{
    if(p_newState == OnOffState::ON)
    {
        m_underlying.set_active(true);
    }
    else
    {
        m_underlying.set_active(false);
    }

    IF_CONDITION_NOT_MET_DO(bool(m_stateChangedSlot), return;);
    m_stateChangedSlot();
}

void cxgui::OnOffSwitch::StateChangedSignalConnect(const std::function<void()>& p_slot)
{
    m_stateChangedSlot = p_slot;
}

size_t cxgui::OnOffSwitch::GetWidth() const
{
    const int width = m_underlying.get_width();
    IF_CONDITION_NOT_MET_DO(width >= 0, return 0u;);

    return width;
}

size_t cxgui::OnOffSwitch::GetHeight() const
{
    const int height = m_underlying.get_height();
    IF_CONDITION_NOT_MET_DO(height >= 0, return 0u;);

    return height;
}

void cxgui::OnOffSwitch::SetEnabled(EnabledState p_enabled)
{
    m_underlying.set_sensitive(p_enabled == EnabledState::Enabled ? true : false);
}

void cxgui::OnOffSwitch::SetMargins(const Margins& p_newMarginSizes)
{
    const int start = p_newMarginSizes.m_left.Get();
    const int end = p_newMarginSizes.m_right.Get();
    const int top = p_newMarginSizes.m_top.Get();
    const int bottom = p_newMarginSizes.m_bottom.Get();

    m_underlying.set_margin_start(start);
    m_underlying.set_margin_end(end);
    m_underlying.set_margin_top(top);
    m_underlying.set_margin_bottom(bottom);
}
