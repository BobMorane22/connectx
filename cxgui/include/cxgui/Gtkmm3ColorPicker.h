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
 * @file Gtkmm3ColorPicker.h
 * @date 2024
 *
 *************************************************************************************************/

#ifndef GTKMM3COLORPICKER_H_1EEA8946_AD91_4032_B0F1_53AC7C01CA2D
#define GTKMM3COLORPICKER_H_1EEA8946_AD91_4032_B0F1_53AC7C01CA2D

#include <vector>

#include <gtkmm/combobox.h>
#include <gtkmm/liststore.h>

#include <cxgui/IColorPicker.h>

namespace cxgui
{

/**********************************************************************************************//**
 * @brief Gtkmm 3 implementation of a color picker.
 *
 * This implementation lets the user pick a color from a vertical list of colors. Since Connect X
 * only supports a limited number of colors, this is ideal.
 *
 * @invariant Thw treeview model is valid.
 *
 *************************************************************************************************/
class Gtkmm3ColorPicker : public IColorPicker,
                          public Gtk::ComboBox
{

public:

    /******************************************************************************************//**
     * @brief Constructor.
     *
     * Constructs a combo box from a list of colors. The listed colors become available options
     * in the combobox.
     *
     * @param p_colors
     *      List of colors to display in the combo box.
     *
     * @pre The list of colors is not empty.
     *
     *********************************************************************************************/
    explicit Gtkmm3ColorPicker(const std::vector<Color>& p_colors);

    /******************************************************************************************//**
     * @brief Sets the delegate for widget common facilities.
     *
     * The delegate is reponsible to carry the implementation for generic `cxgui::IWidget` operations.
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
     *********************************************************************************************/
    void SetDelegate(std::unique_ptr<IWidget> p_delegate);

    // cxgui::IColorPicker:
    [[nodiscard]] Color GetCurrentSelection() const override;
    void SetCurrentSelection(const cxgui::Color& p_color) override;
    [[nodiscard]] std::unique_ptr<ISignal<void>> OnSelectionChanged() override;

    // cxgui::IWidget:
    [[nodiscard]] size_t GetWidth() const override;
    [[nodiscard]] size_t GetHeight() const override;
    void SetEnabled(EnabledState p_enabled) override;
    void SetMargins(const Margins& p_newMarginSizes) override;
    void SetTooltip(const std::string& p_tooltipContents) override;

private:

    void AddElement(const cxgui::Color& p_color, bool p_setActive);
    void OnRenderCell(const Gtk::TreeModel::const_iterator& iter);
    void OnComboChanged();

    struct Record : public Gtk::TreeModel::ColumnRecord
    {

    public:

        Record();

        Gtk::TreeModelColumn<Gdk::RGBA> m_color;
    };

    Record m_records;

    Gtk::CellRendererText m_renderer;
    Glib::RefPtr<Gtk::ListStore> m_treeModel;

    std::unique_ptr<IWidget> m_delegate;

};

} // namespace cxgui

#endif // GTKMM3COLORPICKER_H_1EEA8946_AD91_4032_B0F1_53AC7C01CA2D
