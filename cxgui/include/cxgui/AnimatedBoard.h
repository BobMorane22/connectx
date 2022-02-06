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
 * @file AnimatedBoard.h
 * @date 2021
 *
 *************************************************************************************************/

#ifndef ANIMATEDBOARD_H_AD051257_1B19_403D_88A6_1C3EFBAC0A08
#define ANIMATEDBOARD_H_AD051257_1B19_403D_88A6_1C3EFBAC0A08

#include <gtkmm/drawingarea.h>

#include <cxmath/math.h>

#include "AnimatedBoardTimerRAII.h"
#include "AnimationInformation.h"
#include "BoardAnimation.h"
#include "BoardAnimationNotificationContext.h"
#include "BoardElementCache.h"
#include "IAnimatedBoardModel.h"
#include "IBoardInformation.h"

namespace cxgui
{

class IAnimatedBoardPresenter;
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
class AnimatedBoard : public cxgui::IBoardInformation,
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
     *      The number of positions a chip should move, per second. For example, a value of '3'
     *      would mean that a chip will move three columns (or rows) per second when animated.
     *
     *********************************************************************************************/
    AnimatedBoard(const IGameViewPresenter& p_presenter, const cxgui::AnimationSpeed& p_speed);

    /******************************************************************************************//**
     * @brief Destructor.
     *
     *********************************************************************************************/
    ~AnimatedBoard() = default;

    // cxgui::IBoardInformation:
    [[nodiscard]] const cxmodel::Column& GetCurrentColumn() const override;
    [[nodiscard]] cxmodel::ChipColor GetCurrentChipColor() const override;

private:

    void PerformChipAnimation(BoardAnimation p_animation);

    bool on_draw(const Cairo::RefPtr<Cairo::Context>& p_context) override;
    void DrawActiveColumnHighlight(const Cairo::RefPtr<Cairo::Context>& p_context);
    void DrawBoardElement(const Cairo::RefPtr<Cairo::Context>& p_context, const cxmodel::Row& p_row, const cxmodel::Column& p_column);

    bool Redraw();

    bool OnResize(const cxmath::Dimensions& p_newDimensions);

    void Update(cxgui::BoardAnimationNotificationContext p_context, BoardAnimationSubject* p_subject) override;

    [[nodiscard]] cxmodel::Row GetDropPosition(const cxmodel::Column& p_column) const;
    [[nodiscard]] int ComputeMinimumChipDimension(size_t p_nbRows, size_t p_nbColumns) const;

    // A Game View presenter cache.
    std::unique_ptr<IAnimatedBoardPresenter> m_presenter;
    std::unique_ptr<IAnimatedBoardModel> m_animationModel;

    // Clock (ticks m_FPS times per second).
    std::unique_ptr<AnimatedBoardTimerRAII> m_timer;

    AnimationInformations<cxmath::Width> m_moveLeftAnimationInfo;
    AnimationInformations<cxmath::Width> m_moveRightAnimationInfo;
    AnimationInformations<cxmath::Height> m_dropAnimationInfo;

    cxmath::Dimensions m_lastFrameDimensions{cxmath::Height{0.0}, cxmath::Width{0.0}};

    BoardElementCache m_boardElementsCache;
};

} // namespace cxgui

#endif // ANIMATEDBOARD_H_AD051257_1B19_403D_88A6_1C3EFBAC0A08
