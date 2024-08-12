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
 * @file gtkmmConversions.h
 * @date 2024
 *
 *************************************************************************************************/

#include <gdk/gdkkeysyms.h>

#include <cxcmn/helpers.h>
#include <cxcmnui/DialogRole.h>
#include <cxcmnui/EventPropagation.h>
#include <cxcmnui/Keys.h>
#include <cxcmnui/KeyboardKeyPressedEvent.h>
#include <cxcmnuigtkmm3/gtkmmConversions.h>

template<>
std::optional<cx::cmn::ui::KeyboardKeyPressedEvent> cx::cmn::ui::gtkmm3::FromGtk<cx::cmn::ui::KeyboardKeyPressedEvent, GdkEventKey>(const GdkEventKey& p_event)
{
    RETURN_IF(p_event.type != GdkEventType::GDK_KEY_PRESS, std::nullopt);

    switch(p_event.keyval)
    {
        case GDK_KEY_Left  : return cx::cmn::ui::KeyboardKeyPressedEvent::KEY_LEFT;
        case GDK_KEY_Right : return cx::cmn::ui::KeyboardKeyPressedEvent::KEY_RIGHT;
        case GDK_KEY_Down  : return cx::cmn::ui::KeyboardKeyPressedEvent::KEY_DOWN;
    }

    return std::nullopt;
}

template<>
std::optional<bool> cx::cmn::ui::gtkmm3::ToGtk<bool, cx::cmn::ui::EventPropagation>(const cx::cmn::ui::EventPropagation& p_propagate)
{
    switch(p_propagate)
    {
        case cx::cmn::ui::EventPropagation::PROPAGATE : return false;
        case cx::cmn::ui::EventPropagation::STOP      : return true;
    };

    return std::nullopt;
}

template<>
std::optional<guint> cx::cmn::ui::gtkmm3::ToGtk<guint, cx::cmn::ui::Key>(const cx::cmn::ui::Key& p_key)
{
    switch(p_key)
    {
        case cx::cmn::ui::Key::F1 : return GDK_KEY_F1;
        case cx::cmn::ui::Key::Q  : return GDK_KEY_q;
        case cx::cmn::ui::Key::Y  : return GDK_KEY_y;
        case cx::cmn::ui::Key::Z  : return GDK_KEY_z;
        default             : return std::nullopt;
    }

    // Unreachable code.
    return std::nullopt;
}

template<>
std::optional<Gdk::ModifierType> cx::cmn::ui::gtkmm3::ToGtk<Gdk::ModifierType, cx::cmn::ui::Key>(const cx::cmn::ui::Key& p_key)
{
    switch(p_key)
    {
        case cx::cmn::ui::Key::CTRL : return Gdk::ModifierType::CONTROL_MASK;
        default               : return std::nullopt;
    }

    // Unreachable code.
    return std::nullopt;
}

template<>
std::optional<Gtk::MessageType> cx::cmn::ui::gtkmm3::ToGtk<Gtk::MessageType, cx::cmn::ui::DialogRole>(const cx::cmn::ui::DialogRole& p_role)
{
    switch(p_role)
    {
        case cx::cmn::ui::DialogRole::INFORMATION : return Gtk::MESSAGE_INFO;
        case cx::cmn::ui::DialogRole::QUESTION    : return Gtk::MESSAGE_QUESTION;
        case cx::cmn::ui::DialogRole::WARNING     : return Gtk::MESSAGE_WARNING;
        case cx::cmn::ui::DialogRole::ERROR       : return Gtk::MESSAGE_ERROR;
    }

    return std::nullopt;
}

template<>
std::optional<Gtk::Align> cx::cmn::ui::gtkmm3::ToGtk<Gtk::Align, cx::cmn::ui::ILayout::VerticalAlignement>(const cx::cmn::ui::ILayout::VerticalAlignement& p_alignement)
{
    switch(p_alignement)
    {
        case cx::cmn::ui::ILayout::VerticalAlignement::TOP    : return Gtk::Align::ALIGN_START;
        case cx::cmn::ui::ILayout::VerticalAlignement::CENTER : return Gtk::Align::ALIGN_CENTER;
        case cx::cmn::ui::ILayout::VerticalAlignement::BOTTOM : return Gtk::Align::ALIGN_END;
        case cx::cmn::ui::ILayout::VerticalAlignement::FILL   : return Gtk::Align::ALIGN_FILL;
    }

    return std::nullopt;
}

template<>
std::optional<Gtk::Align> cx::cmn::ui::gtkmm3::ToGtk<Gtk::Align, cx::cmn::ui::ILayout::HorizontalAlignement>(const cx::cmn::ui::ILayout::HorizontalAlignement& p_alignement)
{
    switch(p_alignement)
    {
        case cx::cmn::ui::ILayout::HorizontalAlignement::LEFT   : return Gtk::Align::ALIGN_START;
        case cx::cmn::ui::ILayout::HorizontalAlignement::CENTER : return Gtk::Align::ALIGN_CENTER;
        case cx::cmn::ui::ILayout::HorizontalAlignement::RIGHT  : return Gtk::Align::ALIGN_END;
        case cx::cmn::ui::ILayout::HorizontalAlignement::FILL   : return Gtk::Align::ALIGN_FILL;
    }

    return std::nullopt;
}
