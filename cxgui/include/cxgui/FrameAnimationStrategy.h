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
 * @file FrameAnimationStrategy.h
 * @date 2022
 *
 *************************************************************************************************/

#ifndef FRAMEANIMATIONSTRATEGY_H_04405A9C_707A_45E2_90CC_38952DF4A8A8
#define FRAMEANIMATIONSTRATEGY_H_04405A9C_707A_45E2_90CC_38952DF4A8A8

#include <memory>
#include <optional>

#include <cxmath/Dimensions.h>
#include <cxgui/AnimationInformation.h>


namespace cxgui
{

enum class BoardAnimationNotificationContext;
class IAnimatedBoardModel;
class IAnimatedBoardPresenter;
enum class BoardAnimation;

} // namespace cxgui

namespace cxgui
{

/**********************************************************************************************//**
 * @brief Interface for implementing frame animation strategies.
 *
 * On every animation tick, one of these strategies is called to update a frame. Different
 * animations (e.g. move left one column, drop a chip, etc) use different implementations
 * to update frames.
 *
 *************************************************************************************************/
class IFrameAnimationStrategy
{

public:

    /******************************************************************************************//**
     * @brief Destructor.
     *
     *********************************************************************************************/
    virtual ~IFrameAnimationStrategy() = default;

    /******************************************************************************************//**
     * @brief Updates the frame according to a specific animation.
     *
     * @param p_horizontalAnimationInfo The horizontal animation information.
     * @param p_verticalAnimationInfo   The vertical animation information.
     *
     * @return An optional notification to be handled by the caller.
     *
     *********************************************************************************************/
    virtual std::optional<cxgui::BoardAnimationNotificationContext> PerformAnimation(cxgui::AnimationInformations<cxmath::Width>& p_horizontalAnimationInfo,
                                                                                     cxgui::AnimationInformations<cxmath::Height>& p_verticalAnimationInfo) = 0;

};

/**********************************************************************************************//**
 * @brief Factory method to create different frame animation strategies.
 *
 * @param p_animationModel The board animation model.
 * @param p_presenter      The board animation presenter.
 * @param p_animation      The requested animation. With this parameter, the right strategy is
 *                         configured for the animation to perform.
 *
 * @return The configured strategy to use.
 *
 *************************************************************************************************/
std::unique_ptr<IFrameAnimationStrategy> CreateFrameAnimationStrategy(IAnimatedBoardModel& p_animationModel,
                                                                      const IAnimatedBoardPresenter& p_presenter,
                                                                      const BoardAnimation p_animation);

} // namespace cxgui

#endif // FRAMEANIMATIONSTRATEGY_H_04405A9C_707A_45E2_90CC_38952DF4A8A8
