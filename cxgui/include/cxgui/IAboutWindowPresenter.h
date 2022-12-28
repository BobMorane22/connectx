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
 * @file IAboutWindowPresenter.h
 * @date 2020
 *
 *************************************************************************************************/

#ifndef IABOUTWINDOWPRESENTER_H_D80BCE23_D0F8_42C9_BB00_E4AB9DD557F5
#define IABOUTWINDOWPRESENTER_H_D80BCE23_D0F8_42C9_BB00_E4AB9DD557F5

#include <string>

#include <cxmodel/ModelNotificationContext.h>

namespace cxgui
{

/*********************************************************************************************//**
 * @brief Interface for About window presenters.
 *
 ************************************************************************************************/
class IAboutWindowPresenter
{

public:

    /******************************************************************************************//**
     * @brief Destructor.
     *
     ********************************************************************************************/
    virtual ~IAboutWindowPresenter() = default;

    /******************************************************************************************//**
     * @brief Gets the window title text.
     *
     * @return The window title text.
     *
     ********************************************************************************************/
    virtual std::string GetWindowTitle() const = 0;

    /******************************************************************************************//**
     * @brief Gets the name of the application.
     *
     * @return The application name.
     *
     ********************************************************************************************/
    virtual std::string GetApplicationName() const = 0;

    /******************************************************************************************//**
     * @brief Gets the application version number text.
     *
     * @return A string containing the formatted application version number.
     *
     ********************************************************************************************/
    virtual std::string GetVersionNumber() const = 0;

    /******************************************************************************************//**
     * @brief Gets the application description text.
     *
     * @return The application description text.
     *
     ********************************************************************************************/
    virtual std::string GetApplicationDescription() const = 0;

    /******************************************************************************************//**
     * @brief Gets the license description text.
     *
     * @return The license description text.
     *
     ********************************************************************************************/
    virtual std::string GetLicenseDescription() const = 0;

    /******************************************************************************************//**
     * @brief Gets the copyright notice text.
     *
     * @return The copyright notice text.
     *
     ********************************************************************************************/
    virtual std::string GetCopyrightNotice() const = 0;

    /******************************************************************************************//**
     * @brief Gets the text show on the widget used to close the window.
     *
     * @return The string on the widget used to close the window.
     *
     ********************************************************************************************/
    virtual std::string GetCloseText() const = 0;
};

} // namespace cxgui

#endif // IABOUTWINDOWPRESENTER_H_D80BCE23_D0F8_42C9_BB00_E4AB9DD557F5
