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
 * @file ContextRestoreRAII.cpp
 * @date 2021
 *
 *************************************************************************************************/

#include <cairomm/context.h>

#include <cxinv/assertion.h>
#include <cxgui/ContextRestoreRAII.h>

cxgui::ContextRestoreRAII::ContextRestoreRAII(const Cairo::RefPtr<Cairo::Context>& p_context)
: m_context{p_context}
{
    ASSERT_MSG(bool(m_context), "Invalid context.");
    m_context->save();
}

cxgui::ContextRestoreRAII:: ~ContextRestoreRAII()
{
    ASSERT_MSG(bool(m_context), "Invalid context.");
    m_context->restore();
}

