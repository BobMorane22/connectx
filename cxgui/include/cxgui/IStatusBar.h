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
 * @file IStatusBar.h
 * @date 2020
 *
 *************************************************************************************************/

#ifndef ISTATUSBAR_H_B9E6A5FA_CB18_4646_9BD1_F38CE15F1A62
#define ISTATUSBAR_H_B9E6A5FA_CB18_4646_9BD1_F38CE15F1A62

#include <string>

#include <cxmodel/ModelNotificationContext.h>
#include <cxgui/IWidget.h>

namespace cxgui
{

/*********************************************************************************************//**
 * @brief Status bar.
 *
 * Status bars often appear at the bottom of an application's main window and display some
 * informations about the application state to the user.
 *
 ************************************************************************************************/
class IStatusBar : public IWidget,
                   public cxmodel::IModelObserver
{

public:

    /******************************************************************************************//**
     * @brief Destructor.
     *
     ********************************************************************************************/
    virtual ~IStatusBar() = default;

    /******************************************************************************************//**
     * @brief Sets the status bar's user action status string.
     *
     * When the user make actions, the status bar is updated to reflect the action. To do
     * this, it displays the string indication what specific action was performed by the user.
     * This method sets this string in the status bar.
     *
     * @pre p_lastUserActionDescription is not empty.
     *
     * @param p_lastUserActionDescription The user action status string, ready for display.
     *
     ********************************************************************************************/
    virtual void SetLastUserActionStatus(const std::string& p_lastUserActionDescription) = 0;

};

} // namespace cxgui

#endif // ISTATUSBAR_H_B9E6A5FA_CB18_4646_9BD1_F38CE15F1A62
