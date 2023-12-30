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
 * @file Gtkmm3Layout.h
 * @date 2023
 *
 *************************************************************************************************/

#ifndef GTKMM3CONTAINER_H_AB4FF2E5_DFE6_47C2_8EAC_5FC4FED66A24
#define GTKMM3CONTAINER_H_AB4FF2E5_DFE6_47C2_8EAC_5FC4FED66A24

#include <gtkmm/grid.h>

#include "ILayout.h"

namespace cxgui
{
    class IWidget;
}
 
namespace cxgui
{

/**********************************************************************************************//**
 * @brief Gtkmm 3 implementation for the `cxgui::ILayout` interface.
 *
 *************************************************************************************************/
class Gtkmm3Layout : public ILayout,
                     public Gtk::Grid
{

public:

    void SetDelegate(std::unique_ptr<IWidget> p_delegate);

    // cxgui::ILayout:
    void Register(IWidget& p_widget, const ILayout::RowDescriptor& p_row, const ILayout::ColumnDescriptor& p_column) override;
    void Register(Gtk::Widget& p_gtkWidget, const ILayout::RowDescriptor& p_row, const ILayout::ColumnDescriptor& p_column) override;
    void Unregister(IWidget& p_widget) override;
    void Unregister(Gtk::Widget& p_gtkWidget) override;
    [[nodiscard]] const IWidget* GetWidgetAtPosition(const cxmodel::Row& p_row, const cxmodel::Column& p_column) const override;
    [[nodiscard]] IWidget* GetWidgetAtPosition(const cxmodel::Row& p_row, const cxmodel::Column& p_column) override;
    void SetRowSpacingMode(RowSpacingMode p_newMode) override;
    void SetColumnSpacingMode(ColumnSpacingMode p_newMode) override;

    // cxgui::IWidget:
    [[nodiscard]] size_t GetWidth() const override;
    [[nodiscard]] size_t GetHeight() const override;
    void SetEnabled(EnabledState p_enabled) override;
    void SetMargins(const Margins& p_newMarginSizes) override;

private:

    std::unique_ptr<IWidget> m_delegate;

};

} // namespace cxgui

#endif // GTKMM3CONTAINER_H_AB4FF2E5_DFE6_47C2_8EAC_5FC4FED66A24
