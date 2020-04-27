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
 * @file ModelTests.cpp
 * @date 2019
 *
 *************************************************************************************************/

#include <regex>

#include <gtest/gtest.h>

#include <IObserver.h>
#include <CommandStack.h>
#include <Model.h>

#include "LoggerMock.h"

TEST(Model, GetName_ValidModel_NameReturned)
{
    LoggerMock logger;
    cxmodel::Model concreteModel{std::make_unique<cxmodel::CommandStack>(200), logger};
    cxmodel::IModel& model = concreteModel;

    ASSERT_EQ(model.GetName(), "Connect X");
}

TEST(Model, GetVersionNumber_ValidModel_ValidVersionNumberReturned)
{
    LoggerMock logger;
    cxmodel::Model concreteModel{std::make_unique<cxmodel::CommandStack>(200), logger};
    cxmodel::IModel& model = concreteModel;

    std::regex expected{"v(\\d)\\.(\\d)+"};

    ASSERT_TRUE(std::regex_match(model.GetVersionNumber(), expected));
}

TEST(Model, Signal_ObserverAttached_SignalNotificationReceived)
{
    // We create an observer specific to the SIGNAL notification context:
    class SignalObserver : public cxmodel::IObserver
    {
        void Update(cxmodel::NotificationContext p_context, cxmodel::Subject* p_subject) override
        {
            ASSERT_TRUE(p_subject);
            ASSERT_TRUE(p_context == cxmodel::NotificationContext::SIGNAL);
        }
    };

    // We create a model:
    LoggerMock logger;
    cxmodel::Model concreteModel{std::make_unique<cxmodel::CommandStack>(200), logger};
    cxmodel::IModel& model = concreteModel;

    // And attach it to our observer:
    SignalObserver observer;
    model.Attach(&observer);

    // From this call, our observer's Update method should be called, and contexts checked:
    model.Signal();
}
