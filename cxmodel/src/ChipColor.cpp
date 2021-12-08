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
 * @file ChipColor.cpp
 * @date 2021
 *
 *************************************************************************************************/

#include <cmath>

#include <cxinv/assertion.h>
#include <cxmodel/ChipColor.h>

namespace
{

enum class HSL
{
    HUE,
    SATURATION,
    LUMINOSITY
};

double HueToRGB(double p, double q, double t)
{
    if(t < 0.0)
    {
        t += 1.0;
    }
    
    if(t > 1.0)
    {
        t -= 1;
    }
    
    if(t < 1.0/6.0)
    {
        return p + (q - p) * 6.0 * t;
    }
    
    if(t < 1.0/2.0)
    {
        return q;
    }
    
    if(t < 2.0/3.0)
    {
        return p + (q - p) * (2.0/3.0 - t) * 6.0;
    }
    
    return p;
}

double ComputeHSLFromRGB(const cxmodel::ChipColor& p_color, HSL p_channel)
{
    constexpr unsigned short MAX = std::numeric_limits<unsigned short>::max();

    const double r = p_color.R()/static_cast<double>(MAX);
    const double g = p_color.G()/static_cast<double>(MAX);
    const double b = p_color.B()/static_cast<double>(MAX);

    double maximum = std::max(std::max(r, g), b);
    double minimum = std::min(std::min(r, g), b);

    double h = 0.0;
    double s = 0.0;
    const double l = (maximum + minimum)/2.0;

    if(maximum != minimum)
    {
        double d = maximum - minimum;

        if(l > 0.5)
        {
            s = d/(2.0 - maximum - minimum);
        }
        else
        {
            s = d/(maximum + minimum);
        }

        if(maximum == r)
        {
            h = (g - b)/d + (g < b ? 6.0 : 0.0);
        }
        else if(maximum == g)
        {
            h = (b - r)/d + 2.0;
        }
        else if (maximum == b)
        {
            h = (r - g)/d + 4.0;
        }

        h /= 6.0;
    }

    switch(p_channel)
    {
        case HSL::HUE: return h;
        case HSL::SATURATION: return s;
        case HSL::LUMINOSITY: return l;
        default:
            ASSERT_ERROR_MSG("Unknown channel");
            return 0.0;
    }

    return 0.0;
}

} // namespace

cxmodel::ChipColor cxmodel::MakeFromHSL(double p_hue,
                                        double p_saturation,
                                        double p_lightness)
{
    return cxmodel::MakeFromHSLA(p_hue, p_saturation, p_lightness, 1.0);
}

cxmodel::ChipColor cxmodel::MakeFromHSLA(double p_hue,
                                         double p_saturation,
                                         double p_lightness,
                                         double p_alpha)
{
    IF_PRECONDITION_NOT_MET_DO(p_hue >= 0.0, return cxmodel::MakeTransparent(););
    IF_PRECONDITION_NOT_MET_DO(p_saturation >= 0.0, return cxmodel::MakeTransparent(););
    IF_PRECONDITION_NOT_MET_DO(p_lightness >= 0.0, return cxmodel::MakeTransparent(););
    IF_PRECONDITION_NOT_MET_DO(p_alpha >= 0.0, return cxmodel::MakeTransparent(););

    IF_PRECONDITION_NOT_MET_DO(p_hue <= 1.0, return cxmodel::MakeTransparent(););
    IF_PRECONDITION_NOT_MET_DO(p_saturation <= 1.0, return cxmodel::MakeTransparent(););
    IF_PRECONDITION_NOT_MET_DO(p_lightness <= 1.0, return cxmodel::MakeTransparent(););
    IF_PRECONDITION_NOT_MET_DO(p_alpha <= 1.0, return cxmodel::MakeTransparent(););

    double red, green, blue;

    if(p_saturation == 0.0)
    {
        red   = p_lightness;
        green = p_lightness;
        blue  = p_lightness;
    }
    else
    {
        double q;

        if(p_lightness < 0.5)
        {
            q = p_lightness * (1.0 + p_saturation);
        }
        else
        {
            q = p_lightness + p_saturation - p_lightness * p_saturation;
        }

        const double p = 2.0 * p_lightness - q;

        red   = HueToRGB(p, q, p_hue + 1.0/3.0);
        green = HueToRGB(p, q, p_hue);
        blue  = HueToRGB(p, q, p_hue - 1.0/3.0);
    }

    const unsigned short MAX_INT = std::numeric_limits<unsigned short>::max();
    const double MAX_FLOAT = static_cast<double>(MAX_INT);

    const unsigned short r = static_cast<unsigned short>(std::round(red * MAX_FLOAT));
    const unsigned short g = static_cast<unsigned short>(std::round(green * MAX_FLOAT));
    const unsigned short b = static_cast<unsigned short>(std::round(blue * MAX_FLOAT));
    const unsigned short a = static_cast<unsigned short>(std::round(p_alpha * MAX_FLOAT));

    return ChipColor(r, g, b, a);
}

double cxmodel::ComputeHue(const ChipColor& p_color)
{
    return ComputeHSLFromRGB(p_color, HSL::HUE);
}

double cxmodel::ComputeSaturation(const ChipColor& p_color)
{
    return ComputeHSLFromRGB(p_color, HSL::SATURATION);
}

double cxmodel::ComputeLuminosity(const ChipColor& p_color)
{
    return ComputeHSLFromRGB(p_color, HSL::LUMINOSITY);
}
