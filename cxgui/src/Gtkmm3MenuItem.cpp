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

#include <cxinv/assertion.h>
#include <cxgui/Gtkmm3Layout.h>
#include <cxgui/Gtkmm3MenuItem.h>
#include <cxgui/Gtkmm3WidgetDelegate.h>
#include <cxgui/StdActionIcon.h>

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
