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

#include <limits>

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
 * @return
 *      A transparent chip color instance.
 *
 ********************************************************************************************/
[[nodiscard]] constexpr ChipColor MakeTransparent()
{
    return ChipColor{0u, 0u, 0u, 0u};
}

/******************************************************************************************//**
 * @brief Makes the red color.
 *
 * @return
 *      A red chip color instance.
 *
 ********************************************************************************************/
[[nodiscard]] constexpr ChipColor MakeRed()
{
    return ChipColor{63222u, 6425u, 13878u};
}

/******************************************************************************************//**
 * @brief Makes the blue color.
 *
 * @return
 *      A blue chip color instance.
 *
 ********************************************************************************************/
[[nodiscard]] constexpr ChipColor MakeBlue()
{
    return ChipColor{7453u, 34695u, 65535u};
}

/******************************************************************************************//**
 * @brief Makes the yellow color.
 *
 * @return
 *      A yellow chip color instance.
 *
 ********************************************************************************************/
[[nodiscard]] constexpr ChipColor MakeYellow()
{
    return ChipColor{64764u, 54507u, 9252u};
}

/******************************************************************************************//**
 * @brief Makes the green color.
 *
 * @return
 *      A green chip color instance.
 *
 ********************************************************************************************/
[[nodiscard]] constexpr ChipColor MakeGreen()
{
    return ChipColor{1028u, 56797u, 5911u};
}

/******************************************************************************************//**
 * @brief Makes the pink color.
 *
 * @return
 *      A pink chip color instance.
 *
 ********************************************************************************************/
[[nodiscard]] constexpr ChipColor MakePink()
{
    return ChipColor{62194u, 29041u, 62194u};
}

/******************************************************************************************//**
 * @brief Makes the orange color.
 *
 * @return
 *      A orange chip color instance.
 *
 ********************************************************************************************/
[[nodiscard]] constexpr ChipColor MakeOrange()
{
    return ChipColor{64764u, 29041u, 3855u};
}

/******************************************************************************************//**
 * @brief Makes the aqua color.
 *
 * @return
 *      A aqua chip color instance.
 *
 ********************************************************************************************/
[[nodiscard]] constexpr ChipColor MakeAqua()
{
    return ChipColor{16191u, 61166u, 58339u};
}

/******************************************************************************************//**
 * @brief Makes the black color.
 *
 * @return
 *      A black chip color instance.
 *
 ********************************************************************************************/
[[nodiscard]] constexpr ChipColor MakeBlack()
{
    return ChipColor{10280u, 7967u, 8481u};
}

/******************************************************************************************//**
 * @brief Makes the lilac color.
 *
 * @return
 *      A lilac chip color instance.
 *
 ********************************************************************************************/
[[nodiscard]] constexpr ChipColor MakeLilac()
{
    return ChipColor{31611u, 15163u, 65535u};
}

/******************************************************************************************//**
 * @brief Makes the salmon color.
 *
 * @return
 *      A salmon chip color instance.
 *
 ********************************************************************************************/
[[nodiscard]] constexpr ChipColor MakeSalmon()
{
    return ChipColor{65535u, 41377u, 33410u};
}

/******************************************************************************************//**
 * @brief Factory method for creating chip colors from HSL values. Colors are opaque.
 *
 * @param p_hue
 *      Hue channel value.
 * @param p_saturation
 *      Saturation channel value.
 * @param p_lightness
 *      Lightness channel value.
 *
 * @return
 *      The chip color.
 *
 *********************************************************************************************/
[[nodiscard]] ChipColor MakeFromHSL(double p_hue,
                                    double p_saturation,
                                    double p_lightness);

/******************************************************************************************//**
 * @brief Factory method for creating chip colors from HSLA values.
 *
 * @param p_hue
 *      Hue channel value.
 * @param p_saturation
 *      Saturation channel value.
 * @param p_lightness
 *      Lightness channel value.
 * @param p_alpha
 *      Alpha channel value.
 *
 * @return
 *      The chip color.
 *
 *********************************************************************************************/
[[nodiscard]] ChipColor MakeFromHSLA(double p_hue,
                                     double p_saturation,
                                     double p_lightness,
                                     double p_alpha);

/******************************************************************************************//**
 * @brief Computes the hue channel of a chip color.
 *
 * @param p_color
 *      The chip color.
 *
 * @return
 *      The hue channel (in the \f$[0, 1]\f$ inverval).
 *
 *********************************************************************************************/
[[nodiscard]] double ComputeHue(const ChipColor& p_color);

/******************************************************************************************//**
 * @brief Computes the saturation channel of a chip color.
 *
 * @param p_color
 *      The chip color.
 *
 * @return
 *      The saturation channel (in the \f$[0, 1]\f$ inverval).
 *
 *********************************************************************************************/
[[nodiscard]] double ComputeSaturation(const ChipColor& p_color);

/******************************************************************************************//**
 * @brief Computes the luminosity channel of a chip color.
 *
 * @param p_color
 *      The chip color.
 *
 * @return
 *      The luminosity channel in the \f$[0, 1]\f$ interval).
 *
 *********************************************************************************************/
[[nodiscard]] double ComputeLuminosity(const ChipColor& p_color);

} // namespace cxmodel

#endif // CHIPCOLOR_H_B5759AA2_F394_4B95_900C_C9DEA836633B
