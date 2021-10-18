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
 * @todo Remove hardoded background color. It should be a constant.
 * @todo In model, change "disc" to "chip".
 * @todo In model, replace naked "doubles" by strong types, especially when there is more than
 *       one parameter.
 * @todo In model, clarify the notion of "line width". It is not clear what it means, and it
 *       does not always have the same meaning. For example, there is a line width for chips, and
 *       another one for board elements. This is just too confusing for the user.
 * @todo In model, make all Get*() methods return a const reference (to avoid useless copy).
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

#include "AnimatedBoardModel.h"
#include "AnimatedBoard.h"
#include "common.h"
#include "ContextRestoreRAII.h"
#include "IGameViewPresenter.h"
#include "pathHelpers.h"

namespace
{

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

} // namespace

cxgui::AnimatedBoard::AnimatedBoard(const IGameViewPresenter& p_presenter, size_t p_speed)
: m_speed{p_speed}
{
    m_presenter = std::make_unique<cxgui::AnimatedBoardPresenter>(p_presenter);
    m_animationModel = std::make_unique<cxgui::AnimatedBoardModel>(*m_presenter);

    // Customize width and height according to window dimension.
    const int nbRows = m_presenter->GetBoardHeight();
    const int nbColumns = m_presenter->GetBoardWidth();
    const int chipDimension = ComputeMinimumChipDimension(nbRows, nbColumns);
    set_size_request(nbColumns * chipDimension, nbRows * chipDimension);

    set_vexpand(true);
    set_hexpand(true);

    // In time, make proper RAII:
    m_timer = Glib::signal_timeout().connect([this](){return Redraw();}, 1000.0/m_animationModel->GetFPS());

    // Resize events:
    signal_configure_event().connect([this](GdkEventConfigure* p_event){
        IF_CONDITION_NOT_MET_DO(p_event, return STOP_EVENT_PROPAGATION;);

        return OnResize(static_cast<double>(p_event->height), static_cast<double>(p_event->width));
    });

    POSTCONDITION(m_presenter);
    POSTCONDITION(m_animationModel);
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
            const double delta = oneAnimationWidth / (static_cast<double>(m_animationModel->GetFPS()) / static_cast<double>(m_speed));

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
                m_animationModel->AddDiscDisplacement(-delta, 0.0);
                m_totalMoveLeftDisplacement += delta;
            }

            break;
        }
        case cxgui::BoardAnimation::MOVE_CHIP_RIGHT_ONE_COLUMN:
        {
            const double width = static_cast<double>(allocation.get_width());
            const double oneAnimationWidth = width / m_presenter->GetBoardWidth();
            const double delta = oneAnimationWidth / (static_cast<double>(m_animationModel->GetFPS()) / static_cast<double>(m_speed));

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
                m_animationModel->AddDiscDisplacement(delta, 0.0);
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
            const double relativeFPS = static_cast<double>(m_animationModel->GetFPS()) * (oneAnimationHeight / (height - cellHeight));
            const double delta = oneAnimationHeight / std::ceil(relativeFPS / static_cast<double>(m_speed));

            if(m_totalMoveDownDisplacement >= oneAnimationHeight || std::abs(m_totalMoveDownDisplacement - oneAnimationHeight) <= 1e-6)
            {
                // End animation:
                m_totalMoveDownDisplacement = 0.0;
                m_animateMoveDown = false;

                // Reinitialize disc:
                m_animationModel->ResetDiscPositions();
                m_currentColumn = 0u;

                m_presenter->Sync();

                Notify(cxgui::BoardAnimationNotificationContext::POST_ANIMATE_DROP_CHIP);
                return;
            }
            else
            {
                m_animationModel->AddDiscDisplacement(0.0, delta);
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

// Does the actual drawing. Be careful it mofifying this, it is performance
// critical:
//
//  1. Draw to surfaces to avoid over using the X server.
//  2. Cache the results to avoid redrawing the same things every time.
//
// Make sure that if you change this, the performance is not decreased.
bool cxgui::AnimatedBoard::on_draw(const Cairo::RefPtr<Cairo::Context>& p_context)
{
    // Get window dimensions and update the model:
    const Gtk::Allocation allocation = get_allocation();
    const double height = static_cast<double>(allocation.get_height());
    const double width = static_cast<double>(allocation.get_width());
    m_animationModel->Update({Height{height}, Width{width}}, m_animateMoveLeft || m_animateMoveRight);

    // Prepare data for an eventual resize. We keep track of previous frame dimensions
    // to allow calculating a scaling factor:
    m_lastFrameHeight = height;
    m_lastFrameWidth = width;

    auto buffer = Cairo::ImageSurface::create(Cairo::Format::FORMAT_ARGB32, width, height);
    const auto bufferContext = Cairo::Context::create(buffer);

    // Draw colum highlight:
    DrawActiveColumnHighlight(bufferContext);

    // Draw Disc(s):
    const cxmodel::ChipColor chipColor = m_presenter->GetActivePlayerChipColor();
    DrawDisc(bufferContext,
             m_animationModel->GetDiscPosition(),
             m_animationModel->GetDiscRadius(AddLineWidth::YES),
             chipColor);

    if(m_animationModel->IsMirrorDiscNeeded())
    {
        DrawDisc(bufferContext,
                 m_animationModel->GetMirrorDiscPosition(),
                 m_animationModel->GetDiscRadius(AddLineWidth::YES),
                 chipColor);
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
    const Dimensions cellDimensions = m_animationModel->GetCellDimensions();
    const double cellWidth = cellDimensions.m_width.Get();
    const double cellHeight = cellDimensions.m_height.Get();

    cxgui::ContextRestoreRAII contextRestoreRAII{p_context};

    cxgui::MakeRectanglarPath(p_context,
                              {m_animationModel->GetDiscPosition().m_x - (cellWidth / 2.0), cellHeight},
                              m_animationModel->GetAnimatedAreaDimensions().m_height.Get() - cellHeight,
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
    const Dimensions cellDimensions = m_animationModel->GetCellDimensions();
    const double cellWidth = cellDimensions.m_width.Get();
    const double cellHeight = cellDimensions.m_height.Get();
    const double radius = m_animationModel->GetDiscRadius(AddLineWidth::NO) - (m_animationModel->GetLineWidth() / 2.0);

    const IGameViewPresenter::ChipColors& chipColors = m_presenter->GetBoardChipColors();
    const cxmodel::ChipColor chipColor = chipColors[p_row][p_column];
    if(m_boardElementsCache.HasElement(chipColor))
    {
        // Paint that part to the canvas:
        Gdk::Cairo::set_source_pixbuf(p_context,
                                      m_boardElementsCache.Get(chipColor),
                                      p_column * cellWidth,
                                      (p_row + 1) * cellHeight);
        p_context->paint();

        return;
    }

    // Add a little extra to cover everything...
    auto buffer = Cairo::ImageSurface::create(Cairo::Format::FORMAT_ARGB32,
                                              cellWidth + m_animationModel->GetLineWidth(),
                                              cellHeight + m_animationModel->GetLineWidth());
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
    const Glib::RefPtr<Gdk::Pixbuf> boardElement = Gdk::Pixbuf::create(buffer,
                                                                       0,
                                                                       0,
                                                                       cellWidth + m_animationModel->GetLineWidth(),
                                                                       cellHeight + m_animationModel->GetLineWidth());
    m_boardElementsCache.Add(chipColor, boardElement);

    // Paint that part to the canvas:
    p_context->set_source(buffer,
                          p_column * cellWidth,
                          (p_row + 1) * cellHeight);
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
    const double chipHorizontalPosition = m_animationModel->GetDiscPosition().m_x;

    // Schedule a redraw on the next frame:
    if(m_animateMoveLeft)
    {
        const Gtk::Allocation allocation = get_allocation();
        const double height = static_cast<double>(allocation.get_height());
        const double width = static_cast<double>(allocation.get_width());
        const double cellWidth = width / m_presenter->GetBoardWidth();
        const double delta = cellWidth / (static_cast<double>(m_animationModel->GetFPS()) / static_cast<double>(m_speed));

        if(chipHorizontalPosition < cellWidth / 2.0)
        {
            // Because of the mirror disc, redraw the whole screen.
            queue_draw();
        }
        else
        {
            queue_draw_area(chipHorizontalPosition - cellWidth/2 - delta, 0, cellWidth + 3*delta, height);
        }

        PerformChipAnimation(cxgui::BoardAnimation::MOVE_CHIP_LEFT_ONE_COLUMN);
    }
    if(m_animateMoveRight)
    {
        const Gtk::Allocation allocation = get_allocation();
        const double height = static_cast<double>(allocation.get_height());
        const double width = static_cast<double>(allocation.get_width());
        const double cellWidth = width / m_presenter->GetBoardWidth();
        const double delta = cellWidth / (static_cast<double>(m_animationModel->GetFPS()) / static_cast<double>(m_speed));

        if(chipHorizontalPosition > width - cellWidth / 2.0)
        {
            // Because of the mirror disc, redraw the whole screen.
            queue_draw();
        }
        else
        {
            queue_draw_area(chipHorizontalPosition - cellWidth/2 - delta, 0, cellWidth + 3*delta, height);
        }

        PerformChipAnimation(cxgui::BoardAnimation::MOVE_CHIP_RIGHT_ONE_COLUMN);
    }
    if(m_animateMoveDown)
    {
        queue_draw();
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
        m_animationModel->Resize(1.0, verticalRatio);
    }

    if(!cxmath::AreLogicallyEqual(p_newWidth, m_lastFrameWidth))
    {
        const double horizontalRatio = p_newWidth / m_lastFrameWidth;
        m_animationModel->Resize(horizontalRatio, 1.0);
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
