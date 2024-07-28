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
 * @file Gtkmm3Menu.cpp
 * @date 2024
 *
 *************************************************************************************************/

#include <gtkmm/menuitem.h>

#include <cxinv/assertion.h>
#include <cxuicmn/EventPropagation.h>
#include <cxuicmngtkmm3/Gtkmm3Menu.h>
#include <cxuicmngtkmm3/Gtkmm3MenuItem.h>
#include <cxuicmn/KeyboardKeyPressedEvent.h>
#include <cxuicmn/Margins.h>

cx::ui::cmn::Gtkmm3Menu::Gtkmm3Menu(const std::string& p_title)
{
    PRECONDITION(!p_title.empty());    

    m_titleMenuItem.set_label(p_title);
    m_titleMenuItem.set_submenu(*this);
}

void cx::ui::cmn::Gtkmm3Menu::Register(cx::ui::cmn::IMenuItem& p_item)
{
    auto* gtkMenuItem = dynamic_cast<Gtk::MenuItem*>(&p_item);
    IF_CONDITION_NOT_MET_DO(gtkMenuItem, return;);

    add(*gtkMenuItem);
}

Gtk::MenuItem& cx::ui::cmn::Gtkmm3Menu::GetTitleMenuItem()
{
    return m_titleMenuItem;
}

void cx::ui::cmn::Gtkmm3Menu::SetDelegate(std::unique_ptr<IWidget> p_delegate)
{
    IF_PRECONDITION_NOT_MET_DO(p_delegate, return;);

    m_delegate = std::move(p_delegate);

    POSTCONDITION(m_delegate);
}

size_t cx::ui::cmn::Gtkmm3Menu::GetWidth() const
{
    IF_CONDITION_NOT_MET_DO(m_delegate, return 0u;);
    return m_delegate->GetWidth();
}

size_t cx::ui::cmn::Gtkmm3Menu::GetHeight() const
{
    IF_CONDITION_NOT_MET_DO(m_delegate, return 0u;);
    return m_delegate->GetHeight();
}

void cx::ui::cmn::Gtkmm3Menu::SetEnabled(cx::ui::cmn::EnabledState p_enabled)
{
    IF_CONDITION_NOT_MET_DO(m_delegate, return;);
    m_delegate->SetEnabled(p_enabled);
}

void cx::ui::cmn::Gtkmm3Menu::SetMargins(const Margins& p_newMarginSizes)
{
    IF_CONDITION_NOT_MET_DO(m_delegate, return;);
    m_delegate->SetMargins(p_newMarginSizes);
}

void cx::ui::cmn::Gtkmm3Menu::SetTooltip(const std::string& p_tooltipContents)
{
    IF_CONDITION_NOT_MET_DO(m_delegate, return;);
    m_delegate->SetTooltip(p_tooltipContents);
}

std::unique_ptr<cx::ui::cmn::ISignal<cx::ui::cmn::EventPropagation, cx::ui::cmn::KeyboardKeyPressedEvent>> cx::ui::cmn::Gtkmm3Menu::OnKeyPressed()
{
    IF_CONDITION_NOT_MET_DO(m_delegate, return nullptr;);
    return m_delegate->OnKeyPressed();
}
