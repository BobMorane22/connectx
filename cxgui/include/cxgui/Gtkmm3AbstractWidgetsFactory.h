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
 * @file Gtkmm3AbstractWidgetsFactory.h
 * @date 2024
 *
 *************************************************************************************************/

#ifndef GTKMM3ABSTRACTWIDGETSFACTORY_H_5986FF4A_306A_4809_8E54_BA7B1D8FDEEA
#define GTKMM3ABSTRACTWIDGETSFACTORY_H_5986FF4A_306A_4809_8E54_BA7B1D8FDEEA

#include <gtkmm/application.h>

#include <cxgui/IAbstractWidgetsFactory.h>

namespace cxgui
{

/**********************************************************************************************//**
 * @brief Abstract widgets factory for Gtkmm 3.24.5.
 *
 * This factory handles the "standard" widgets (e.g. buttons, labels, comboboxes, etc).
 *
 *************************************************************************************************/
class Gtkmm3AbstractWidgetsFactory final : public IAbstractWidgetsFactory
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
    explicit Gtkmm3AbstractWidgetsFactory(Glib::RefPtr<Gtk::Application> p_gtkApplication);

    // IAbstractWidgetsFactory:
    [[nodiscard]] std::unique_ptr<IButton> CreateButton() const override;
    [[nodiscard]] std::unique_ptr<IButton> CreateButton(const std::string& p_contents) const override;
    [[nodiscard]] std::unique_ptr<ILabel> CreateLabel() const override;
    [[nodiscard]] std::unique_ptr<ILabel> CreateLabel(const std::string& p_contents) const override;
    [[nodiscard]] std::unique_ptr<ISpinBox> CreateSpinBox(
        int p_initialValue,
        const ISpinBox::ClimbRate& p_climbRate,
        const ISpinBox::Range& p_range) const override;
    [[nodiscard]] std::unique_ptr<IMenuBar> CreateMenuBar() const override;
    [[nodiscard]] std::unique_ptr<IMenu> CreateMenu(const std::string p_title) const override;
    [[nodiscard]] std::unique_ptr<IMenuItem> CreateMenuItem(
        const std::string p_label,
        const std::optional<FreeDesktop::StdActionIcon>& p_icon = std::nullopt) const override;
    [[nodiscard]] std::unique_ptr<IStatusBar> CreateStatusBar(IStatusBarPresenter& p_presenter) const override;

private:

    Glib::RefPtr<Gtk::Application> m_gtkApplication;
};

} // namespace cxgui

#endif // GTKMM3ABSTRACTWIDGETSFACTORY_H_5986FF4A_306A_4809_8E54_BA7B1D8FDEEA
