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
 * @file Gtkmm3MenuItem.cpp
 * @date 2023
 *
 *************************************************************************************************/

#include <gdk/gdkkeysyms.h>
#include <gdkmm/types.h>

#include <cxinv/assertion.h>
#include <cxgui/Gtkmm3Connection.h>
#include <cxgui/Gtkmm3Layout.h>
#include <cxgui/Gtkmm3MenuItem.h>
#include <cxgui/Gtkmm3WidgetDelegate.h>
#include <cxgui/KeyboardShortcut.h>
#include <cxgui/Keys.h>
#include <cxgui/StdActionIcon.h>

namespace
{

// From a `cxgui::Key`, generate a Gdk key (which is used by Gtkmm).
// Those keys are carries throuhg a naked `guint` type.
[[nodiscard]] constexpr guint ToGtkmmKey(const cxgui::Key& p_key)
{
    switch(p_key)
    {
        case cxgui::Key::F1:
            return GDK_KEY_F1;

        case cxgui::Key::Q:
            return GDK_KEY_q;

        case cxgui::Key::Y:
            return GDK_KEY_y;

        case cxgui::Key::Z:
            return GDK_KEY_z;

        default:
            ASSERT_ERROR_MSG("Unknown action key.");
            break;
    }

    return GDK_KEY_VoidSymbol;
}

// From a `cxgui::Key`, generate a Gtk modifier type (which is used by Gtkmm).
[[nodiscard]]  constexpr Gdk::ModifierType ToGtkmmModifierType(const cxgui::Key& p_key)
{
    switch(p_key)
    {
        case cxgui::Key::CTRL:
            return Gdk::ModifierType::CONTROL_MASK;

        default:
            ASSERT_ERROR_MSG("Unknown modifier key.");
            break;
    }

    return ~Gdk::ModifierType::MODIFIER_MASK; // No modifer (all modifiers off).
}

class Gtkmm3OnTriggeredSignal : public cxgui::ISignal<void>
{

public:

    explicit Gtkmm3OnTriggeredSignal(Gtk::MenuItem& p_triggeredMenuItem)
    : m_triggeredMenuItem{p_triggeredMenuItem}
    {
    }

    std::unique_ptr<cxgui::IConnection> Connect(const std::function<void()>& p_slot) override
    {
        sigc::connection gtkConnection = m_triggeredMenuItem.signal_activate().connect(p_slot);

        return std::make_unique<cxgui::Gtkmm3Connection>(gtkConnection);
    }

private:

    Gtk::MenuItem& m_triggeredMenuItem;
};

}

cxgui::Gtkmm3MenuItem::Gtkmm3MenuItem(const std::string& p_label,
                                      const std::optional<cxgui::FreeDesktop::StdActionIcon>& p_icon)
{
    PRECONDITION(!p_label.empty());

    // We handle the icon:
    if(p_icon)
    {
        const std::string iconName = cxgui::FreeDesktop::StdNameGet(*p_icon);
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
    m_accelerator->set_hexpand(true); // Necessary otherwise the key shortcut is not displayed.

    // We register the icon and the label in the container:
    m_layout = CreateWidget<Gtkmm3Layout>();
    ASSERT(m_layout);

    constexpr cxmodel::Row row0{0u};
    constexpr cxgui::ILayout::RowSpan oneRowSpan{1u};

    constexpr cxmodel::Column column0{0u};
    constexpr cxmodel::Column column1{1u};
    constexpr cxgui::ILayout::ColumnSpan oneColumnSpan{1u};

    m_layout->Register(*m_icon,        {row0, oneRowSpan}, {column0, oneColumnSpan});
    m_layout->Register(*m_accelerator, {row0, oneRowSpan}, {column1, oneColumnSpan});

    // Finally, we set up the actual menu item:
    // TG-355 : this cast is needed until Gtk::MenuItem is abstracted away:
    auto* layoutAsGtk = dynamic_cast<Gtk::Widget*>(m_layout.get());
    ASSERT(layoutAsGtk);

    add(*layoutAsGtk);
}

cxgui::Gtkmm3MenuItem::~Gtkmm3MenuItem()
{
    // Before anything is destroyed, we remove it from the menu item:
    remove();
}

void cxgui::Gtkmm3MenuItem::SetDelegate(std::unique_ptr<IWidget> p_delegate)
{
    IF_PRECONDITION_NOT_MET_DO(p_delegate, return;);

    m_delegate = std::move(p_delegate);

    POSTCONDITION(m_delegate);
}

std::unique_ptr<cxgui::ISignal<void>> cxgui::Gtkmm3MenuItem::OnTriggered()
{
    return std::make_unique<Gtkmm3OnTriggeredSignal>(*this);
}

void cxgui::Gtkmm3MenuItem::RegisterKeyboardShortcut(const cxgui::KeyboardShortcut& p_shortcut)
{
    Gdk::ModifierType modifier = ~Gdk::ModifierType::MODIFIER_MASK; // No modifier.
    guint key = GDK_KEY_VoidSymbol; // Invalid key.

    if(p_shortcut.m_second)
    {
        // In this case, we have a modifier as the first key, and an action key
        // as the second key.
        modifier = ToGtkmmModifierType(p_shortcut.m_first);
        key = ToGtkmmKey(*p_shortcut.m_second);
    }
    else
    {
        // In this case, we do not have a modifier. The shortcut consitsts of a single key.
        key = ToGtkmmKey(p_shortcut.m_first);
    }

    const Gtk::AccelKey gtkKeyboardShortcut(key, modifier);
    set_accel_key(gtkKeyboardShortcut);
}

size_t cxgui::Gtkmm3MenuItem::GetWidth() const
{
    IF_CONDITION_NOT_MET_DO(m_delegate, return 0u;);
    return m_delegate->GetWidth();
}

size_t cxgui::Gtkmm3MenuItem::GetHeight() const
{
    IF_CONDITION_NOT_MET_DO(m_delegate, return 0u;);
    return m_delegate->GetHeight();
}

void cxgui::Gtkmm3MenuItem::SetEnabled(cxgui::EnabledState p_enabled)
{
    IF_CONDITION_NOT_MET_DO(m_delegate, return;);
    m_delegate->SetEnabled(p_enabled);
}

void cxgui::Gtkmm3MenuItem::SetMargins(const Margins& p_newMarginSizes)
{
    IF_CONDITION_NOT_MET_DO(m_delegate, return;);
    m_delegate->SetMargins(p_newMarginSizes);
}
