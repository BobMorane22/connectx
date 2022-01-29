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

#include <cxmath/Dimensions.h>
#include <cxmath/Position.h>
#include <cxmath/Radius.h>
#include <cxmodel/ChipColor.h>
#include <cxmodel/common.h>
#include <cxgui/ScalingRatios.h>

namespace cxgui
{

/**********************************************************************************************//**
 * @brief Number of frames per second in the animation.
 *
 *************************************************************************************************/
using FPS = cxstd::StrongType<size_t, struct FpsTag, cxstd::EqualityComparable>;

/**********************************************************************************************//**
 * @brief Number of chips widths travelled per second.
 *
 *************************************************************************************************/
using AnimationSpeed = cxstd::StrongType<size_t, struct AnimationSpeedTag, cxstd::EqualityComparable>;

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
    virtual void Update(const cxmath::Dimensions& p_widgetDimensions, bool p_isChipMovingHorizontally) = 0;

    /******************************************************************************************//**
     * @brief Resizes the current animation according to horizontal and vertical ratios.
     *
     * @pre Both ratios are strictly positive.
     *
     * @param p_scalingRatios
     *      The horizontal and vertical scaling ratios.
     *
     *********************************************************************************************/
    virtual void Resize(const ScalingRatios& p_scalingRatios) = 0;

    /******************************************************************************************//**
     * @brief Adds vertical and horizontal displacements to the main chip.
     *
     * @param p_vertical
     *      A vertical displacement (in pixels).
     * @param p_horizontal
     *      An horizontal displacement (in pixels).
     *
     *********************************************************************************************/
     virtual void AddChipDisplacement(const cxmath::Height& p_vertical, const cxmath::Width& p_horizontal) = 0;
     
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
    virtual void UpdateCurrentColumn(const cxmodel::Column& p_newCurrentColumn) = 0;

///@}

///@{ @name Information access

    /******************************************************************************************//**
     * @brief Gets the "Frames per second" value.
     *
     * @return The "Frames per second" value.
     *
     *********************************************************************************************/
    [[nodiscard]] virtual FPS GetFPS() const = 0;

    /******************************************************************************************//**
     * @brief Gets the animation speed (chips/sec).
     *
     * @return The animation speed.
     *
     *********************************************************************************************/
    [[nodiscard]] virtual AnimationSpeed GetAnimationSpeed() const = 0;

    /******************************************************************************************//**
     * @brief Gets the dimensions for the whole animated widget.
     *
     * @return The dimensions of the animated widget.
     *
     *********************************************************************************************/
    [[nodiscard]] virtual const cxmath::Dimensions& GetAnimatedAreaDimensions() const = 0;

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
    [[nodiscard]] virtual const cxmath::Dimensions& GetCellDimensions() const = 0;

    /******************************************************************************************//**
     * @brief Gets the radius of a chip.
     *
     * @return The radius of the chip.
     *
     *********************************************************************************************/
    [[nodiscard]] virtual cxmath::Radius GetChipRadius() const = 0;

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
    [[nodiscard]] virtual cxmath::Width GetHorizontalMargin() const = 0;

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
    [[nodiscard]] virtual cxmath::Width GetLineWidth(Feature p_feature) const = 0;

    /******************************************************************************************//**
     * @brief Gets the current column.
     *
     * The current column is the column on which the active player's chip (i.e. The next chip
     * to be dropped) is located.
     *
     * @return The current column.
     *
     *********************************************************************************************/
    [[nodiscard]] virtual const cxmodel::Column& GetCurrentColumn() const = 0;

///@}

};

} // namespace cxgui

#endif // IANIMATEDBOARDMODEL_H_01D250F8_D2F7_42FE_9D3F_762B6B5D1F37
