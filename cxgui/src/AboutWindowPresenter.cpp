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

#include <cxmodel/IVersioning.h>
#include <cxmodel/ModelNotificationContext.h>
#include <cxgui/AboutWindowPresenter.h>

cxgui::AboutWindowPresenter::AboutWindowPresenter(const cxmodel::IVersioning& p_model)
 : m_applicationName{p_model.GetName()}
 , m_versionNumber{p_model.GetVersionNumber()}
{
    // Nothing to do...
}

std::string cxgui::AboutWindowPresenter::GetWindowTitle() const
{
    return "About";
}

std::string cxgui::AboutWindowPresenter::GetApplicationName() const
{
    return m_applicationName;
}

std::string cxgui::AboutWindowPresenter::GetVersionNumber() const
{
    return m_versionNumber;
}

std::string cxgui::AboutWindowPresenter::GetApplicationDescription() const
{
    return "Connect X is a scalable Four-In-A-Row clone";
}

std::string cxgui::AboutWindowPresenter::GetWebsiteLinkContents() const
{
    return "<a href=\"https://github.com/BobMorane22/connectx\">Website</a>";
}

std::string cxgui::AboutWindowPresenter::GetLicenseDescription() const
{
    return "License: GNU GPL v3";
}

std::string cxgui::AboutWindowPresenter::GetCopyrightNotice() const
{
    return "Copyright © 2020 - Éric Poirier";
}

std::string cxgui::AboutWindowPresenter::GetCloseText() const
{
    return "Close";
}
