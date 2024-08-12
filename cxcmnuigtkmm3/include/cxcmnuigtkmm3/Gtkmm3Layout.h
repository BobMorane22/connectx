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

#include <cxcmnui/ILayout.h>

namespace cx::cmn::ui
{
    class IWidget;
}
 
namespace cx::cmn::ui::gtkmm3
{

/**********************************************************************************************//**
 * @brief Gtkmm 3 implementation for the `cx::cmn::ui::gtkmm3::ILayout` interface.
 *
 *************************************************************************************************/
class Gtkmm3Layout : public cx::cmn::ui::ILayout,
                     public Gtk::Grid
{

public:

    /*******************************************************************************************//**
     * @brief Sets the delegate for widget common facilities.
     *
     * The delegate is reponsible to carry the implementation for generic `cx::cmn::ui::gtkmm3::IWidget` operations.
     * It is meant to avoid implementation duplication.
     *
     * @param p_delegate
     *      The widget delegate.
     *
     * @pre
     *      The widget delegate instance given as an argument is valid.
     * @post
     *      The registered widget delegate is valid.
     *
     **********************************************************************************************/
    void SetDelegate(std::unique_ptr<IWidget> p_delegate);

    // cx::cmn::ui::ILayout:
    void Register(IWidget& p_widget,
        const cx::cmn::ui::ILayout::RowDescriptor& p_row,
        const cx::cmn::ui::ILayout::ColumnDescriptor& p_column,
        const cx::cmn::ui::ILayout::Alignement& p_alignement = {}) override;
    void Register(Gtk::Widget& p_gtkWidget,
        const cx::cmn::ui::ILayout::RowDescriptor& p_row,
        const cx::cmn::ui::ILayout::ColumnDescriptor& p_column,
        const cx::cmn::ui::ILayout::Alignement& p_alignement = {}) override;
    void Unregister(
        cx::cmn::ui::IWidget& p_widget) override;
    void Unregister(
        Gtk::Widget& p_gtkWidget) override;
    [[nodiscard]] const IWidget* GetWidgetAtPosition(
        const cx::model::Row& p_row,
        const cx::model::Column& p_column) const override;
    [[nodiscard]] cx::cmn::ui::IWidget* GetWidgetAtPosition(
        const cx::model::Row& p_row,
        const cx::model::Column& p_column) override;
    void SetRowSpacingMode(
        cx::cmn::ui::ILayout::RowSpacingMode p_newMode) override;
    void SetColumnSpacingMode(
        cx::cmn::ui::ILayout::ColumnSpacingMode p_newMode) override;

    // cx::cmn::ui::IWidget:
    [[nodiscard]] size_t GetWidth() const override;
    [[nodiscard]] size_t GetHeight() const override;
    void SetEnabled(
        cx::cmn::ui::EnabledState p_enabled) override;
    void SetMargins(
        const cx::cmn::ui::Margins& p_newMarginSizes) override;
    void SetTooltip(
        const std::string& p_tooltipContents) override;
    [[nodiscard]] std::unique_ptr<cx::cmn::ui::ISignal<cx::cmn::ui::EventPropagation, cx::cmn::ui::KeyboardKeyPressedEvent>> OnKeyPressed() override;

private:

    std::unique_ptr<IWidget> m_delegate;

};

} // namespace cx::cmn::ui::gtkmm3

#endif // GTKMM3CONTAINER_H_AB4FF2E5_DFE6_47C2_8EAC_5FC4FED66A24
