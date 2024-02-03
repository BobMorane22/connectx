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
 * @date 2023
 *
 *************************************************************************************************/

#include "Gtkmm3EditBox.h"
#include "Gtkmm3Signal.h"

namespace
{

class Gtkmm3OnTextInsertSignal : public ISignal<void, const std::string&>
{

public:

    explicit Gtkmm3OnTextInsertSignal(Gtk::Entry& p_insertedToEntry)
    : m_insertedToEntry{p_insertedToEntry}
    {
    }

    std::unique_ptr<IConnection> Connect(const std::function<void(const std::string&)>& p_slot) override
    {
        sigc::connection gtkConnection = m_insertedToEntry.signal_insert_at_cursor().connect(p_slot);

        return std::make_unique<Gtkmm3Connection>(gtkConnection);
    }

private:

    Gtk::Entry& m_insertedToEntry;

};

} // namespace

void Gtkmm3EditBox::Show()
{
    show();
}

void Gtkmm3EditBox::SetText(const std::string& p_text)
{
    set_text(p_text);
}

std::string Gtkmm3EditBox::GetText() const
{
    return get_text();
}

std::unique_ptr<ISignal<void, const std::string&>> Gtkmm3EditBox::OnTextInsert()
{
    return std::make_unique<Gtkmm3OnTextInsertSignal>(*this);
}
