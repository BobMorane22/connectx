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
 * @file IAbstractConnectXWidgetsFactory.h
 * @date 2024
 *
 *************************************************************************************************/

#ifndef IABSTRACTCONNECTXWIDGETSFACTORY_H_27E986AD_66DF_4324_96AB_AC531266A928
#define IABSTRACTCONNECTXWIDGETSFACTORY_H_27E986AD_66DF_4324_96AB_AC531266A928

#include <memory>

#include <cxmodel/ModelNotificationContext.h>

namespace cxgui
{
    class IAboutWindowPresenter;
    class IMainWindowController;
    class IMainWindowPresenter;

    class IWindow;
}

namespace cxgui
{

/**********************************************************************************************//**
 * @brief Connect X specific widgets abstract factory.
 *
 * Create Connect X specific widgets (i.e. Game board, new players list, windows, etc.) without
 * having to deal with the underlying widgets toolkit.
 *
 *************************************************************************************************/
class IAbstractConnectXWidgetsFactory
{

public:

// ================================================================================================
///@{ @name Windows.
// ================================================================================================

    /******************************************************************************************//**
     * @brief Creates the Connect X main window.
     *
     * The Connect X main window is where everything happens. It is composed of a menu on top,
     * a view on the middle and a status bar at the bottom.
     *
     * Once Connect X is launched, everything happens on the main window and only the view is
     * updated to reflect the application's mode.
     *
     * @warning
     *      There should only be one Connect X main window instance by application.
     *
     * @param p_model
     *      A Connect X compatible model.
     * @param p_controller
     *      A compatible Connect X main window controller.
     * @param p_presenter
     *      A compatible Connect X main window presenter.
     *
     * @post
     *      The returned main window instance is valid.
     *
     * @return
     *      A Connect X main window instance.
     *
     *********************************************************************************************/
    [[nodiscard]] virtual std::unique_ptr<IWindow> CreateMainWindow(
        cxmodel::ModelSubject& p_model,
        IMainWindowController& p_controller,
        IMainWindowPresenter& p_presenter) const = 0;

    /******************************************************************************************//**
     * @brief Creates the Connect X about window.
     *
     * @param p_presenter
     *      An about window presenter.
     *
     * @pre
     *      The about window presenter is valid.
     *
     * @post
     *      The returned about window instance is valid.
     *
     * @return
     *      An about window instance.
     *
     *********************************************************************************************/
    [[nodiscard]] virtual std::unique_ptr<IWindow> CreateAboutWindow(
        std::unique_ptr<IAboutWindowPresenter> p_presenter) const = 0;

///@}

};

} // namespace cxgui

#endif // IABSTRACTCONNECTXWIDGETSFACTORY_H_27E986AD_66DF_4324_96AB_AC531266A928
