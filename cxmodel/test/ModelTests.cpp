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

TEST(Model, CreateNewGame_ValidNewGameInformation_NewGameCreated)
{
    // We create a model:
    LoggerMock logger;
    cxmodel::Model concreteModel{std::make_unique<cxmodel::CommandStack>(200), logger};
    cxmodel::IModel& model = concreteModel;

    // We create valid new game information:
    cxmodel::NewGameInformation newGameInfo;
    newGameInfo.m_inARowValue = 4u;
    newGameInfo.m_gridWidth = 7u;
    newGameInfo.m_gridHeight = 6u;
    newGameInfo.AddPlayer({"John Doe", "Red"});
    const size_t expectedNbPlayers = newGameInfo.AddPlayer({"Jane Doe", "Blue"});
    const cxmodel::NewGameInformation expected = newGameInfo;

    // We create a new game:
    model.CreateNewGame(newGameInfo);
    const cxmodel::NewGameInformation result = model.GetGameInformation();

    // And check it has indeed been created:
    ASSERT_EQ(result.m_inARowValue, expected.m_inARowValue);
    ASSERT_EQ(result.m_gridWidth, expected.m_gridWidth);
    ASSERT_EQ(result.m_gridHeight, expected.m_gridHeight);

    ASSERT_EQ(result.GetPlayersInformation().size(), expectedNbPlayers);

    const auto playersExpected = expected.GetPlayersInformation();
    const auto playersResult = result.GetPlayersInformation();

    for(size_t i = 0; i < expectedNbPlayers; ++i)
    {
        ASSERT_EQ(playersExpected[i].m_name, playersResult[i].m_name);
        ASSERT_EQ(playersExpected[i].m_discColor, playersResult[i].m_discColor);
    }
}

TEST(Model, CreateNewGame_ValidNewGameInformation_CreateNewNotificationSent)
{
    // We create an observer specific to the CREATE_NEW_GAME notification context:
    class SignalObserver : public cxmodel::IObserver
    {
        void Update(cxmodel::NotificationContext p_context, cxmodel::Subject* p_subject) override
        {
            ASSERT_TRUE(p_subject);
            ASSERT_TRUE(p_context == cxmodel::NotificationContext::CREATE_NEW_GAME);
        }
    };

    // We create a model:
    LoggerMock logger;
    cxmodel::Model concreteModel{std::make_unique<cxmodel::CommandStack>(200), logger};
    cxmodel::IModel& model = concreteModel;

    // And attach it to our observer:
    SignalObserver observer;
    model.Attach(&observer);

    // We create valid new game information:
    cxmodel::NewGameInformation newGameInfo;
    newGameInfo.m_inARowValue = 4u;
    newGameInfo.m_gridWidth = 7u;
    newGameInfo.m_gridHeight = 6u;
    newGameInfo.AddPlayer({"John Doe", "Red"});
    newGameInfo.AddPlayer({"Jane Doe", "Blue"});

    // Then we create the new game:
    model.CreateNewGame(newGameInfo);
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

TEST(Model, SetVerbosityLevel_FromNoneToDebug_VerbosityLevelSet)
{
    // We create a model:
    LoggerMock logger;
    cxmodel::Model concreteModel{std::make_unique<cxmodel::CommandStack>(200), logger};
    cxlog::ILogger& model = concreteModel;

    // Set verbosity level to none:
    model.SetVerbosityLevel(cxlog::VerbosityLevel::NONE);
    ASSERT_EQ(model.GetVerbosityLevel(), cxlog::VerbosityLevel::NONE);

    // We change it to debug and check it has an impact:
    model.SetVerbosityLevel(cxlog::VerbosityLevel::DEBUG);
    ASSERT_EQ(model.GetVerbosityLevel(), cxlog::VerbosityLevel::DEBUG);
}
