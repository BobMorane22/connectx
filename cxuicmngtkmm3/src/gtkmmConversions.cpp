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
#include <cxuicmn/DialogRole.h>
#include <cxuicmn/EventPropagation.h>
#include <cxuicmngtkmm3/gtkmmConversions.h>
#include <cxuicmn/Keys.h>
#include <cxuicmn/KeyboardKeyPressedEvent.h>

template<>
std::optional<cx::ui::cmn::KeyboardKeyPressedEvent> cx::ui::cmn::FromGtk<cx::ui::cmn::KeyboardKeyPressedEvent, GdkEventKey>(const GdkEventKey& p_event)
{
    RETURN_IF(p_event.type != GdkEventType::GDK_KEY_PRESS, std::nullopt);

    switch(p_event.keyval)
    {
        case GDK_KEY_Left  : return cx::ui::cmn::KeyboardKeyPressedEvent::KEY_LEFT;
        case GDK_KEY_Right : return cx::ui::cmn::KeyboardKeyPressedEvent::KEY_RIGHT;
        case GDK_KEY_Down  : return cx::ui::cmn::KeyboardKeyPressedEvent::KEY_DOWN;
    }

    return std::nullopt;
}

template<>
std::optional<bool> cx::ui::cmn::ToGtk<bool, cx::ui::cmn::EventPropagation>(const cx::ui::cmn::EventPropagation& p_propagate)
{
    switch(p_propagate)
    {
        case cx::ui::cmn::EventPropagation::PROPAGATE : return false;
        case cx::ui::cmn::EventPropagation::STOP      : return true;
    };

    return std::nullopt;
}

template<>
std::optional<guint> cx::ui::cmn::ToGtk<guint, cx::ui::cmn::Key>(const cx::ui::cmn::Key& p_key)
{
    switch(p_key)
    {
        case cx::ui::cmn::Key::F1 : return GDK_KEY_F1;
        case cx::ui::cmn::Key::Q  : return GDK_KEY_q;
        case cx::ui::cmn::Key::Y  : return GDK_KEY_y;
        case cx::ui::cmn::Key::Z  : return GDK_KEY_z;
        default             : return std::nullopt;
    }

    // Unreachable code.
    return std::nullopt;
}

template<>
std::optional<Gdk::ModifierType> cx::ui::cmn::ToGtk<Gdk::ModifierType, cx::ui::cmn::Key>(const cx::ui::cmn::Key& p_key)
{
    switch(p_key)
    {
        case cx::ui::cmn::Key::CTRL : return Gdk::ModifierType::CONTROL_MASK;
        default               : return std::nullopt;
    }

    // Unreachable code.
    return std::nullopt;
}

template<>
std::optional<Gtk::MessageType> cx::ui::cmn::ToGtk<Gtk::MessageType, cx::ui::cmn::DialogRole>(const cx::ui::cmn::DialogRole& p_role)
{
    switch(p_role)
    {
        case cx::ui::cmn::DialogRole::INFORMATION : return Gtk::MESSAGE_INFO;
        case cx::ui::cmn::DialogRole::QUESTION    : return Gtk::MESSAGE_QUESTION;
        case cx::ui::cmn::DialogRole::WARNING     : return Gtk::MESSAGE_WARNING;
        case cx::ui::cmn::DialogRole::ERROR       : return Gtk::MESSAGE_ERROR;
    }

    return std::nullopt;
}

template<> std::optional<Gtk::Align> cx::ui::cmn::ToGtk<Gtk::Align, cx::ui::cmn::ILayout::VerticalAlignement>(const cx::ui::cmn::ILayout::VerticalAlignement& p_alignement)
{
    switch(p_alignement)
    {
        case cx::ui::cmn::ILayout::VerticalAlignement::TOP    : return Gtk::Align::ALIGN_START;
        case cx::ui::cmn::ILayout::VerticalAlignement::CENTER : return Gtk::Align::ALIGN_CENTER;
        case cx::ui::cmn::ILayout::VerticalAlignement::BOTTOM : return Gtk::Align::ALIGN_END;
        case cx::ui::cmn::ILayout::VerticalAlignement::FILL   : return Gtk::Align::ALIGN_FILL;
    }

    return std::nullopt;
}

template<> std::optional<Gtk::Align> cx::ui::cmn::ToGtk<Gtk::Align, cx::ui::cmn::ILayout::HorizontalAlignement>(const cx::ui::cmn::ILayout::HorizontalAlignement& p_alignement)
{
    switch(p_alignement)
    {
        case cx::ui::cmn::ILayout::HorizontalAlignement::LEFT   : return Gtk::Align::ALIGN_START;
        case cx::ui::cmn::ILayout::HorizontalAlignement::CENTER : return Gtk::Align::ALIGN_CENTER;
        case cx::ui::cmn::ILayout::HorizontalAlignement::RIGHT  : return Gtk::Align::ALIGN_END;
        case cx::ui::cmn::ILayout::HorizontalAlignement::FILL   : return Gtk::Align::ALIGN_FILL;
    }

    return std::nullopt;
}
