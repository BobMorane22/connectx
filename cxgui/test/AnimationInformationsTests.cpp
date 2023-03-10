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
 * @file AnimationInformationsTests.cpp
 * @date 2022
 *
 *************************************************************************************************/

#include <gtest/gtest.h>

#include <cxgui/AnimationInformation.h>

using DisplacementType = double;

TEST(AnimationInformations, Constructor_Default_DefaultAnimationInformationsCreated)
{
    const cxgui::AnimationInformations<DisplacementType> info;

    ASSERT_TRUE(info.m_isAnimating == false);
    ASSERT_TRUE(info.m_nbOfRenderedFrames == 0u);
    ASSERT_TRUE(info.m_animation == std::nullopt);
    ASSERT_TRUE(info.m_currentDisplacement == 0.0);
}

TEST(AnimationInformations, Start_NotAnimating_IsAnimatingIsTrue)
{
    cxgui::AnimationInformations<DisplacementType> info;
    info.m_isAnimating = false;
    info.m_animation = std::nullopt;
    info.m_currentDisplacement = 0.0;

    info.Start(cxgui::BoardAnimation::MOVE_CHIP_LEFT_ONE_COLUMN);

    ASSERT_TRUE(info.m_isAnimating == true);
    ASSERT_TRUE(info.m_nbOfRenderedFrames == 0u);
    ASSERT_TRUE(info.m_animation == cxgui::BoardAnimation::MOVE_CHIP_LEFT_ONE_COLUMN);
    ASSERT_TRUE(info.m_currentDisplacement == 0.0);
}

TEST(AnimationInformations, Stop_Animating_IsAnimatingIsFalse)
{
    cxgui::AnimationInformations<DisplacementType> info;
    info.m_isAnimating = true;
    info.m_nbOfRenderedFrames = 5u;
    info.m_animation = cxgui::BoardAnimation::MOVE_CHIP_LEFT_ONE_COLUMN;
    info.m_currentDisplacement = 50.0;

    info.Stop();

    ASSERT_TRUE(info.m_isAnimating == false);
    ASSERT_TRUE(info.m_nbOfRenderedFrames == 5u);
    ASSERT_TRUE(info.m_animation == std::nullopt);
    ASSERT_TRUE(info.m_currentDisplacement == 50.0);
}

TEST(AnimationInformations, Reset_IsAnimatingAndHasDisplacement_DefaultIsBack)
{
    cxgui::AnimationInformations<DisplacementType> info;
    info.m_isAnimating = true;
    info.m_nbOfRenderedFrames = 5u;
    info.m_animation = cxgui::BoardAnimation::MOVE_CHIP_LEFT_ONE_COLUMN;
    info.m_currentDisplacement = 50.0;

    info.Reset();

    ASSERT_TRUE(info.m_isAnimating == false);
    ASSERT_TRUE(info.m_nbOfRenderedFrames == 0u);
    ASSERT_TRUE(info.m_animation == std::nullopt);
    ASSERT_TRUE(info.m_currentDisplacement == 0.0);
}
