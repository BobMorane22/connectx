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
 * @file Window.h
 * @date 2020
 *
 *************************************************************************************************/

#ifndef GTKMM3WINDOW_H_861FC628_597C_407E_8206_E67F71000A55
#define GTKMM3WINDOW_H_861FC628_597C_407E_8206_E67F71000A55

#include <gtkmm/window.h>

#include <cxinv/assertion.h>
#include <cxcmnui/ISignal.h>
#include <cxcmnui/IWindow.h>
#include <cxui/generated/ressources.h>

namespace cx::cmn::ui
{
    class IAbstractWidgetsFactory;
    class ILayout;
    class IWidget;
}

namespace cx::ui::gtkmm3
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
class Window : public cx::cmn::ui::IWindow,
               public Gtk::Window
{

public:

    /******************************************************************************************//**
     * @brief Constructor.
     *
     * @param p_standardWidgetsFactory
     *      An instance to a common widgets factory.
     *
     * @post
     *      The window's main layout is valid.
     *
     ********************************************************************************************/
    explicit Window(
        const cx::cmn::ui::IAbstractWidgetsFactory& p_standardWidgetsFactory);

    /******************************************************************************************//**
     * @brief Initializes the window widgets.
     *
     * This method is automatically called when the "Realize" signal is emitted from the
     * underlying Gtkmm window.
     *
     ********************************************************************************************/
    void Init();

    /*******************************************************************************************//**
     * @brief Sets the delegate for widget common facilities.
     *
     * The delegate is reponsible to carry the implementation for generic `cx::cmn::ui::gtkmm3::IWidget` operations.
     * It is meant to avoid implementation duplication.
     *
     * @param p_delegate
     *      The widget delegate.
     *
     * @pre
     *      The widget delegate instance given as an argument is valid.
     * @post
     *      The registered widget delegate is valid.
     *
     **********************************************************************************************/
    void SetDelegate(
        std::unique_ptr<cx::cmn::ui::IWidget> p_delegate);

    // cx::cmn::ui::IWindow:
    [[nodiscard]] int Show() override;
    void ShrinkToContents(
        cx::cmn::ui::IWindow::Orientation p_orientation) override;
    void RegisterLayout(            
        cx::cmn::ui::ILayout& p_layout) override;

    // cx::cmn::ui::IWidget:
    [[nodiscard]] virtual size_t GetWidth() const override;
    [[nodiscard]] virtual size_t GetHeight() const override;
    void SetEnabled(cx::cmn::ui::EnabledState p_enabled) override;
    void SetMargins(const cx::cmn::ui::Margins& p_newMarginSizes) override;
    void SetTooltip(const std::string& p_tooltipContents) override;
    [[nodiscard]] std::unique_ptr<cx::cmn::ui::ISignal<cx::cmn::ui::EventPropagation, cx::cmn::ui::KeyboardKeyPressedEvent>> OnKeyPressed() override;

protected:

    /** The window's top level layout. */
    std::unique_ptr<cx::cmn::ui::ILayout> m_mainLayout;

private:

    /*******************************************************************************************//**
     * @brief Configures the window icon.
     *
     * Override this method to specify a path for the window icon.
     *
     **********************************************************************************************/
    void ConfigureWindowIcon();

    /*******************************************************************************************//**
     * @brief Initializes every widget needed to create the initial window.
     *
     * Override this method to create all the necessary widgets for creating the window.
     *
     **********************************************************************************************/
    virtual void InitializeWidgets() = 0;

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

private:

    const cx::cmn::ui::IAbstractWidgetsFactory& m_standardWidgetsFactory;
    std::unique_ptr<cx::cmn::ui::IWidget> m_delegate;
};

} // namespace cx::ui::gtkmm3

#endif // GTKMM3WINDOW_H_861FC628_597C_407E_8206_E67F71000A55
