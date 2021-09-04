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
 * @file SubjectTests.cpp
 * @date 2019
 *
 *************************************************************************************************/

#include <gtest/gtest.h>

#include <ModelNotificationContext.h>

#include "ConcreteObserverMock.h"
#include "ConcreteSubjectMock.h"
#include "SubjectTestFixture.h"


TEST_F(SubjectTestFixture, /*DISABLED_*/Attach_OneObserver_UpdateWorks)
{
    ASSERT_EQ(0, m_observer1.GetData());

    m_subject.Attach(&m_observer1);
    m_subject.IncrementData();

    ASSERT_EQ(1, m_observer1.GetData());
}

TEST_F(SubjectTestFixture, /*DISABLED_*/Attach_TwoObservers_UpdateWorks)
{
    ASSERT_EQ(0, m_observer1.GetData());
    ASSERT_EQ(0, m_observer2.GetData());

    m_subject.Attach(&m_observer1);
    m_subject.Attach(&m_observer2);
    m_subject.IncrementData();

    ASSERT_EQ(1, m_observer1.GetData());
    ASSERT_EQ(1, m_observer1.GetData());
}

TEST_F(SubjectTestFixtureStdErrStreamRedirector, /*DISABLED_*/Attach_NullObserver_PreconditionFail)
{
    ASSERT_TRUE(GetStdErrContents().empty());

    m_subject.Attach(nullptr);

    ASSERT_TRUE(GetStdErrContents().find("Precondition") != std::string::npos);
}

TEST_F(SubjectTestFixtureStdErrStreamRedirector, /*DISABLED_*/Attach_SameObserverTwice_PreconditionFail)
{
    ASSERT_TRUE(GetStdErrContents().empty());

    m_subject.Attach(&m_observer1);
    m_subject.Attach(&m_observer1);

    ASSERT_TRUE(GetStdErrContents().find("Precondition") != std::string::npos);
}

TEST_F(SubjectTestFixture, /*DISABLED_*/Detach_AttachedObserver_NoLongerUpdates)
{
    m_subject.Attach(&m_observer1);
    m_subject.Attach(&m_observer2);
    m_subject.IncrementData();

    ASSERT_EQ(1, m_observer1.GetData());
    ASSERT_EQ(1, m_observer2.GetData());

    m_subject.Detatch(&m_observer1);
    m_subject.IncrementData();

    ASSERT_EQ(1, m_observer1.GetData());
    ASSERT_EQ(2, m_observer2.GetData());
}

TEST_F(SubjectTestFixtureStdErrStreamRedirector, /*DISABLED_*/Detach_NullObserver_PreconditionFail)
{
    ASSERT_TRUE(GetStdErrContents().empty());

    m_subject.Attach(&m_observer1);
    m_subject.Detatch(nullptr);

    ASSERT_TRUE(GetStdErrContents().find("Precondition") != std::string::npos);
}

TEST_F(SubjectTestFixtureStdErrStreamRedirector, /*DISABLED_*/Detach_UnknownObserver_PreconditionFail)
{
    ASSERT_TRUE(GetStdErrContents().empty());

    m_subject.Attach(&m_observer1);
    m_subject.Detatch(&m_observer2);

    ASSERT_TRUE(GetStdErrContents().find("Precondition") != std::string::npos);
}

TEST_F(SubjectTestFixtureStdErrStreamRedirector, /*DISABLED_*/Detach_NoObserverListed_PreconditionFail)
{
    ASSERT_TRUE(GetStdErrContents().empty());

    m_subject.Detatch(&m_observer1);

    ASSERT_TRUE(GetStdErrContents().find("Precondition") != std::string::npos);
}

TEST_F(SubjectTestFixture, /*DISABLED_*/DetachAll_TwoObservers_NoLongerUpdate)
{
    ASSERT_EQ(0, m_observer1.GetData());
    ASSERT_EQ(0, m_observer2.GetData());

    m_subject.Attach(&m_observer1);
    m_subject.Attach(&m_observer2);
    m_subject.IncrementData();

    ASSERT_EQ(1, m_observer1.GetData());
    ASSERT_EQ(1, m_observer2.GetData());

    m_subject.DetatchAll();
    m_subject.IncrementData();

    ASSERT_EQ(1, m_observer1.GetData());
    ASSERT_EQ(1, m_observer2.GetData());
}
