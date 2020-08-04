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
 * @file ColorComboBox.h
 * @date 2020
 *
 *************************************************************************************************/

#ifndef COLORCOMBOBOX_H_5E88E30A_0D5A_436B_A526_C17215FEE819
#define COLORCOMBOBOX_H_5E88E30A_0D5A_436B_A526_C17215FEE819

#include <gtkmm/combobox.h>
#include <gtkmm/liststore.h>

#include "common.h"

namespace cxgui
{

/*********************************************************************************************//**
 * @brief Combo box box for picking a color.
 *
 * Combo box that lets a user pick a color visually (i.e. not by color name).
 *
 ************************************************************************************************/
class ColorComboBox : public Gtk::ComboBox
{

public:

    /******************************************************************************************//**
     * @brief Constructor.
     *
     ********************************************************************************************/
    ColorComboBox();

    /******************************************************************************************//**
     * @brief Retrieves the current user selection.
     *
     * @return The color currently visible in the combo box.
     *
     ********************************************************************************************/
    Color GetCurrentSelection() const;

private:

    void AddElement(const cxgui::Color& p_color, bool p_setActive);
    void OnRenderCell(const Gtk::TreeModel::const_iterator& iter);
    void OnComboChanged();

    //
    struct Record : public Gtk::TreeModel::ColumnRecord
    {

    public:

        Record();

        Gtk::TreeModelColumn<Gdk::Color> m_color;
    };

    Record m_records;

    Gtk::CellRendererText m_renderer;
    Glib::RefPtr<Gtk::ListStore> m_treeModel;

};

} // namespace cxgui

#endif // COLORCOMBOBOX_H_5E88E30A_0D5A_436B_A526_C17215FEE819
