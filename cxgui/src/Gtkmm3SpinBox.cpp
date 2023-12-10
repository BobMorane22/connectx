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
 * @file Gtkmm3SpinBox.cpp
 * @date 2023
 *
 *************************************************************************************************/

#include <cxinv/assertion.h>
#include <cxgui/EnabledState.h>
#include <cxgui/Gtkmm3SpinBox.h>
#include <cxgui/Margins.h>

cxgui::ISpinBox::Range::Range(const cxgui::ISpinBox::Minimum& p_min,
                              const cxgui::ISpinBox::Maximum& p_max)
: m_min{0}, m_max{0}
{
    PRECONDITION(p_max.Get() > p_min.Get());

    m_min = p_min;
    m_max = p_max;

    POSTCONDITION(m_max.Get() > m_min.Get());
    INVARIANT(m_max.Get() > m_min.Get());
}

cxgui::Gtkmm3SpinBox::Gtkmm3SpinBox(int p_initialValue,
                                    const cxgui::ISpinBox::ClimbRate& p_climbRate,
                                    const cxgui::ISpinBox::Range& p_range)
: m_limits{p_range}
{
    PRECONDITION(p_climbRate.Get() >  0);

    const double initialValue = static_cast<double>(p_initialValue);
    const double climbRate = static_cast<double>(p_climbRate.Get());
    const double min = static_cast<double>(p_range.m_min.Get());
    const double max = static_cast<double>(p_range.m_max.Get());

    auto adjustment = Gtk::Adjustment::create(initialValue, min, max, climbRate);
    set_adjustment(adjustment);
}

size_t cxgui::Gtkmm3SpinBox::GetWidth() const
{
    const int width = get_width();
    IF_CONDITION_NOT_MET_DO(width > 0, return 0u;);

    return static_cast<size_t>(width);
}

size_t cxgui::Gtkmm3SpinBox::GetHeight() const
{
    const int height = get_height();
    IF_CONDITION_NOT_MET_DO(height > 0, return 0u;);

    return static_cast<size_t>(height);
}

void cxgui::Gtkmm3SpinBox::SetEnabled(EnabledState p_enabled)
{
    set_sensitive(p_enabled == EnabledState::Enabled ? true : false);
}

void cxgui::Gtkmm3SpinBox::SetMargins(const Margins& p_newMarginSizes)
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

int cxgui::Gtkmm3SpinBox::GetValue() const
{
    const int value = get_value_as_int();

    POSTCONDITION(m_limits.m_min.Get() <= value);
    POSTCONDITION(m_limits.m_max.Get() >= value);

    return value;
}

