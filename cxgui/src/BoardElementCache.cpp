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
 * @file BoardElementCache.cpp
 * @date 2021
 *
 *************************************************************************************************/

#include <algorithm>

#include <gdkmm/pixbuf.h>

#include <cxinv/include/assertion.h>

#include "BoardElementCache.h"

void cxgui::BoardElementCache::Add(const cxmodel::ChipColor& p_color, const Glib::RefPtr<Gdk::Pixbuf> p_surface)
{
    // Only add if not already present:
    const bool isNewKey = (std::find(m_keys.cbegin(), m_keys.cend(), p_color) == m_keys.cend());
    IF_CONDITION_NOT_MET_DO(m_keys.size() == m_surfaces.size(), return;);

    if(isNewKey)
    {
        m_keys.push_back(p_color);
        m_surfaces.push_back(p_surface);
    }
}

Glib::RefPtr<Gdk::Pixbuf> cxgui::BoardElementCache::Get(const cxmodel::ChipColor& p_color) const
{
    size_t index = 0;

    // Search for the color and get the index:
    for(const auto& key : m_keys)
    {
        if(key == p_color)
        {
            return m_surfaces[index];
        }

        ++index;
    }

    ASSERT_ERROR_MSG("Board element cache miss.");

    return m_surfaces[0];
}

void cxgui::BoardElementCache::Clear()
{
    m_keys.clear();
    m_surfaces.clear();
}

bool cxgui::BoardElementCache::HasElement(const cxmodel::ChipColor& p_color)
{
    return (std::find(m_keys.cbegin(), m_keys.cend(), p_color) != m_keys.cend());
}
