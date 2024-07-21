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
 * @file Gtkmm3StatusBar.cpp
 * @date 2020
 *
 *************************************************************************************************/

#include <cxinv/assertion.h>
#include <cxgui/EventPropagation.h>
#include <cxgui/Gtkmm3StatusBar.h>
#include <cxgui/KeyboardKeyPressedEvent.h>
#include <cxgui/Margins.h>

cx::gui::Gtkmm3StatusBar::Gtkmm3StatusBar(IStatusBarPresenter& p_presenter)
 : m_presenter{p_presenter}
{
}

void cx::gui::Gtkmm3StatusBar::SetDelegate(std::unique_ptr<IWidget> p_delegate)
{
    IF_PRECONDITION_NOT_MET_DO(p_delegate, return;);

    m_delegate = std::move(p_delegate);

    POSTCONDITION(m_delegate);
}

void cx::gui::Gtkmm3StatusBar::SetLastUserActionStatus(const std::string& p_lastUserActionDescription)
{
    push(p_lastUserActionDescription);
}

void cx::gui::Gtkmm3StatusBar::Update(cxmodel::ModelNotificationContext, cxmodel::ModelSubject* p_subject)
{
    if(p_subject)
    {
        SetLastUserActionStatus(m_presenter.GetStatusBarMessage());
    }
}

size_t cx::gui::Gtkmm3StatusBar::GetWidth() const 
{
    IF_CONDITION_NOT_MET_DO(m_delegate, return 0u;);
    return m_delegate->GetWidth();
}

size_t cx::gui::Gtkmm3StatusBar::GetHeight() const 
{
    IF_CONDITION_NOT_MET_DO(m_delegate, return 0u;);
    return m_delegate->GetHeight();
}

void cx::gui::Gtkmm3StatusBar::SetEnabled(EnabledState p_enabled) 
{
    IF_CONDITION_NOT_MET_DO(m_delegate, return;);
    m_delegate->SetEnabled(p_enabled);
}

void cx::gui::Gtkmm3StatusBar::SetMargins(const Margins& p_newMarginSizes) 
{
    IF_CONDITION_NOT_MET_DO(m_delegate, return;);
    m_delegate->SetMargins(p_newMarginSizes);
}

void cx::gui::Gtkmm3StatusBar::SetTooltip(const std::string& p_tooltipContents)
{
    IF_CONDITION_NOT_MET_DO(m_delegate, return;);
    m_delegate->SetTooltip(p_tooltipContents);
}

std::unique_ptr<cx::gui::ISignal<cx::gui::EventPropagation, cx::gui::KeyboardKeyPressedEvent>> cx::gui::Gtkmm3StatusBar::OnKeyPressed()
{
    IF_CONDITION_NOT_MET_DO(m_delegate, return nullptr;);
    return m_delegate->OnKeyPressed();
}
