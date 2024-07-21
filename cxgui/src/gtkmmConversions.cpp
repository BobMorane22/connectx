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
#include <cxgui/DialogRole.h>
#include <cxgui/EventPropagation.h>
#include <cxgui/gtkmmConversions.h>
#include <cxgui/Keys.h>
#include <cxgui/KeyboardKeyPressedEvent.h>

template<>
std::optional<cx::gui::KeyboardKeyPressedEvent> cx::gui::FromGtk<cx::gui::KeyboardKeyPressedEvent, GdkEventKey>(const GdkEventKey& p_event)
{
    RETURN_IF(p_event.type != GdkEventType::GDK_KEY_PRESS, std::nullopt);

    switch(p_event.keyval)
    {
        case GDK_KEY_Left  : return cx::gui::KeyboardKeyPressedEvent::KEY_LEFT;
        case GDK_KEY_Right : return cx::gui::KeyboardKeyPressedEvent::KEY_RIGHT;
        case GDK_KEY_Down  : return cx::gui::KeyboardKeyPressedEvent::KEY_DOWN;
    }

    return std::nullopt;
}

template<>
std::optional<bool> cx::gui::ToGtk<bool, cx::gui::EventPropagation>(const cx::gui::EventPropagation& p_propagate)
{
    switch(p_propagate)
    {
        case cx::gui::EventPropagation::PROPAGATE : return false;
        case cx::gui::EventPropagation::STOP      : return true;
    };

    return std::nullopt;
}

template<>
std::optional<guint> cx::gui::ToGtk<guint, cx::gui::Key>(const cx::gui::Key& p_key)
{
    switch(p_key)
    {
        case cx::gui::Key::F1 : return GDK_KEY_F1;
        case cx::gui::Key::Q  : return GDK_KEY_q;
        case cx::gui::Key::Y  : return GDK_KEY_y;
        case cx::gui::Key::Z  : return GDK_KEY_z;
        default             : return std::nullopt;
    }

    // Unreachable code.
    return std::nullopt;
}

template<>
std::optional<Gdk::ModifierType> cx::gui::ToGtk<Gdk::ModifierType, cx::gui::Key>(const cx::gui::Key& p_key)
{
    switch(p_key)
    {
        case cx::gui::Key::CTRL : return Gdk::ModifierType::CONTROL_MASK;
        default               : return std::nullopt;
    }

    // Unreachable code.
    return std::nullopt;
}

template<>
std::optional<Gtk::MessageType> cx::gui::ToGtk<Gtk::MessageType, cx::gui::DialogRole>(const cx::gui::DialogRole& p_role)
{
    switch(p_role)
    {
        case cx::gui::DialogRole::INFORMATION : return Gtk::MESSAGE_INFO;
        case cx::gui::DialogRole::QUESTION    : return Gtk::MESSAGE_QUESTION;
        case cx::gui::DialogRole::WARNING     : return Gtk::MESSAGE_WARNING;
        case cx::gui::DialogRole::ERROR       : return Gtk::MESSAGE_ERROR;
    }

    return std::nullopt;
}

template<> std::optional<Gtk::Align> cx::gui::ToGtk<Gtk::Align, cx::gui::ILayout::VerticalAlignement>(const cx::gui::ILayout::VerticalAlignement& p_alignement)
{
    switch(p_alignement)
    {
        case cx::gui::ILayout::VerticalAlignement::TOP    : return Gtk::Align::ALIGN_START;
        case cx::gui::ILayout::VerticalAlignement::CENTER : return Gtk::Align::ALIGN_CENTER;
        case cx::gui::ILayout::VerticalAlignement::BOTTOM : return Gtk::Align::ALIGN_END;
        case cx::gui::ILayout::VerticalAlignement::FILL   : return Gtk::Align::ALIGN_FILL;
    }

    return std::nullopt;
}

template<> std::optional<Gtk::Align> cx::gui::ToGtk<Gtk::Align, cx::gui::ILayout::HorizontalAlignement>(const cx::gui::ILayout::HorizontalAlignement& p_alignement)
{
    switch(p_alignement)
    {
        case cx::gui::ILayout::HorizontalAlignement::LEFT   : return Gtk::Align::ALIGN_START;
        case cx::gui::ILayout::HorizontalAlignement::CENTER : return Gtk::Align::ALIGN_CENTER;
        case cx::gui::ILayout::HorizontalAlignement::RIGHT  : return Gtk::Align::ALIGN_END;
        case cx::gui::ILayout::HorizontalAlignement::FILL   : return Gtk::Align::ALIGN_FILL;
    }

    return std::nullopt;
}
