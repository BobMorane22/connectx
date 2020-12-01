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
 * @file ModelTestHelpers.cpp
 * @date 2020
 *
 *************************************************************************************************/

#ifndef MODELTESTHELPERS_H_467CB750_5143_4A88_9FB0_D3BFCAD3A69D
#define MODELTESTHELPERS_H_467CB750_5143_4A88_9FB0_D3BFCAD3A69D

#include <gtest/gtest.h>

#include "ModelTestHelpers.h"

ModelNotificationCatcher::ModelNotificationCatcher(cxmodel::NotificationContext p_contextUnderTest)
:m_contextUnderTest{p_contextUnderTest}
{
    EXPECT_FALSE(m_wasNotified);
}

ModelNotificationCatcher::~ModelNotificationCatcher()
{
    if(!m_wasNotified)
    {
        // Notification did not happen. Did you forget to attach?
        EXPECT_TRUE(false);
    }
}

bool ModelNotificationCatcher::WasNotified() const
{
    return m_wasNotified;
}

void ModelNotificationCatcher::Update(cxmodel::NotificationContext p_context, cxmodel::Subject* p_subject)
{
    ASSERT_TRUE(p_subject);

    if(p_context == m_contextUnderTest)
    {
        m_wasNotified = true;
    }
}

#endif // MODELTESTHELPERS_H_467CB750_5143_4A88_9FB0_D3BFCAD3A69D
