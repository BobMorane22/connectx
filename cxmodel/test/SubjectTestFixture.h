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
 * @file SubjectTestFixture.h
 * @date 2019
 *
 *************************************************************************************************/

#ifndef SUBJECTTESTFIXTURE_H_83B6FB5F_0CB1_4F54_9400_C95474AF439B
#define SUBJECTTESTFIXTURE_H_83B6FB5F_0CB1_4F54_9400_C95474AF439B

#include <gtest/gtest.h>

#include <cxunit/include/StdStreamRedirector.h>

#include <ConcreteObserverMock.h>
#include <ConcreteSubjectMock.h>

class SubjectTestFixture : public testing::Test
{

public:

    SubjectTestFixture();

protected:

    ConcreteSubjectMock m_subject;
    ConcreteObserverMock m_observer1;
    ConcreteObserverMock m_observer2;

};

ADD_STREAM_REDIRECTORS(SubjectTestFixture);

#endif // SUBJECTTESTFIXTURE_H_83B6FB5F_0CB1_4F54_9400_C95474AF439B
