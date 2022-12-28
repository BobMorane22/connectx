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
 * Helpers to create Cairo paths. These functions do no drawing, they only deal with the
 * creation of paths.
 *
 * @file pathHelpers.h
 * @date 2021
 *
 *************************************************************************************************/

#ifndef PATHHELPERS_H_5305E912_5A6B_41D9_8FEA_1ADBFC3DDF86
#define PATHHELPERS_H_5305E912_5A6B_41D9_8FEA_1ADBFC3DDF86

#include <cairomm/refptr.h>

namespace Cairo
{
    class Context;
}

namespace cxmath
{
    class Position;
}

namespace cxgui
{

/**********************************************************************************************//**
 * @brief Created a rectagular path.
 *
 * Makes a rectangular path originating from a top/left position and spanning a predifined
 * height and width:
 *
 @verbatim
                     top/left
             X          +--------------------------------------------+
      +------>          |                                            |
      |                 |                                            |
      |                 |                                            |
      |                 |                                            | height
    Y v                 |                                            |
                        |                                            |
                        |                                            |
                        +--------------------------------------------+
                                            width
 @endverbatim
 * 
 * The window in GTK is seen as an X/Y plane in which positive Y is pointing towards
 * the bottom of the window. The "top" in "top/left" refers to the top of the window.
 * This means that the top/left position usually has a smaller Y value that the
 * bottom/left position.
 *
 * @param p_context
 *      The cairo context to use.
 * @param p_topLeft
 *      Rectangle path origin, as the top/left rectangle corner (see diagram above).
 * @param p_height
 *      The path's wanted height (see diagram above).
 * @param p_width
 *      The path's wanted width (see diagram above).
 *
 *************************************************************************************************/
void MakeRectanglarPath(const Cairo::RefPtr<Cairo::Context>& p_context,
                        const cxmath::Position& p_topLeft,
                        double p_height,
                        double p_width);

/**********************************************************************************************//**
 * @brief Creates a circular path.
 *
 * @param p_context
 *      The cairo context to use.
 * @param p_centerPosition
 *      The disc's wanted center position.
 * @param p_radius
 *      The discs wanted radius.
 *
 *************************************************************************************************/
void MakeCircularPath(const Cairo::RefPtr<Cairo::Context>& p_context,
                      const cxmath::Position& p_centerPosition,
                      double p_radius);

} // namespace cxgui

#endif // PATHHELPERS_H_5305E912_5A6B_41D9_8FEA_1ADBFC3DDF86
