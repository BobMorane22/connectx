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

#ifndef ANIMATEDBOARD_H_AD051257_1B19_403D_88A6_1C3EFBAC0A08
#define ANIMATEDBOARD_H_AD051257_1B19_403D_88A6_1C3EFBAC0A08

#include <gtkmm/drawingarea.h>

#include <cxmath/include/math.h>

#include "BoardAnimation.h"
#include "BoardAnimationNotificationContext.h"
#include "BoardElementCache.h"
#include "IBoardAnimator.h"
#include "IBoardInformation.h"

namespace cxgui
{

class IGameViewPresenter;

}

namespace cxgui
{

/**********************************************************************************************//**
 * @brief Connect X animated game board widget.
 *
 * Represents a customizable game board for Connect X. The game board is composed of the actual
 * board in which chips are actually droped, but also an extra row, at the top, to visualize
 * the chip of the player that is currently playing. We will refer to this chip as "the chip".
 *
 * With this widget, chip movements are animated (moving left, right, etc). Board animation
 * events are handled through a subject/observer system in which a user can, for example,
 * start an animation and then be notified when the animation finishes to resume the game.
 *
 * For now, animations are assumed to be synchronous, which means that during animations, the
 * game must not go on and the user should not be able to interract with the board.
 *
 *************************************************************************************************/
class AnimatedBoard : public cxgui::IBoardAnimator,
                      public cxgui::IBoardInformation,
                      public cxgui::IBoardAnimationObserver,
                      public cxgui::BoardAnimationSubject,
                      public Gtk::DrawingArea
{

public:

    /******************************************************************************************//**
     * @brief Constructor.
     *
     * @param p_presenter
     *      The Game View presenter.
     * @param p_speed
     *      The number of positions a disc shoulb move, per second. For example, a value of '3'
     *      would mean that a disc will move three columns (or rows) per second when animated.
     *
     *********************************************************************************************/
    AnimatedBoard(const IGameViewPresenter& p_presenter, size_t p_speed);

    /******************************************************************************************//**
     * @brief Destructor.
     *
     *********************************************************************************************/
    ~AnimatedBoard();

    // cxgui::IBoardAnimator:
    void PerformChipAnimation(BoardAnimation p_animation) override;

    // cxgui::IBoardInformation:
    [[nodiscard]] size_t GetCurrentColumn() const override;
    [[nodiscard]] cxmodel::ChipColor GetCurrentChipColor() const override;

private:

    // Implementation methods and functions:
    bool on_draw(const Cairo::RefPtr<Cairo::Context>& p_context) override;
    void DrawActiveColumnHighlight(const Cairo::RefPtr<Cairo::Context>& p_context);
    void DrawBoardElement(const Cairo::RefPtr<Cairo::Context>& p_context, size_t p_row, size_t p_column);

    bool Redraw();

    bool OnResize(double p_newHeight, double p_newWidth);

    void Update(cxgui::BoardAnimationNotificationContext p_context, BoardAnimationSubject* p_subject) override;

    template<BoardAnimation A>
    [[nodiscard]] bool ComputeDiscPosition(double p_windowWidth, double p_halfDiscSize, double p_horizontalMargin);
    [[nodiscard]] bool ComputeDiscLeftPosition(double p_windowWidth, double p_halfDiscSize, double p_horizontalMargin);
    [[nodiscard]] bool ComputeDiscRightPosition(double p_windowWidth, double p_halfDiscSize, double p_horizontalMargin);
    void ComputeDiscVerticalPosition(const double p_halfDiscSize, double p_height);

    [[nodiscard]] int GetDropPosition(int p_column) const;
    [[nodiscard]] int ComputeMinimumChipDimension(size_t p_nbRows, size_t p_nbColumns) const;

    // General data:
    const int m_FPS = 24; // Frames per second.

    const IGameViewPresenter& m_presenter; // The Game View presenter.
    const size_t m_speed;                  // The number of discs covered per second when moving.

    double m_x = 0.0; // Disc center position (horizontal).
    double m_y = 0.0; // Disc center position (vertical).

    size_t m_currentColumn = 0; // The disc current's column.

    double m_xx = 0.0; // Mirror center position (horizontal). This is used when a disc
                       // crosses over the window boundary, to trace its other half on
                       // the other side.

    sigc::connection m_timer; // Clock (ticks m_FPS times per second).

    // Grid information:
    cxmath::Position m_cellCenterPosition{0.0, 0.0}; // Position of the first game board cell.

    // Left move animation:
    bool m_animateMoveLeft = false;
    double m_totalMoveLeftDisplacement = 0.0;

    // Right move animation:
    bool m_animateMoveRight = false;
    double m_totalMoveRightDisplacement = 0.0;

    // Down move animation:
    bool m_animateMoveDown = false;           // Flag indicating if a "move down" animation is ongoing.
    double m_totalMoveDownDisplacement = 0.0; // Sum of down displacement deltas in the context of a single animation (i.e. one disc only).

    // Last frame information:
    double m_lastFrameHeight = 0.0; // Height of the animation for last frame.
    double m_lastFrameWidth = 0.0;  // Width of the animation for last frame.

    // Performance:
    BoardElementCache m_boardElementsCache;

};

} // namespace cxgui

#endif // ANIMATEDBOARD_H_AD051257_1B19_403D_88A6_1C3EFBAC0A08
