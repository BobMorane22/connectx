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
#include <cxgui/Margins.h>

namespace
{

[[nodiscard]] Gtk::Align ToGtk(cxgui::ILayout::VerticalAlignement p_alignement)
{
    switch(p_alignement)
    {
        case cxgui::ILayout::VerticalAlignement::TOP:    return Gtk::Align::ALIGN_START;
        case cxgui::ILayout::VerticalAlignement::CENTER: return Gtk::Align::ALIGN_CENTER;
        case cxgui::ILayout::VerticalAlignement::BOTTOM: return Gtk::Align::ALIGN_END;
        case cxgui::ILayout::VerticalAlignement::FILL:   return Gtk::Align::ALIGN_FILL;
    }

    ASSERT_ERROR_MSG("Unknown alignement value");
    return Gtk::Align::ALIGN_FILL;
}

[[nodiscard]] Gtk::Align ToGtk(cxgui::ILayout::HorizontalAlignement p_alignement)
{
    switch(p_alignement)
    {
        case cxgui::ILayout::HorizontalAlignement::LEFT:   return Gtk::Align::ALIGN_START;
        case cxgui::ILayout::HorizontalAlignement::CENTER: return Gtk::Align::ALIGN_CENTER;
        case cxgui::ILayout::HorizontalAlignement::RIGHT:  return Gtk::Align::ALIGN_END;
        case cxgui::ILayout::HorizontalAlignement::FILL:   return Gtk::Align::ALIGN_FILL;
    }

    ASSERT_ERROR_MSG("Unknown alignement value");
    return Gtk::Align::ALIGN_FILL;
}

} // namespace

void cxgui::Gtkmm3Layout::SetDelegate(std::unique_ptr<IWidget> p_delegate)
{
    IF_PRECONDITION_NOT_MET_DO(p_delegate, return;);

    m_delegate = std::move(p_delegate);

    POSTCONDITION(m_delegate);
}

void cxgui::Gtkmm3Layout::Register(cxgui::IWidget& p_widget,
                                   const cxgui::ILayout::RowDescriptor& p_row,
                                   const cxgui::ILayout::ColumnDescriptor& p_column,
                                   const ILayout::Alignement& p_alignement)
{
    const int left = static_cast<int>(p_column.m_coordinate.Get());
    const int top = static_cast<int>(p_row.m_coordinate.Get());
    const int width = static_cast<int>(p_column.m_span.Get());
    const int height = static_cast<int>(p_row.m_span.Get());

    auto* gtkWidget = dynamic_cast<Gtk::Widget*>(&p_widget);
    ASSERT(gtkWidget);

    gtkWidget->set_valign(ToGtk(p_alignement.m_vertical));
    gtkWidget->set_halign(ToGtk(p_alignement.m_horizontal));

    gtkWidget->set_hexpand(true);
    gtkWidget->set_vexpand(true);

    attach(*gtkWidget, left, top, width, height );
}

void cxgui::Gtkmm3Layout::Register(Gtk::Widget& p_gtkWidget,
                                   const cxgui::ILayout::RowDescriptor& p_row,
                                   const cxgui::ILayout::ColumnDescriptor& p_column,
                                   const ILayout::Alignement& p_alignement)
{
    const int left = static_cast<int>(p_column.m_coordinate.Get());
    const int top = static_cast<int>(p_row.m_coordinate.Get());
    const int width = static_cast<int>(p_column.m_span.Get());
    const int height = static_cast<int>(p_row.m_span.Get());

    p_gtkWidget.set_valign(ToGtk(p_alignement.m_vertical));
    p_gtkWidget.set_halign(ToGtk(p_alignement.m_horizontal));

    p_gtkWidget.set_hexpand(true);
    p_gtkWidget.set_vexpand(true);

    attach(p_gtkWidget, left, top, width, height );
}

void cxgui::Gtkmm3Layout::Unregister(cxgui::IWidget& p_widget)
{
    auto* gtkWidget = dynamic_cast<Gtk::Widget*>(&p_widget);
    ASSERT(gtkWidget);

    remove(*gtkWidget);
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

size_t cxgui::Gtkmm3Layout::GetWidth() const
{
    IF_CONDITION_NOT_MET_DO(m_delegate, return 0u;);
    return m_delegate->GetWidth();
}

size_t cxgui::Gtkmm3Layout::GetHeight() const
{
    IF_CONDITION_NOT_MET_DO(m_delegate, return 0u;);
    return m_delegate->GetHeight();
}

void  cxgui::Gtkmm3Layout::SetEnabled(EnabledState p_enabled)
{
    IF_CONDITION_NOT_MET_DO(m_delegate, return;);
    m_delegate->SetEnabled(p_enabled);
}

void cxgui::Gtkmm3Layout::SetMargins(const Margins& p_newMarginSizes)
{
    IF_CONDITION_NOT_MET_DO(m_delegate, return;);
    m_delegate->SetMargins(p_newMarginSizes);
}

void cxgui::Gtkmm3Layout::SetTooltip(const std::string& p_tooltipContents)
{
    IF_CONDITION_NOT_MET_DO(m_delegate, return;);
    m_delegate->SetTooltip(p_tooltipContents);
}
