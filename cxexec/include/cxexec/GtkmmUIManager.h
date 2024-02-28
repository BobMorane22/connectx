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
 * @file GtkmmUIManager.h
 * @date 2019
 *
 *************************************************************************************************/

#ifndef GTKMMUIMANAGER_H_E1DB88FF_B8D0_4340_B32B_E1970564E266
#define GTKMMUIMANAGER_H_E1DB88FF_B8D0_4340_B32B_E1970564E266

#include <memory>

#include <gtkmm/application.h>

#include <cxmodel/ModelNotificationContext.h>

#include <cxgui/IMainWindowController.h>
#include <cxgui/IMainWindowPresenter.h>

#include "IUIManager.h"

namespace cx
{
    class ModelReferences;
}

namespace cxgui
{
    class IWindow;
}

namespace cx
{

/*********************************************************************************************//**
 * @brief A Gtkmm UI manager.
 *
 * Manages a Gtkmm implemented UI. For more information, see: https://www.gtkmm.org/en/
 *
 ************************************************************************************************/
class GtkmmUIManager : public cx::IUIManager
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
     *      The argument list is not @c nullptr.
     *
     ********************************************************************************************/
    GtkmmUIManager(int argc, char *argv[], cx::ModelReferences& p_model);

    int Manage() override;


private:

    void InitializeGtkmm(int argc, char *argv[]);

    void CheckInvariants();

    Glib::RefPtr<Gtk::Application> m_app;

    std::unique_ptr<cxgui::IMainWindowController> m_controller;
    std::unique_ptr<cxgui::IMainWindowPresenter> m_presenter;
    std::unique_ptr<cxgui::IWindow> m_mainWindow;
};

} // namespace cx

#endif // GTKMMUIMANAGER_H_E1DB88FF_B8D0_4340_B32B_E1970564E266
