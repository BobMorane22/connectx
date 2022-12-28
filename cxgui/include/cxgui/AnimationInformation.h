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
 * @file AnimationInformation.h
 * @date 2022
 *
 *************************************************************************************************/

#ifndef ANIMATIONINFORMATION_H_DB49E138_EC0C_4907_8C76_6E11A5CED74D
#define ANIMATIONINFORMATION_H_DB49E138_EC0C_4907_8C76_6E11A5CED74D

#include <optional>

#include "BoardAnimation.h"
#include "IAnimatedBoardModel.h"

namespace cxgui
{

/**********************************************************************************************//**
 * @brief Animation informations.
 *
 * Regroups information indication the current status of an animation.
 *
 *************************************************************************************************/
template<typename T>
struct AnimationInformations
{

    /******************************************************************************************//**
     * @brief Starts the animation.
     *
     * @param p_animation The animation to start.
     *
     *********************************************************************************************/
    void Start(BoardAnimation p_animation)
    {
        m_isAnimating = true;
        m_animation = p_animation;
    };

    /******************************************************************************************//**
     * @brief Stops the animation.
     *
     *********************************************************************************************/
    void Stop()
    {
        m_isAnimating = false;
        m_animation.reset();
    };

    /******************************************************************************************//**
     * @brief Resets the animation.
     *
     * After a call to this, all the animation information is reset as if no animation ever
     * occured.
     *
     *********************************************************************************************/
    void Reset()
    {
        Stop();
        m_currentDisplacement = T{0.0};
    }

    /** Indicates if the animation is currently running. */
    bool m_isAnimating = false;

    /** The animation currently running (if any). */
    std::optional<BoardAnimation> m_animation;

    /** Indicates the displacement actually covered by the animation. */
    T m_currentDisplacement = T{0.0};

    /** Indicates the current animation (if any). */
    std::optional<cxgui::BoardAnimation> m_currentAnimation = std::nullopt;

};

} // namespace cxgui

#endif // ANIMATIONINFORMATION_H_DB49E138_EC0C_4907_8C76_6E11A5CED74D
