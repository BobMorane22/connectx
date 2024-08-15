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
 * @file WidgetDelegate.cpp
 * @date 2023
 *
 *************************************************************************************************/

#include <gtkmm/widget.h>

#include <cxinv/assertion.h>
#include <cxcmnui/EnabledState.h>
#include <cxcmnui/EventPropagation.h>
#include <cxcmnui/KeyboardKeyPressedEvent.h>
#include <cxcmnui/Margins.h>
#include <cxcmnuigtkmm3/Connection.h>
#include <cxcmnuigtkmm3/WidgetDelegate.h>

#include "conversions.h"

namespace
{

class Gtkmm3KeyboardOnKeyPressedEventSignal : public cx::cmn::ui::ISignal<cx::cmn::ui::EventPropagation, cx::cmn::ui::KeyboardKeyPressedEvent>
{

public:

    explicit Gtkmm3KeyboardOnKeyPressedEventSignal(Gtk::Widget& p_widget)
    : m_widget{p_widget}
    {
    }

    [[nodiscard]] std::unique_ptr<cx::cmn::ui::IConnection> Connect(const std::function<cx::cmn::ui::EventPropagation(cx::cmn::ui::KeyboardKeyPressedEvent)>& p_slot)
    {
        const auto gtkSlot = [p_slot](GdkEventKey* p_event)
        {
            IF_PRECONDITION_NOT_MET_DO(p_event, return true;);

            const auto event = cx::cmn::ui::gtkmm3::FromGtk<cx::cmn::ui::KeyboardKeyPressedEvent>(*p_event);
            RETURN_IF(!event.has_value(), true);

            const cx::cmn::ui::EventPropagation propagate = p_slot(event.value());

            const auto isHandled = cx::cmn::ui::gtkmm3::ToGtk<bool>(propagate);
            IF_CONDITION_NOT_MET_DO(isHandled.has_value(), return true;);

            return isHandled.value();
        };

        sigc::connection gtkConnection = m_widget.signal_key_press_event().connect(gtkSlot, false);
        IF_CONDITION_NOT_MET_DO(gtkConnection.connected(), return nullptr;);

        return std::make_unique<cx::cmn::ui::gtkmm3::Connection>(gtkConnection);
    }

private:

    Gtk::Widget& m_widget;
};

} // namespace

void cx::cmn::ui::gtkmm3::WidgetDelegate::SetUnderlying(Gtk::Widget* p_underlying)
{
    PRECONDITION(p_underlying);

    m_underlying = p_underlying;

    POSTCONDITION(m_underlying);
}

size_t cx::cmn::ui::gtkmm3::WidgetDelegate::GetWidth() const
{
    IF_PRECONDITION_NOT_MET_DO(m_underlying, return 0u;);

    const int width = m_underlying->get_width();
    IF_CONDITION_NOT_MET_DO(width > 0, return 0u;);

    return static_cast<size_t>(width);
}

size_t cx::cmn::ui::gtkmm3::WidgetDelegate::GetHeight() const {
    IF_PRECONDITION_NOT_MET_DO(m_underlying, return 0u;);

    const int height = m_underlying->get_height();
    IF_CONDITION_NOT_MET_DO(height > 0, return 0u;);

    return static_cast<size_t>(height);
}

void cx::cmn::ui::gtkmm3::WidgetDelegate::SetEnabled(cx::cmn::ui::EnabledState p_enabled)
{
    IF_PRECONDITION_NOT_MET_DO(m_underlying, return;);

    m_underlying->set_sensitive(p_enabled == cx::cmn::ui::EnabledState::Enabled ? true : false);
}

void cx::cmn::ui::gtkmm3::WidgetDelegate::SetMargins(const cx::cmn::ui::Margins& p_newMarginSizes)
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

void cx::cmn::ui::gtkmm3::WidgetDelegate::SetTooltip(const std::string& p_tooltipContents)
{
    IF_PRECONDITION_NOT_MET_DO(m_underlying, return;);

    m_underlying->set_tooltip_text(p_tooltipContents);
}

std::unique_ptr<cx::cmn::ui::ISignal<cx::cmn::ui::EventPropagation, cx::cmn::ui::KeyboardKeyPressedEvent>> cx::cmn::ui::gtkmm3::WidgetDelegate::OnKeyPressed()
{
    IF_PRECONDITION_NOT_MET_DO(m_underlying, return nullptr;);

    return std::make_unique<Gtkmm3KeyboardOnKeyPressedEventSignal>(*m_underlying);
}
