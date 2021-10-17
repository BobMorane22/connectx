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
 * @file IAnimatedBoardModel.h
 * @date 2021
 *
 *************************************************************************************************/

#ifndef IANIMATEDBOARDMODEL_H_01D250F8_D2F7_42FE_9D3F_762B6B5D1F37
#define IANIMATEDBOARDMODEL_H_01D250F8_D2F7_42FE_9D3F_762B6B5D1F37

#include <cxmath/include/math.h>
#include <cxmodel/include/ChipColor.h>
#include <cxmodel/include/StrongType.h>

namespace cxgui
{

using Height = cxstd::StrongType<double, struct HeightParameter>;
using Width = cxstd::StrongType<double, struct WidthParameter>;

/**********************************************************************************************//**
 * @brief 2D dimensions (in pixels) for widgets.
 *
 *************************************************************************************************/
struct Dimensions
{
    Dimensions(const Height& p_height, const Width& p_width)
    : m_height(p_height)
    , m_width(p_width)
    {
    }

    Height m_height;
    Width m_width;
};

/**********************************************************************************************//**
 * @brief Line width mode for calculations.
 *
 *************************************************************************************************/
enum class AddLineWidth
{
    YES,
    NO,
};

/**********************************************************************************************//**
 * @brief Animated board model.
 *
 * The role of this model is to abstract away the redundant calculations about the animations,
 * such as disc size, positions and so on. This model should be completely agnostic to the
 * animation technology.
 *
 *************************************************************************************************/
class IAnimatedBoardModel
{

public:

    /******************************************************************************************//**
     * @brief Destructor.
     *
     *********************************************************************************************/
    virtual ~IAnimatedBoardModel() = default;

///@{ @name Information update

    /******************************************************************************************//**
     * @brief Update model calculations.
     *
     * @param p_widgetDimensions
     *      The dimensions of the whole animated board widget.
     * @param p_isDiscMovingHorizontally
     *      Indicates if the disc is currently moving left of right.
     *
     *********************************************************************************************/
    virtual void Update(Dimensions p_widgetDimensions, bool p_isDiscMovingHorizontally) = 0;

    /******************************************************************************************//**
     * @brief Resizes the current animation according to horizontal and vertical ratios.
     *
     * @param p_horizontalRatio
     *      The horizontal scaling ratio.
     * @param p_verticalRatio
     *      The vertical scaling ratio.
     *
     *********************************************************************************************/
    virtual void Resize(double p_horizontalRatio, double p_verticalRatio) = 0;

    /******************************************************************************************//**
     * @brief Adds horizontal and vertical displacements to the main chip.
     *
     * @param p_horizontal
     *      An horizontal displacement (in pixels).
     * @param p_vertical
     *      A vertical displacement (in pixels).
     *
     *********************************************************************************************/
     virtual void AddDiscDisplacement(double p_horizontal, double p_vertical) = 0;
     
    /******************************************************************************************//**
     * @brief Resets all chip positions.
     *
     *********************************************************************************************/
    virtual void ResetDiscPositions() = 0;

///@}

///@{ @name Information access

    /******************************************************************************************//**
     * @brief Gets the "Frames per second" value.
     *
     * @return The "Frames per second" value.
     *
     *********************************************************************************************/
    [[nodiscard]] virtual size_t GetFPS() const = 0;

    /******************************************************************************************//**
     * @brief Gets the dimensions for a single cell.
     *
     * The animated game board is composed of "cells", which can be thought of as the single disc
     * visual container. It displays the disc, but also some of the area around it. All cells have
     * the same size on the board. The collection of all the cells, displayed along each other on
     * rows and columns, forms the actual board.
     *
     * @return Dimensions for a single cell.
     *
     *********************************************************************************************/
    [[nodiscard]] virtual Dimensions GetCellDimensions() const = 0;

    /******************************************************************************************//**
     * @brief Gets the radius of a disc.
     *
     * @param p_addLineWidth Indicates if line width should be taken into account.
     *
     * @return The radius of the disc.
     *
     *********************************************************************************************/
    [[nodiscard]] virtual double GetDiscRadius(AddLineWidth p_addLineWidth) const = 0;

    /******************************************************************************************//**
     * @brief Gets the main chip current position.
     *
     * @return The main chip's current position.
     *
     *********************************************************************************************/
    [[nodiscard]] virtual cxmath::Position GetDiscPosition() const = 0;

    /******************************************************************************************//**
     * @brief Gets the current horizontal margin.
     *
     * The horizontal margin is the free horizontal space between a chip and the boarder of
     * that chip cell.
     *
     * @return The horizontal margin.
     *
     *********************************************************************************************/
    [[nodiscard]] virtual double GetHorizontalMargin() const = 0;

    /******************************************************************************************//**
     * @brief Gets the mirror chip's current position.
     *
     * @return The mirror chip's current position.
     *
     *********************************************************************************************/
    [[nodiscard]] virtual cxmath::Position GetMirrorDiscPosition() const = 0;

    /******************************************************************************************//**
     * @brief Indicates if the drawing of a mirror chip is required.
     *
     * @return `true` if drawing a mirror disc is required, `false` otherwise.
     *
     *********************************************************************************************/
    [[nodiscard]] virtual bool IsMirrorDiscNeeded() const = 0;

///@}

};

} // namespace cxgui

#endif // IANIMATEDBOARDMODEL_H_01D250F8_D2F7_42FE_9D3F_762B6B5D1F37
