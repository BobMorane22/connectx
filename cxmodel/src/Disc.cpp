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

#include <cxmodel/Disc.h>

cx::model::Disc::Disc(const ChipColor p_color)
 : m_color{p_color}
{
    // Nothing to do...
}

cx::model::Disc cx::model::Disc::MakeTransparentDisc()
{
    return cx::model::Disc(cx::model::MakeTransparent());
}

cx::model::ChipColor cx::model::Disc::GetColor() const
{
    return m_color;
}

void cx::model::Disc::Reset()
{
    m_color = cx::model::MakeTransparent();
}

