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
 * @file KeyboardShortcutTests.cpp
 * @date 2024
 *
 *************************************************************************************************/

#include <gtest/gtest.h>

#include <cxunit/DisableStdStreamsRAII.h>
#include <cxgui/KeyboardShortcut.h>

TEST(KeyboardShortcut, Constructor_SingleKey_ValidFirstKey)
{
    using namespace cxgui;
    const KeyboardShortcut shortcut{Key::F1};

    ASSERT_TRUE(shortcut.m_first == Key::F1);
    ASSERT_TRUE(shortcut.m_second == std::nullopt);
}

TEST(KeyboardShortcut, Constructor_ImplicitSingleKey_ValidFirstKey)
{
    using namespace cxgui;
    const KeyboardShortcut shortcut{{Key::F1}};

    ASSERT_TRUE(shortcut.m_first == Key::F1);
    ASSERT_TRUE(shortcut.m_second == std::nullopt);
}

TEST(KeyboardShortcut, Constructor_TwoKeys_BothKeysValid)
{
    using namespace cxgui;
    const KeyboardShortcut shortcut{Key::CTRL + Key::Q};

    ASSERT_TRUE(shortcut.m_first == Key::CTRL);
    ASSERT_TRUE(shortcut.m_second == Key::Q);
}

TEST(KeyboardShortcut, Constructor_TwoSameKeys_PreconditionFails)
{
    using namespace cxgui;

    cxunit::DisableStdStreamsRAII redirector;
    const KeyboardShortcut shortcut{Key::CTRL + Key::CTRL};
    ASSERT_PRECONDITION_FAILED(redirector);

    ASSERT_TRUE(shortcut.m_first == Key::CTRL);
    ASSERT_TRUE(shortcut.m_second == std::nullopt);
}
