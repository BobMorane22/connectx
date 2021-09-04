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
 *  along with Connect X. If not, see <https://www.gnu.org/licenses/>.
 *
 *************************************************************************************************/
/**********************************************************************************************//**
 * @file StatusBarPresenter.cpp
 * @date 2020
 *
 *************************************************************************************************/

#include <cxinv/include/assertion.h>

#include <StatusBarPresenter.h>

std::string cxgui::StatusBarPresenter::GetStatusBarMessage() const
{
    return m_statusBarMessage;
}

void cxgui::StatusBarPresenter::Update(cxmodel::NotificationContext p_context, cxmodel::ModelSubject* p_subject)
{
    if(p_subject)
    {
        m_statusBarMessage = MakeStatusBarContextString(p_context);

        Notify(p_context);
    }
}

std::string cxgui::MakeStatusBarContextString(cxmodel::NotificationContext p_context)
{
    switch(p_context)
    {
        case cxmodel::NotificationContext::CREATE_NEW_GAME:
            return "New game created.";

        case cxmodel::NotificationContext::CHIP_DROPPED:
            return "Chip dropped.";

        case cxmodel::NotificationContext::UNDO_CHIP_DROPPED:
            return "Undo.";

        case cxmodel::NotificationContext::GAME_WON:
            return "Game won!";

        case cxmodel::NotificationContext::GAME_TIED:
            return "Game tied!";

        case cxmodel::NotificationContext::GAME_ENDED:
            return "";

        case cxmodel::NotificationContext::GAME_REINITIALIZED:
            return "Game reinitialized.";

        default:                                                     // LCOV_EXCL_LINE
            ASSERT_ERROR_MSG("Unknown notification context.");       // LCOV_EXCL_LINE
            return {};                                               // LCOV_EXCL_LINE
    }
}
