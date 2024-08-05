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
 * @file Gtkmm3UIManager.h
 * @date 2019
 *
 *************************************************************************************************/

#ifndef GTKMM3UIMANAGER_H_E1DB88FF_B8D0_4340_B32B_E1970564E266
#define GTKMM3UIMANAGER_H_E1DB88FF_B8D0_4340_B32B_E1970564E266

#include <memory>

#include <cxexec/IUIManager.h>

namespace cx
{
    class ModelReferences;
}

namespace cx::ui::cmn
{
    class IAbstractWidgetsFactory;
    class IAbstractConnectCWidgetsFactory;
    class IMainWindowController;
    class IMainWindowPresenter;
    class IWindow;
    class WidgetsFactories;
}

namespace cx
{

/*********************************************************************************************//**
 * @brief A Gtkmm UI manager compatible with Gtkmm 3.24.5.
 *
 * Manages a Gtkmm implemented UI. For more information, see: https://www.gtkmm.org/en/
 *
 ************************************************************************************************/
class Gtkmm3UIManager : public cx::IUIManager
{

public:

    /******************************************************************************************//**
     * @brief Constructor.
     *
     * @param argc
     *      Command line argument count.
     * @param argv
     *      A C-style array of arguments.
     * @param p_model
     *      References to a Connect X compatible model.
     *
     * @pre
     *      The argument count is at least 1.
     * @pre
     *      The argument list is valid.
     *
     * @post
     *      The standard widgets abstract factory is valid.
     *
     * @post
     *      The Connect X specific widgets abstract factory is valid.
     *
     * @post
     *     The widget factories container is valid.
     *
     * @post
     *     The main window is valid.
     *
     ********************************************************************************************/
    Gtkmm3UIManager(int argc, char *argv[], cx::ModelReferences& p_model);

    // cx::IUIManager:
    [[nodiscard]] int Manage() override;


private:

    void CheckInvariants();

private:

    // Widgets factories.
    std::unique_ptr<cx::ui::cmn::IAbstractWidgetsFactory> m_abstractWidgetsFactory;
    std::unique_ptr<cx::ui::IAbstractConnectXWidgetsFactory> m_abstractConnectXWidgetsFactory;
    std::unique_ptr<cx::ui::WidgetsFactories> m_widgetsFactories;

    // Main window.
    std::unique_ptr<cx::ui::cmn::IWindow> m_mainWindow;
    std::unique_ptr<cx::ui::IMainWindowController> m_controller;
    std::unique_ptr<cx::ui::IMainWindowPresenter> m_presenter;

};

} // namespace cx

#endif // GTKMM3UIMANAGER_H_E1DB88FF_B8D0_4340_B32B_E1970564E266
