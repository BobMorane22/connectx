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
 * @file ColorComboBox.cpp
 * @date 2020
 *
 *************************************************************************************************/

#include <ColorComboBox.h>

#include <cxinv/include/assertion.h>

cxgui::ColorComboBox::Record::Record()
{
    add(m_color);
}

cxgui::ColorComboBox::ColorComboBox()
{
    m_treeModel = Gtk::ListStore::create(m_records);
    ASSERT(bool(m_treeModel));

    set_model(m_treeModel);

    AddElement(cxgui::Color::MakePredefined(cxgui::Color::Predefined::RED), true);
    AddElement(cxgui::Color::MakePredefined(cxgui::Color::Predefined::GREEN), true);
    AddElement(cxgui::Color::MakePredefined(cxgui::Color::Predefined::BLUE), true);

    set_cell_data_func(m_renderer, sigc::mem_fun(*this, &cxgui::ColorComboBox::OnRenderCell));
    pack_start(m_renderer);

    //Connect signal handler:
    signal_changed().connect([this](){OnComboChanged();});

    INVARIANT(bool(m_treeModel));
}

cxgui::Color cxgui::ColorComboBox::GetCurrentSelection() const
{
    cxgui::Color currentColor{0, 0, 0, 0}; // Transparent...

    Gtk::TreeModel::iterator iter = get_active();

    if(ASSERT(iter))
    {
        Gtk::TreeModel::Row row = *iter;

        if(ASSERT(row))
        {
            // Get the data for the selected row, using our knowledge of the tree model:
            const Gdk::Color color = row[m_records.m_color];

            currentColor = cxgui::Color{color.get_red(), color.get_green(), color.get_blue()};
        }
    }

    INVARIANT(bool(m_treeModel));

    return currentColor;
}

void cxgui::ColorComboBox::SetCurrentSelection(const cxgui::Color& p_color)
{
    Gtk::TreeModel::iterator iter = get_active();

    if(ASSERT(iter))
    {
        Gtk::TreeModel::Row row = *iter;

        if(ASSERT(row))
        {
            Gdk::Color newColor;
            newColor.set_rgb(p_color.R(), p_color.G(), p_color.B());

            // Set the data for the selected row, using our knowledge of the tree model:
            row[m_records.m_color] = newColor;
        }
    }
}

void cxgui::ColorComboBox::AddElement(const cxgui::Color& p_color, bool p_setActive)
{
    if(!PRECONDITION(bool(m_treeModel)))
    {
        return;
    }

    Gtk::TreeModel::Row row = *(m_treeModel->append());

    Gdk::Color color;
    color.set_rgb(p_color.R(), p_color.G(), p_color.B());

    row[m_records.m_color] = Gdk::Color(color);

    if(p_setActive)
    {
        set_active(row);
    }

    INVARIANT(bool(m_treeModel));
}

void cxgui::ColorComboBox::OnRenderCell(const Gtk::TreeModel::const_iterator& iter)
{
    auto row = *iter;
    const Gdk::Color color = row[m_records.m_color];

    //Change other cell renderer properties too:
    m_renderer.property_background() = color.to_string();

    INVARIANT(bool(m_treeModel));
}

void cxgui::ColorComboBox::OnComboChanged()
{
    const cxgui::Color currentColor = GetCurrentSelection();
    Gdk::Color currentGdkColor;
    currentGdkColor.set_rgb(currentColor.R(), currentColor.G(), currentColor.B());

    const Glib::ustring colorName = currentGdkColor.to_string();

    INVARIANT(bool(m_treeModel));
}
