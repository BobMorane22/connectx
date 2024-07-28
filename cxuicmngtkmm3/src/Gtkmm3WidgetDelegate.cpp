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

#include <gtkmm/widget.h>

#include <cxinv/assertion.h>
#include <cxuicmn/EnabledState.h>
#include <cxuicmn/EventPropagation.h>
#include <cxuicmngtkmm3/gtkmmConversions.h>
#include <cxuicmngtkmm3/Gtkmm3Connection.h>
#include <cxuicmngtkmm3/Gtkmm3WidgetDelegate.h>
#include <cxuicmn/KeyboardKeyPressedEvent.h>
#include <cxuicmn/Margins.h>

namespace
{

class Gtkmm3KeyboardOnKeyPressedEventSignal : public cx::ui::cmn::ISignal<cx::ui::cmn::EventPropagation, cx::ui::cmn::KeyboardKeyPressedEvent>
{

public:

    explicit Gtkmm3KeyboardOnKeyPressedEventSignal(Gtk::Widget& p_widget)
    : m_widget{p_widget}
    {
    }

    [[nodiscard]] std::unique_ptr<cx::ui::cmn::IConnection> Connect(const std::function<cx::ui::cmn::EventPropagation(cx::ui::cmn::KeyboardKeyPressedEvent)>& p_slot)
    {
        const auto gtkSlot = [p_slot](GdkEventKey* p_event)
        {
            IF_PRECONDITION_NOT_MET_DO(p_event, return true;);

            const auto event = cx::ui::cmn::FromGtk<cx::ui::cmn::KeyboardKeyPressedEvent>(*p_event);
            RETURN_IF(!event.has_value(), true);

            const cx::ui::cmn::EventPropagation propagate = p_slot(event.value());

            const auto isHandled = cx::ui::cmn::ToGtk<bool>(propagate);
            IF_CONDITION_NOT_MET_DO(isHandled.has_value(), return true;);

            return isHandled.value();
        };

        sigc::connection gtkConnection = m_widget.signal_key_press_event().connect(gtkSlot, false);
        IF_CONDITION_NOT_MET_DO(gtkConnection.connected(), return nullptr;);

        return std::make_unique<cx::ui::cmn::Gtkmm3Connection>(gtkConnection);
    }

private:

    Gtk::Widget& m_widget;
};

} // namespace

void cx::ui::cmn::Gtkmm3WidgetDelegate::SetUnderlying(Gtk::Widget* p_underlying)
{
    PRECONDITION(p_underlying);

    m_underlying = p_underlying;

    POSTCONDITION(m_underlying);
}

size_t cx::ui::cmn::Gtkmm3WidgetDelegate::GetWidth() const
{
    IF_PRECONDITION_NOT_MET_DO(m_underlying, return 0u;);

    const int width = m_underlying->get_width();
    IF_CONDITION_NOT_MET_DO(width > 0, return 0u;);

    return static_cast<size_t>(width);
}

size_t cx::ui::cmn::Gtkmm3WidgetDelegate::GetHeight() const {
    IF_PRECONDITION_NOT_MET_DO(m_underlying, return 0u;);

    const int height = m_underlying->get_height();
    IF_CONDITION_NOT_MET_DO(height > 0, return 0u;);

    return static_cast<size_t>(height);
}

void cx::ui::cmn::Gtkmm3WidgetDelegate::SetEnabled(EnabledState p_enabled)
{
    IF_PRECONDITION_NOT_MET_DO(m_underlying, return;);

    m_underlying->set_sensitive(p_enabled == EnabledState::Enabled ? true : false);
}

void cx::ui::cmn::Gtkmm3WidgetDelegate::SetMargins(const Margins& p_newMarginSizes)
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

void cx::ui::cmn::Gtkmm3WidgetDelegate::SetTooltip(const std::string& p_tooltipContents)
{
    IF_PRECONDITION_NOT_MET_DO(m_underlying, return;);

    m_underlying->set_tooltip_text(p_tooltipContents);
}

std::unique_ptr<cx::ui::cmn::ISignal<cx::ui::cmn::EventPropagation, cx::ui::cmn::KeyboardKeyPressedEvent>> cx::ui::cmn::Gtkmm3WidgetDelegate::OnKeyPressed()
{
    IF_PRECONDITION_NOT_MET_DO(m_underlying, return nullptr;);

    return std::make_unique<Gtkmm3KeyboardOnKeyPressedEventSignal>(*m_underlying);
}
