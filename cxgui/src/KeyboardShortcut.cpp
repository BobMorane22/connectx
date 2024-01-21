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
 * @file KeyboardShortcut.cpp
 * @date 2024
 *
 *************************************************************************************************/

#include <cxinv/assertion.h>
#include <cxgui/KeyboardShortcut.h>

cxgui::KeyboardShortcut::KeyboardShortcut(cxgui::Key p_first)
: m_first{p_first}
, m_second{std::nullopt}
{
}

cxgui::KeyboardShortcut::KeyboardShortcut(const cxgui::KeyboardShortcut& p_shortcut)
{
    m_first = p_shortcut.m_first;
    m_second = p_shortcut.m_second;
}

[[nodiscard]] cxgui::KeyboardShortcut cxgui::operator+(cxgui::Key p_first, cxgui::Key p_second)
{
    PRECONDITION(p_first != p_second);

    cxgui::KeyboardShortcut shortcut{p_first};

    if(p_first != p_second)
    {
        shortcut.m_second = p_second;
    }
    else
    {
        shortcut.m_second = std::nullopt;
    }

    POSTCONDITION(shortcut.m_second.has_value());
    return shortcut;
}
