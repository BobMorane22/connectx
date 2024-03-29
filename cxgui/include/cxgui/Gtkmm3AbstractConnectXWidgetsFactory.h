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
 * @file Gtkmm3AbstractConnectXWidgetsFactory.h
 * @date 2024
 *
 *************************************************************************************************/

#ifndef GTKMM3ABSTRACTCONNECTXWIDGETSFACTORY_H_B3944DEE_5157_44D5_91D7_B238464FDD05
#define GTKMM3ABSTRACTCONNECTXWIDGETSFACTORY_H_B3944DEE_5157_44D5_91D7_B238464FDD05

#include <gtkmm/application.h>

#include <cxgui/IAbstractConnectXWidgetsFactory.h>

namespace cxgui
{
    class IAbstractWidgetsFactory;
}

namespace cxgui
{

/**********************************************************************************************//**
 * @brief Abstract widgets factory for Gtkmm 3.24.5.
 *
 * This factory handles the Connect X specific widgets.
 *
 *************************************************************************************************/
class Gtkmm3AbstractConnectXWidgetsFactory final : public IAbstractConnectXWidgetsFactory
{

public:

   /******************************************************************************************//**
    * @brief Constructor.
    *
    * @param p_stdWidgetsFactory
    *      A standard widgets factory. Useful for reusing standard widgets in Connect X specific
    *      widgets, which makes porting easier.
    *
    * @param p_gtkApplication
    *      The `Gtk::Application` instance representing the current application the factory
    *      is used for. Without it, widgets cannot be rendered on the screen.
    *
    * @pre
    *      The `Gtk::Application` instance given as an argument is valid.
    *
    *********************************************************************************************/
    Gtkmm3AbstractConnectXWidgetsFactory(
        IAbstractWidgetsFactory& p_stdWidgetsFactory,
        Glib::RefPtr<Gtk::Application> p_gtkApplication);

   /******************************************************************************************//**
    * @brief Creates a main Connect X window instance.
    *
    * @param p_model
    *      A Connect X compatible model.
    *
    * @param p_controller
    *      A main window controller.
    *
    * @param p_presenter
    *      A main window presenter.
    *
    * @post
    *     The returned instance is valid.
    *
    * @return
    *     A valid Connect X main window instance.
    *
    *********************************************************************************************/
    [[nodiscard]] std::unique_ptr<IWindow> CreateMainWindow(cxmodel::ModelSubject& p_model, IMainWindowController& p_controller, IMainWindowPresenter& p_presenter) const override;

private:

    // Use this whenever possible instead of plain Gtkmm.
    IAbstractWidgetsFactory& m_stdWidgetsFactory;

    Glib::RefPtr<Gtk::Application> m_gtkApplication;

};

} // namespace cxgui

#endif // GTKMM3ABSTRACTCONNECTXWIDGETSFACTORY_H_B3944DEE_5157_44D5_91D7_B238464FDD05
