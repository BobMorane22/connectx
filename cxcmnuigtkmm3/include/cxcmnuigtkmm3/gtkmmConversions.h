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

#ifndef GTKMMCONVERSIONS_H_B4274961_44D3_4DE7_BB4D_2374BE3AB908
#define GTKMMCONVERSIONS_H_B4274961_44D3_4DE7_BB4D_2374BE3AB908

#include <optional>
#include <type_traits>

#include <gdk/gdk.h>
#include <gdkmm/types.h>
#include <gtkmm/enums.h>

#include <cxcmnui/ILayout.h>

namespace cx::cmn::ui
{
    enum class DialogRole;
    enum class Key;
    enum class KeyboardKeyPressedEvent;
    enum class EventPropagation;
}

namespace cx::cmn::ui
{

/**********************************************************************************************//**
 * @brief Converts a Gtkmm source value into its equivalent non Gtkmm value, if possible.
 *
 * @tparam Target
 *      The type to convert to. The returned value will be of this type.

 * @tparam GtkmmSource
 *      The Gtkmm type of the source value to convert.
 *
 * @param
 *      The source value to convert.
 *
 * @return
 *      A `std::optional` contaning the converted value, if the conversion was possible,
 *      or `std::nullopt otherwise.
 *
 *************************************************************************************************/
template<typename Target, typename GtkmmSource>
[[nodiscard]] std::optional<Target> FromGtk(const GtkmmSource& p_event);

template<> [[nodiscard]] std::optional<KeyboardKeyPressedEvent> FromGtk<KeyboardKeyPressedEvent, GdkEventKey>(const GdkEventKey& p_event);


/**********************************************************************************************//**
 * @brief Converts a non Gtkmm source value into its equivalent Gtkmm value, if possible.
 *
 * @tparam GtkmmTarget
 *      The Gtkmm type to convert to. The returned value will be of this type.

 * @tparam Source
 *      The type of the source value to convert.
 *
 * @param
 *      The source value to convert.
 *
 * @return
 *      A `std::optional` contaning the converted value, if the conversion was possible,
 *      or `std::nullopt otherwise.
 *
 *************************************************************************************************/
template <typename GtkmmTarget, typename Source>
[[nodiscard]] std::optional<GtkmmTarget> ToGtk(const Source& p_source);

template<> [[nodiscard]] std::optional<bool> ToGtk<bool, EventPropagation>(const EventPropagation& p_propagate);
template<> [[nodiscard]] std::optional<guint> ToGtk<guint, Key>(const Key& p_key);
template<> [[nodiscard]] std::optional<Gdk::ModifierType> ToGtk<Gdk::ModifierType, Key>(const Key& p_key);
template<> [[nodiscard]] std::optional<Gtk::MessageType> ToGtk<Gtk::MessageType, DialogRole>(const DialogRole& p_role);
template<> [[nodiscard]] std::optional<Gtk::Align> ToGtk<Gtk::Align, ILayout::VerticalAlignement>(const ILayout::VerticalAlignement& p_alignement);
template<> [[nodiscard]] std::optional<Gtk::Align> ToGtk<Gtk::Align, ILayout::HorizontalAlignement>(const ILayout::HorizontalAlignement& p_alignement);

} // namespace cx::cmn::ui

#endif // GTKMMCONVERSIONS_H_B4274961_44D3_4DE7_BB4D_2374BE3AB908
