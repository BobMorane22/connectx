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

#include <cxmath/include/Position.h>
#include <cxmodel/include/ChipColor.h>
#include <cxgui/include/Dimensions.h>

namespace cxgui
{

/**********************************************************************************************//**
 * @brief Type of feature for which to get the line width.
 *
 *************************************************************************************************/
enum class Feature
{
    CELL,
    CHIP,
};

/**********************************************************************************************//**
 * @brief Animated board model.
 *
 * The role of this model is to abstract away the redundant calculations about the animations,
 * such as chip size, positions and so on. This model should be completely agnostic to the
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
     * This should be called on every animation tick to update the model values and review all
     * calculations. Otherwise everything that comes from the model will not be updated (as if
     * there was no animation).
     *
     * @pre Both widget dimensions are strictly positive.
     *
     * @param p_widgetDimensions
     *      The dimensions of the whole animated board widget.
     * @param p_isChipMovingHorizontally
     *      Indicates if the chip is currently moving left of right.
     *
     *********************************************************************************************/
    virtual void Update(const Dimensions& p_widgetDimensions, bool p_isChipMovingHorizontally) = 0;

    /******************************************************************************************//**
     * @brief Resizes the current animation according to horizontal and vertical ratios.
     *
     * @pre Both ratios are strictly positive.
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
     virtual void AddChipDisplacement(double p_horizontal, double p_vertical) = 0;
     
    /******************************************************************************************//**
     * @brief Resets all chip positions.
     *
     *********************************************************************************************/
    virtual void ResetChipPositions() = 0;

    /******************************************************************************************//**
     * @brief Updates the current column to some new value.
     *
     * @param p_newCurrentColumn
     *      The new value for the current column.
     *
     *********************************************************************************************/
    virtual void UpdateCurrentColumn(size_t p_newCurrentColumn) = 0;

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
     * @brief Gets the animation speed (chips/sec).
     *
     * @return The animation speed.
     *
     *********************************************************************************************/
    [[nodiscard]] virtual size_t GetAnimationSpeed() const = 0;

    /******************************************************************************************//**
     * @brief Gets the dimensions for the whole animated widget.
     *
     * @return The dimensions of the animated widget.
     *
     *********************************************************************************************/
    [[nodiscard]] virtual const Dimensions& GetAnimatedAreaDimensions() const = 0;

    /******************************************************************************************//**
     * @brief Gets the dimensions for a single cell.
     *
     * The animated game board is composed of "cells", which can be thought of as the single chip
     * visual container. It displays the chip, but also some of the area around it. All cells have
     * the same size on the board. The collection of all the cells, displayed along each other on
     * rows and columns, forms the actual board.
     *
     * @return Dimensions for a single cell.
     *
     *********************************************************************************************/
    [[nodiscard]] virtual const Dimensions& GetCellDimensions() const = 0;

    /******************************************************************************************//**
     * @brief Gets the radius of a chip.
     *
     * @return The radius of the chip.
     *
     *********************************************************************************************/
    [[nodiscard]] virtual double GetChipRadius() const = 0;

    /******************************************************************************************//**
     * @brief Gets the main chip current position.
     *
     * @return The main chip's current position.
     *
     *********************************************************************************************/
    [[nodiscard]] virtual const cxmath::Position& GetChipPosition() const = 0;

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
    [[nodiscard]] virtual const cxmath::Position& GetMirrorChipPosition() const = 0;

    /******************************************************************************************//**
     * @brief Indicates if the drawing of a mirror chip is required.
     *
     * @return `true` if drawing a mirror chip is required, `false` otherwise.
     *
     *********************************************************************************************/
    [[nodiscard]] virtual bool IsMirrorChipNeeded() const = 0;

    /******************************************************************************************//**
     * @brief Gets the current line width value for a specified feature.
     *
     * @paran p_feature The feature to get the line width for.
     *
     * @return The current line width value.
     *
     *********************************************************************************************/
    [[nodiscard]] virtual double GetLineWidth(Feature p_feature) const = 0;

    /******************************************************************************************//**
     * @brief Gets the current column.
     *
     * The current column is the column on which the active player's chip (i.e. The next chip
     * to be dropped) is located.
     *
     * @return The current column.
     *
     *********************************************************************************************/
    [[nodiscard]] virtual size_t GetCurrentColumn() const = 0;

///@}

};

} // namespace cxgui

#endif // IANIMATEDBOARDMODEL_H_01D250F8_D2F7_42FE_9D3F_762B6B5D1F37
