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
 * @file Label.cpp
 * @date 2024
 *
 *************************************************************************************************/

#include <cxinv/assertion.h>

#include "Label.h"

cx::cmn::ui::gtkmm3::Label::Label()
: Label("")
{
}

cx::cmn::ui::gtkmm3::Label::Label(const std::string& p_contents)
: Gtk::Label{p_contents}
{
    set_use_markup(true);
}

void cx::cmn::ui::gtkmm3::Label::SetDelegate(std::unique_ptr<IWidget> p_delegate)
{
    IF_PRECONDITION_NOT_MET_DO(p_delegate, return;);

    m_delegate = std::move(p_delegate);

    POSTCONDITION(m_delegate);
}

void cx::cmn::ui::gtkmm3::Label::UpdateContents(const std::string& p_newContents) 
{
    set_markup(p_newContents);
}

std::string cx::cmn::ui::gtkmm3::Label::GetContents() const
{
    return get_text();
}

size_t cx::cmn::ui::gtkmm3::Label::GetWidth() const 
{
    IF_CONDITION_NOT_MET_DO(m_delegate, return 0u;);
    return m_delegate->GetWidth();
}

size_t cx::cmn::ui::gtkmm3::Label::GetHeight() const 
{
    IF_CONDITION_NOT_MET_DO(m_delegate, return 0u;);
    return m_delegate->GetHeight();
}

void cx::cmn::ui::gtkmm3::Label::SetEnabled(EnabledState p_enabled) 
{
    IF_CONDITION_NOT_MET_DO(m_delegate, return;);
    m_delegate->SetEnabled(p_enabled);
}

void cx::cmn::ui::gtkmm3::Label::SetMargins(const Margins& p_newMarginSizes) 
{
    IF_CONDITION_NOT_MET_DO(m_delegate, return;);
    m_delegate->SetMargins(p_newMarginSizes);
}

void cx::cmn::ui::gtkmm3::Label::SetTooltip(const std::string& p_tooltipContents)
{
    IF_CONDITION_NOT_MET_DO(m_delegate, return;);
    m_delegate->SetTooltip(p_tooltipContents);
}

std::unique_ptr<cx::cmn::ui::ISignal<cx::cmn::ui::EventPropagation, cx::cmn::ui::KeyboardKeyPressedEvent>> cx::cmn::ui::gtkmm3::Label::OnKeyPressed()
{
    IF_CONDITION_NOT_MET_DO(m_delegate, return nullptr;);
    return m_delegate->OnKeyPressed();
}
