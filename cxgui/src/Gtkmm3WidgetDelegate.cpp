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
 * @file Gtkmm3WidgetDelegate.cpp
 * @date 2023
 *
 *************************************************************************************************/

#include <optional>
#include <type_traits>

#include <gtkmm/widget.h>

#include <cxinv/assertion.h>
#include <cxgui/EnabledState.h>
#include <cxgui/EventPropagation.h>
#include <cxgui/Gtkmm3Connection.h>
#include <cxgui/Gtkmm3WidgetDelegate.h>
#include <cxgui/KeyboardKeyPressedEvent.h>
#include <cxgui/Margins.h>

namespace
{

template<typename T>
struct DependantFalse : std::false_type
{};

template<typename Target, typename GtkSource>
[[nodiscard]] std::optional<Target> FromGtk(const GtkSource& /*p_source*/)
{
    // This should be explicitely specialized.
    static_assert(DependantFalse<Target>::value && DependantFalse<GtkSource>::value);
    return std::nullopt;
}

template<> 
[[nodiscard]] std::optional<cxgui::KeyboardKeyPressedEvent> FromGtk(const GdkEventKey& p_event)
{
    RETURN_IF(p_event.type != GdkEventType::GDK_KEY_PRESS, std::nullopt);

    switch(p_event.keyval)
    {
        case GDK_KEY_Left:
            return cxgui::KeyboardKeyPressedEvent::KEY_LEFT;

        case GDK_KEY_Right:
            return cxgui::KeyboardKeyPressedEvent::KEY_RIGHT;

        case GDK_KEY_Down:
            return cxgui::KeyboardKeyPressedEvent::KEY_DOWN;

        default:
            break;
    }

    return std::nullopt;
}

template<typename GtkTarget, typename Source>
[[nodiscard]] std::optional<GtkTarget> ToGtk(const Source& /*p_source*/)
{
    // This should be explicitely specialized.
    static_assert(DependantFalse<GtkTarget>::value && DependantFalse<Source>::value);
    return std::nullopt;
}

template<>
[[nodiscard]] std::optional<bool> ToGtk<bool, cxgui::EventPropagation>(const cxgui::EventPropagation& p_propagate)
{
    switch(p_propagate)
    {
        case cxgui::EventPropagation::PROPAGATE:
        {
            // Not handled, so we propagate.
            return false;
        }
        case cxgui::EventPropagation::STOP:
        {
            // Handled here, do not propagate.
            return true;
        }
        default:
            break;
    };

    return std::nullopt;
}

class Gtkmm3KeyboardOnKeyPressedEventSignal : public cxgui::ISignal<cxgui::EventPropagation, cxgui::KeyboardKeyPressedEvent>
{

public:

    explicit Gtkmm3KeyboardOnKeyPressedEventSignal(Gtk::Widget& p_widget)
    : m_widget{p_widget}
    {
    }

    [[nodiscard]] std::unique_ptr<cxgui::IConnection> Connect(const std::function<cxgui::EventPropagation(cxgui::KeyboardKeyPressedEvent)>& p_slot)
    {
        const auto gtkSlot = [p_slot](GdkEventKey* p_event)
        {
            IF_PRECONDITION_NOT_MET_DO(p_event, return true;);

            const auto event = FromGtk<cxgui::KeyboardKeyPressedEvent>(*p_event);
            RETURN_IF(!event.has_value(), true);

            const cxgui::EventPropagation propagate = p_slot(event.value());

            const auto isHandled = ToGtk<bool>(propagate);
            IF_CONDITION_NOT_MET_DO(isHandled.has_value(), return true;);

            return isHandled.value();
        };

        sigc::connection gtkConnection = m_widget.signal_key_press_event().connect(gtkSlot, false);
        IF_CONDITION_NOT_MET_DO(gtkConnection.connected(), return nullptr;);

        return std::make_unique<cxgui::Gtkmm3Connection>(gtkConnection);
    }

private:

    Gtk::Widget& m_widget;
};

} // namespace

void cxgui::Gtkmm3WidgetDelegate::SetUnderlying(Gtk::Widget* p_underlying)
{
    PRECONDITION(p_underlying);

    m_underlying = p_underlying;

    POSTCONDITION(m_underlying);
}

size_t cxgui::Gtkmm3WidgetDelegate::GetWidth() const
{
    IF_PRECONDITION_NOT_MET_DO(m_underlying, return 0u;);

    const int width = m_underlying->get_width();
    IF_CONDITION_NOT_MET_DO(width > 0, return 0u;);

    return static_cast<size_t>(width);
}

size_t cxgui::Gtkmm3WidgetDelegate::GetHeight() const {
    IF_PRECONDITION_NOT_MET_DO(m_underlying, return 0u;);

    const int height = m_underlying->get_height();
    IF_CONDITION_NOT_MET_DO(height > 0, return 0u;);

    return static_cast<size_t>(height);
}

void cxgui::Gtkmm3WidgetDelegate::SetEnabled(EnabledState p_enabled)
{
    IF_PRECONDITION_NOT_MET_DO(m_underlying, return;);

    m_underlying->set_sensitive(p_enabled == EnabledState::Enabled ? true : false);
}

void cxgui::Gtkmm3WidgetDelegate::SetMargins(const Margins& p_newMarginSizes)
{
    IF_PRECONDITION_NOT_MET_DO(m_underlying, return;);

    const int start = p_newMarginSizes.m_left.Get();
    const int end = p_newMarginSizes.m_right.Get();
    const int top = p_newMarginSizes.m_top.Get();
    const int bottom = p_newMarginSizes.m_bottom.Get();

    m_underlying->set_margin_start(start);
    m_underlying->set_margin_end(end);
    m_underlying->set_margin_top(top);
    m_underlying->set_margin_bottom(bottom);
}

void cxgui::Gtkmm3WidgetDelegate::SetTooltip(const std::string& p_tooltipContents)
{
    IF_PRECONDITION_NOT_MET_DO(m_underlying, return;);

    m_underlying->set_tooltip_text(p_tooltipContents);
}

std::unique_ptr<cxgui::ISignal<cxgui::EventPropagation, cxgui::KeyboardKeyPressedEvent>> cxgui::Gtkmm3WidgetDelegate::OnKeyPressed()
{
    IF_PRECONDITION_NOT_MET_DO(m_underlying, return nullptr;);

    return std::make_unique<Gtkmm3KeyboardOnKeyPressedEventSignal>(*m_underlying);
}
