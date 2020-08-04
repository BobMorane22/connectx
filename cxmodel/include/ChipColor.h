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
 * @file ChipColor.h
 * @date 2020
 *
 *************************************************************************************************/

#ifndef CHIPCOLOR_H_B5759AA2_F394_4B95_900C_C9DEA836633B
#define CHIPCOLOR_H_B5759AA2_F394_4B95_900C_C9DEA836633B

#include "Color.h"

namespace cxmodel
{

/******************************************************************************************//**
 * @brief Color specific to a chip.
 *
 ********************************************************************************************/
using ChipColor = Color<unsigned short>;

/******************************************************************************************//**
 * @brief Makes the "transparent" color.
 *
 ********************************************************************************************/
constexpr ChipColor MakeTransparent()
{
    return ChipColor{0u, 0u, 0u, 0u};
}

/******************************************************************************************//**
 * @brief Makes the red color.
 *
 ********************************************************************************************/
constexpr ChipColor MakeRed()
{
    return ChipColor::MakePredefined(ChipColor::Predefined::RED);
}

/******************************************************************************************//**
 * @brief Makes the blue color.
 *
 ********************************************************************************************/
constexpr ChipColor MakeBlue()
{
    return ChipColor::MakePredefined(ChipColor::Predefined::BLUE);
}

/******************************************************************************************//**
 * @brief Makes the yellow color.
 *
 ********************************************************************************************/
constexpr ChipColor MakeYellow()
{
    return ChipColor::MakePredefined(ChipColor::Predefined::YELLOW);
}

/******************************************************************************************//**
 * @brief Makes the green color.
 *
 ********************************************************************************************/
constexpr ChipColor MakeGreen()
{
    return ChipColor::MakePredefined(ChipColor::Predefined::GREEN);
}

} // namespace cxmodel

#endif // CHIPCOLOR_H_B5759AA2_F394_4B95_900C_C9DEA836633B
