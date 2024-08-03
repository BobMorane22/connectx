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
#include <cxui/AboutWindowPresenter.h>

cx::ui::cmn::AboutWindowPresenter::AboutWindowPresenter(const cx::model::IVersioning& p_model)
 : m_applicationName{p_model.GetName()}
 , m_versionNumber{p_model.GetVersionNumber()}
{
    // Nothing to do...
}

std::string cx::ui::cmn::AboutWindowPresenter::GetWindowTitle() const
{
    return "About";
}

std::string cx::ui::cmn::AboutWindowPresenter::GetApplicationName() const
{
    return m_applicationName;
}

std::string cx::ui::cmn::AboutWindowPresenter::GetVersionNumber() const
{
    return m_versionNumber;
}

std::string cx::ui::cmn::AboutWindowPresenter::GetApplicationDescription() const
{
    return "Connect X is a scalable Four-In-A-Row clone";
}

std::string cx::ui::cmn::AboutWindowPresenter::GetWebsiteLinkContents() const
{
    return "<a href=\"https://github.com/BobMorane22/connectx\">Website</a>";
}

std::string cx::ui::cmn::AboutWindowPresenter::GetLicenseDescription() const
{
    return "License: GNU GPL v3";
}

std::string cx::ui::cmn::AboutWindowPresenter::GetCopyrightNotice() const
{
    return "Copyright © 2020 - Éric Poirier";
}

std::string cx::ui::cmn::AboutWindowPresenter::GetCloseText() const
{
    return "Close";
}
