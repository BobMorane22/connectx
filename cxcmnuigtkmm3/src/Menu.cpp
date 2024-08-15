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
 * @file Menu.cpp
 * @date 2024
 *
 *************************************************************************************************/

#include <gtkmm/menuitem.h>

#include <cxinv/assertion.h>
#include <cxcmnui/EventPropagation.h>
#include <cxcmnui/KeyboardKeyPressedEvent.h>
#include <cxcmnui/Margins.h>

#include "Menu.h"
#include "MenuItem.h"

cx::cmn::ui::gtkmm3::Menu::Menu(const std::string& p_title)
{
    PRECONDITION(!p_title.empty());    

    m_titleMenuItem.set_label(p_title);
    m_titleMenuItem.set_submenu(*this);
}

void cx::cmn::ui::gtkmm3::Menu::Register(cx::cmn::ui::IMenuItem& p_item)
{
    auto* gtkMenuItem = dynamic_cast<Gtk::MenuItem*>(&p_item);
    IF_CONDITION_NOT_MET_DO(gtkMenuItem, return;);

    add(*gtkMenuItem);
}

Gtk::MenuItem& cx::cmn::ui::gtkmm3::Menu::GetTitleMenuItem()
{
    return m_titleMenuItem;
}

void cx::cmn::ui::gtkmm3::Menu::SetDelegate(std::unique_ptr<IWidget> p_delegate)
{
    IF_PRECONDITION_NOT_MET_DO(p_delegate, return;);

    m_delegate = std::move(p_delegate);

    POSTCONDITION(m_delegate);
}

size_t cx::cmn::ui::gtkmm3::Menu::GetWidth() const
{
    IF_CONDITION_NOT_MET_DO(m_delegate, return 0u;);
    return m_delegate->GetWidth();
}

size_t cx::cmn::ui::gtkmm3::Menu::GetHeight() const
{
    IF_CONDITION_NOT_MET_DO(m_delegate, return 0u;);
    return m_delegate->GetHeight();
}

void cx::cmn::ui::gtkmm3::Menu::SetEnabled(cx::cmn::ui::EnabledState p_enabled)
{
    IF_CONDITION_NOT_MET_DO(m_delegate, return;);
    m_delegate->SetEnabled(p_enabled);
}

void cx::cmn::ui::gtkmm3::Menu::SetMargins(const Margins& p_newMarginSizes)
{
    IF_CONDITION_NOT_MET_DO(m_delegate, return;);
    m_delegate->SetMargins(p_newMarginSizes);
}

void cx::cmn::ui::gtkmm3::Menu::SetTooltip(const std::string& p_tooltipContents)
{
    IF_CONDITION_NOT_MET_DO(m_delegate, return;);
    m_delegate->SetTooltip(p_tooltipContents);
}

std::unique_ptr<cx::cmn::ui::ISignal<cx::cmn::ui::EventPropagation, cx::cmn::ui::KeyboardKeyPressedEvent>> cx::cmn::ui::gtkmm3::Menu::OnKeyPressed()
{
    IF_CONDITION_NOT_MET_DO(m_delegate, return nullptr;);
    return m_delegate->OnKeyPressed();
}
