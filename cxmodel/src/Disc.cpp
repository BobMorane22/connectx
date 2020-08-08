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
 * @file Disc.cpp
 * @date 2020
 *
 *************************************************************************************************/

#include <Disc.h>

cxmodel::Disc::Disc(const ChipColor p_color)
 : m_color{p_color}
{
    // Nothing to do...
}

cxmodel::ChipColor cxmodel::Disc::GetColor() const
{
    return m_color;
}

bool cxmodel::operator==(const cxmodel::Disc& p_lhs, const cxmodel::Disc& p_rhs)
{
    return p_lhs.GetColor() == p_rhs.GetColor();
}

bool cxmodel::operator!=(const cxmodel::Disc& p_lhs, const cxmodel::Disc& p_rhs)
{
    return !(p_lhs == p_rhs);
}
