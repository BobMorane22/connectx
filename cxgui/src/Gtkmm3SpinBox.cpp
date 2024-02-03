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
#include <cxstd/helpers.h>
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

void cxgui::Gtkmm3SpinBox::SetDelegate(std::unique_ptr<cxgui::IWidget> p_delegate)
{
    IF_PRECONDITION_NOT_MET_DO(p_delegate, return;);

    m_delegate = std::move(p_delegate);

    POSTCONDITION(m_delegate);
}

size_t cxgui::Gtkmm3SpinBox::GetWidth() const
{
    IF_CONDITION_NOT_MET_DO(m_delegate, return 0u;);
    return m_delegate->GetWidth();
}

size_t cxgui::Gtkmm3SpinBox::GetHeight() const
{
    IF_CONDITION_NOT_MET_DO(m_delegate, return 0u;);
    return m_delegate->GetHeight();
}

void cxgui::Gtkmm3SpinBox::SetEnabled(EnabledState p_enabled)
{
    IF_CONDITION_NOT_MET_DO(m_delegate, return;);
    m_delegate->SetEnabled(p_enabled);
}

void cxgui::Gtkmm3SpinBox::SetMargins(const Margins& p_newMarginSizes)
{
    IF_CONDITION_NOT_MET_DO(m_delegate, return;);
    m_delegate->SetMargins(p_newMarginSizes);
}

void cxgui::Gtkmm3SpinBox::SetTooltip(const std::string& p_tooltipContents)
{
    IF_CONDITION_NOT_MET_DO(m_delegate, return;);
    m_delegate->SetTooltip(p_tooltipContents);
}

int cxgui::Gtkmm3SpinBox::GetValue() const
{
    const int value = get_value_as_int();

    POSTCONDITION(m_limits.m_min.Get() <= value);
    POSTCONDITION(m_limits.m_max.Get() >= value);

    return value;
}
