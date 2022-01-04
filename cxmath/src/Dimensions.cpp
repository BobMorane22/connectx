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
 * @file Dimensions.cpp
 * @date 2021
 *
 *************************************************************************************************/

#include <cxmath/Dimensions.h>

bool cxmath::operator==(const cxmath::Dimensions& p_lhs, const cxmath::Dimensions& p_rhs)
{
    return (p_lhs.m_height.Get() == p_rhs.m_height.Get()) &&
           (p_lhs.m_width.Get() == p_rhs.m_width.Get());
}

bool cxmath::operator!=(const cxmath::Dimensions& p_lhs, const cxmath::Dimensions& p_rhs)
{
    return !(p_lhs == p_rhs);
}
