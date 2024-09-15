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
 * @file Layout.cpp
 * @date 2023
 *
 *************************************************************************************************/

#include <cxinv/assertion.h>
#include <cxcmn/helpers.h>
#include <cxcmnui/EventPropagation.h>
#include <cxcmnui/IWidget.h>
#include <cxcmnui/KeyboardKeyPressedEvent.h>
#include <cxcmnui/Margins.h>

#include "conversions.h"
#include "Layout.h"

void cx::cmn::ui::gtkmm3::Layout::SetDelegate(
    std::unique_ptr<IWidget> p_delegate)
{
    IF_PRECONDITION_NOT_MET_DO(p_delegate, return;);

    m_delegate = std::move(p_delegate);

    POSTCONDITION(m_delegate);
}

//! [AWT - Layout and casts]
void cx::cmn::ui::gtkmm3::Layout::Register(
    cx::cmn::ui::IWidget& p_widget,
    const cx::cmn::ui::ILayout::RowDescriptor& p_row,
    const cx::cmn::ui::ILayout::ColumnDescriptor& p_column,
    const cx::cmn::ui::ILayout::Alignement& p_alignement)
{
    const int left = static_cast<int>(p_column.m_coordinate.Get());
    const int top = static_cast<int>(p_row.m_coordinate.Get());
    const int width = static_cast<int>(p_column.m_span.Get());
    const int height = static_cast<int>(p_row.m_span.Get());

    auto* gtkWidget = dynamic_cast<Gtk::Widget*>(&p_widget);
    ASSERT(gtkWidget);

    const auto verticalAlignementConversion = cx::cmn::ui::gtkmm3::ToGtk<Gtk::Align>(p_alignement.m_vertical);
    gtkWidget->set_valign(verticalAlignementConversion.value_or(Gtk::ALIGN_FILL));
    const auto horizontalAlignementConversion = cx::cmn::ui::gtkmm3::ToGtk<Gtk::Align>(p_alignement.m_horizontal);
    gtkWidget->set_halign(horizontalAlignementConversion.value_or(Gtk::ALIGN_FILL));

    gtkWidget->set_hexpand(true);
    gtkWidget->set_vexpand(true);

    attach(*gtkWidget, left, top, width, height );
}
//! [AWT - Layout and casts]

void cx::cmn::ui::gtkmm3::Layout::Unregister(
    cx::cmn::ui::IWidget& p_widget)
{
    auto* gtkWidget = dynamic_cast<Gtk::Widget*>(&p_widget);
    ASSERT(gtkWidget);

    remove(*gtkWidget);
}

const cx::cmn::ui::IWidget* cx::cmn::ui::gtkmm3::Layout::GetWidgetAtPosition(
    const cx::model::Row& p_row,
    const cx::model::Column& p_column) const
{
    const int left = static_cast<int>(p_column.Get());
    const int top = static_cast<int>(p_row.Get());

    const Gtk::Widget* gtkWidget = get_child_at(left, top);
    RETURN_IF(!gtkWidget, nullptr);

    const auto* widget = dynamic_cast<const cx::cmn::ui::IWidget*>(gtkWidget);
    IF_CONDITION_NOT_MET_DO(widget, return nullptr;);

    return widget;
}

cx::cmn::ui::IWidget* cx::cmn::ui::gtkmm3::Layout::GetWidgetAtPosition(
    const cx::model::Row& p_row,
    const cx::model::Column& p_column)
{
    return const_cast<cx::cmn::ui::IWidget*>(const_cast<const cx::cmn::ui::gtkmm3::Layout*>(this)->GetWidgetAtPosition(p_row, p_column));
}

void cx::cmn::ui::gtkmm3::Layout::SetRowSpacingMode(
    cx::cmn::ui::ILayout::RowSpacingMode p_newMode)
{
    if(p_newMode == cx::cmn::ui::ILayout::RowSpacingMode::EQUAL)
    {
        set_row_homogeneous(true);
    }
    else
    {
        set_row_homogeneous(false);
    }
}

void cx::cmn::ui::gtkmm3::Layout::SetColumnSpacingMode(
    cx::cmn::ui::ILayout::ColumnSpacingMode p_newMode)
{
    if(p_newMode == cx::cmn::ui::ILayout::ColumnSpacingMode::EQUAL)
    {
        set_column_homogeneous(true);
    }
    else
    {
        set_column_homogeneous(false);
    }
}

size_t cx::cmn::ui::gtkmm3::Layout::GetWidth() const
{
    IF_CONDITION_NOT_MET_DO(m_delegate, return 0u;);
    return m_delegate->GetWidth();
}

size_t cx::cmn::ui::gtkmm3::Layout::GetHeight() const
{
    IF_CONDITION_NOT_MET_DO(m_delegate, return 0u;);
    return m_delegate->GetHeight();
}

void  cx::cmn::ui::gtkmm3::Layout::SetEnabled(
    cx::cmn::ui::EnabledState p_enabled)
{
    IF_CONDITION_NOT_MET_DO(m_delegate, return;);
    m_delegate->SetEnabled(p_enabled);
}

void cx::cmn::ui::gtkmm3::Layout::SetMargins(const 
    cx::cmn::ui::Margins& p_newMarginSizes)
{
    IF_CONDITION_NOT_MET_DO(m_delegate, return;);
    m_delegate->SetMargins(p_newMarginSizes);
}

void cx::cmn::ui::gtkmm3::Layout::SetTooltip(
    const std::string& p_tooltipContents)
{
    IF_CONDITION_NOT_MET_DO(m_delegate, return;);
    m_delegate->SetTooltip(p_tooltipContents);
}

std::unique_ptr<cx::cmn::ui::ISignal<cx::cmn::ui::EventPropagation, cx::cmn::ui::KeyboardKeyPressedEvent>> cx::cmn::ui::gtkmm3::Layout::OnKeyPressed()
{
    IF_CONDITION_NOT_MET_DO(m_delegate, return nullptr;);
    return m_delegate->OnKeyPressed();
}
