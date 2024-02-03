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
 * @file Gtkmm3MenuBar.cpp
 * @date 2024
 *
 *************************************************************************************************/

#include <gtkmm/menuitem.h>

#include <cxinv/assertion.h>
#include <cxgui/Gtkmm3Menu.h>
#include <cxgui/Gtkmm3MenuBar.h>
#include <cxgui/IMenu.h>

void cxgui::Gtkmm3MenuBar::Register(cxgui::IMenu& p_menu)
{
    auto* gtkmm3Menu = dynamic_cast<cxgui::Gtkmm3Menu*>(&p_menu);
    IF_CONDITION_NOT_MET_DO(gtkmm3Menu, return;);

    Gtk::MenuItem& gtkMenuItem = gtkmm3Menu->GetTitleMenuItem();

    add(gtkMenuItem);
}

void cxgui::Gtkmm3MenuBar::SetDelegate(std::unique_ptr<IWidget> p_delegate)
{
    IF_PRECONDITION_NOT_MET_DO(p_delegate, return;);

    m_delegate = std::move(p_delegate);

    POSTCONDITION(m_delegate);
}

size_t cxgui::Gtkmm3MenuBar::GetWidth() const
{
    IF_CONDITION_NOT_MET_DO(m_delegate, return 0u;);
    return m_delegate->GetWidth();
}

size_t cxgui::Gtkmm3MenuBar::GetHeight() const
{
    IF_CONDITION_NOT_MET_DO(m_delegate, return 0u;);
    return m_delegate->GetHeight();
}

void cxgui::Gtkmm3MenuBar::SetEnabled(cxgui::EnabledState p_enabled)
{
    IF_CONDITION_NOT_MET_DO(m_delegate, return;);
    m_delegate->SetEnabled(p_enabled);
}

void cxgui::Gtkmm3MenuBar::SetMargins(const Margins& p_newMarginSizes)
{
    IF_CONDITION_NOT_MET_DO(m_delegate, return;);
    m_delegate->SetMargins(p_newMarginSizes);
}
