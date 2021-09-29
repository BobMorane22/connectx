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
 * @file AnimatedBoard.cpp
 * @date 2021
 *
 *************************************************************************************************/

#include <algorithm>
#include <chrono>
#include <cmath>
#include <iostream>

#include <gdkmm/display.h>
#include <gdkmm/general.h>
#include <glibmm/main.h>

#include <cxinv/include/assertion.h>
#include <cxmodel/include/Color.h>
#include <cxmodel/include/Disc.h>

#include "AnimatedBoard.h"
#include "common.h"
#include "ContextRestoreRAII.h"
#include "IGameViewPresenter.h"
#include "pathHelpers.h"

#define UNUSED(p_parameter) (void)p_parameter

namespace
{

constexpr double LINE_WIDTH_SCALING_FACTOR = 0.005;

constexpr bool STOP_EVENT_PROPAGATION = true;
constexpr bool PROPAGATE_EVENT = false;

/**************************************************************************************************
 * @brief Draw a disc.
 *
 * The disc will have a boarder around it.
 *
 * @param p_context
 *      The cairo context to use.
 * @param p_centerPosition
 *      The disc's wanted center position.
 * @param p_radius
 *      The discs wanted radius.
 * @param p_backgroundColor
 *      The discs wanted background color.
 *
 *************************************************************************************************/
void DrawDisc(const Cairo::RefPtr<Cairo::Context>& p_context,
              const cxmath::Position& p_centerPosition,
              double p_radius,
              const cxmodel::ChipColor& p_backgroundColor)
{
    cxgui::ContextRestoreRAII contextRestoreRAII{p_context};

    cxgui::MakeCircularPath(p_context, p_centerPosition, p_radius);

    // Set background color:
    p_context->set_source_rgba(cxmodel::NormalizedR(p_backgroundColor),
                               cxmodel::NormalizedG(p_backgroundColor),
                               cxmodel::NormalizedB(p_backgroundColor),
                               cxmodel::NormalizedA(p_backgroundColor));

    // Draw everything:
    p_context->fill();
}

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
                                                                          double p_windowWidth,
                                                                          double p_halfDiscSize)
{
    UNUSED(p_windowWidth);
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
                                                                                    double p_windowWidth,
                                                                                    double p_halfDiscSize,
                                                                                    double p_horizontalMargin)
{
    UNUSED(p_windowWidth);
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
                                                                                        double p_windowWidth,
                                                                                        double p_halfDiscSize,
                                                                                        double p_horizontalMargin)
{
    UNUSED(p_windowWidth);
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
                                                                                      double p_windowWidth,
                                                                                      double p_halfDiscSize,
                                                                                      double p_horizontalMargin)
{
    UNUSED(p_windowWidth);
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

cxgui::AnimatedBoard::AnimatedBoard(const IGameViewPresenter& p_presenter, size_t p_speed)
: m_speed{p_speed}
{
    m_presenter = std::make_unique<cxgui::AnimatedBoardPresenter>(p_presenter);

    // Customize width and height according to window dimension.
    const int nbRows = m_presenter->GetBoardHeight();
    const int nbColumns = m_presenter->GetBoardWidth();
    const int chipDimension = ComputeMinimumChipDimension(nbRows, nbColumns);
    set_size_request(nbColumns * chipDimension, nbRows * chipDimension);

    set_vexpand(true);
    set_hexpand(true);

    // In time, make proper RAII:
    m_timer = Glib::signal_timeout().connect([this](){return Redraw();}, 1000.0/m_FPS);

    // Resize events:
    signal_configure_event().connect([this](GdkEventConfigure* p_event){
        IF_CONDITION_NOT_MET_DO(p_event, return STOP_EVENT_PROPAGATION;);

        return OnResize(static_cast<double>(p_event->height), static_cast<double>(p_event->width));
    });

    POSTCONDITION(m_presenter);
}

cxgui::AnimatedBoard::~AnimatedBoard()
{
    m_timer.disconnect();
}

// Performs an "frame increment". This is called on every tick (m_FPS times/sec) and
// keeps track of all displacements. It also notifies when the animation completes.
void cxgui::AnimatedBoard::PerformChipAnimation(BoardAnimation p_animation)
{
    // Get window dimensions:
    const Gtk::Allocation allocation = get_allocation();

    switch(p_animation)
    {
        case cxgui::BoardAnimation::MOVE_CHIP_LEFT_ONE_COLUMN:
        {
            const double width = static_cast<double>(allocation.get_width());
            const double oneAnimationWidth = width / m_presenter->GetBoardWidth();
            const double delta = oneAnimationWidth / (static_cast<double>(m_FPS) / static_cast<double>(m_speed));

            if(m_totalMoveLeftDisplacement >= oneAnimationWidth || std::abs(m_totalMoveLeftDisplacement - oneAnimationWidth) <= 1e-6)
            {
                if(m_currentColumn <= 0)
                {
                    m_currentColumn = m_presenter->GetBoardWidth() - 1;
                }
                else
                {
                    --m_currentColumn;
                }

                // End animation:
                m_totalMoveLeftDisplacement = 0.0;
                m_animateMoveLeft = false;
                m_presenter->Sync();
                Notify(cxgui::BoardAnimationNotificationContext::POST_ANIMATE_MOVE_LEFT_ONE_COLUMN);
                return;
            }
            else
            {
                m_x -= delta;
                m_totalMoveLeftDisplacement += delta;
            }

            break;
        }
        case cxgui::BoardAnimation::MOVE_CHIP_RIGHT_ONE_COLUMN:
        {
            const double width = static_cast<double>(allocation.get_width());
            const double oneAnimationWidth = width / m_presenter->GetBoardWidth();
            const double delta = oneAnimationWidth / (static_cast<double>(m_FPS) / static_cast<double>(m_speed));

            if(m_totalMoveRightDisplacement >= oneAnimationWidth || std::abs(m_totalMoveRightDisplacement - oneAnimationWidth) <= 1e-6)
            {
                if(m_currentColumn >= m_presenter->GetBoardWidth() - 1u)
                {
                    m_currentColumn = 0;
                }
                else
                {
                    ++m_currentColumn;
                }

                // End animation:
                m_totalMoveRightDisplacement = 0.0;
                m_animateMoveRight = false;
                m_presenter->Sync();
                Notify(cxgui::BoardAnimationNotificationContext::POST_ANIMATE_MOVE_RIGHT_ONE_COLUMN);
                return;
            }
            else
            {
                m_x += delta;
                m_totalMoveRightDisplacement += delta;
            }

            break;
        }
        case cxgui::BoardAnimation::DROP_CHIP:
        {
            const double height = static_cast<double>(allocation.get_height());
            const double cellHeight = height / (m_presenter->GetBoardHeight() + 1.0);
            const double oneAnimationHeight = (GetDropPosition(m_currentColumn) + 1.0) * cellHeight;

            // Since the falling distance may vary, the number of frames needed for the
            // animation has to be adjusted to make sure the speed is constant for the
            // user:
            const double relativeFPS = static_cast<double>(m_FPS) * (oneAnimationHeight / (height - cellHeight));
            const double delta = oneAnimationHeight / std::ceil(relativeFPS / static_cast<double>(m_speed));

            if(m_totalMoveDownDisplacement >= oneAnimationHeight || std::abs(m_totalMoveDownDisplacement - oneAnimationHeight) <= 1e-6)
            {
                // End animation:
                m_totalMoveDownDisplacement = 0.0;
                m_animateMoveDown = false;
                m_presenter->Sync();
                Notify(cxgui::BoardAnimationNotificationContext::POST_ANIMATE_DROP_CHIP);
                return;
            }
            else
            {
                m_y += delta;
                m_totalMoveDownDisplacement += delta;
            }

            break;
        }
        default:
        {
            ASSERT_ERROR_MSG("Unsupported move.");
        }
    }
}

size_t cxgui::AnimatedBoard::GetCurrentColumn() const
{
    return m_currentColumn;
}

cxmodel::ChipColor cxgui::AnimatedBoard::GetCurrentChipColor() const
{
    // I don't think this is good. The problem is that the animation
    // is performed AFTER the model is updated. This means that the
    // active player is seen by the presenter is not the active player
    // that should be used by the animation. It should be the previous
    // player.
    //
    // To solve this, a cache of the presenter's state should be introduced
    // here, keeping all previous states. The cache could be updated
    // once the animation is completed.
    return m_presenter->GetActivePlayerChipColor();
}

// Compute the current disc's position. If needed, the current mirror disc position is also
// computed. Refer to the subfunction documentation for more details.
template<cxgui::BoardAnimation A>
bool cxgui::AnimatedBoard::ComputeDiscPosition(double p_windowWidth, double p_halfDiscSize, double p_horizontalMargin)
{
    bool isMirrorDiscNeeded = false;

    const bool isDiscMovingHorizontally = (m_animateMoveLeft || m_animateMoveRight);
    if(!isDiscMovingHorizontally)
    {
        if(HasDiscCompletelyCrossedOver<A>(m_x, p_windowWidth, p_halfDiscSize, p_horizontalMargin))
        {
            // At this point, the disc has completely crossed over to the right,
            // so we update its horizontal location:
            ComputeDiscPositionForOtherSide<A>(m_x, p_windowWidth, p_halfDiscSize, p_horizontalMargin);
        }
        else if(HasDiscCrossedOver<A>(m_x, p_windowWidth, p_halfDiscSize))
        {
            // Otherwise, since it is not moving anymore and located completely
            // to the right, we make sure it is completely visible (we do not
            // want half a disc lost in the right edge):
            ClampDiscPositionToCurrentSide<A>(m_x, p_windowWidth, p_halfDiscSize, p_horizontalMargin);
        }
    }
    else if(HasDiscCrossedOver<A>(m_x, p_windowWidth, p_halfDiscSize))
    {
        // The disc has gone over the edge on the left, so an extra disc, the mirror
        // disc, will be needed on the far right side for the animation to be smooth.
        // We handle its horizontal position here:
        isMirrorDiscNeeded = true;
        ComputeMirrorDiscPosition<A>(m_xx, m_x, p_windowWidth);
    }

    return isMirrorDiscNeeded;
}

bool cxgui::AnimatedBoard::ComputeDiscLeftPosition(double p_windowWidth, double p_halfDiscSize, double p_horizontalMargin)
{
    return ComputeDiscPosition<cxgui::BoardAnimation::MOVE_CHIP_LEFT_ONE_COLUMN>(p_windowWidth, p_halfDiscSize, p_horizontalMargin);
}

bool cxgui::AnimatedBoard::ComputeDiscRightPosition(double p_windowWidth, double p_halfDiscSize, double p_horizontalMargin)
{
    return ComputeDiscPosition<cxgui::BoardAnimation::MOVE_CHIP_RIGHT_ONE_COLUMN>(p_windowWidth, p_halfDiscSize, p_horizontalMargin);
}

void cxgui::AnimatedBoard::ComputeDiscVerticalPosition(const double p_halfDiscSize, double p_height)
{
    if(m_y < p_halfDiscSize)
    {
        m_y = p_halfDiscSize;
    }

    if(m_y > p_height - p_halfDiscSize)
    {
        m_y = p_height - p_halfDiscSize;
    }
}

// Does the actual drawing. Be careful it mofifying this, it is performance
// critical:
//
//  1. Draw to surfaces to avoid over using the X server.
//  2. Cache the results to avoid redrawing the same things every time.
//
// Make sure that if you change this, the performance is not decreased.
bool cxgui::AnimatedBoard::on_draw(const Cairo::RefPtr<Cairo::Context>& p_context)
{
    using namespace std::chrono;

    // Get window dimensions:
    const Gtk::Allocation allocation = get_allocation();
    const double height = static_cast<double>(allocation.get_height());
    const double width = static_cast<double>(allocation.get_width());
    const double smallestDimensionSize = std::min(width, height);

    // Prepare data for an eventual resize. We keep track of previous frame dimensions
    // to allow calculating a scaling factor:
    m_lastFrameHeight = height;
    m_lastFrameWidth = width;

    // Compute useful dimensions:
    const double maximumNbDiscs = std::max(m_presenter->GetBoardHeight() + 1, m_presenter->GetBoardWidth());
    const double theoreticalRadius = (smallestDimensionSize / (maximumNbDiscs * 2.0));
    const double lineWidth = theoreticalRadius * LINE_WIDTH_SCALING_FACTOR;
    const double radius = theoreticalRadius - lineWidth / 2.0;
    const double halfDiscSize = radius + lineWidth / 2.0;
    const double horizontalMargin = ((width / m_presenter->GetBoardWidth()) - 2 * halfDiscSize) / 2.0;

    // Compute disc(s) position(s):
    const bool mirrorToTheLeft = ComputeDiscLeftPosition(width, halfDiscSize, horizontalMargin);
    const bool mirrorToTheRight = ComputeDiscRightPosition(width, halfDiscSize, horizontalMargin);
    ComputeDiscVerticalPosition(halfDiscSize, height);

    auto buffer = Cairo::ImageSurface::create(Cairo::Format::FORMAT_ARGB32, width, height);
    const auto bufferContext = Cairo::Context::create(buffer);

    // Draw colum highlight:
    DrawActiveColumnHighlight(bufferContext);

    // Draw Disc(s):
    const cxmodel::ChipColor chipColor = m_presenter->GetActivePlayerChipColor();
    DrawDisc(bufferContext, {m_x, m_y}, radius, chipColor);
    if(mirrorToTheLeft || mirrorToTheRight)
    {
        DrawDisc(bufferContext, {m_xx, m_y}, radius, chipColor);
    }

    // Draw the game board:
    m_boardElementsCache.Clear();
    for(size_t row = 0u; row < m_presenter->GetBoardHeight(); ++row)
    {
        for(size_t column = 0u; column < m_presenter->GetBoardWidth(); ++column)
        {
            DrawBoardElement(bufferContext, row, column);
        }
    }

    // Draw the whole thing:
    p_context->set_source(buffer, 0, 0);
    p_context->paint();

    return true;
}

// Draws a "column highlight" that follows the current chip. This helps the user locate the
// current column. Especially helpful on larger boards.
void cxgui::AnimatedBoard::DrawActiveColumnHighlight(const Cairo::RefPtr<Cairo::Context>& p_context)
{
    // Get window information:
    const Gtk::Allocation allocation = get_allocation();
    const double height = static_cast<double>(allocation.get_height());
    const double width = static_cast<double>(allocation.get_width());
    const double cellHeight = (height / (m_presenter->GetBoardHeight() + 1.0));
    const double cellWidth = (width / m_presenter->GetBoardWidth());
    const double halfCellWidth = cellWidth / 2.0;

    cxgui::ContextRestoreRAII contextRestoreRAII{p_context};

    cxgui::MakeRectanglarPath(p_context,
                              {m_x - halfCellWidth, cellHeight},
                              height - cellHeight,
                              cellWidth);

    // Set background color:
    p_context->set_source_rgba(0.3, 0.3, 0.3, 0.5);

    // Draw everything:
    p_context->fill_preserve();
    p_context->stroke();
}

// See `on_draw()`. Basically draws a disc and the rectangular space around it (which has the board color). All
// these elements together make the board.
void cxgui::AnimatedBoard::DrawBoardElement(const Cairo::RefPtr<Cairo::Context>& p_context, size_t p_row, size_t p_column)
{
    // Get window information:
    const Gtk::Allocation allocation = get_allocation();
    const double height = static_cast<double>(allocation.get_height());
    const double width = static_cast<double>(allocation.get_width());

    // Compute cell dimensions:
    const double cellWidth = (width / m_presenter->GetBoardWidth());
    const double cellHeight = (height / (m_presenter->GetBoardHeight() + 1.0));

    // Compute disc radius:
    const double smallestDimensionSize = std::min(width, height);
    const double lineWidth = smallestDimensionSize * LINE_WIDTH_SCALING_FACTOR;
    const double maximumNbDiscs = std::max(m_presenter->GetBoardHeight() + 1, m_presenter->GetBoardWidth());
    const double radius = (smallestDimensionSize / (maximumNbDiscs * 2.0)) - lineWidth / 2.0;

    const IGameViewPresenter::ChipColors& chipColors = m_presenter->GetBoardChipColors();
    const cxmodel::ChipColor chipColor = chipColors[p_row][p_column];
    if(m_boardElementsCache.HasElement(chipColor))
    {
        // Paint that part to the canvas:
        Gdk::Cairo::set_source_pixbuf(p_context, m_boardElementsCache.Get(chipColor), p_column * cellWidth, (p_row + 1) * cellHeight);
        p_context->paint();

        return;
    }

    // Add a little extra to cover everything...
    auto buffer = Cairo::ImageSurface::create(Cairo::Format::FORMAT_ARGB32, cellWidth + lineWidth, cellHeight + lineWidth);
    const auto bufferContext = Cairo::Context::create(buffer);
    {
        cxgui::ContextRestoreRAII contextRestoreRAII{bufferContext};

        // Draw paths for disc space and the cell contour:
        cxgui::MakeCircularPath(bufferContext, {cellWidth / 2.0, cellHeight / 2.0}, radius);
        cxgui::MakeRectanglarPath(bufferContext, {0.0, 0.0}, cellHeight, cellWidth);

        // Set background color:
        bufferContext->set_source_rgba(0.0, 0.0, 0.8, 1.0);

        // Draw everything:
        bufferContext->set_fill_rule(Cairo::FILL_RULE_EVEN_ODD);
        bufferContext->fill_preserve();
        bufferContext->stroke();
    }

    // Add border and draw model discs:
    {
        cxgui::ContextRestoreRAII contextRestoreRAII{bufferContext};

        cxgui::MakeCircularPath(bufferContext, {cellWidth / 2.0, cellHeight / 2.0}, radius);

        bufferContext->set_source_rgba(cxmodel::NormalizedR(chipColor),
                                       cxmodel::NormalizedG(chipColor),
                                       cxmodel::NormalizedB(chipColor),
                                       cxmodel::NormalizedA(chipColor));

        bufferContext->fill();
    }

    // Add to the cache:
    const Glib::RefPtr<Gdk::Pixbuf> boardElement = Gdk::Pixbuf::create(buffer, 0, 0, cellWidth + lineWidth, cellHeight + lineWidth);
    m_boardElementsCache.Add(chipColor, boardElement);

    // Paint that part to the canvas:
    p_context->set_source(buffer, p_column * cellWidth, (p_row + 1) * cellHeight);
    p_context->paint();
}

// Schedule redraws for specific board regions. Called m_FPS times per second.
//
// This function is critical for performance: redrawing too often or too much
// (ex.: redraw the whole widget every time) can be very costly, especially
// with lots of board elements and in full screen. Be careful when modifying
// this.
bool cxgui::AnimatedBoard::Redraw()
{
    // Schedule a redraw on the next frame:
    if(m_animateMoveLeft)
    {
        const Gtk::Allocation allocation = get_allocation();
        const double height = static_cast<double>(allocation.get_height());
        const double width = static_cast<double>(allocation.get_width());
        const double cellWidth = width / m_presenter->GetBoardWidth();
        const double delta = cellWidth / (static_cast<double>(m_FPS) / static_cast<double>(m_speed));

        if(m_x < cellWidth / 2.0)
        {
            // Because of the mirror disc, redraw the whole screen.
            queue_draw();
        }
        else
        {
            queue_draw_area(m_x - cellWidth/2 - delta, 0, cellWidth + 3*delta, height);
        }

        PerformChipAnimation(cxgui::BoardAnimation::MOVE_CHIP_LEFT_ONE_COLUMN);
    }
    if(m_animateMoveRight)
    {
        const Gtk::Allocation allocation = get_allocation();
        const double height = static_cast<double>(allocation.get_height());
        const double width = static_cast<double>(allocation.get_width());
        const double cellWidth = width / m_presenter->GetBoardWidth();
        const double delta = cellWidth / (static_cast<double>(m_FPS) / static_cast<double>(m_speed));

        if(m_x > width - cellWidth / 2.0)
        {
            // Because of the mirror disc, redraw the whole screen.
            queue_draw();
        }
        else
        {
            queue_draw_area(m_x - cellWidth/2 - delta, 0, cellWidth + 3*delta, height);
        }

        PerformChipAnimation(cxgui::BoardAnimation::MOVE_CHIP_RIGHT_ONE_COLUMN);
    }
    if(m_animateMoveDown)
    {
        const Gtk::Allocation allocation = get_allocation();
        const double height = static_cast<double>(allocation.get_height());
        const double width = static_cast<double>(allocation.get_width());
        const double cellWidth = width / m_presenter->GetBoardWidth();

        queue_draw_area(m_x - cellWidth/1.5, 0, 1.5*cellWidth, height);
        PerformChipAnimation(cxgui::BoardAnimation::DROP_CHIP);
    }

    return true;
}

// Called when the window is resized. Positions are updated to fit the
// new ratio.
bool cxgui::AnimatedBoard::OnResize(double p_newHeight, double p_newWidth)
{
    // Handling initial values to avoid division by zero:
    if(m_lastFrameHeight == 0.0)
    {
        return STOP_EVENT_PROPAGATION;
    }

    if(m_lastFrameWidth == 0.0)
    {
        return STOP_EVENT_PROPAGATION;
    }

    // Now the real work:
    if(!cxmath::AreLogicallyEqual(p_newHeight, m_lastFrameHeight))
    {
        const double verticalRatio = p_newHeight / m_lastFrameHeight;
        m_y *= verticalRatio;
    }

    if(!cxmath::AreLogicallyEqual(p_newWidth, m_lastFrameWidth))
    {
        const double horizontalRatio = p_newWidth / m_lastFrameWidth;
        m_x *= horizontalRatio;
        m_totalMoveLeftDisplacement *= horizontalRatio;
        m_totalMoveRightDisplacement *= horizontalRatio;
    }

    return STOP_EVENT_PROPAGATION;
}

// Called in repetition until the animation completes.
void cxgui::AnimatedBoard::Update(cxgui::BoardAnimationNotificationContext p_context, BoardAnimationSubject* p_subject)
{
    IF_CONDITION_NOT_MET_DO(p_subject, return;);

    switch(p_context)
    {
        case cxgui::BoardAnimationNotificationContext::ANIMATE_MOVE_LEFT_ONE_COLUMN:
        {
            m_animateMoveLeft = true;
            PerformChipAnimation(cxgui::BoardAnimation::MOVE_CHIP_LEFT_ONE_COLUMN);
            break;
        }
        case cxgui::BoardAnimationNotificationContext::ANIMATE_MOVE_RIGHT_ONE_COLUMN:
        {
            m_animateMoveRight = true;
            PerformChipAnimation(cxgui::BoardAnimation::MOVE_CHIP_RIGHT_ONE_COLUMN);
            break;
        }
        case cxgui::BoardAnimationNotificationContext::ANIMATE_MOVE_DROP_CHIP:
        {
            m_animateMoveDown = true;
            PerformChipAnimation(cxgui::BoardAnimation::DROP_CHIP);
            break;
        }
        default:
        {
            ASSERT_ERROR_MSG("Unsupported notification context");
        }
    }
}

int cxgui::AnimatedBoard::GetDropPosition(int p_column) const
{
    const IGameViewPresenter::ChipColors& chipColors = m_presenter->GetBoardChipColors();

    for(int row = m_presenter->GetBoardHeight() - 1; row >= 0; --row)
    {
        if(chipColors[row][p_column] == cxmodel::MakeTransparent())
        {
            return row;
        }
    }

    ASSERT_ERROR_MSG("Column unavailable. Check of availability first");

    return 0;
}

// Computes the best chip dimension so that the game view, when the board is present with all
// chips drawn, is entirely viewable on the user's screen.
int cxgui::AnimatedBoard::ComputeMinimumChipDimension(size_t p_nbRows, size_t p_nbColumns) const
{
    // Get screen containing the widget:
    const Glib::RefPtr<const Gdk::Screen> screen = get_screen();
    IF_CONDITION_NOT_MET_DO(bool(screen), return -1;);

    // Get the screen dimensions:
    const int fullScreenHeight = screen->get_height();
    const int fullScreenWidth = screen->get_width();

    // Get minimum screen dimension:
    const int minFullScreenDimension = std::min(fullScreenHeight, fullScreenWidth);

    // First, we check if the chips can use their default size:
    int nbRows = static_cast<int>(p_nbRows);
    int nbColumns = static_cast<int>(p_nbColumns);

    if(nbRows * cxgui::DEFAULT_CHIP_SIZE < (2 * fullScreenHeight) / 3)
    {
        if(nbColumns * cxgui::DEFAULT_CHIP_SIZE < (2 * fullScreenWidth) / 3)
        {
            return cxgui::DEFAULT_CHIP_SIZE;
        }
    }

    // The the biggest board dimension:
    const int maxBoardDimension = std::max(nbRows, nbColumns);

    // From this, the max chip dimension (dimension at which together, chips from the board would fill the
    // entire screen in its smallest dimension) is computed:
    const int maxChipDimension = (minFullScreenDimension / maxBoardDimension);

    // We take two thirds from this value for the board (leaving the remaining to the rest of the
    // game view):
    return (maxChipDimension * 2) / 3;
}
