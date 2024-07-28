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
#include <cxcmn/helpers.h>
#include <cxuicmn/EnabledState.h>
#include <cxuicmn/EventPropagation.h>
#include <cxuicmngtkmm3/Gtkmm3SpinBox.h>
#include <cxuicmn/KeyboardKeyPressedEvent.h>
#include <cxuicmn/Margins.h>

cx::ui::cmn::ISpinBox::Range::Range(const cx::ui::cmn::ISpinBox::Minimum& p_min,
                              const cx::ui::cmn::ISpinBox::Maximum& p_max)
: m_min{0}, m_max{0}
{
    PRECONDITION(p_max.Get() > p_min.Get());

    m_min = p_min;
    m_max = p_max;

    POSTCONDITION(m_max.Get() > m_min.Get());
    INVARIANT(m_max.Get() > m_min.Get());
}

cx::ui::cmn::Gtkmm3SpinBox::Gtkmm3SpinBox(int p_initialValue,
                                    const cx::ui::cmn::ISpinBox::ClimbRate& p_climbRate,
                                    const cx::ui::cmn::ISpinBox::Range& p_range)
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

void cx::ui::cmn::Gtkmm3SpinBox::SetDelegate(std::unique_ptr<cx::ui::cmn::IWidget> p_delegate)
{
    IF_PRECONDITION_NOT_MET_DO(p_delegate, return;);

    m_delegate = std::move(p_delegate);

    POSTCONDITION(m_delegate);
}

int cx::ui::cmn::Gtkmm3SpinBox::GetValue() const
{
    const int value = get_value_as_int();

    POSTCONDITION(m_limits.m_min.Get() <= value);
    POSTCONDITION(m_limits.m_max.Get() >= value);

    return value;
}

size_t cx::ui::cmn::Gtkmm3SpinBox::GetWidth() const
{
    IF_CONDITION_NOT_MET_DO(m_delegate, return 0u;);
    return m_delegate->GetWidth();
}

size_t cx::ui::cmn::Gtkmm3SpinBox::GetHeight() const
{
    IF_CONDITION_NOT_MET_DO(m_delegate, return 0u;);
    return m_delegate->GetHeight();
}

void cx::ui::cmn::Gtkmm3SpinBox::SetEnabled(EnabledState p_enabled)
{
    IF_CONDITION_NOT_MET_DO(m_delegate, return;);
    m_delegate->SetEnabled(p_enabled);
}

void cx::ui::cmn::Gtkmm3SpinBox::SetMargins(const Margins& p_newMarginSizes)
{
    IF_CONDITION_NOT_MET_DO(m_delegate, return;);
    m_delegate->SetMargins(p_newMarginSizes);
}

void cx::ui::cmn::Gtkmm3SpinBox::SetTooltip(const std::string& p_tooltipContents)
{
    IF_CONDITION_NOT_MET_DO(m_delegate, return;);
    m_delegate->SetTooltip(p_tooltipContents);
}

std::unique_ptr<cx::ui::cmn::ISignal<cx::ui::cmn::EventPropagation, cx::ui::cmn::KeyboardKeyPressedEvent>> cx::ui::cmn::Gtkmm3SpinBox::OnKeyPressed()
{
    IF_CONDITION_NOT_MET_DO(m_delegate, return nullptr;);
    return m_delegate->OnKeyPressed();
}
