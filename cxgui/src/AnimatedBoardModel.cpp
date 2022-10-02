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

#include <cxinv/assertion.h>
#include <cxmath/math.h>
#include <cxgui/AnimatedBoardModel.h>
#include <cxgui/AnimatedBoardPresenter.h>

namespace
{

constexpr double LINE_WIDTH_SCALING_FACTOR = 0.005;

/**************************************************************************************************
 * @brief Checks if the chip has crossed over to one side of the window.
 *
 * A chip has "crossed over" if some part of it is located outside one edge of the window. For
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
 *                         The chip has not         The chip has
 *                          crossed over.           crossed over.
 *
 *
 * @param p_currentHorizontalPosition
 *      The current horizontal position of the chip's center.
 *
 * @param p_windowWidth
 *      The width of the window.
 *
 * @param p_discRadius
 *      The width of a half chip (the radius and half the chip's line width's width). In Cairo,
 *      only half of the line width is actually included in the chip's path. The other half
 *      crosses the path's boundary.
 *
 * @return `true` if the chip has crossed over, `false` otherwise.
 *
 *************************************************************************************************/
template<cxgui::BoardAnimation A>
bool HasChipCrossedOver(double p_currentHorizontalPosition,
                        double p_windowWidth,
                        const cxmath::Radius& p_discRadius);

template<>
bool HasChipCrossedOver<cxgui::BoardAnimation::MOVE_CHIP_LEFT_ONE_COLUMN>(double p_currentHorizontalPosition,
                                                                          [[maybe_unused]]double p_windowWidth,
                                                                          const cxmath::Radius& p_discRadius)
{
    return p_currentHorizontalPosition < p_discRadius.Get();
}

template<>
bool HasChipCrossedOver<cxgui::BoardAnimation::MOVE_CHIP_RIGHT_ONE_COLUMN>(double p_currentHorizontalPosition,
                                                                           double p_windowWidth,
                                                                           const cxmath::Radius& p_discRadius)
{
    return p_currentHorizontalPosition > p_windowWidth - p_discRadius.Get();
}

/**************************************************************************************************
 * @brief Check if chip has crossed over completely (i.e. all of it should be on the other side).
 *
 * A chip has crossed over completely on one side if all of it is outside the window (at this
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
 *                          The chip has             The chip has
 *                           started to               completely
 *                           cross over.             crossed over.
 *
 *
 * @param p_currentHorizontalPosition
 *      The current horizontal position of the chip's center.
 *
 * @param p_windowWidth
 *      The width of the window.
 *
 * @param p_discRadius
 *      The width of a half chip (the radius and half the chip's line width's width). In Cairo,
 *      only half of the line width is actually included in the chip's path. The other half
 *      crosses the path's boundary.
 *
 * @param p_horizontalMargin
 *      The difference between a half chip and half a chip's drawing space. In between two
 *      adjacent chips, there are two horizontal margins of space. If the chip's drawing
 *      space is a square, or a taller rectangle this margin is zero.
 *
 * @return `true` if the chip has completely crossed over, `false` otherwise.
 *
 *************************************************************************************************/
template<cxgui::BoardAnimation A>
bool HasChipCompletelyCrossedOver(double p_currentHorizontalPosition,
                                  double p_windowWidth,
                                  const cxmath::Radius& p_discRadius,
                                  double p_horizontalMargin);

template<>
bool HasChipCompletelyCrossedOver<cxgui::BoardAnimation::MOVE_CHIP_LEFT_ONE_COLUMN>(double p_currentHorizontalPosition,
                                                                                    [[maybe_unused]] double p_windowWidth,
                                                                                    const cxmath::Radius& p_discRadius,
                                                                                    double p_horizontalMargin)
{
    return cxmath::AreLogicallyEqual(-p_currentHorizontalPosition, p_discRadius.Get() + p_horizontalMargin); 
}

template<>
bool HasChipCompletelyCrossedOver<cxgui::BoardAnimation::MOVE_CHIP_RIGHT_ONE_COLUMN>(double p_currentHorizontalPosition,
                                                                                     double p_windowWidth,
                                                                                     const cxmath::Radius& p_discRadius,
                                                                                     double p_horizontalMargin)
{
    return cxmath::AreLogicallyEqual(p_currentHorizontalPosition, p_windowWidth + p_discRadius.Get() + p_horizontalMargin);
}

/**************************************************************************************************
 * @brief Updates position of the chip so it is drawn on the other side of the window.
 *
 * @param p_currentHorizontalPosition
 *      The current horizontal position of the chip's center.
 *
 * @param p_windowWidth
 *      The width of the window.
 *
 * @param p_discRadius
 *      The width of a half chip (the radius and half the chip's line width's width). In Cairo,
 *      only half of the line width is actually included in the chip's path. The other half
 *      crosses the path's boundary.
 *
 * @param p_horizontalMargin
 *      The difference between a half chip and half a chip's drawing space. In between two
 *      adjacent chips, there are two horizontal margins of space. If the chip's drawing
 *      space is a square, or a taller rectangle this margin is zero.
 *
 *************************************************************************************************/
template<cxgui::BoardAnimation A>
void ComputeChipPositionForOtherSide(double& p_currentHorizontalPosition,
                                     double p_windowWidth,
                                     const cxmath::Radius& p_discRadius,
                                     double p_horizontalMargin);

template<>
void ComputeChipPositionForOtherSide<cxgui::BoardAnimation::MOVE_CHIP_LEFT_ONE_COLUMN>(double& p_currentHorizontalPosition,
                                                                                       double p_windowWidth,
                                                                                       const cxmath::Radius& p_discRadius,
                                                                                       double p_horizontalMargin)
{
    p_currentHorizontalPosition = p_windowWidth - p_discRadius.Get() - p_horizontalMargin;
}

template<>
void ComputeChipPositionForOtherSide<cxgui::BoardAnimation::MOVE_CHIP_RIGHT_ONE_COLUMN>(double& p_currentHorizontalPosition,
                                                                                        [[maybe_unused]] double p_windowWidth,
                                                                                        const cxmath::Radius& p_discRadius,
                                                                                        double p_horizontalMargin)
{
    p_currentHorizontalPosition = p_discRadius.Get() + p_horizontalMargin;
}

/**************************************************************************************************
 * @brief Clamps the chip's extrimity to one side of the window.
 *
 * @param p_currentHorizontalPosition
 *      The current horizontal position of the chip's center.
 *
 * @param p_windowWidth
 *      The width of the window.
 *
 * @param p_discRadius
 *      The width of a half chip (the radius and half the chip's line width's width). In Cairo,
 *      only half of the line width is actually included in the chip's path. The other half
 *      crosses the path's boundary.
 *
 * @param p_horizontalMargin
 *      The difference between a half chip and half a chip's drawing space. In between two
 *      adjacent chips, there are two horizontal margins of space. If the chip's drawing
 *      space is a square, or a taller rectangle this margin is zero.
 *
 *************************************************************************************************/
template<cxgui::BoardAnimation A>
void ClampChipPositionToCurrentSide(double& p_currentHorizontalPosition,
                                    double p_windowWidth,
                                    const cxmath::Radius& p_discRadius,
                                    double p_horizontalMargin);

template<>
void ClampChipPositionToCurrentSide<cxgui::BoardAnimation::MOVE_CHIP_LEFT_ONE_COLUMN>(double& p_currentHorizontalPosition,
                                                                                      [[maybe_unused]] double p_windowWidth,
                                                                                      const cxmath::Radius& p_discRadius,
                                                                                      double p_horizontalMargin)
{
    p_currentHorizontalPosition = p_discRadius.Get() + p_horizontalMargin;
}

template<>
void ClampChipPositionToCurrentSide<cxgui::BoardAnimation::MOVE_CHIP_RIGHT_ONE_COLUMN>(double& p_currentHorizontalPosition,
                                                                                       double p_windowWidth,
                                                                                       const cxmath::Radius& p_discRadius,
                                                                                       double p_horizontalMargin)
{
    p_currentHorizontalPosition = p_windowWidth - p_discRadius.Get() - p_horizontalMargin;
}

/**************************************************************************************************
 * @brief Compute the mirror chip's center position.
 *
 * The "mirror" chip is the chip's double that is drawn to the other side of the window when it
 * crosses over to give the illusion that the chip does not go outside the window (but rather
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
 *     The chip has                                                              And the mirror
 *     crossed over.                                                              chip appears.
 *       
 *
 * @param p_currentMirrorHorizontalPosition
 *      the current horizontal position of the mirror chip's center.
 *
 * @param p_currentHorizontalPosition
 *      the current horizontal position of the chip's center.
 *
 * @param p_windowWidth
 *      The width of the window.
 *
 * @param p_halfChipSize
 *      The width of a half chip (the radius and half the chip's line width's width). In Cairo,
 *      only half of the line width is actually included in the chip's path. The other half
 *      crosses the path's boundary.
 *
 *************************************************************************************************/
template<cxgui::BoardAnimation A>
void ComputeMirrorChipPosition(double& p_currentMirrorHorizontalPosition,
                               double p_currentHorizontalPosition,
                               double p_windowWidth);

template<>
void ComputeMirrorChipPosition<cxgui::BoardAnimation::MOVE_CHIP_LEFT_ONE_COLUMN>(double& p_currentMirrorHorizontalPosition,
                                                                                 double p_currentHorizontalPosition,
                                                                                 double p_windowWidth)
{
    p_currentMirrorHorizontalPosition = p_windowWidth + p_currentHorizontalPosition;
}

template<>
void ComputeMirrorChipPosition<cxgui::BoardAnimation::MOVE_CHIP_RIGHT_ONE_COLUMN>(double& p_currentMirrorHorizontalPosition,
                                                                                  double p_currentHorizontalPosition,
                                                                                  double p_windowWidth)
{
    p_currentMirrorHorizontalPosition = p_currentHorizontalPosition - p_windowWidth;
}

} // namespace

cxgui::AnimatedBoardModel::AnimatedBoardModel(const cxgui::IAnimatedBoardPresenter& p_presenter, const cxgui::AnimationSpeed& p_animationSpeed)
: m_presenter{p_presenter}
, m_animationSpeed{p_animationSpeed}
{
    // Nothing to do...
}

// Compute the current chip's position. If needed, the current mirror chip position is also
// computed. Refer to the subfunction documentation for more details.
template<cxgui::BoardAnimation A>
bool cxgui::AnimatedBoardModel::ComputeChipPosition(double p_windowWidth, const cxmath::Radius& p_discRadius, double p_horizontalMargin)
{
    bool isMirrorChipNeeded = false;

    if(!m_isChipMovingHorizontally)
    {
        if(HasChipCompletelyCrossedOver<A>(m_chipPosition.m_x, p_windowWidth, p_discRadius, p_horizontalMargin))
        {
            // At this point, the chip has completely crossed over to the right,
            // so we update its horizontal location:
            ComputeChipPositionForOtherSide<A>(m_chipPosition.m_x, p_windowWidth, p_discRadius, p_horizontalMargin);
        }
        else if(HasChipCrossedOver<A>(m_chipPosition.m_x, p_windowWidth, p_discRadius))
        {
            // Otherwise, since it is not moving anymore and located completely
            // to the right, we make sure it is completely visible (we do not
            // want half a chip lost in the right edge):
            ClampChipPositionToCurrentSide<A>(m_chipPosition.m_x, p_windowWidth, p_discRadius, p_horizontalMargin);
        }
    }
    else if(HasChipCrossedOver<A>(m_chipPosition.m_x, p_windowWidth, p_discRadius))
    {
        // The chip has gone over the edge on the left, so an extra chip, the mirror
        // chip, will be needed on the far right side for the animation to be smooth.
        // We handle its horizontal position here:
        isMirrorChipNeeded = true;
        ComputeMirrorChipPosition<A>(m_mirrorChipPosition.m_x, m_chipPosition.m_x, p_windowWidth);
    }

    return isMirrorChipNeeded;
}

bool cxgui::AnimatedBoardModel::ComputeChipLeftPosition(double p_windowWidth, const cxmath::Radius& p_discRadius, double p_horizontalMargin)
{
    return ComputeChipPosition<cxgui::BoardAnimation::MOVE_CHIP_LEFT_ONE_COLUMN>(p_windowWidth, p_discRadius, p_horizontalMargin);
}

bool cxgui::AnimatedBoardModel::ComputeChipRightPosition(double p_windowWidth, const cxmath::Radius& p_discRadius, double p_horizontalMargin)
{
    return ComputeChipPosition<cxgui::BoardAnimation::MOVE_CHIP_RIGHT_ONE_COLUMN>(p_windowWidth, p_discRadius, p_horizontalMargin);
}

void cxgui::AnimatedBoardModel::ComputeChipVerticalPosition(const cxmath::Radius& p_discRadius, double p_height)
{
    if(m_chipPosition.m_y < p_discRadius.Get())
    {
        m_chipPosition.m_y = p_discRadius.Get();
    }

    if(m_chipPosition.m_y > p_height - p_discRadius.Get())
    {
        m_chipPosition.m_y = p_height - p_discRadius.Get();
    }
}

void cxgui::AnimatedBoardModel::Update(const cxmath::Dimensions& p_widgetDimensions, bool p_isChipMovingHorizontally)
{
    IF_PRECONDITION_NOT_MET_DO((p_widgetDimensions.m_height.Get() > 0.0 && p_widgetDimensions.m_width.Get() > 0.0), return;);

    // First, we update the dimensions for the animated widgets. They will be the
    // basis for most other quantities:
    m_widgetDimensions = p_widgetDimensions;

    // Cell dimensions:
    const cxmath::Height cellHeight = cxmath::Height(m_widgetDimensions.m_height.Get() / (m_presenter.GetBoardHeight().Get() + 1.0));
    const cxmath::Width cellWidth = cxmath::Width(m_widgetDimensions.m_width.Get() / m_presenter.GetBoardWidth().Get());
    m_cellDimensions = cxmath::Dimensions{cellHeight, cellWidth};
    const double smallestDimensionSize = std::min(m_widgetDimensions.m_height.Get(), m_widgetDimensions.m_width.Get());
    m_cellLineWidth = cxmath::Width{smallestDimensionSize * LINE_WIDTH_SCALING_FACTOR};

    // Chip radius:
    const double maximumNbChips = std::max(m_presenter.GetBoardHeight().Get() + 1, m_presenter.GetBoardWidth().Get());
    m_chipRadius = cxmath::Radius{static_cast<double>((smallestDimensionSize / (maximumNbChips * 2.0)))};
    m_chipLineWidth = cxmath::Width{m_chipRadius.Get() * LINE_WIDTH_SCALING_FACTOR};

    // Chips positions (central and mirror):
    m_horizontalMargin = cxmath::Width{(cellWidth.Get() - (2.0 * m_chipRadius.Get())) / 2.0};

    m_isChipMovingHorizontally = p_isChipMovingHorizontally;
    const bool mirrorToTheLeft = ComputeChipLeftPosition(m_widgetDimensions.m_width.Get(), m_chipRadius, m_horizontalMargin.Get());
    const bool mirrorToTheRight = ComputeChipRightPosition(m_widgetDimensions.m_width.Get(), m_chipRadius, m_horizontalMargin.Get());
    ComputeChipVerticalPosition(m_chipRadius, m_widgetDimensions.m_height.Get());
    m_mirrorChipPosition.m_y = m_chipPosition.m_y;

    m_isMirrorChipNeeded = (mirrorToTheLeft || mirrorToTheRight);
}

void cxgui::AnimatedBoardModel::Resize(const cxgui::ScalingRatios& p_scalingRatios)
{
    IF_PRECONDITION_NOT_MET_DO(p_scalingRatios.m_horizontalRatio.Get() > 0.0 &&
                               p_scalingRatios.m_verticalRatio.Get() > 0.0,
                               return;);

    m_chipPosition.m_x *= p_scalingRatios.m_horizontalRatio.Get();
    m_chipPosition.m_y *= p_scalingRatios.m_verticalRatio.Get();
}

void cxgui::AnimatedBoardModel::AddChipDisplacement(const cxmath::Height& p_vertical, const cxmath::Width& p_horizontal)
{
    m_chipPosition.m_x += p_horizontal.Get();
    m_chipPosition.m_y += p_vertical.Get();
}

void cxgui::AnimatedBoardModel::ResetChipPositions()
{
    const double horizontalStartPosition = m_horizontalMargin.Get() + m_chipRadius.Get();

    m_chipPosition = {horizontalStartPosition, 0.0};
    m_mirrorChipPosition = {horizontalStartPosition, 0.0};
}

void cxgui::AnimatedBoardModel::UpdateCurrentColumn(const cxmodel::Column& p_newCurrentColumn)
{
    m_currentColumn = p_newCurrentColumn;
}

cxgui::FPS cxgui::AnimatedBoardModel::GetFPS() const
{
    return cxgui::FPS{24u};
}

cxgui::AnimationSpeed cxgui::AnimatedBoardModel::GetAnimationSpeed() const
{
    return m_animationSpeed;
}

const cxmath::Dimensions& cxgui::AnimatedBoardModel::GetAnimatedAreaDimensions() const
{
    return m_widgetDimensions;
}

const cxmath::Dimensions& cxgui::AnimatedBoardModel::GetCellDimensions() const
{
    return m_cellDimensions;
}

cxmath::Radius cxgui::AnimatedBoardModel::GetChipRadius() const
{
    return m_chipRadius;
}

const cxmath::Position& cxgui::AnimatedBoardModel::GetChipPosition() const
{
    return m_chipPosition;
}

cxmath::Width cxgui::AnimatedBoardModel::GetHorizontalMargin() const
{
    return m_horizontalMargin;
}

const cxmath::Position& cxgui::AnimatedBoardModel::GetMirrorChipPosition() const
{
    return m_mirrorChipPosition;
}

bool cxgui::AnimatedBoardModel::IsMirrorChipNeeded() const
{
    return m_isMirrorChipNeeded;
}

cxmath::Width cxgui::AnimatedBoardModel::GetLineWidth(Feature p_feature) const
{
    switch(p_feature)
    {
        case Feature::CELL:
            return m_cellLineWidth;

        case Feature::CHIP:
            return m_chipLineWidth;

        default:
            ASSERT_ERROR_MSG("Unknown feature type.");
            return cxmath::Width{0.0};
    }
}

const cxmodel::Column& cxgui::AnimatedBoardModel::GetCurrentColumn() const
{
    return m_currentColumn;
}
