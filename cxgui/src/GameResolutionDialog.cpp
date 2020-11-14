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
 * @file GameResolutionDialog.cpp
 * @date 2020
 *
 *************************************************************************************************/

#include <GameResolutionDialog.h>
#include <IGameResolutionDialogPresenter.h>

cxgui::GameResolutionDialog::GameResolutionDialog(std::unique_ptr<IGameResolutionDialogPresenter> p_presenter)
: m_presenter{std::move(p_presenter)}
{
    POSTCONDITION(m_presenter);
}

void cxgui::GameResolutionDialog::Update(cxmodel::NotificationContext /*p_context*/, cxmodel::Subject* /*p_subject*/)
{
    // Nothing to do...
}

void cxgui::GameResolutionDialog::ConfigureWindow()
{
    m_window.set_modal(true);
}

void cxgui::GameResolutionDialog::RegisterLayouts()
{
    // Nothing to do...
}

void cxgui::GameResolutionDialog::RegisterWidgets()
{
    m_mainLayout.attach(m_message, 0, 0, 1, 1);
}

void cxgui::GameResolutionDialog::ConfigureLayouts()
{
    // Nothing to do...
}

void cxgui::GameResolutionDialog::ConfigureWidgets()
{
    m_message.set_text(m_presenter->GetResolutionMessage());
}

void cxgui::GameResolutionDialog::ConfigureSignalHandlers()
{
    // Nothing to do...
}
