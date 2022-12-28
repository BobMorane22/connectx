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
 * @file AboutWindowPresenter.h
 * @date 2020
 *
 *************************************************************************************************/

#ifndef ABOUTWINDOWPRESENTER_H_FF0579FF_28AC_4A2E_8900_B3D1A73C3E38
#define ABOUTWINDOWPRESENTER_H_FF0579FF_28AC_4A2E_8900_B3D1A73C3E38

namespace cxmodel
{
    class IVersioning;
}

#include "IAboutWindowPresenter.h"

namespace cxgui
{

/*********************************************************************************************//**
 * @brief Presenter for the About window.
 *
 ************************************************************************************************/
class AboutWindowPresenter : public IAboutWindowPresenter
{

public:

    /*****************************************************************************************//**
     * @brief Constructor.
     *
     * @param p_model The model (versioning part).
     *
     ********************************************************************************************/
    explicit AboutWindowPresenter(const cxmodel::IVersioning& p_model);

    ~AboutWindowPresenter() override = default;

    // cxgui::IAboutWindowPresenter:
    std::string GetWindowTitle() const override;
    std::string GetApplicationName() const override;
    std::string GetVersionNumber() const override;
    std::string GetApplicationDescription() const override;
    std::string GetLicenseDescription() const override;
    std::string GetCopyrightNotice() const override;
    std::string GetCloseText() const override;


private:

    std::string m_applicationName;
    std::string m_versionNumber;
};

} // namespace cxgui

#endif // ABOUTWINDOWPRESENTER_H_FF0579FF_28AC_4A2E_8900_B3D1A73C3E38
