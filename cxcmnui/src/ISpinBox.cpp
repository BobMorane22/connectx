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
 * @file ISpinBox.cpp
 * @date 2024
 *
 *************************************************************************************************/

 #include <cxinv/assertion.h>

 #include <cxcmnui/ISpinBox.h>

cx::cmn::ui::ISpinBox::Range::Range(
    const cx::cmn::ui::ISpinBox::Minimum& p_min,
    const cx::cmn::ui::ISpinBox::Maximum& p_max)
: m_min{0}, m_max{0}
{
    PRECONDITION(p_max.Get() > p_min.Get());

    m_min = p_min;
    m_max = p_max;

    POSTCONDITION(m_max.Get() > m_min.Get());
    INVARIANT(m_max.Get() > m_min.Get());
}

