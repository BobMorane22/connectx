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
 * @file AbstractWidgetsFactory.cpp
 * @date 2024
 *
 *************************************************************************************************/

#include <gtkmm/application.h>

#include <cxinv/assertion.h>
#include <cxcmnui/IAbstractWidgetsFactory.h>
#include <cxcmnui/StdActionIcon.h>
#include <cxcmnuigtkmm3/AbstractWidgetsFactory.h>
#include <cxcmnuigtkmm3/WidgetDelegate.h>

#include "Button.h"
#include "Dialog.h"
#include "EditBox.h"
#include "Label.h"
#include "Layout.h"
#include "Menu.h"
#include "MenuBar.h"
#include "MenuItem.h"
#include "OnOffSwitch.h"
#include "SpinBox.h"

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

cx::cmn::ui::gtkmm3::AbstractWidgetsFactory::AbstractWidgetsFactory(Glib::RefPtr<Gtk::Application> p_gtkApplication)
{
    PRECONDITION(bool(p_gtkApplication));

    m_gtkApplication = p_gtkApplication;

    POSTCONDITION(bool(m_gtkApplication));
}

std::unique_ptr<cx::cmn::ui::ILayout> cx::cmn::ui::gtkmm3::AbstractWidgetsFactory::CreateLayout() const
{
    auto layout = CreateWidget<cx::cmn::ui::gtkmm3::Layout>();
    POSTCONDITION(layout);

    return layout;
}

std::unique_ptr<cx::cmn::ui::IButton> cx::cmn::ui::gtkmm3::AbstractWidgetsFactory::CreateButton() const 
{
    auto button = CreateWidget<cx::cmn::ui::gtkmm3::Button>();
    POSTCONDITION(button);

    return button;
}

std::unique_ptr<cx::cmn::ui::IButton> cx::cmn::ui::gtkmm3::AbstractWidgetsFactory::CreateButton(const std::string& p_contents) const 
{
    auto button = CreateWidget<cx::cmn::ui::gtkmm3::Button>(p_contents);
    POSTCONDITION(button);

    return button;
}

std::unique_ptr<cx::cmn::ui::ILabel> cx::cmn::ui::gtkmm3::AbstractWidgetsFactory::CreateLabel() const 
{
    auto label = CreateWidget<cx::cmn::ui::gtkmm3::Label>();
    POSTCONDITION(label);

    return label;
}

std::unique_ptr<cx::cmn::ui::ILabel> cx::cmn::ui::gtkmm3::AbstractWidgetsFactory::CreateLabel(const std::string& p_contents) const 
{
    auto label = CreateWidget<cx::cmn::ui::gtkmm3::Label>(p_contents);
    POSTCONDITION(label);

    return label;
}

std::unique_ptr<cx::cmn::ui::IEditBox> cx::cmn::ui::gtkmm3::AbstractWidgetsFactory::CreateEditBox() const
{
    auto editBox = CreateWidget<cx::cmn::ui::gtkmm3::EditBox>();
    POSTCONDITION(editBox);

    return editBox;
}

std::unique_ptr<cx::cmn::ui::ISpinBox> cx::cmn::ui::gtkmm3::AbstractWidgetsFactory::CreateSpinBox(
    int p_initialValue,
    const ISpinBox::ClimbRate& p_climbRate,
    const ISpinBox::Range& p_range) const
{
    auto spinBox = CreateWidget<cx::cmn::ui::gtkmm3::SpinBox>(p_initialValue, p_climbRate, p_range);
    POSTCONDITION(spinBox);

    return spinBox;
}

std::unique_ptr<cx::cmn::ui::IOnOffSwitch> cx::cmn::ui::gtkmm3::AbstractWidgetsFactory::CreateOnOffSwitch() const
{
    auto onOffSwitch = CreateWidget<cx::cmn::ui::gtkmm3::OnOffSwitch>();
    POSTCONDITION(onOffSwitch);

    return onOffSwitch;
}

std::unique_ptr<cx::cmn::ui::IWindow> cx::cmn::ui::gtkmm3::AbstractWidgetsFactory::CreateDialog(
    cx::cmn::ui::IWindow& p_parent,
    cx::cmn::ui::DialogRole p_dialogRole,
    const std::string& p_message) const
{
    PRECONDITION(!p_message.empty());

    auto dialog = CreateWidget<cx::cmn::ui::gtkmm3::Dialog>(
        p_parent,
        p_dialogRole,
        p_message);
    POSTCONDITION(dialog);

    return dialog;
}

std::unique_ptr<cx::cmn::ui::IMenuBar> cx::cmn::ui::gtkmm3::AbstractWidgetsFactory::CreateMenuBar() const
{
    auto menuBar = CreateWidget<cx::cmn::ui::gtkmm3::MenuBar>();
    POSTCONDITION(menuBar);

    return menuBar;
}

std::unique_ptr<cx::cmn::ui::IMenu> cx::cmn::ui::gtkmm3::AbstractWidgetsFactory::CreateMenu(const std::string p_title) const
{
    IF_PRECONDITION_NOT_MET_DO(!p_title.empty(), return nullptr;);

    auto menu = CreateWidget<cx::cmn::ui::gtkmm3::Menu>(p_title);
    POSTCONDITION(menu);

    return menu;
}

std::unique_ptr<cx::cmn::ui::IMenuItem> cx::cmn::ui::gtkmm3::AbstractWidgetsFactory::CreateMenuItem(
    const std::string p_label,
    const std::optional<cx::cmn::ui::FreeDesktop::StdActionIcon>& p_icon) const
{
    IF_PRECONDITION_NOT_MET_DO(!p_label.empty(), return nullptr;);

    auto menuItem = CreateWidget<cx::cmn::ui::gtkmm3::MenuItem>(p_label, p_icon);
    POSTCONDITION(menuItem);

    return menuItem;
}

std::unique_ptr<cx::cmn::ui::IAbstractWidgetsFactory> cx::cmn::ui::gtkmm3::CreateFactory(Glib::RefPtr<Gtk::Application> p_gtkApplication)
{
    IF_PRECONDITION_NOT_MET_DO(bool(p_gtkApplication), return nullptr;);

    auto factory = std::make_unique<cx::cmn::ui::gtkmm3::AbstractWidgetsFactory>(p_gtkApplication);

    POSTCONDITION(factory);

    return factory;
}
