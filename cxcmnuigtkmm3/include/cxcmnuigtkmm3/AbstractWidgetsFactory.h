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
 * @file AbstractWidgetsFactory.h
 * @date 2024
 *
 *************************************************************************************************/

#ifndef GTKMM3ABSTRACTWIDGETSFACTORY_H_5986FF4A_306A_4809_8E54_BA7B1D8FDEEA
#define GTKMM3ABSTRACTWIDGETSFACTORY_H_5986FF4A_306A_4809_8E54_BA7B1D8FDEEA

#include <memory>

#include <gtkmm/application.h>

#include <cxcmnui/IAbstractWidgetsFactory.h>

namespace cx::cmn::ui::gtkmm3
{

/**********************************************************************************************//**
 * @brief Abstract widgets factory for Gtkmm 3.24.5.
 *
 * This factory handles the "standard" widgets (e.g. buttons, labels, comboboxes, etc).
 *
 *************************************************************************************************/
class AbstractWidgetsFactory final : public IAbstractWidgetsFactory
{

public:

   /******************************************************************************************//**
    * @brief Constructor.
    *
    * @param p_gtkApplication
    *      The `Gtk::Application` instance representing the current application the factory
    *      is used for. Without it, widgets cannot be rendered on the screen.
    *
    * @pre
    *      The `Gtk::Application` instance given as an argument is valid.
    *
    * @post
    *      The stored `Gtk::Application` instance is valid.
    *
    *********************************************************************************************/
    explicit AbstractWidgetsFactory(Glib::RefPtr<Gtk::Application> p_gtkApplication);

   /******************************************************************************************//**
    * @brief Get the underlying `Gtk::Application` instance.
    *
    * This call is typically used to extend the widgets factory for specific application needs.
    * Another factory can be set up using the same application instance.
    *
    * @return The underlying `Gtk::Application` instance.
    *
    *********************************************************************************************/
    [[nodiscard]] Glib::RefPtr<Gtk::Application> GetGtkApplication();

    // IAbstractWidgetsFactory:
    [[nodiscard]] std::unique_ptr<cx::cmn::ui::ILayout> CreateLayout() const override;
    [[nodiscard]] std::unique_ptr<cx::cmn::ui::IButton> CreateButton() const override;
    [[nodiscard]] std::unique_ptr<cx::cmn::ui::IButton> CreateButton(const std::string& p_contents) const override;
    [[nodiscard]] std::unique_ptr<cx::cmn::ui::ILabel> CreateLabel() const override;
    [[nodiscard]] std::unique_ptr<cx::cmn::ui::ILabel> CreateLabel(const std::string& p_contents) const override;
    [[nodiscard]] std::unique_ptr<cx::cmn::ui::IEditBox> CreateEditBox() const override;
    [[nodiscard]] std::unique_ptr<cx::cmn::ui::ISpinBox> CreateSpinBox(
        int p_initialValue,
        const cx::cmn::ui::ISpinBox::ClimbRate& p_climbRate,
        const cx::cmn::ui::ISpinBox::Range& p_range) const override;
    [[nodiscard]] std::unique_ptr<cx::cmn::ui::IOnOffSwitch> CreateOnOffSwitch() const override;
    [[nodiscard]] std::unique_ptr<cx::cmn::ui::IWindow> CreateDialog(
        cx::cmn::ui::IWindow& p_parent,
        cx::cmn::ui::DialogRole p_dialogRole,
        const std::string& p_message) const override;
    [[nodiscard]] std::unique_ptr<cx::cmn::ui::IMenuBar> CreateMenuBar() const override;
    [[nodiscard]] std::unique_ptr<cx::cmn::ui::IMenu> CreateMenu(const std::string p_title) const override;
    [[nodiscard]] std::unique_ptr<cx::cmn::ui::IMenuItem> CreateMenuItem(
        const std::string p_label,
        const std::optional<cx::cmn::ui::FreeDesktop::StdActionIcon>& p_icon = std::nullopt) const override;


private:

    Glib::RefPtr<Gtk::Application> m_gtkApplication;
};

} // namespace cx::cmn::ui::gtkmm3

#endif // GTKMM3ABSTRACTWIDGETSFACTORY_H_5986FF4A_306A_4809_8E54_BA7B1D8FDEEA
