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

#include <gdkmm/display.h>
#include <gdkmm/general.h>

#include <cxinv/assertion.h>
#include <cxmodel/Disc.h>
#include <cxgui/AnimatedBoard.h>
#include <cxgui/AnimatedBoardModel.h>
#include <cxgui/AnimatedBoardPresenter.h>
#include <cxgui/common.h>
#include <cxgui/ContextRestoreRAII.h>
#include <cxgui/FrameAnimationStrategy.h>
#include <cxgui/IGameViewPresenter.h>
#include <cxgui/pathHelpers.h>

namespace
{

/**************************************************************************************************
 * @brief Draw a chip.
 *
 * The chip will have a boarder around it.
 *
 * @param p_context
 *      The cairo context to use.
 * @param p_centerPosition
 *      The chip's wanted center position.
 * @param p_radius
 *      The chips wanted radius.
 * @param p_backgroundColor
 *      The chips wanted background color.
 *
 *************************************************************************************************/
void DrawChip(const Cairo::RefPtr<Cairo::Context>& p_context,
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

cxgui::AnimatedBoard::AnimatedBoard(const IGameViewPresenter& p_presenter, const cxgui::AnimationSpeed& p_speed)
{
    m_presenter = std::make_unique<cxgui::AnimatedBoardPresenter>(p_presenter);
    m_animationModel = std::make_unique<cxgui::AnimatedBoardModel>(*m_presenter, p_speed);

    // Customize width and height according to window dimension.
    const cxmodel::Height nbRows = m_presenter->GetBoardHeight();
    const cxmodel::Width nbColumns = m_presenter->GetBoardWidth();
    const int chipDimension = ComputeMinimumChipDimension(nbRows.Get(), nbColumns.Get());
    set_size_request(nbColumns.Get() * chipDimension, nbRows.Get() * chipDimension);

    set_vexpand(true);
    set_hexpand(true);

    m_timer = std::make_unique<AnimatedBoardTimerRAII>(
       [this](){return Redraw();},
       Period{1000.0/m_animationModel->GetFPS().Get()});

    // Resize events:
    signal_configure_event().connect([this](GdkEventConfigure* p_event){
        IF_CONDITION_NOT_MET_DO(p_event, return STOP_EVENT_PROPAGATION;);

        const cxmath::Height newHeight{static_cast<double>(p_event->height)};
        const cxmath::Width newWidth{static_cast<double>(p_event->width)};
        return OnResize({newHeight, newWidth});
    });

    POSTCONDITION(m_presenter);
    POSTCONDITION(m_animationModel);
}

// Performs an "frame increment". This is called on every tick (m_FPS times/sec) and
// keeps track of all displacements. It also notifies when the animation completes.
void cxgui::AnimatedBoard::PerformChipAnimation(BoardAnimation p_animation)
{
    switch(p_animation)
    {
        case cxgui::BoardAnimation::MOVE_CHIP_LEFT_ONE_COLUMN:
        case cxgui::BoardAnimation::MOVE_CHIP_RIGHT_ONE_COLUMN:
        case cxgui::BoardAnimation::DROP_CHIP:
        case cxgui::BoardAnimation::UNDO_DROP_CHIP:
        case cxgui::BoardAnimation::REDO_DROP_CHIP:
        {
            AnimationInformations<cxmath::Width>* horizontalAnimationInfo = &m_moveRightAnimationInfo;
            if(p_animation == cxgui::BoardAnimation::MOVE_CHIP_LEFT_ONE_COLUMN)
            {
                horizontalAnimationInfo = &m_moveLeftAnimationInfo;
            }

            auto strategy = CreateFrameAnimationStrategy(*m_animationModel, *m_presenter, p_animation);
            IF_CONDITION_NOT_MET_DO(strategy, return;);

            const auto res = strategy->PerformAnimation(*horizontalAnimationInfo, m_dropAnimationInfo);
            if(res)
            {
                Notify(*res);
            }

            break;
        }
        case cxgui::BoardAnimation::REINITIALIZE:
        {
            // Reinitialize chip:
            m_animationModel->ResetChipPositions();
            m_animationModel->UpdateCurrentColumn(cxmodel::Column{0u});

            m_boardElementsCache.Clear();
            m_presenter->Sync();

            Notify(cxgui::BoardAnimationNotificationContext::POST_ANIMATE_REINITIALIZE_BOARD);
            break;
        }
        default:
        {
            ASSERT_ERROR_MSG("Unsupported move.");
        }
    }
}

const cxmodel::Column& cxgui::AnimatedBoard::GetCurrentColumn() const
{
    return m_animationModel->GetCurrentColumn();
}

cxmodel::ChipColor cxgui::AnimatedBoard::GetCurrentChipColor() const
{
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
    // Get window dimensions. We keep track of previous frame dimensions to allow
    // calculating a scaling factor in the case of a resize:
    const Gtk::Allocation allocation = get_allocation();
    m_lastFrameDimensions.m_height = cxmath::Height{static_cast<double>(allocation.get_height())};
    m_lastFrameDimensions.m_width = cxmath::Width{static_cast<double>(allocation.get_width())};

    m_animationModel->Update(m_lastFrameDimensions, m_moveLeftAnimationInfo.m_isAnimating || m_moveRightAnimationInfo.m_isAnimating);

    auto buffer = Cairo::ImageSurface::create(Cairo::Format::FORMAT_ARGB32,
                                              m_animationModel->GetAnimatedAreaDimensions().m_width.Get(),
                                              m_animationModel->GetAnimatedAreaDimensions().m_height.Get());
    const auto bufferContext = Cairo::Context::create(buffer);

    // Draw colum highlight:
    DrawActiveColumnHighlight(bufferContext);

    // Draw Chip(s):
    const cxmodel::ChipColor chipColor = m_presenter->GetActivePlayerChipColor();
    DrawChip(bufferContext,
             m_animationModel->GetChipPosition(),
             m_animationModel->GetChipRadius().Get() + m_animationModel->GetLineWidth(cxgui::Feature::CHIP).Get(),
             chipColor);

    if(m_animationModel->IsMirrorChipNeeded())
    {
        DrawChip(bufferContext,
                 m_animationModel->GetMirrorChipPosition(),
                 m_animationModel->GetChipRadius().Get() + m_animationModel->GetLineWidth(cxgui::Feature::CHIP).Get(),
                 chipColor);
    }

    // Draw the game board:
    m_boardElementsCache.Clear();
    for(size_t row = 0u; row < m_presenter->GetBoardHeight().Get(); ++row)
    {
        for(size_t column = 0u; column < m_presenter->GetBoardWidth().Get(); ++column)
        {
            DrawBoardElement(bufferContext, cxmodel::Row{row}, cxmodel::Column{column});
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
    const cxmath::Dimensions cellDimensions = m_animationModel->GetCellDimensions();
    const double cellWidth = cellDimensions.m_width.Get();
    const double cellHeight = cellDimensions.m_height.Get();

    cxgui::ContextRestoreRAII contextRestoreRAII{p_context};

    cxgui::MakeRectanglarPath(p_context,
                              {m_animationModel->GetChipPosition().m_x - (cellWidth / 2.0), cellHeight},
                              m_animationModel->GetAnimatedAreaDimensions().m_height.Get() - cellHeight,
                              cellWidth);

    // Set background color:
    p_context->set_source_rgba(0.3, 0.3, 0.3, 0.5);

    // Draw everything:
    p_context->fill_preserve();
    p_context->stroke();
}

// See `on_draw()`. Basically draws a chip and the rectangular space around it (which has the board color). All
// these elements together make the board.
void cxgui::AnimatedBoard::DrawBoardElement(const Cairo::RefPtr<Cairo::Context>& p_context, const cxmodel::Row& p_row, const cxmodel::Column& p_column)
{
    const cxmath::Dimensions cellDimensions = m_animationModel->GetCellDimensions();
    const double cellWidth = cellDimensions.m_width.Get();
    const double cellHeight = cellDimensions.m_height.Get();
    const double radius = m_animationModel->GetChipRadius().Get() + m_animationModel->GetLineWidth(cxgui::Feature::CHIP).Get();

    const IGameViewPresenter::ChipColors& chipColors = m_presenter->GetBoardChipColors();
    const cxmodel::ChipColor chipColor = chipColors[p_row.Get()][p_column.Get()];
    if(m_boardElementsCache.HasElement(chipColor))
    {
        // Paint that part to the canvas:
        Gdk::Cairo::set_source_pixbuf(p_context,
                                      m_boardElementsCache.Get(chipColor),
                                      p_column.Get() * cellWidth,
                                      (p_row.Get() + 1) * cellHeight);
        p_context->paint();

        return;
    }

    // Add a little extra to cover everything...
    auto buffer = Cairo::ImageSurface::create(Cairo::Format::FORMAT_ARGB32,
                                              cellWidth + m_animationModel->GetLineWidth(cxgui::Feature::CELL).Get(),
                                              cellHeight + m_animationModel->GetLineWidth(cxgui::Feature::CELL).Get());
    const auto bufferContext = Cairo::Context::create(buffer);
    {
        cxgui::ContextRestoreRAII contextRestoreRAII{bufferContext};

        // Draw paths for chip space and the cell contour:
        cxgui::MakeCircularPath(bufferContext, {cellWidth / 2.0, cellHeight / 2.0}, radius);
        cxgui::MakeRectanglarPath(bufferContext, {0.0, 0.0}, cellHeight, cellWidth);

        // Set background color:
        bufferContext->set_source_rgba(0.0, 0.0, 0.8, 1.0);

        // Draw everything:
        bufferContext->set_fill_rule(Cairo::FILL_RULE_EVEN_ODD);
        bufferContext->fill_preserve();
        bufferContext->stroke();
    }

    // Add border and draw model chips:
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
                                                                       cellWidth + m_animationModel->GetLineWidth(cxgui::Feature::CELL).Get(),
                                                                       cellHeight + m_animationModel->GetLineWidth(cxgui::Feature::CELL).Get());
    m_boardElementsCache.Add(chipColor, boardElement);

    // Paint that part to the canvas:
    p_context->set_source(buffer,
                          p_column.Get() * cellWidth,
                          (p_row.Get() + 1) * cellHeight);
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
    const double chipHorizontalPosition = m_animationModel->GetChipPosition().m_x;
    const cxmath::Dimensions cellDimensions = m_animationModel->GetCellDimensions();
    const double cellWidth = cellDimensions.m_width.Get();
    const double fps = static_cast<double>(m_animationModel->GetFPS().Get());
    const double speed = static_cast<double>(m_animationModel->GetAnimationSpeed().Get());

    // Schedule a redraw on the next frame:
    if(m_moveLeftAnimationInfo.m_isAnimating)
    {
        const double nbFramesPerChip = fps / speed;
        const double delta = cellWidth / nbFramesPerChip;

        if(chipHorizontalPosition < cellWidth / 2.0)
        {
            // Because of the mirror chip, redraw the whole screen.
            queue_draw();
        }
        else
        {
            queue_draw_area(chipHorizontalPosition - cellWidth / 2.0 - delta, 0.0, cellWidth + 3 * delta, m_animationModel->GetAnimatedAreaDimensions().m_height.Get());
        }

        PerformChipAnimation(cxgui::BoardAnimation::MOVE_CHIP_LEFT_ONE_COLUMN);
    }
    if(m_moveRightAnimationInfo.m_isAnimating)
    {
        const double nbFramesPerChip = fps / speed;
        const double delta = cellWidth / nbFramesPerChip;

        if(chipHorizontalPosition > m_animationModel->GetAnimatedAreaDimensions().m_width.Get() - cellWidth / 2.0)
        {
            // Because of the mirror chip, redraw the whole screen.
            queue_draw();
        }
        else
        {
            queue_draw_area(chipHorizontalPosition - cellWidth / 2.0 - delta, 0.0, cellWidth + 3 * delta, m_animationModel->GetAnimatedAreaDimensions().m_height.Get());
        }

        PerformChipAnimation(cxgui::BoardAnimation::MOVE_CHIP_RIGHT_ONE_COLUMN);
    }
    if(m_dropAnimationInfo.m_isAnimating)
    {
        queue_draw();
        PerformChipAnimation(cxgui::BoardAnimation::DROP_CHIP);
    }

    return true;
}

// Called when the window is resized. Positions are updated to fit the
// new ratio.
bool cxgui::AnimatedBoard::OnResize(const cxmath::Dimensions& p_newDimensions)
{
    // Handling initial values to avoid division by zero:
    if(m_lastFrameDimensions.m_height == cxmath::Height{0.0})
    {
        return cxgui::STOP_EVENT_PROPAGATION;
    }

    if(m_lastFrameDimensions.m_width == cxmath::Width{0.0})
    {
        return cxgui::STOP_EVENT_PROPAGATION;
    }

    // Now the real work:
    if(!cxmath::AreLogicallyEqual(p_newDimensions.m_height.Get(), m_lastFrameDimensions.m_height.Get()))
    {
        const cxgui::ScalingRatios ratios{cxgui::VerticalScalingRatio{p_newDimensions.m_height.Get() / m_lastFrameDimensions.m_height.Get()}};
        m_animationModel->Resize(ratios);
    }

    if(!cxmath::AreLogicallyEqual(p_newDimensions.m_width.Get(), m_lastFrameDimensions.m_width.Get()))
    {
        const cxgui::ScalingRatios ratios{cxgui::HorizontalScalingRatio{p_newDimensions.m_width.Get() / m_lastFrameDimensions.m_width.Get()}};
        m_animationModel->Resize(ratios);
        m_moveLeftAnimationInfo.m_currentDisplacement.Get() *= ratios.m_horizontalRatio.Get();
        m_moveRightAnimationInfo.m_currentDisplacement.Get() *= ratios.m_horizontalRatio.Get();
    }

    return cxgui::STOP_EVENT_PROPAGATION;
}

// Called in repetition until the animation completes.
void cxgui::AnimatedBoard::Update(cxgui::BoardAnimationNotificationContext p_context, BoardAnimationSubject* p_subject)
{
    IF_CONDITION_NOT_MET_DO(p_subject, return;);

    switch(p_context)
    {
        case cxgui::BoardAnimationNotificationContext::ANIMATE_MOVE_LEFT_ONE_COLUMN:
        {
            m_moveLeftAnimationInfo.Start();
            PerformChipAnimation(cxgui::BoardAnimation::MOVE_CHIP_LEFT_ONE_COLUMN);
            break;
        }
        case cxgui::BoardAnimationNotificationContext::ANIMATE_MOVE_RIGHT_ONE_COLUMN:
        {
            m_moveRightAnimationInfo.Start();
            PerformChipAnimation(cxgui::BoardAnimation::MOVE_CHIP_RIGHT_ONE_COLUMN);
            break;
        }
        case cxgui::BoardAnimationNotificationContext::ANIMATE_MOVE_DROP_CHIP:
        {
            m_dropAnimationInfo.Start();
            PerformChipAnimation(cxgui::BoardAnimation::DROP_CHIP);
            break;
        }
        case cxgui::BoardAnimationNotificationContext::ANIMATE_UNDO_DROP_CHIP:
        {
            PerformChipAnimation(cxgui::BoardAnimation::UNDO_DROP_CHIP);

            // Because there is no real animation associated with an undo
            // (the chip simply diseapears, PerformChipAnimation only updates
            // the model data), we request a redraw directly here:
            queue_draw();
            break;
        }
        case cxgui::BoardAnimationNotificationContext::ANIMATE_REDO_DROP_CHIP:
        {
            PerformChipAnimation(cxgui::BoardAnimation::REDO_DROP_CHIP);

            // Because there is no real animation associated with a redo
            // (the chip simply reapears, PerformChipAnimation only updates
            // the model data), we request a redraw directly here:
            queue_draw();
            break;
        }
        case cxgui::BoardAnimationNotificationContext::ANIMATE_REINITIALIZE_BOARD:
        {
            PerformChipAnimation(cxgui::BoardAnimation::REINITIALIZE);
            // Because there is no real animation associated with reinitializing
            // (the board simply clears, PerformChipAnimation only updates
            // the model data), we request a redraw directly here:
            queue_draw();
            break;
        }
        default:
        {
            ASSERT_ERROR_MSG("Unsupported notification context");
        }
    }
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
