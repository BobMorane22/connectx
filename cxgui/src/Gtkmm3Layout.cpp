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
#include <cxstd/helpers.h>

#include <cxgui/Gtkmm3Layout.h>
#include <cxgui/IWidget.h>

void cxgui::Gtkmm3Layout::Register(cxgui::IWidget& p_widget,
                                   const cxgui::ILayout::RowDescriptor& p_row,
                                   const cxgui::ILayout::ColumnDescriptor& p_column)
{
    const int left = static_cast<int>(p_column.m_coordinate.Get());
    const int top = static_cast<int>(p_row.m_coordinate.Get());
    const int width = static_cast<int>(p_column.m_span.Get());
    const int height = static_cast<int>(p_row.m_span.Get());

    auto* gtkWidget = dynamic_cast<Gtk::Widget*>(&p_widget);
    ASSERT(gtkWidget);

    attach(*gtkWidget, left, top, width, height );
}

void cxgui::Gtkmm3Layout::Register(cxgui::ILayout& p_layout,
                                   const cxgui::ILayout::RowDescriptor& p_row,
                                   const cxgui::ILayout::ColumnDescriptor& p_column)
{
    const int left = static_cast<int>(p_column.m_coordinate.Get());
    const int top = static_cast<int>(p_row.m_coordinate.Get());
    const int width = static_cast<int>(p_column.m_span.Get());
    const int height = static_cast<int>(p_row.m_span.Get());

    auto* gtkGrid = dynamic_cast<Gtk::Grid*>(&p_layout);
    ASSERT(gtkGrid);

    attach(*gtkGrid, left, top, width, height );
}

void cxgui::Gtkmm3Layout::Register(Gtk::Widget& p_gtkWidget,
                                   const cxgui::ILayout::RowDescriptor& p_row,
                                   const cxgui::ILayout::ColumnDescriptor& p_column)
{
    const int left = static_cast<int>(p_column.m_coordinate.Get());
    const int top = static_cast<int>(p_row.m_coordinate.Get());
    const int width = static_cast<int>(p_column.m_span.Get());
    const int height = static_cast<int>(p_row.m_span.Get());

    attach(p_gtkWidget, left, top, width, height );
}

void cxgui::Gtkmm3Layout::Unregister(cxgui::IWidget& p_widget)
{
    auto* gtkWidget = dynamic_cast<Gtk::Widget*>(&p_widget);
    ASSERT(gtkWidget);

    remove(*gtkWidget);
}

void cxgui::Gtkmm3Layout::Unregister(cxgui::ILayout& p_layout)
{
    auto* gtkGrid = dynamic_cast<Gtk::Grid*>(&p_layout);
    ASSERT(gtkGrid);

    remove(*gtkGrid);
}

void cxgui::Gtkmm3Layout::Unregister(Gtk::Widget& p_gtkWidget)
{
    remove(p_gtkWidget);
}

const cxgui::IWidget* cxgui::Gtkmm3Layout::GetWidgetAtPosition(const cxmodel::Row& p_row, const cxmodel::Column& p_column) const
{
    const int left = static_cast<int>(p_column.Get());
    const int top = static_cast<int>(p_row.Get());

    const Gtk::Widget* gtkWidget = get_child_at(left, top);
    RETURN_IF(!gtkWidget, nullptr);

    const auto* widget = dynamic_cast<const cxgui::IWidget*>(gtkWidget);
    IF_CONDITION_NOT_MET_DO(widget, return nullptr;);

    return widget;
}

cxgui::IWidget* cxgui::Gtkmm3Layout::GetWidgetAtPosition(const cxmodel::Row& p_row, const cxmodel::Column& p_column)
{
    return const_cast<cxgui::IWidget*>(const_cast<const cxgui::Gtkmm3Layout*>(this)->GetWidgetAtPosition(p_row, p_column));
}

const cxgui::ILayout* cxgui::Gtkmm3Layout::GetLayoutAtPosition(const cxmodel::Row& p_row, const cxmodel::Column& p_column) const
{
    const int left = static_cast<int>(p_column.Get());
    const int top = static_cast<int>(p_row.Get());

    const Gtk::Widget* gtkLayout = get_child_at(left, top);
    RETURN_IF(!gtkLayout, nullptr);

    const auto* layout = dynamic_cast<const cxgui::ILayout*>(gtkLayout);
    IF_CONDITION_NOT_MET_DO(layout, return nullptr;);

    return layout;
}

cxgui::ILayout* cxgui::Gtkmm3Layout::GetLayoutAtPosition(const cxmodel::Row& p_row, const cxmodel::Column& p_column)
{
    return const_cast<cxgui::ILayout*>(const_cast<const cxgui::Gtkmm3Layout*>(this)->GetLayoutAtPosition(p_row, p_column));
}

void cxgui::Gtkmm3Layout::SetMargins(const Margins& p_newMarginSizes)
{
    const int start = p_newMarginSizes.m_left.Get();
    const int end = p_newMarginSizes.m_right.Get();
    const int top = p_newMarginSizes.m_top.Get();
    const int bottom = p_newMarginSizes.m_bottom.Get();

    set_margin_start(start);
    set_margin_end(end);
    set_margin_top(top);
    set_margin_bottom(bottom);
}

void cxgui::Gtkmm3Layout::SetRowSpacingMode(cxgui::ILayout::RowSpacingMode p_newMode)
{
    if(p_newMode == cxgui::ILayout::RowSpacingMode::EQUAL)
    {
        set_row_homogeneous(true);
    }
    else
    {
        set_row_homogeneous(false);
    }
}

void cxgui::Gtkmm3Layout::SetColumnSpacingMode(cxgui::ILayout::ColumnSpacingMode p_newMode)
{
    if(p_newMode == cxgui::ILayout::ColumnSpacingMode::EQUAL)
    {
        set_column_homogeneous(true);
    }
    else
    {
        set_column_homogeneous(false);
    }
}
