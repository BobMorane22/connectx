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
 * @file AnimatedBoardModel.cpp
 * @date 2021
 *
 *************************************************************************************************/

#include "AnimatedBoardModel.h"

namespace
{

constexpr double LINE_WIDTH_SCALING_FACTOR = 0.005;

/**************************************************************************************************
 * @brief Checks if the disc has crossed over to one side of the window.
 *
 * A disc has "crossed over" if some part of it is located outside one edge of the window. For
 * Example:
 *
 *                                     < ---- Moving
 *
 *                        |      +  +                |   +  +
 *                        |   +        +             |+        +
 *                        |  +          +            +          +
 *                        | +            +          +|           +
 *                        | +            +          +|           +
 *                        |  +          +            +          +
 *                        |   +       +              |+       +
 *                        |      +  +                |   +  +
 *
 *                         The disc has not         The disc has
 *                          crossed over.           crossed over.
 *
 *
 * @param p_currentHorizontalPosition
 *      The current horizontal position of the disc's center.
 *
 * @param p_windowWidth
 *      The width of the window.
 *
 * @param p_halfDiscSize
 *      The width of a half disc (the radius and half the disc's line width's width). In Cairo,
 *      only half of the line width is actually included in the disc's path. The other half
 *      crosses the path's boundary.
 *
 * @return `true` if the disc has crossed over, `false` otherwise.
 *
 *************************************************************************************************/
template<cxgui::BoardAnimation A>
bool HasDiscCrossedOver(double p_currentHorizontalPosition,
                        double p_windowWidth,
                        double p_halfDiscSize);

template<>
bool HasDiscCrossedOver<cxgui::BoardAnimation::MOVE_CHIP_LEFT_ONE_COLUMN>(double p_currentHorizontalPosition,
                                                                          [[maybe_unused]]double p_windowWidth,
                                                                          double p_halfDiscSize)
{
    return p_currentHorizontalPosition < p_halfDiscSize;
}

template<>
bool HasDiscCrossedOver<cxgui::BoardAnimation::MOVE_CHIP_RIGHT_ONE_COLUMN>(double p_currentHorizontalPosition,
                                                                           double p_windowWidth,
                                                                           double p_halfDiscSize)
{
    return p_currentHorizontalPosition > p_windowWidth - p_halfDiscSize;
}

/**************************************************************************************************
 * @brief Check if disc has crossed over completely (i.e. all of it should be on the other side).
 *
 * A disc has crossed over completely on one side if all of it is outside the window (at this
 * point, it should be entirely drawn on the other side of the window). For example:
 *
 *
 *                                     < ---- Moving
 *
 *                           |   +  +                    +  +     |
 *                           |+        +              +        +  |
 *                           +          +            +          + |
 *                          +|           *          +            +|
 *                          +|           *          +            +|
 *                           +          +            +          + |
 *                           |+       +               +       +   |
 *                           |   +  +                    +  +     |
 *                                                      
 *                    
 *                          The disc has             The disc has
 *                           started to               completely
 *                           cross over.             crossed over.
 *
 *
 * @param p_currentHorizontalPosition
 *      The current horizontal position of the disc's center.
 *
 * @param p_windowWidth
 *      The width of the window.
 *
 * @param p_halfDiscSize
 *      The width of a half disc (the radius and half the disc's line width's width). In Cairo,
 *      only half of the line width is actually included in the disc's path. The other half
 *      crosses the path's boundary.
 *
 * @param p_horizontalMargin
 *      The difference between a half disc and half a disc's drawing space. In between two
 *      adjacent discs, there are two horizontal margins of space. If the disc's drawing
 *      space is a square, or a taller rectangle this margin is zero.
 *
 * @return `true` if the disc has completely crossed over, `false` otherwise.
 *
 *************************************************************************************************/
template<cxgui::BoardAnimation A>
bool HasDiscCompletelyCrossedOver(double p_currentHorizontalPosition,
                                  double p_windowWidth,
                                  double p_halfDiscSize,
                                  double p_horizontalMargin);

template<>
bool HasDiscCompletelyCrossedOver<cxgui::BoardAnimation::MOVE_CHIP_LEFT_ONE_COLUMN>(double p_currentHorizontalPosition,
                                                                                    [[maybe_unused]] double p_windowWidth,
                                                                                    double p_halfDiscSize,
                                                                                    double p_horizontalMargin)
{
    return cxmath::AreLogicallyEqual(-p_currentHorizontalPosition, p_halfDiscSize + p_horizontalMargin); 
}

template<>
bool HasDiscCompletelyCrossedOver<cxgui::BoardAnimation::MOVE_CHIP_RIGHT_ONE_COLUMN>(double p_currentHorizontalPosition,
                                                                                     double p_windowWidth,
                                                                                     double p_halfDiscSize,
                                                                                     double p_horizontalMargin)
{
    return cxmath::AreLogicallyEqual(p_currentHorizontalPosition, p_windowWidth + p_halfDiscSize + p_horizontalMargin);
}

/**************************************************************************************************
 * @brief Updates position of the disc so it is drawn on the other side of the window.
 *
 * @param p_currentHorizontalPosition
 *      The current horizontal position of the disc's center.
 *
 * @param p_windowWidth
 *      The width of the window.
 *
 * @param p_halfDiscSize
 *      The width of a half disc (the radius and half the disc's line width's width). In Cairo,
 *      only half of the line width is actually included in the disc's path. The other half
 *      crosses the path's boundary.
 *
 * @param p_horizontalMargin
 *      The difference between a half disc and half a disc's drawing space. In between two
 *      adjacent discs, there are two horizontal margins of space. If the disc's drawing
 *      space is a square, or a taller rectangle this margin is zero.
 *
 *************************************************************************************************/
template<cxgui::BoardAnimation A>
void ComputeDiscPositionForOtherSide(double& p_currentHorizontalPosition,
                                     double p_windowWidth,
                                     double p_halfDiscSize,
                                     double p_horizontalMargin);

template<>
void ComputeDiscPositionForOtherSide<cxgui::BoardAnimation::MOVE_CHIP_LEFT_ONE_COLUMN>(double& p_currentHorizontalPosition,
                                                                                       double p_windowWidth,
                                                                                       double p_halfDiscSize,
                                                                                       double p_horizontalMargin)
{
    p_currentHorizontalPosition = p_windowWidth - p_halfDiscSize - p_horizontalMargin;
}

template<>
void ComputeDiscPositionForOtherSide<cxgui::BoardAnimation::MOVE_CHIP_RIGHT_ONE_COLUMN>(double& p_currentHorizontalPosition,
                                                                                        [[maybe_unused]] double p_windowWidth,
                                                                                        double p_halfDiscSize,
                                                                                        double p_horizontalMargin)
{
    p_currentHorizontalPosition = p_halfDiscSize + p_horizontalMargin;
}

/**************************************************************************************************
 * @brief Clamps the disc's extrimity to one side of the window.
 *
 * @param p_currentHorizontalPosition
 *      The current horizontal position of the disc's center.
 *
 * @param p_windowWidth
 *      The width of the window.
 *
 * @param p_halfDiscSize
 *      The width of a half disc (the radius and half the disc's line width's width). In Cairo,
 *      only half of the line width is actually included in the disc's path. The other half
 *      crosses the path's boundary.
 *
 * @param p_horizontalMargin
 *      The difference between a half disc and half a disc's drawing space. In between two
 *      adjacent discs, there are two horizontal margins of space. If the disc's drawing
 *      space is a square, or a taller rectangle this margin is zero.
 *
 *************************************************************************************************/
template<cxgui::BoardAnimation A>
void ClampDiscPositionToCurrentSide(double& p_currentHorizontalPosition,
                                    double p_windowWidth,
                                    double p_halfDiscSize,
                                    double p_horizontalMargin);

template<>
void ClampDiscPositionToCurrentSide<cxgui::BoardAnimation::MOVE_CHIP_LEFT_ONE_COLUMN>(double& p_currentHorizontalPosition,
                                                                                      [[maybe_unused]] double p_windowWidth,
                                                                                      double p_halfDiscSize,
                                                                                      double p_horizontalMargin)
{
    p_currentHorizontalPosition = p_halfDiscSize + p_horizontalMargin;
}

template<>
void ClampDiscPositionToCurrentSide<cxgui::BoardAnimation::MOVE_CHIP_RIGHT_ONE_COLUMN>(double& p_currentHorizontalPosition,
                                                                                       double p_windowWidth,
                                                                                       double p_halfDiscSize,
                                                                                       double p_horizontalMargin)
{
    p_currentHorizontalPosition = p_windowWidth - p_halfDiscSize - p_horizontalMargin;
}

/**************************************************************************************************
 * @brief Compute the mirror disc's center position.
 *
 * The "mirror" disc is the disc's double that is drawn to the other side of the window when it
 * crosses over to give the illusion that the disc does not go outside the window (but rather
 * translates to the other side. For example:
 *
 *
 *                                        The window frame
 *       +-------------------------------------------------------------------------------+
 *       |+  +                                                                            |
 *       |      +                                                                       + |
 *       |       +                                                                     +  |
 *       |        *                        <---- Moving                               +   |
 *       |        *                                                                   +   |
 *       |       +                                                                     +  |
 *       |     +                                                                        + |
 *       |+  +                                                                            |
 *       |                                                                                |
 *
 *     The disc has                                                              And the mirror
 *     crossed over.                                                              disc appears.
 *       
 *
 * @param p_currentMirrorHorizontalPosition
 *      the current horizontal position of the mirror disc's center.
 *
 * @param p_currentHorizontalPosition
 *      the current horizontal position of the disc's center.
 *
 * @param p_windowWidth
 *      The width of the window.
 *
 * @param p_halfDiscSize
 *      The width of a half disc (the radius and half the disc's line width's width). In Cairo,
 *      only half of the line width is actually included in the disc's path. The other half
 *      crosses the path's boundary.
 *
 *************************************************************************************************/
template<cxgui::BoardAnimation A>
void ComputeMirrorDiscPosition(double& p_currentMirrorHorizontalPosition,
                               double p_currentHorizontalPosition,
                               double p_windowWidth);

template<>
void ComputeMirrorDiscPosition<cxgui::BoardAnimation::MOVE_CHIP_LEFT_ONE_COLUMN>(double& p_currentMirrorHorizontalPosition,
                                                                                 double p_currentHorizontalPosition,
                                                                                 double p_windowWidth)
{
    p_currentMirrorHorizontalPosition = p_windowWidth + p_currentHorizontalPosition;
}

template<>
void ComputeMirrorDiscPosition<cxgui::BoardAnimation::MOVE_CHIP_RIGHT_ONE_COLUMN>(double& p_currentMirrorHorizontalPosition,
                                                                                  double p_currentHorizontalPosition,
                                                                                  double p_windowWidth)
{
    p_currentMirrorHorizontalPosition = p_currentHorizontalPosition - p_windowWidth;
}

} // namespace

cxgui::AnimatedBoardModel::AnimatedBoardModel(const cxgui::AnimatedBoardPresenter& p_presenter)
: m_presenter{p_presenter}
{
    // Nothing to do...
}

// Compute the current disc's position. If needed, the current mirror disc position is also
// computed. Refer to the subfunction documentation for more details.
template<cxgui::BoardAnimation A>
bool cxgui::AnimatedBoardModel::ComputeDiscPosition(double p_windowWidth, double p_halfDiscSize, double p_horizontalMargin)
{
    bool isMirrorDiscNeeded = false;

    if(!m_isDiscMovingHorizontally)
    {
        if(HasDiscCompletelyCrossedOver<A>(m_discPosition.m_x, p_windowWidth, p_halfDiscSize, p_horizontalMargin))
        {
            // At this point, the disc has completely crossed over to the right,
            // so we update its horizontal location:
            ComputeDiscPositionForOtherSide<A>(m_discPosition.m_x, p_windowWidth, p_halfDiscSize, p_horizontalMargin);
        }
        else if(HasDiscCrossedOver<A>(m_discPosition.m_x, p_windowWidth, p_halfDiscSize))
        {
            // Otherwise, since it is not moving anymore and located completely
            // to the right, we make sure it is completely visible (we do not
            // want half a disc lost in the right edge):
            ClampDiscPositionToCurrentSide<A>(m_discPosition.m_x, p_windowWidth, p_halfDiscSize, p_horizontalMargin);
        }
    }
    else if(HasDiscCrossedOver<A>(m_discPosition.m_x, p_windowWidth, p_halfDiscSize))
    {
        // The disc has gone over the edge on the left, so an extra disc, the mirror
        // disc, will be needed on the far right side for the animation to be smooth.
        // We handle its horizontal position here:
        isMirrorDiscNeeded = true;
        ComputeMirrorDiscPosition<A>(m_mirrorDiscPosition.m_x, m_discPosition.m_x, p_windowWidth);
    }

    return isMirrorDiscNeeded;
}

bool cxgui::AnimatedBoardModel::ComputeDiscLeftPosition(double p_windowWidth, double p_halfDiscSize, double p_horizontalMargin)
{
    return ComputeDiscPosition<cxgui::BoardAnimation::MOVE_CHIP_LEFT_ONE_COLUMN>(p_windowWidth, p_halfDiscSize, p_horizontalMargin);
}

bool cxgui::AnimatedBoardModel::ComputeDiscRightPosition(double p_windowWidth, double p_halfDiscSize, double p_horizontalMargin)
{
    return ComputeDiscPosition<cxgui::BoardAnimation::MOVE_CHIP_RIGHT_ONE_COLUMN>(p_windowWidth, p_halfDiscSize, p_horizontalMargin);
}

void cxgui::AnimatedBoardModel::ComputeDiscVerticalPosition(const double p_halfDiscSize, double p_height)
{
    if(m_discPosition.m_y < p_halfDiscSize)
    {
        m_discPosition.m_y = p_halfDiscSize;
    }

    if(m_discPosition.m_y > p_height - p_halfDiscSize)
    {
        m_discPosition.m_y = p_height - p_halfDiscSize;
    }
}

void cxgui::AnimatedBoardModel::Update(Dimensions p_widgetDimensions, bool p_isDiscMovingHorizontally)
{
    // First, we update the dimensions for the animated widgets. They will be the
    // basis for most other quantities:
    m_widgetDimensions = p_widgetDimensions;

    // Cell dimensions:
    const Height cellHeight = Height((m_widgetDimensions.m_height.Get() / m_presenter.GetBoardHeight()) + 1.0);
    const Width cellWidth = Width(m_widgetDimensions.m_width.Get() / m_presenter.GetBoardWidth());
    m_cellDimensions = Dimensions(cellHeight, cellWidth);
    const double smallestDimensionSize = std::min(m_widgetDimensions.m_height.Get(), m_widgetDimensions.m_width.Get());

    // Disc radius:
    const double maximumNbDiscs = std::max(m_presenter.GetBoardHeight() + 1, m_presenter.GetBoardWidth());
    m_theoreticalDiscRadius = (smallestDimensionSize / (maximumNbDiscs * 2.0));

    const double lineWidth = m_theoreticalDiscRadius * LINE_WIDTH_SCALING_FACTOR;
    m_discRadius = m_theoreticalDiscRadius - (lineWidth / 2.0);

    // Discs positions (central and mirror):
    const double halfDiscSize = m_discRadius + lineWidth / 2.0;
    m_horizontalMargin = (cellWidth.Get() - (2.0 * halfDiscSize)) / 2.0;

    m_isDiscMovingHorizontally = p_isDiscMovingHorizontally;
    const bool mirrorToTheLeft = ComputeDiscLeftPosition(m_widgetDimensions.m_width.Get(), halfDiscSize, m_horizontalMargin);
    const bool mirrorToTheRight = ComputeDiscRightPosition(m_widgetDimensions.m_width.Get(), halfDiscSize, m_horizontalMargin);
    ComputeDiscVerticalPosition(halfDiscSize, m_widgetDimensions.m_height.Get());
    m_mirrorDiscPosition.m_y = m_discPosition.m_y;

    m_isMirrorDiscNeeded = (mirrorToTheLeft || mirrorToTheRight);
}

void cxgui::AnimatedBoardModel::Resize(double p_horizontalRatio, double p_verticalRatio)
{
    m_discPosition.m_x *= p_horizontalRatio;
    m_discPosition.m_y *= p_verticalRatio;
}

void cxgui::AnimatedBoardModel::AddDiscDisplacement(double p_horizontal, double p_vertical)
{
    m_discPosition.m_x += p_horizontal;
    m_discPosition.m_y += p_vertical;
}

void cxgui::AnimatedBoardModel::ResetDiscPositions()
{
    m_discPosition = {0.0, 0.0};
    m_mirrorDiscPosition = {0.0, 0.0};
}

size_t cxgui::AnimatedBoardModel::GetFPS() const
{
    return 24u;
}

cxgui::Dimensions cxgui::AnimatedBoardModel::GetCellDimensions() const
{
    return m_cellDimensions;
}

double cxgui::AnimatedBoardModel::GetDiscRadius(AddLineWidth p_addLineWidth) const
{
    if(p_addLineWidth == AddLineWidth::NO)
    {
        return m_theoreticalDiscRadius;
    }

    return m_discRadius;
}

cxmath::Position cxgui::AnimatedBoardModel::GetDiscPosition() const
{
    return m_discPosition;
}

double cxgui::AnimatedBoardModel::GetHorizontalMargin() const
{
    return m_horizontalMargin;
}

cxmath::Position cxgui::AnimatedBoardModel::GetMirrorDiscPosition() const
{
    return m_mirrorDiscPosition;
}

bool cxgui::AnimatedBoardModel::IsMirrorDiscNeeded() const
{
    return m_isMirrorDiscNeeded;
}
