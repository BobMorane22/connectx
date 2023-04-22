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

#include <cxinv/assertion.h>
#include <cxgui/ColorComboBox.h>

cxgui::ColorComboBox::Record::Record()
{
    add(m_color);
}

cxgui::ColorComboBox::ColorComboBox(const std::vector<cxgui::Color>& p_colors)
{
    PRECONDITION(p_colors.size() != 0u);

    m_treeModel = Gtk::ListStore::create(m_records);
    ASSERT(m_treeModel);

    set_model(m_treeModel);

    for(const auto& color : p_colors)
    {
        AddElement(color, true);
    }

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

    if(INL_ASSERT(iter))
    {
        Gtk::TreeModel::Row row = *iter;

        if(INL_ASSERT(row))
        {
            // Get the data for the selected row, using our knowledge of the tree model:
            const Gdk::RGBA color = row[m_records.m_color];

            currentColor = cxgui::Color{color.get_red_u(), color.get_green_u(), color.get_blue_u()};
        }
    }

    INVARIANT(bool(m_treeModel));

    return currentColor;
}

void cxgui::ColorComboBox::SetCurrentSelection(const cxgui::Color& p_color)
{
    IF_PRECONDITION_NOT_MET_DO(bool(m_treeModel), return;);

    Gdk::RGBA newColor;
    newColor.set_rgba_u(p_color.R(), p_color.G(), p_color.B());

    Gtk::TreeModel::Children rows = m_treeModel->children();
    IF_CONDITION_NOT_MET_DO(rows, return;);

    for(auto row : m_treeModel->children())
    {
        IF_CONDITION_NOT_MET_DO(row, return;);
        if((*row)[m_records.m_color] == newColor)
        {
            set_active(row);
            break;
        }
    }
}

void cxgui::ColorComboBox::AddElement(const cxgui::Color& p_color, bool p_setActive)
{
    IF_PRECONDITION_NOT_MET_DO(bool(m_treeModel), return;);

    Gtk::TreeModel::Row row = *(m_treeModel->append());

    Gdk::RGBA color;
    color.set_rgba_u(p_color.R(), p_color.G(), p_color.B());

    row[m_records.m_color] = Gdk::RGBA(color);

    if(p_setActive)
    {
        set_active(row);
    }

    INVARIANT(bool(m_treeModel));
}

void cxgui::ColorComboBox::OnRenderCell(const Gtk::TreeModel::const_iterator& iter)
{
    auto row = *iter;
    const Gdk::RGBA color = row[m_records.m_color];

    // Change other cell renderer properties too:
    m_renderer.property_background() = color.to_string();

    INVARIANT(bool(m_treeModel));
}

void cxgui::ColorComboBox::OnComboChanged()
{
    const cxgui::Color currentColor = GetCurrentSelection();
    Gdk::RGBA currentGdkColor;
    currentGdkColor.set_rgba_u(currentColor.R(), currentColor.G(), currentColor.B());

    const Glib::ustring colorName = currentGdkColor.to_string();

    INVARIANT(bool(m_treeModel));
}
