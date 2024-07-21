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
 * @file Gtkmm3Layout.cpp
 * @date 2023
 *
 *************************************************************************************************/

#include <cxinv/assertion.h>
#include <cxcmn/helpers.h>
#include <cxgui/EventPropagation.h>
#include <cxgui/gtkmmConversions.h>
#include <cxgui/Gtkmm3Layout.h>
#include <cxgui/IWidget.h>
#include <cxgui/KeyboardKeyPressedEvent.h>
#include <cxgui/Margins.h>

void cx::gui::Gtkmm3Layout::SetDelegate(std::unique_ptr<IWidget> p_delegate)
{
    IF_PRECONDITION_NOT_MET_DO(p_delegate, return;);

    m_delegate = std::move(p_delegate);

    POSTCONDITION(m_delegate);
}

void cx::gui::Gtkmm3Layout::Register(cx::gui::IWidget& p_widget,
                                   const cx::gui::ILayout::RowDescriptor& p_row,
                                   const cx::gui::ILayout::ColumnDescriptor& p_column,
                                   const ILayout::Alignement& p_alignement)
{
    const int left = static_cast<int>(p_column.m_coordinate.Get());
    const int top = static_cast<int>(p_row.m_coordinate.Get());
    const int width = static_cast<int>(p_column.m_span.Get());
    const int height = static_cast<int>(p_row.m_span.Get());

    auto* gtkWidget = dynamic_cast<Gtk::Widget*>(&p_widget);
    ASSERT(gtkWidget);

    const auto verticalAlignementConversion = cx::gui::ToGtk<Gtk::Align>(p_alignement.m_vertical);
    gtkWidget->set_valign(verticalAlignementConversion.value_or(Gtk::ALIGN_FILL));
    const auto horizontalAlignementConversion = cx::gui::ToGtk<Gtk::Align>(p_alignement.m_horizontal);
    gtkWidget->set_halign(horizontalAlignementConversion.value_or(Gtk::ALIGN_FILL));

    gtkWidget->set_hexpand(true);
    gtkWidget->set_vexpand(true);

    attach(*gtkWidget, left, top, width, height );
}

void cx::gui::Gtkmm3Layout::Register(Gtk::Widget& p_gtkWidget,
                                   const cx::gui::ILayout::RowDescriptor& p_row,
                                   const cx::gui::ILayout::ColumnDescriptor& p_column,
                                   const ILayout::Alignement& p_alignement)
{
    const int left = static_cast<int>(p_column.m_coordinate.Get());
    const int top = static_cast<int>(p_row.m_coordinate.Get());
    const int width = static_cast<int>(p_column.m_span.Get());
    const int height = static_cast<int>(p_row.m_span.Get());

    const auto verticalAlignementConversion = cx::gui::ToGtk<Gtk::Align>(p_alignement.m_vertical);
    p_gtkWidget.set_valign(verticalAlignementConversion.value_or(Gtk::ALIGN_FILL));
    const auto horizontalAlignementConversion = cx::gui::ToGtk<Gtk::Align>(p_alignement.m_horizontal);
    p_gtkWidget.set_halign(horizontalAlignementConversion.value_or(Gtk::ALIGN_FILL));

    p_gtkWidget.set_hexpand(true);
    p_gtkWidget.set_vexpand(true);

    attach(p_gtkWidget, left, top, width, height );
}

void cx::gui::Gtkmm3Layout::Unregister(cx::gui::IWidget& p_widget)
{
    auto* gtkWidget = dynamic_cast<Gtk::Widget*>(&p_widget);
    ASSERT(gtkWidget);

    remove(*gtkWidget);
}

void cx::gui::Gtkmm3Layout::Unregister(Gtk::Widget& p_gtkWidget)
{
    remove(p_gtkWidget);
}

const cx::gui::IWidget* cx::gui::Gtkmm3Layout::GetWidgetAtPosition(const cx::model::Row& p_row, const cx::model::Column& p_column) const
{
    const int left = static_cast<int>(p_column.Get());
    const int top = static_cast<int>(p_row.Get());

    const Gtk::Widget* gtkWidget = get_child_at(left, top);
    RETURN_IF(!gtkWidget, nullptr);

    const auto* widget = dynamic_cast<const cx::gui::IWidget*>(gtkWidget);
    IF_CONDITION_NOT_MET_DO(widget, return nullptr;);

    return widget;
}

cx::gui::IWidget* cx::gui::Gtkmm3Layout::GetWidgetAtPosition(const cx::model::Row& p_row, const cx::model::Column& p_column)
{
    return const_cast<cx::gui::IWidget*>(const_cast<const cx::gui::Gtkmm3Layout*>(this)->GetWidgetAtPosition(p_row, p_column));
}

void cx::gui::Gtkmm3Layout::SetRowSpacingMode(cx::gui::ILayout::RowSpacingMode p_newMode)
{
    if(p_newMode == cx::gui::ILayout::RowSpacingMode::EQUAL)
    {
        set_row_homogeneous(true);
    }
    else
    {
        set_row_homogeneous(false);
    }
}

void cx::gui::Gtkmm3Layout::SetColumnSpacingMode(cx::gui::ILayout::ColumnSpacingMode p_newMode)
{
    if(p_newMode == cx::gui::ILayout::ColumnSpacingMode::EQUAL)
    {
        set_column_homogeneous(true);
    }
    else
    {
        set_column_homogeneous(false);
    }
}

size_t cx::gui::Gtkmm3Layout::GetWidth() const
{
    IF_CONDITION_NOT_MET_DO(m_delegate, return 0u;);
    return m_delegate->GetWidth();
}

size_t cx::gui::Gtkmm3Layout::GetHeight() const
{
    IF_CONDITION_NOT_MET_DO(m_delegate, return 0u;);
    return m_delegate->GetHeight();
}

void  cx::gui::Gtkmm3Layout::SetEnabled(EnabledState p_enabled)
{
    IF_CONDITION_NOT_MET_DO(m_delegate, return;);
    m_delegate->SetEnabled(p_enabled);
}

void cx::gui::Gtkmm3Layout::SetMargins(const Margins& p_newMarginSizes)
{
    IF_CONDITION_NOT_MET_DO(m_delegate, return;);
    m_delegate->SetMargins(p_newMarginSizes);
}

void cx::gui::Gtkmm3Layout::SetTooltip(const std::string& p_tooltipContents)
{
    IF_CONDITION_NOT_MET_DO(m_delegate, return;);
    m_delegate->SetTooltip(p_tooltipContents);
}

std::unique_ptr<cx::gui::ISignal<cx::gui::EventPropagation, cx::gui::KeyboardKeyPressedEvent>> cx::gui::Gtkmm3Layout::OnKeyPressed()
{
    IF_CONDITION_NOT_MET_DO(m_delegate, return nullptr;);
    return m_delegate->OnKeyPressed();
}
