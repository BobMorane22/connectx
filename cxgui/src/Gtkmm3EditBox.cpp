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
 * @file Gtkmm3EditBox.cpp
 * @date 2024
 *
 *************************************************************************************************/

#include <cxinv/assertion.h>
#include <cxgui/Gtkmm3Connection.h>
#include <cxgui/Gtkmm3EditBox.h>

namespace
{

class Gtkmm3OnContentsChangedSignal : public cxgui::ISignal<void>
{

public:

    explicit Gtkmm3OnContentsChangedSignal(Gtk::Entry& p_entry)
    : m_entry{p_entry}
    {
    }

    [[nodiscard]] std::unique_ptr<cxgui::IConnection> Connect(const std::function<void()>& p_slot) override
    {
        sigc::connection gtkConnection = m_entry.signal_changed().connect(p_slot);
        IF_CONDITION_NOT_MET_DO(gtkConnection.connected(), return nullptr;);

        return std::make_unique<cxgui::Gtkmm3Connection>(gtkConnection);
    }

private:

    Gtk::Entry& m_entry;

};

} // namespace

void cxgui::Gtkmm3EditBox::SetDelegate(std::unique_ptr<IWidget> p_delegate)
{
    IF_PRECONDITION_NOT_MET_DO(p_delegate, return;);

    m_delegate = std::move(p_delegate);

    POSTCONDITION(m_delegate);
}

void cxgui::Gtkmm3EditBox::UpdateContents(const std::string& p_newContents)
{
    set_text(p_newContents);
}

std::string cxgui::Gtkmm3EditBox::GetContents() const
{
    return get_text();
}

std::unique_ptr<cxgui::ISignal<void>> cxgui::Gtkmm3EditBox::OnContentsChanged()
{
    return std::make_unique<Gtkmm3OnContentsChangedSignal>(*this);
}

size_t cxgui::Gtkmm3EditBox::GetWidth() const 
{
    IF_CONDITION_NOT_MET_DO(m_delegate, return 0u;);
    return m_delegate->GetWidth();
}

size_t cxgui::Gtkmm3EditBox::GetHeight() const 
{
    IF_CONDITION_NOT_MET_DO(m_delegate, return 0u;);
    return m_delegate->GetHeight();
}

void cxgui::Gtkmm3EditBox::SetEnabled(EnabledState p_enabled) 
{
    IF_CONDITION_NOT_MET_DO(m_delegate, return;);
    m_delegate->SetEnabled(p_enabled);
}

void cxgui::Gtkmm3EditBox::SetMargins(const Margins& p_newMarginSizes) 
{
    IF_CONDITION_NOT_MET_DO(m_delegate, return;);
    m_delegate->SetMargins(p_newMarginSizes);
}

void cxgui::Gtkmm3EditBox::SetTooltip(const std::string& p_tooltipContents)
{
    IF_CONDITION_NOT_MET_DO(m_delegate, return;);
    m_delegate->SetTooltip(p_tooltipContents);
}
