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
 * @file MenuItem.cpp
 * @date 2023
 *
 *************************************************************************************************/

#include <gdk/gdkkeysyms.h>
#include <gdkmm/types.h>
#include <gtkmm/grid.h>

#include <cxinv/assertion.h>
#include <cxcmnui/EventPropagation.h>
#include <cxcmnui/KeyboardKeyPressedEvent.h>
#include <cxcmnui/KeyboardShortcut.h>
#include <cxcmnui/Keys.h>
#include <cxcmnui/StdActionIcon.h>
#include <cxcmnuigtkmm3/Connection.h>
#include <cxcmnuigtkmm3/WidgetDelegate.h>

#include "conversions.h"
#include "MenuItem.h"

namespace
{

class Gtkmm3OnTriggeredSignal : public cx::cmn::ui::ISignal<void>
{

public:

    explicit Gtkmm3OnTriggeredSignal(Gtk::MenuItem& p_triggeredMenuItem)
    : m_triggeredMenuItem{p_triggeredMenuItem}
    {
    }

    std::unique_ptr<cx::cmn::ui::IConnection> Connect(const std::function<void()>& p_slot) override
    {
        sigc::connection gtkConnection = m_triggeredMenuItem.signal_activate().connect(p_slot);

        return std::make_unique<cx::cmn::ui::gtkmm3::Connection>(gtkConnection);
    }

private:

    Gtk::MenuItem& m_triggeredMenuItem;
};

}

cx::cmn::ui::gtkmm3::MenuItem::MenuItem(
    const std::string& p_label,
    const std::optional<cx::cmn::ui::FreeDesktop::StdActionIcon>& p_icon)
{
    PRECONDITION(!p_label.empty());

    // We handle the icon:
    if(p_icon)
    {
        const std::string iconName = cx::cmn::ui::FreeDesktop::StdNameGet(*p_icon);
        m_icon = std::make_unique<Gtk::Image>(iconName, Gtk::BuiltinIconSize::ICON_SIZE_MENU);
    }
    else
    {
         // If no icon name is specified, we use an "empty" icon, to make sure all
         // menu string labels are aligned:
         const Gtk::IconSize iconSize = Gtk::BuiltinIconSize::ICON_SIZE_MENU;
         int width, height;
         Gtk::IconSize::lookup(iconSize, width, height);
         const auto iconSurface = Cairo::ImageSurface::create(Cairo::Format::FORMAT_ARGB32, width, height);
         m_icon = std::make_unique<Gtk::Image>(iconSurface);
    }

    ASSERT(m_icon);
    m_icon->set_margin_end(5);

    // We handle the label:
    m_accelerator = std::make_unique<Gtk::AccelLabel>(p_label);
    ASSERT(m_accelerator);
    m_accelerator->set_xalign(0.0);
    m_accelerator->set_accel_widget(*this);

    // We register the icon and the label in the container:
    m_layout = std::make_unique<Gtk::Grid>();
    ASSERT(m_layout);

    m_layout->attach(*m_icon,        0, 0, 1, 1);
    m_layout->attach(*m_accelerator, 1, 0, 1, 1);

    add(*m_layout);
}

cx::cmn::ui::gtkmm3::MenuItem::~MenuItem()
{
    // Before anything is destroyed, we remove it from the menu item:
    remove();
}

void cx::cmn::ui::gtkmm3::MenuItem::SetDelegate(std::unique_ptr<cx::cmn::ui::IWidget> p_delegate)
{
    IF_PRECONDITION_NOT_MET_DO(p_delegate, return;);

    m_delegate = std::move(p_delegate);

    POSTCONDITION(m_delegate);
}

std::unique_ptr<cx::cmn::ui::ISignal<void>> cx::cmn::ui::gtkmm3::MenuItem::OnTriggered()
{
    return std::make_unique<Gtkmm3OnTriggeredSignal>(*this);
}

void cx::cmn::ui::gtkmm3::MenuItem::RegisterKeyboardShortcut(const cx::cmn::ui::KeyboardShortcut& p_shortcut)
{
    Gdk::ModifierType modifier = ~Gdk::ModifierType::MODIFIER_MASK; // No modifier.
    guint key = GDK_KEY_VoidSymbol; // Invalid key.

    if(p_shortcut.m_second)
    {
        // In this case, we have a modifier as the first key, and an action key
        // as the second key.
        auto modifierConversion = cx::cmn::ui::gtkmm3::ToGtk<Gdk::ModifierType>(p_shortcut.m_first);
        modifierConversion.value_or(~Gdk::ModifierType::MODIFIER_MASK);

        auto keyConversion = cx::cmn::ui::gtkmm3::ToGtk<guint>(*p_shortcut.m_second);
        key = keyConversion.value_or(GDK_KEY_VoidSymbol);
    }
    else
    {
        // In this case, we do not have a modifier. The shortcut consitsts of a single key.
        auto keyConversion = cx::cmn::ui::gtkmm3::ToGtk<guint>(p_shortcut.m_first);
        key = keyConversion.value_or(GDK_KEY_VoidSymbol);
    }

    const Gtk::AccelKey gtkKeyboardShortcut(key, modifier);
    set_accel_key(gtkKeyboardShortcut);
}

size_t cx::cmn::ui::gtkmm3::MenuItem::GetWidth() const
{
    IF_CONDITION_NOT_MET_DO(m_delegate, return 0u;);
    return m_delegate->GetWidth();
}

size_t cx::cmn::ui::gtkmm3::MenuItem::GetHeight() const
{
    IF_CONDITION_NOT_MET_DO(m_delegate, return 0u;);
    return m_delegate->GetHeight();
}

void cx::cmn::ui::gtkmm3::MenuItem::SetEnabled(cx::cmn::ui::EnabledState p_enabled)
{
    IF_CONDITION_NOT_MET_DO(m_delegate, return;);
    m_delegate->SetEnabled(p_enabled);
}

void cx::cmn::ui::gtkmm3::MenuItem::SetMargins(const cx::cmn::ui::Margins& p_newMarginSizes)
{
    IF_CONDITION_NOT_MET_DO(m_delegate, return;);
    m_delegate->SetMargins(p_newMarginSizes);
}

void cx::cmn::ui::gtkmm3::MenuItem::SetTooltip(const std::string& p_tooltipContents)
{
    IF_CONDITION_NOT_MET_DO(m_delegate, return;);
    m_delegate->SetTooltip(p_tooltipContents);
}

std::unique_ptr<cx::cmn::ui::ISignal<cx::cmn::ui::EventPropagation, cx::cmn::ui::KeyboardKeyPressedEvent>> cx::cmn::ui::gtkmm3::MenuItem::OnKeyPressed()
{
    IF_CONDITION_NOT_MET_DO(m_delegate, return nullptr;);
    return m_delegate->OnKeyPressed();
}
