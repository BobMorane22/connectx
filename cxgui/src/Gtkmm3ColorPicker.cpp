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
 * @file Gtkmm3ColorPicker.cpp
 * @date 2024
 *
 *************************************************************************************************/

#include "gtkmm/combobox.h"
#include <cxinv/assertion.h>
#include <cxgui/Gtkmm3ColorPicker.h>
#include <cxgui/Gtkmm3Connection.h>
#include <cxgui/Margins.h>

namespace
{

class Gtkmm3OnSelectionChangedSignal : public cxgui::ISignal<void>
{

public:

    explicit Gtkmm3OnSelectionChangedSignal(Gtk::ComboBox& p_comboBox)
    : m_comboBox{p_comboBox}
    {
    }

    [[nodiscard]] std::unique_ptr<cxgui::IConnection> Connect(const std::function<void()>& p_slot) override
    {
        sigc::connection gtkConnection = m_comboBox.signal_changed().connect(p_slot);
        IF_CONDITION_NOT_MET_DO(gtkConnection.connected(), return nullptr;);

        return std::make_unique<cxgui::Gtkmm3Connection>(gtkConnection);
    }

private:

    Gtk::ComboBox& m_comboBox;

};

} // namespace

cxgui::Gtkmm3ColorPicker::Record::Record()
{
    add(m_color);
}

cxgui::Gtkmm3ColorPicker::Gtkmm3ColorPicker(const std::vector<Color>& p_colors)
{
    PRECONDITION(!p_colors.empty());

    m_treeModel = Gtk::ListStore::create(m_records);
    ASSERT(m_treeModel);

    set_model(m_treeModel);

    for(const auto& color : p_colors)
    {
        AddElement(color, true);
    }

    set_cell_data_func(m_renderer, sigc::mem_fun(*this, &cxgui::Gtkmm3ColorPicker::OnRenderCell));
    pack_start(m_renderer);

    // Connect signal handler:
    signal_changed().connect([this](){OnComboChanged();});
}

void cxgui::Gtkmm3ColorPicker::SetDelegate(std::unique_ptr<IWidget> p_delegate)
{
    IF_PRECONDITION_NOT_MET_DO(p_delegate, return;);

    m_delegate = std::move(p_delegate);

    POSTCONDITION(m_delegate);
}

cxgui::Color cxgui::Gtkmm3ColorPicker::GetCurrentSelection() const 
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

void cxgui::Gtkmm3ColorPicker::SetCurrentSelection(const cxgui::Color& p_color) 
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

std::unique_ptr<cxgui::ISignal<void>> cxgui::Gtkmm3ColorPicker::OnSelectionChanged()
{
    return std::make_unique<Gtkmm3OnSelectionChangedSignal>(*this);
}

size_t cxgui::Gtkmm3ColorPicker::GetWidth() const 
{
    IF_CONDITION_NOT_MET_DO(m_delegate, return 0u;);
    return m_delegate->GetWidth();
}

size_t cxgui::Gtkmm3ColorPicker::GetHeight() const 
{
    IF_CONDITION_NOT_MET_DO(m_delegate, return 0u;);
    return m_delegate->GetHeight();
}

void cxgui::Gtkmm3ColorPicker::SetEnabled(EnabledState p_enabled) 
{
    IF_CONDITION_NOT_MET_DO(m_delegate, return;);
    m_delegate->SetEnabled(p_enabled);
}

void cxgui::Gtkmm3ColorPicker::SetMargins(const Margins& p_newMarginSizes) 
{
    IF_CONDITION_NOT_MET_DO(m_delegate, return;);
    m_delegate->SetMargins(p_newMarginSizes);
}

void cxgui::Gtkmm3ColorPicker::SetTooltip(const std::string& p_tooltipContents)
{
    IF_CONDITION_NOT_MET_DO(m_delegate, return;);
    m_delegate->SetTooltip(p_tooltipContents);
}

void cxgui::Gtkmm3ColorPicker::AddElement(const cxgui::Color& p_color, bool p_setActive)
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

void cxgui::Gtkmm3ColorPicker::OnRenderCell(const Gtk::TreeModel::const_iterator& iter)
{
    auto row = *iter;
    const Gdk::RGBA color = row[m_records.m_color];

    // Update cell color:
    m_renderer.property_background() = color.to_string();

    // Fix cell width (in number of characters). Otherwise the combobox, which
    // has no text, is too narrow and looks bad.
    m_renderer.property_width_chars() = 6;

    INVARIANT(bool(m_treeModel));
}

void cxgui::Gtkmm3ColorPicker::OnComboChanged()
{
    const cxgui::Color currentColor = GetCurrentSelection();
    Gdk::RGBA currentGdkColor;
    currentGdkColor.set_rgba_u(currentColor.R(), currentColor.G(), currentColor.B());

    const Glib::ustring colorName = currentGdkColor.to_string();

    INVARIANT(bool(m_treeModel));
}
