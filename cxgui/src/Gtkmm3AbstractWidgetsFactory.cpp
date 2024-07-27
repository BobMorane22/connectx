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
 * @file Gtkmm3AbstractWidgetsFactory.cpp
 * @date 2024
 *
 *************************************************************************************************/

#include <cxinv/assertion.h>
#include <cxgui/StdActionIcon.h>
#include <cxgui/Gtkmm3AbstractWidgetsFactory.h>
#include <cxgui/Gtkmm3Button.h>
#include <cxgui/Gtkmm3Dialog.h>
#include <cxgui/Gtkmm3EditBox.h>
#include <cxgui/Gtkmm3Label.h>
#include <cxgui/Gtkmm3Layout.h>
#include <cxgui/Gtkmm3Menu.h>
#include <cxgui/Gtkmm3MenuBar.h>
#include <cxgui/Gtkmm3MenuItem.h>
#include <cxgui/Gtkmm3OnOffSwitch.h>
#include <cxgui/Gtkmm3SpinBox.h>
#include <cxgui/Gtkmm3StatusBar.h>
#include <cxgui/Gtkmm3WidgetDelegate.h>
#include <cxgui/IStatusBarPresenter.h>

cx::cmn::ui::Gtkmm3AbstractWidgetsFactory::Gtkmm3AbstractWidgetsFactory(Glib::RefPtr<Gtk::Application> p_gtkApplication)
{
    PRECONDITION(bool(p_gtkApplication));

    m_gtkApplication = p_gtkApplication;

    POSTCONDITION(bool(m_gtkApplication));
}

std::unique_ptr<cx::cmn::ui::ILayout> cx::cmn::ui::Gtkmm3AbstractWidgetsFactory::CreateLayout() const
{
    auto layout = CreateWidget<Gtkmm3Layout>();
    POSTCONDITION(layout);

    return layout;
}

std::unique_ptr<cx::cmn::ui::IButton> cx::cmn::ui::Gtkmm3AbstractWidgetsFactory::CreateButton() const 
{
    auto button = CreateWidget<Gtkmm3Button>();
    POSTCONDITION(button);

    return button;
}

std::unique_ptr<cx::cmn::ui::IButton> cx::cmn::ui::Gtkmm3AbstractWidgetsFactory::CreateButton(const std::string& p_contents) const 
{
    auto button = CreateWidget<Gtkmm3Button>(p_contents);
    POSTCONDITION(button);

    return button;
}

std::unique_ptr<cx::cmn::ui::ILabel> cx::cmn::ui::Gtkmm3AbstractWidgetsFactory::CreateLabel() const 
{
    auto label = CreateWidget<Gtkmm3Label>();
    POSTCONDITION(label);

    return label;
}

std::unique_ptr<cx::cmn::ui::ILabel> cx::cmn::ui::Gtkmm3AbstractWidgetsFactory::CreateLabel(const std::string& p_contents) const 
{
    auto label = CreateWidget<Gtkmm3Label>(p_contents);
    POSTCONDITION(label);

    return label;
}

std::unique_ptr<cx::cmn::ui::IEditBox> cx::cmn::ui::Gtkmm3AbstractWidgetsFactory::CreateEditBox() const
{
    auto editBox = CreateWidget<Gtkmm3EditBox>();
    POSTCONDITION(editBox);

    return editBox;
}

std::unique_ptr<cx::cmn::ui::ISpinBox> cx::cmn::ui::Gtkmm3AbstractWidgetsFactory::CreateSpinBox(
    int p_initialValue,
    const ISpinBox::ClimbRate& p_climbRate,
    const ISpinBox::Range& p_range) const
{
    auto spinBox = CreateWidget<Gtkmm3SpinBox>(p_initialValue, p_climbRate, p_range);
    POSTCONDITION(spinBox);

    return spinBox;
}

std::unique_ptr<cx::cmn::ui::IOnOffSwitch> cx::cmn::ui::Gtkmm3AbstractWidgetsFactory::CreateOnOffSwitch() const
{
    auto onOffSwitch = CreateWidget<Gtkmm3OnOffSwitch>();
    POSTCONDITION(onOffSwitch);

    return onOffSwitch;
}

std::unique_ptr<cx::cmn::ui::IWindow> cx::cmn::ui::Gtkmm3AbstractWidgetsFactory::CreateDialog(
    IWindow& p_parent,
    DialogRole p_dialogRole,
    const std::string& p_message) const
{
    PRECONDITION(!p_message.empty());

    auto dialog = CreateWidget<Gtkmm3Dialog>(
        p_parent,
        p_dialogRole,
        p_message);
    POSTCONDITION(dialog);

    return dialog;
}

std::unique_ptr<cx::cmn::ui::IMenuBar> cx::cmn::ui::Gtkmm3AbstractWidgetsFactory::CreateMenuBar() const
{
    auto menuBar = CreateWidget<Gtkmm3MenuBar>();
    POSTCONDITION(menuBar);

    return menuBar;
}

std::unique_ptr<cx::cmn::ui::IMenu> cx::cmn::ui::Gtkmm3AbstractWidgetsFactory::CreateMenu(const std::string p_title) const
{
    IF_PRECONDITION_NOT_MET_DO(!p_title.empty(), return nullptr;);

    auto menu = CreateWidget<Gtkmm3Menu>(p_title);
    POSTCONDITION(menu);

    return menu;
}

std::unique_ptr<cx::cmn::ui::IMenuItem> cx::cmn::ui::Gtkmm3AbstractWidgetsFactory::CreateMenuItem(
    const std::string p_label,
    const std::optional<FreeDesktop::StdActionIcon>& p_icon) const
{
    IF_PRECONDITION_NOT_MET_DO(!p_label.empty(), return nullptr;);

    auto menuItem = CreateWidget<Gtkmm3MenuItem>(p_label, p_icon);
    POSTCONDITION(menuItem);

    return menuItem;
}

std::unique_ptr<cx::cmn::ui::IStatusBar> cx::cmn::ui::Gtkmm3AbstractWidgetsFactory::CreateStatusBar(cx::cmn::ui::IStatusBarPresenter& p_presenter) const
{
    auto statusBar = CreateWidget<Gtkmm3StatusBar>(p_presenter);
    POSTCONDITION(statusBar);

    return statusBar;
}
