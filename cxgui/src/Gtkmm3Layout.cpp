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

#include <gtkmm/widget.h>

#include <cxinv/assertion.h>

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

    m_gtkmm3Layout.attach(*gtkWidget, left, top, width, height );
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

    m_gtkmm3Layout.attach(*gtkGrid, left, top, width, height );
}

void cxgui::Gtkmm3Layout::Register(Gtk::Widget& p_gtkWidget,
                                   const cxgui::ILayout::RowDescriptor& p_row,
                                   const cxgui::ILayout::ColumnDescriptor& p_column)
{
    const int left = static_cast<int>(p_column.m_coordinate.Get());
    const int top = static_cast<int>(p_row.m_coordinate.Get());
    const int width = static_cast<int>(p_column.m_span.Get());
    const int height = static_cast<int>(p_row.m_span.Get());

    m_gtkmm3Layout.attach(p_gtkWidget, left, top, width, height );
}
