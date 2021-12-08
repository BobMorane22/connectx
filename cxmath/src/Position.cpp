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
 * @file Position.cpp
 * @date 2021
 *
 *************************************************************************************************/

#include <cxmath/Position.h>
 
bool cxmath::operator==(const cxmath::Position& p_lhs, const cxmath::Position& p_rhs)
{
    return (p_lhs.m_x == p_rhs.m_x) && (p_lhs.m_y == p_rhs.m_y);
}

bool cxmath::operator!=(const cxmath::Position& p_lhs, const cxmath::Position& p_rhs)
{
    return !(p_lhs == p_rhs);
}
