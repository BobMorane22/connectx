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
 * @file GameKeyHandlerStrategyFactoryTests.cpp
 * @date 2021
 *
 *************************************************************************************************/

#include <gtest/gtest.h>

#include <gdk/gdk.h>

#include <cxunit/include/DisableStdStreamsRAII.h>

#include <GameDownKeyHandlerStrategy.h>
#include <GameKeyHandlerStrategyFactory.h>
#include <GameLeftKeyHandlerStrategy.h>
#include <GameRightKeyHandlerStrategy.h>

TEST(GameDownKeyHandlerStrategy, Create_DownKey_DownStrategyCreated)
{
    cxgui::GameKeyHandlerStrategyFactory factory;

    GdkEventKey event;
    event.keyval = GDK_KEY_Down;

    auto strategy = factory.Create(&event);

    ASSERT_TRUE(dynamic_cast<cxgui::GameDownKeyHandlerStrategy*>(strategy.get()));
}

TEST(GameDownKeyHandlerStrategy, Create_LeftKey_LeftStrategyCreated)
{
    cxgui::GameKeyHandlerStrategyFactory factory;

    GdkEventKey event;
    event.keyval = GDK_KEY_Left;

    auto strategy = factory.Create(&event);

    ASSERT_TRUE(dynamic_cast<cxgui::GameLeftKeyHandlerStrategy*>(strategy.get()));
}

TEST(GameDownKeyHandlerStrategy, Create_RightKey_RightStrategyCreated)
{
    cxgui::GameKeyHandlerStrategyFactory factory;

    GdkEventKey event;
    event.keyval = GDK_KEY_Right;

    auto strategy = factory.Create(&event);

    ASSERT_TRUE(dynamic_cast<cxgui::GameRightKeyHandlerStrategy*>(strategy.get()));
}

TEST(GameDownKeyHandlerStrategy, Create_UnknownKey_NoStrategyCreated)
{
    cxgui::GameKeyHandlerStrategyFactory factory;

    GdkEventKey event;
    event.keyval = GDK_KEY_Up;

    auto strategy = factory.Create(&event);

    ASSERT_TRUE(strategy == nullptr);
}

TEST(GameDownKeyHandlerStrategy, Create_InvalidGdkKeyEvent_NoStrategyCreated)
{
    cxunit::DisableStdStreamsRAII m_streamDisabler;
    m_streamDisabler.DisableStdErr();

    cxgui::GameKeyHandlerStrategyFactory factory;

    std::string assertionMessage = m_streamDisabler.GetStdErrContents();
    ASSERT_TRUE(assertionMessage.empty());

    auto strategy = factory.Create(nullptr);

    assertionMessage = m_streamDisabler.GetStdErrContents();
    ASSERT_FALSE(assertionMessage.empty());
    ASSERT_TRUE(assertionMessage.find("Precondition") != std::string::npos);

    ASSERT_TRUE(strategy == nullptr);
}
