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
 * @file Gtkmm3AnimatedBoard.h
 * @date 2021
 *
 *************************************************************************************************/

#ifndef GTKMM3ANIMATEDBOARD_H_5A2F73E1_EAC4_4C34_9F79_7540148552C2
#define GTKMM3ANIMATEDBOARD_H_5A2F73E1_EAC4_4C34_9F79_7540148552C2

#include <gtkmm/drawingarea.h>

#include <cxmath/Dimensions.h>
#include <cxgui/AnimatedBoardTimerRAII.h>            // GTK related...
#include <cxgui/AnimationInformation.h>
#include <cxgui/BoardElementCache.h>                 // Gtk related...
#include <cxgui/IAnimatedBoard.h>

namespace cxgui
{

enum class BoardAnimation;
class IAnimatedBoardModel;
class IAnimatedBoardPresenter;
class IGameViewPresenter;

}

namespace cxgui
{

/**********************************************************************************************//**
 * @brief Gtkmm3 implementation of an animated game board.
 *
 *************************************************************************************************/
class Gtkmm3AnimatedBoard : public IAnimatedBoard,
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
    Gtkmm3AnimatedBoard(const IGameViewPresenter& p_presenter, const cxgui::AnimationSpeed& p_speed);

    /******************************************************************************************//**
     * @brief Destructor.
     *
     *********************************************************************************************/
    ~Gtkmm3AnimatedBoard() override = default;

    /*******************************************************************************************//**
     * @brief Sets the delegate for widget common facilities.
     *
     * The delegate is reponsible to carry the implementation for generic `cxgui::IWidget` operations.
     * It is meant to avoid implementation duplication.
     *
     * @param p_delegate
     *      The widget delegate.
     *
     * @pre
     *      The widget delegate instance given as an argument is valid.
     * @post
     *      The registered widget delegate is valid.
     *
     **********************************************************************************************/
    void SetDelegate(std::unique_ptr<IWidget> p_delegate);

    // cxgui::IAnimatedBoard:
    [[nodiscard]] const cxmodel::Column& GetCurrentColumn() const override;
    [[nodiscard]] cxmodel::ChipColor GetCurrentChipColor() const override;

    // cxgui::IWidget:
    [[nodiscard]] size_t GetWidth() const override;
    [[nodiscard]] size_t GetHeight() const override;
    void SetEnabled(EnabledState p_enabled) override;
    void SetMargins(const Margins& p_newMarginSizes) override;
    void SetTooltip(const std::string& p_tooltipContents) override;

private:

    void PerformChipAnimation(BoardAnimation p_animation);

    bool on_draw(const Cairo::RefPtr<Cairo::Context>& p_context) override;
    void DrawActiveColumnHighlight(const Cairo::RefPtr<Cairo::Context>& p_context);
    void DrawBoardElement(const Cairo::RefPtr<Cairo::Context>& p_context, const cxmodel::Row& p_row, const cxmodel::Column& p_column);

    bool Redraw();

    bool OnResize(const cxmath::Dimensions& p_newDimensions);

    void Update(BoardAnimationNotificationContext p_context, BoardAnimationSubject* p_subject) override;

    void CustomizeHeightAccordingToMonitorDimensions();

    // Handlers:
    bool OnMouseButtonPressed(GdkEventButton* p_event);
    bool OnMouseMotion(GdkEventMotion* p_event);

private:

    std::unique_ptr<IWidget> m_delegate;

    // A Game View presenter cache:
    std::unique_ptr<IAnimatedBoardPresenter> m_presenter;
    std::unique_ptr<IAnimatedBoardModel> m_animationModel;

    // Clock (ticks m_FPS times per second):
    std::unique_ptr<AnimatedBoardTimerRAII> m_timer;

    AnimationInformations<cxmath::Width> m_moveLeftAnimationInfo;
    AnimationInformations<cxmath::Width> m_moveRightAnimationInfo;
    AnimationInformations<cxmath::Height> m_dropAnimationInfo;

    cxmath::Dimensions m_lastFrameDimensions{cxmath::Height{0.0}, cxmath::Width{0.0}};

    // Surfaces in RAM on which to perform the drawing, in memory, before effectively
    // drawing on the screen. Caching these surfaces here avoids recreating them on every
    // frame draw, which helps performancewise:
    BoardElementCache m_boardElementsCache;             // For individual discs.
    Cairo::RefPtr<Cairo::Surface> m_columnHilightCache; // For the column hilight.
    Cairo::RefPtr<Cairo::Surface> m_surfaceCache;       // For the whole drawn surface.

    // Signals:
    sigc::connection m_mouseButtonPressedConnection;
    sigc::connection m_mouseMotionConnection;
    sigc::connection m_initialSizeAllocationConnection;

};

} // namespace cxgui

#endif // GTKMM3ANIMATEDBOARD_H_5A2F73E1_EAC4_4C34_9F79_7540148552C2
