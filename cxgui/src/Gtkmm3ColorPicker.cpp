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

#include <cxinv/assertion.h>
#include <cxgui/EventPropagation.h>
#include <cxgui/Gtkmm3ColorPicker.h>
#include <cxgui/Gtkmm3Connection.h>
#include <cxgui/KeyboardKeyPressedEvent.h>
#include <cxgui/Margins.h>

namespace
{

class Gtkmm3OnSelectionChangedSignal : public cx::cmn::ui::ISignal<void>
{

public:

    explicit Gtkmm3OnSelectionChangedSignal(Gtk::ComboBox& p_comboBox)
    : m_comboBox{p_comboBox}
    {
    }

    [[nodiscard]] std::unique_ptr<cx::cmn::ui::IConnection> Connect(const std::function<void()>& p_slot) override
    {
        sigc::connection gtkConnection = m_comboBox.signal_changed().connect(p_slot);
        IF_CONDITION_NOT_MET_DO(gtkConnection.connected(), return nullptr;);

        return std::make_unique<cx::cmn::ui::Gtkmm3Connection>(gtkConnection);
    }

private:

    Gtk::ComboBox& m_comboBox;

};

} // namespace

cx::cmn::ui::Gtkmm3ColorPicker::Record::Record()
{
    add(m_color);
}

cx::cmn::ui::Gtkmm3ColorPicker::Gtkmm3ColorPicker(const std::vector<Color>& p_colors)
{
    PRECONDITION(!p_colors.empty());

    m_treeModel = Gtk::ListStore::create(m_records);
    ASSERT(m_treeModel);

    set_model(m_treeModel);

    for(const auto& color : p_colors)
    {
        AddElement(color, true);
    }

    set_cell_data_func(m_renderer, sigc::mem_fun(*this, &cx::cmn::ui::Gtkmm3ColorPicker::OnRenderCell));
    pack_start(m_renderer);

    // Connect signal handler:
    signal_changed().connect([this](){OnComboChanged();});
}

void cx::cmn::ui::Gtkmm3ColorPicker::SetDelegate(std::unique_ptr<IWidget> p_delegate)
{
    IF_PRECONDITION_NOT_MET_DO(p_delegate, return;);

    m_delegate = std::move(p_delegate);

    POSTCONDITION(m_delegate);
}

cx::cmn::ui::Color cx::cmn::ui::Gtkmm3ColorPicker::GetCurrentSelection() const 
{
    cx::cmn::ui::Color currentColor{0, 0, 0, 0}; // Transparent...

    Gtk::TreeModel::iterator iter = get_active();

    if(INL_ASSERT(iter))
    {
        Gtk::TreeModel::Row row = *iter;

        if(INL_ASSERT(row))
        {
            // Get the data for the selected row, using our knowledge of the tree model:
            const Gdk::RGBA color = row[m_records.m_color];

            currentColor = cx::cmn::ui::Color{color.get_red_u(), color.get_green_u(), color.get_blue_u()};
        }
    }

    INVARIANT(bool(m_treeModel));

    return currentColor;
}

void cx::cmn::ui::Gtkmm3ColorPicker::SetCurrentSelection(const cx::cmn::ui::Color& p_color) 
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

std::unique_ptr<cx::cmn::ui::ISignal<void>> cx::cmn::ui::Gtkmm3ColorPicker::OnSelectionChanged()
{
    return std::make_unique<Gtkmm3OnSelectionChangedSignal>(*this);
}

size_t cx::cmn::ui::Gtkmm3ColorPicker::GetWidth() const 
{
    IF_CONDITION_NOT_MET_DO(m_delegate, return 0u;);
    return m_delegate->GetWidth();
}

size_t cx::cmn::ui::Gtkmm3ColorPicker::GetHeight() const 
{
    IF_CONDITION_NOT_MET_DO(m_delegate, return 0u;);
    return m_delegate->GetHeight();
}

void cx::cmn::ui::Gtkmm3ColorPicker::SetEnabled(EnabledState p_enabled) 
{
    IF_CONDITION_NOT_MET_DO(m_delegate, return;);
    m_delegate->SetEnabled(p_enabled);
}

void cx::cmn::ui::Gtkmm3ColorPicker::SetMargins(const Margins& p_newMarginSizes) 
{
    IF_CONDITION_NOT_MET_DO(m_delegate, return;);
    m_delegate->SetMargins(p_newMarginSizes);
}

void cx::cmn::ui::Gtkmm3ColorPicker::SetTooltip(const std::string& p_tooltipContents)
{
    IF_CONDITION_NOT_MET_DO(m_delegate, return;);
    m_delegate->SetTooltip(p_tooltipContents);
}

std::unique_ptr<cx::cmn::ui::ISignal<cx::cmn::ui::EventPropagation, cx::cmn::ui::KeyboardKeyPressedEvent>> cx::cmn::ui::Gtkmm3ColorPicker::OnKeyPressed()
{
    IF_CONDITION_NOT_MET_DO(m_delegate, return nullptr;);
    return m_delegate->OnKeyPressed();
}

void cx::cmn::ui::Gtkmm3ColorPicker::AddElement(const cx::cmn::ui::Color& p_color, bool p_setActive)
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

void cx::cmn::ui::Gtkmm3ColorPicker::OnRenderCell(const Gtk::TreeModel::const_iterator& iter)
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

void cx::cmn::ui::Gtkmm3ColorPicker::OnComboChanged()
{
    const cx::cmn::ui::Color currentColor = GetCurrentSelection();
    Gdk::RGBA currentGdkColor;
    currentGdkColor.set_rgba_u(currentColor.R(), currentColor.G(), currentColor.B());

    const Glib::ustring colorName = currentGdkColor.to_string();

    INVARIANT(bool(m_treeModel));
}
