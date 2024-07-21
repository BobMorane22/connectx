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
std::optional<cxgui::KeyboardKeyPressedEvent> cxgui::FromGtk<cxgui::KeyboardKeyPressedEvent, GdkEventKey>(const GdkEventKey& p_event)
{
    RETURN_IF(p_event.type != GdkEventType::GDK_KEY_PRESS, std::nullopt);

    switch(p_event.keyval)
    {
        case GDK_KEY_Left  : return cxgui::KeyboardKeyPressedEvent::KEY_LEFT;
        case GDK_KEY_Right : return cxgui::KeyboardKeyPressedEvent::KEY_RIGHT;
        case GDK_KEY_Down  : return cxgui::KeyboardKeyPressedEvent::KEY_DOWN;
    }

    return std::nullopt;
}

template<>
std::optional<bool> cxgui::ToGtk<bool, cxgui::EventPropagation>(const cxgui::EventPropagation& p_propagate)
{
    switch(p_propagate)
    {
        case cxgui::EventPropagation::PROPAGATE : return false;
        case cxgui::EventPropagation::STOP      : return true;
    };

    return std::nullopt;
}

template<>
std::optional<guint> cxgui::ToGtk<guint, cxgui::Key>(const cxgui::Key& p_key)
{
    switch(p_key)
    {
        case cxgui::Key::F1 : return GDK_KEY_F1;
        case cxgui::Key::Q  : return GDK_KEY_q;
        case cxgui::Key::Y  : return GDK_KEY_y;
        case cxgui::Key::Z  : return GDK_KEY_z;
        default             : return std::nullopt;
    }

    // Unreachable code.
    return std::nullopt;
}

template<>
std::optional<Gdk::ModifierType> cxgui::ToGtk<Gdk::ModifierType, cxgui::Key>(const cxgui::Key& p_key)
{
    switch(p_key)
    {
        case cxgui::Key::CTRL : return Gdk::ModifierType::CONTROL_MASK;
        default               : return std::nullopt;
    }

    // Unreachable code.
    return std::nullopt;
}

template<>
std::optional<Gtk::MessageType> cxgui::ToGtk<Gtk::MessageType, cxgui::DialogRole>(const cxgui::DialogRole& p_role)
{
    switch(p_role)
    {
        case cxgui::DialogRole::INFORMATION : return Gtk::MESSAGE_INFO;
        case cxgui::DialogRole::QUESTION    : return Gtk::MESSAGE_QUESTION;
        case cxgui::DialogRole::WARNING     : return Gtk::MESSAGE_WARNING;
        case cxgui::DialogRole::ERROR       : return Gtk::MESSAGE_ERROR;
    }

    return std::nullopt;
}

template<> std::optional<Gtk::Align> cxgui::ToGtk<Gtk::Align, cxgui::ILayout::VerticalAlignement>(const cxgui::ILayout::VerticalAlignement& p_alignement)
{
    switch(p_alignement)
    {
        case cxgui::ILayout::VerticalAlignement::TOP    : return Gtk::Align::ALIGN_START;
        case cxgui::ILayout::VerticalAlignement::CENTER : return Gtk::Align::ALIGN_CENTER;
        case cxgui::ILayout::VerticalAlignement::BOTTOM : return Gtk::Align::ALIGN_END;
        case cxgui::ILayout::VerticalAlignement::FILL   : return Gtk::Align::ALIGN_FILL;
    }

    return std::nullopt;
}

template<> std::optional<Gtk::Align> cxgui::ToGtk<Gtk::Align, cxgui::ILayout::HorizontalAlignement>(const cxgui::ILayout::HorizontalAlignement& p_alignement)
{
    switch(p_alignement)
    {
        case cxgui::ILayout::HorizontalAlignement::LEFT   : return Gtk::Align::ALIGN_START;
        case cxgui::ILayout::HorizontalAlignement::CENTER : return Gtk::Align::ALIGN_CENTER;
        case cxgui::ILayout::HorizontalAlignement::RIGHT  : return Gtk::Align::ALIGN_END;
        case cxgui::ILayout::HorizontalAlignement::FILL   : return Gtk::Align::ALIGN_FILL;
    }

    return std::nullopt;
}
