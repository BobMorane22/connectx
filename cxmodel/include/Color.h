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
 * @file Color.h
 * @date 2020
 *
 *************************************************************************************************/

#ifndef COLOR_H_2CBE2E5B_FB8A_412E_A9F8_981A1851DD34
#define COLOR_H_2CBE2E5B_FB8A_412E_A9F8_981A1851DD34

#include <array>
#include <cstdint>
#include <limits>
#include <type_traits>

namespace cxmodel
{

/**********************************************************************************************//**
 * @brief Class for manipulating RGB(A) colors.
 *
 * @tparam Channel RGBA channels.
 *
 *************************************************************************************************/
template<typename Channel>
class Color final
{

private:

    using Rgba = std::array<Channel, 4>;
    Rgba m_rgba;

public:

    /******************************************************************************************//**
     * @brief Predefined colors.
     *
     *********************************************************************************************/
    enum class Predefined
    {
        AQUA,
        BLACK,
        BLUE,
        FUSCHIA,
        GRAY,
        GREEN,
        LIME,
        MAROON,
        NAVY,
        OLIVE,
        PURPLE,
        RED,
        TEAL,
        WHITE,
        YELLOW,
    };

    /******************************************************************************************//**
     * @brief Constructor.
     *
     * @param p_red   Red channel value.
     * @param p_green Green channel value.
     * @param p_blue  Blue channel value.
     * @param p_alpha Alpha channel value.
     *
     * Constructs a cxmodel::Color object based on values for RGBA channels.
     *
     *********************************************************************************************/
    constexpr Color(Channel p_red,
                    Channel p_green,
                    Channel p_blue,
                    Channel p_alpha )
    : m_rgba{p_red, p_green, p_blue, p_alpha}
    {
        // Nothing to do...

        // Color class should stay small and fast. Beside the four channel, not other data
        // members should be added to this class.
        static_assert(sizeof(cxmodel::Color<Channel>) == 4 * sizeof(Channel), "Extra (unwanted) data member added.");

        // The color channel underlying type should be an unsigned arithmetic type (but not a bool).
        static_assert(std::is_unsigned<Channel>::value, "Underlying channel type should be unsigned");
        static_assert(!std::is_same<Channel, bool>::value, "bool is not an accepted unsigned type for color channels.");
    }


    /******************************************************************************************//**
     * @brief Constructor.
     *
     * @param p_red   Red channel value.
     * @param p_green Green channel value.
     * @param p_blue  Blue channel value.
     *
     * Constructs a cxmodel::Color object based on values for RGB channels. The color will be
     * completely opaque.
     *
     *********************************************************************************************/
    constexpr Color(Channel p_red,
                    Channel p_green,
                    Channel p_blue )
    : Color(p_red, p_green, p_blue, std::numeric_limits< Channel >::max())
    {
        // Nothing to do...
    }

    /******************************************************************************************//**
     * @brief Red channel acessor.
     *
     * @return The red channel value.
     *
     *********************************************************************************************/
    constexpr Channel R() const {return m_rgba[0];}

    /******************************************************************************************//**
     * @brief Green channel acessor.
     *
     * @return The green channel value.
     *
     *********************************************************************************************/
    constexpr Channel G() const {return m_rgba[1];}

    /******************************************************************************************//**
     * @brief Blue channel acessor.
     *
     * @return The blue channel value.
     *
     *********************************************************************************************/
    constexpr Channel B() const {return m_rgba[2];}

    /******************************************************************************************//**
     * @brief Alpha channel acessor.
     *
     * @return The alpha channel value.
     *
     *********************************************************************************************/
    constexpr Channel A() const {return m_rgba[3];}

    /******************************************************************************************//**
     * @brief Creates a predefined color instance.
     *
     * @param p_color the wanted predefined color.
     *
     * @return The instance.
     *
     *********************************************************************************************/
    constexpr static Color<Channel> MakePredefined(Color<Channel>::Predefined p_color);

private:

    constexpr Color()
    : Color{0u, 0u, 0u, 0u}
    {
        // Nothing to do...
    }

};

template<typename Channel>
constexpr Color<Channel> Color<Channel>::MakePredefined(Color::Predefined p_color)
{
    constexpr Channel MAX = std::numeric_limits<Channel>::max();
    constexpr Channel MID = (MAX >> 1);

    switch (p_color)
    {
        case Color::Predefined::AQUA:     return Color(0u,  MAX, MAX);
        case Color::Predefined::BLACK:    return Color(0u,  0u,  0u );
        case Color::Predefined::BLUE:     return Color(0u,  0u,  MAX);
        case Color::Predefined::FUSCHIA:  return Color(MAX, 0u,  MAX);
        case Color::Predefined::GRAY:     return Color(MID, MID, MID);
        case Color::Predefined::GREEN:    return Color(0u,  MID, 0u );
        case Color::Predefined::LIME:     return Color(0u,  MAX, 0u );
        case Color::Predefined::MAROON:   return Color(MID, 0u,  0u );
        case Color::Predefined::NAVY:     return Color(0u,  0u,  MID);
        case Color::Predefined::OLIVE:    return Color(MID, MID, 0u );
        case Color::Predefined::PURPLE:   return Color(MID, 0u,  MID);
        case Color::Predefined::RED:      return Color(MAX, 0u,  0u );
        case Color::Predefined::TEAL:     return Color(0u,  MID, MID);
        case Color::Predefined::WHITE:    return Color(MAX, MAX, MAX);
        case Color::Predefined::YELLOW:   return Color(MAX, MAX, 0u );

        default:
            // Assert
            return {};
    }
}

/*********************************************************************************************//**
 * @brief Equal-to operator.
 *
 * @param p_lhs The first color to compare to.
 * @param p_rhs The second color to compare to.
 *
 * @return 'true' if both colors are the same, 'false' otherwise.
 *
 * Two colors are considered equal if both colors are all the same channel values.
 *
 ************************************************************************************************/
template<typename Channel>
constexpr bool operator==(const Color<Channel>& p_lhs, const Color<Channel>& p_rhs )
{
    return (p_lhs.R() == p_rhs.R()) &&
           (p_lhs.G() == p_rhs.G()) &&
           (p_lhs.B() == p_rhs.B()) &&
           (p_lhs.A() == p_rhs.A());
}

/*********************************************************************************************//**
 * @brief Not equal-to operator.
 *
 * @param p_lhs The first color to compare to.
 * @param p_rhs The second color to compare to.
 *
 * @return 'true' if both colors are different, 'false' otherwise.
 *
 * Two colors are considered not equal if for at least one channel, the values are different.
 *
 ************************************************************************************************/
template<typename Channel>
constexpr bool operator!=(const Color<Channel>& p_lhs, const Color<Channel>& p_rhs )
{
    return !(p_lhs == p_rhs);
}

} // namespace cxmodel

#endif // COLOR_H_2CBE2E5B_FB8A_412E_A9F8_981A1851DD34
