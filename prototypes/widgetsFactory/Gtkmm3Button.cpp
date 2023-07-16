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
 * @file Gtkmm3Button.cpp
 * @date 2023
 *
 *************************************************************************************************/

#include "Gtkmm3Button.h"
#include "Gtkmm3Signal.h"

namespace
{

class Gtkmm3OnClickedSignal : public ISignal<void>
{

public:

    Gtkmm3OnClickedSignal(Gtk::Button& p_clickedButton)
    : m_clickedButton{p_clickedButton}
    {
    }

    std::unique_ptr<IConnection> Connect(const std::function<void()>& p_slot) override
    {
        sigc::connection gtkConnection = m_clickedButton.signal_clicked().connect(p_slot);

        return std::make_unique<Gtkmm3Connection>(gtkConnection);
    }

private:

    Gtk::Button& m_clickedButton;
};

}

void Gtkmm3Button::SetText(const std::string& p_text)
{
    set_label(p_text);
}

std::unique_ptr<ISignal<void>> Gtkmm3Button::OnClicked()
{
    return std::make_unique<Gtkmm3OnClickedSignal>(*this);
}
