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
 * @file AboutWindowPresenter.cpp
 * @date 2020
 *
 *************************************************************************************************/

#include <cxmodel/include/Model.h>

#include <AboutWindowPresenter.h>

void cxgui::AboutWindowPresenter::Update(cxmodel::NotificationContext p_context, Subject* p_subject)
{
    if(p_subject && p_context == cxmodel::NotificationContext::SIGNAL )
    {
        cxmodel::IModel* model = static_cast<cxmodel::Model*>(p_subject);

        m_applicationName = model->GetName();
        m_versionNumber = model->GetVersionNumber();
    }

    Notify(p_context);
}

std::string cxgui::AboutWindowPresenter::AboutWindowPresenter::GetWindowTitle() const
{
    return "About";
}

std::string cxgui::AboutWindowPresenter::AboutWindowPresenter::GetApplicationName() const
{
    return m_applicationName;
}

std::string cxgui::AboutWindowPresenter::AboutWindowPresenter::GetVersionNumber() const
{
    return m_versionNumber;
}

std::string cxgui::AboutWindowPresenter::AboutWindowPresenter::GetApplicationDescription() const
{
    return "Connect X is a scalable Four-In-A-Row clone";
}

std::string cxgui::AboutWindowPresenter::AboutWindowPresenter::GetLicenseDescription() const
{
    return "License: GNU GPL v3";
}

std::string cxgui::AboutWindowPresenter::AboutWindowPresenter::GetCopyrightNotice() const
{
    return "Copyright © 2020 - Éric Poirier";
}

std::string cxgui::AboutWindowPresenter::AboutWindowPresenter::GetCloseText() const
{
    return "Close";
}
