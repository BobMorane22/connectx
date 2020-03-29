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
 * @file StatusBar.cpp
 * @date 2020
 *
 *************************************************************************************************/

#include <cxinv/include/assertion.h>

#include <StatusBar.h>

cxgui::StatusBar::~StatusBar() = default;

cxgui::StatusBar::StatusBar(IStatusBarPresenter& p_presenter)
 : m_presenter{p_presenter}
{
}

void cxgui::StatusBar::SetLastUserActionStatus(const std::string& p_lastUserActionDescription)
{
    m_statusbar.push(p_lastUserActionDescription);
}

void cxgui::StatusBar::Update(cxmodel::NotificationContext, cxmodel::Subject* p_subject)
{
    if(p_subject)
    {
        SetLastUserActionStatus(m_presenter.GetStatusBarMessage());
    }
}

Gtk::Statusbar& cxgui::StatusBar::GetGtkStatusBar()
{
    return m_statusbar;
}
