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
 * @file Gtkmm3Window.h
 * @date 2020
 *
 *************************************************************************************************/

#ifndef GTKMM3WINDOW_H_861FC628_597C_407E_8206_E67F71000A55
#define GTKMM3WINDOW_H_861FC628_597C_407E_8206_E67F71000A55

#include <glibmm/fileutils.h>
#include <gtkmm/window.h>

#include <cxinv/assertion.h>
#include <cxgui/generated/ressources.h>
#include <cxgui/Gtkmm3Layout.h>
#include <cxgui/ILayout.h>
#include <cxgui/Gtkmm3WidgetDelegate.h>

#include "IWindow.h"


namespace cxgui
{

/*********************************************************************************************//**
 * @brief An abstract base class for windows implemented in terms of Gtkmm windows.
 *
 * @tparam GtkmmWindow
 *      The base Gtkmm window type used for implementation. This type must support the
 *      following methods:
 *
 *        1. `Gtk::Container::add`
 *        2. `Gtk::Widget::signal_realize`
 *        3. `Gtk::Widget::show_all`
 *        4. `Gtk::Window::set_icon_from_file`
 *
 * This class provides methods that can be overridden to configure the window items, such as
 * child widgets, layouts and the window itself.
 *
 ************************************************************************************************/
class Gtkmm3Window : public IWindow,
                     public Gtk::Window
{

public:

    /******************************************************************************************//**
     * @brief Constructor.
     *
     ********************************************************************************************/
    Gtkmm3Window();

    // cxgui::IWindow:
    [[nodiscard]] int Show() override;

    /******************************************************************************************//**
     * @brief Initializes the window widgets.
     *
     * This method is automatically called when the "Realize" signal is emitted from the
     * underlying Gtkmm window.
     *
     ********************************************************************************************/
    void Init();

protected:

    /*******************************************************************************************//**
     * @brief Configures the window icon.
     *
     * Override this method to specify a path for the window icon.
     *
     **********************************************************************************************/
    void ConfigureWindowIcon();

    /*******************************************************************************************//**
     * @brief Configures the window.
     *
     * Override this method to configure window properties.
     *
     **********************************************************************************************/
    virtual void ConfigureWindow() = 0;

    /*******************************************************************************************//**
     * @brief Structures the layouts.
     *
     * Override this method to structure your layouts. For example, if you have a sublayout, add
     * it (register it) to the main layout here so that it is know to the window.
     *
     **********************************************************************************************/
    virtual void RegisterLayouts() = 0;

    /*******************************************************************************************//**
     * @brief Structure the widgets.
     *
     * Override this method to structure your widgets. Add them to the layouts they belong to so
     * that they appear as you intended (layout-wise) on the screen.
     *
     **********************************************************************************************/
    virtual void RegisterWidgets() = 0;

    /*******************************************************************************************//**
     * @brief Configure the layouts' attributes.
     *
     * Override this method to have control on layouts' attributes. If you need to set anything
     * else than a 'Layout A contains layout B' dependence, this is where it happens.
     *
     **********************************************************************************************/
    virtual void ConfigureLayouts() = 0;

    /*******************************************************************************************//**
     * @brief Configure widgets' attributes.
     *
     * Override this method to have control on the widgets' attributes. If you need to set anything
     * else than a 'Widget A belongs to layout B' dependence, this is where it happens.
     *
     **********************************************************************************************/
    virtual void ConfigureWidgets() = 0;

    /*******************************************************************************************//**
     * @brief Configure the window's signal handlers.
     *
     * Override this method to connect different signals to a handler function or method.
     *
     **********************************************************************************************/
    virtual void ConfigureSignalHandlers() = 0;

    /** The underlying window's top level layout. */
    std::unique_ptr<cxgui::ILayout> m_mainLayout;

};

} // namespace cxgui

#endif // GTKMM3WINDOW_H_861FC628_597C_407E_8206_E67F71000A55
