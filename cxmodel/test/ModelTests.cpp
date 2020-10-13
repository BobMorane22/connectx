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

#include "CommandStackMock.h"
#include "LoggerMock.h"

TEST(Model, /*DISABLED_*/GetName_ValidModel_NameReturned)
{
    LoggerMock logger;
    cxmodel::Model model{std::make_unique<cxmodel::CommandStack>(200), logger};

    ASSERT_EQ(model.GetName(), "Connect X");
}

TEST(Model, /*DISABLED_*/GetVersionNumber_ValidModel_ValidVersionNumberReturned)
{
    LoggerMock logger;
    cxmodel::Model model{std::make_unique<cxmodel::CommandStack>(200), logger};

    std::regex expected{"v(\\d)\\.(\\d)+"};

    ASSERT_TRUE(std::regex_match(model.GetVersionNumber(), expected));
}

TEST(Model, /*DISABLED_*/GetMinimumGridHeight_ValidModel_ValueReturned)
{
    LoggerMock logger;
    cxmodel::Model model{std::make_unique<cxmodel::CommandStack>(200), logger};

    ASSERT_EQ(model.GetMinimumGridHeight(), 6u);
}

TEST(Model, /*DISABLED_*/GetMinimumGridWidth_ValidModel_ValueReturned)
{
    LoggerMock logger;
    cxmodel::Model model{std::make_unique<cxmodel::CommandStack>(200), logger};

    ASSERT_EQ(model.GetMinimumGridWidth(), 7u);
}

TEST(Model, /*DISABLED_*/GetMinimumInARowValue_ValidModel_ValueReturned)
{
    LoggerMock logger;
    cxmodel::Model model{std::make_unique<cxmodel::CommandStack>(200), logger};

    ASSERT_EQ(model.GetMinimumInARowValue(), 3u);
}

TEST(Model, /*DISABLED_*/GetMaximumGridHeight_ValidModel_ValueReturned)
{
    LoggerMock logger;
    cxmodel::Model model{std::make_unique<cxmodel::CommandStack>(200), logger};

    ASSERT_EQ(model.GetMaximumGridHeight(), 64u);
}

TEST(Model, /*DISABLED_*/GetMaximumGridWidth_ValidModel_ValueReturned)
{
    LoggerMock logger;
    cxmodel::Model model{std::make_unique<cxmodel::CommandStack>(200), logger};

    ASSERT_EQ(model.GetMaximumGridWidth(), 64u);
}

TEST(Model, /*DISABLED_*/GetMaximumInARowValue_ValidModel_ValueReturned)
{
    LoggerMock logger;
    cxmodel::Model model{std::make_unique<cxmodel::CommandStack>(200), logger};

    ASSERT_EQ(model.GetMaximumInARowValue(), 8u);
}

TEST(Model, /*DISABLED_*/GetMinimumNumberOfPlayers_ValidModel_ValueReturned)
{
    LoggerMock logger;
    cxmodel::Model model{std::make_unique<cxmodel::CommandStack>(200), logger};

    ASSERT_EQ(model.GetMinimumNumberOfPlayers(), 2u);
}

TEST(Model, /*DISABLED_*/GetMaximumNumberOfPlayers_ValidModel_ValueReturned)
{
    LoggerMock logger;
    cxmodel::Model model{std::make_unique<cxmodel::CommandStack>(200), logger};

    ASSERT_EQ(model.GetMaximumNumberOfPlayers(), 10u);
}

TEST(Model, /*DISABLED_*/CreateNewGame_ValidNewGameInformation_NewGameCreated)
{
    // We create a model:
    LoggerMock logger;
    cxmodel::Model model{std::make_unique<cxmodel::CommandStack>(200), logger};

    // We create valid new game information:
    constexpr size_t GRID_WIDTH = 7u;
    constexpr size_t GRID_HEIGHT = 6u;
    constexpr size_t IN_A_ROW = 4u;
    const cxmodel::Player JOHN_DOE{"John Doe", cxmodel::MakeRed()};
    const cxmodel::Player JANE_DOE{"Jane Doe", cxmodel::MakeBlue()};

    cxmodel::NewGameInformation newGameInfo;
    newGameInfo.m_gridWidth = GRID_WIDTH;
    newGameInfo.m_gridHeight = GRID_HEIGHT;
    newGameInfo.m_inARowValue = IN_A_ROW;
    newGameInfo.AddPlayer(JOHN_DOE);
    newGameInfo.AddPlayer(JANE_DOE);

    // We create a new game:
    model.CreateNewGame(newGameInfo);

    // And check it has indeed been created:
    ASSERT_EQ(model.GetActivePlayer(), JOHN_DOE);
    ASSERT_EQ(model.GetNextPlayer(), JANE_DOE);
    ASSERT_EQ(model.GetCurrentGridWidth(), 7u);
    ASSERT_EQ(model.GetCurrentGridHeight(), 6u);
    ASSERT_EQ(model.GetCurrentInARowValue(), 4u);
}

TEST(Model, /*DISABLED_*/CreateNewGame_ValidNewGameInformation_CreateNewNotificationSent)
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
    cxmodel::Model model{std::make_unique<cxmodel::CommandStack>(200), logger};

    // And attach it to our observer:
    SignalObserver observer;
    model.Attach(&observer);

    // We create valid new game information:
    cxmodel::NewGameInformation newGameInfo;
    newGameInfo.m_inARowValue = 4u;
    newGameInfo.m_gridWidth = 7u;
    newGameInfo.m_gridHeight = 6u;
    newGameInfo.AddPlayer({"John Doe", cxmodel::MakeRed()});
    newGameInfo.AddPlayer({"Jane Doe", cxmodel::MakeBlue()});

    // Then we create the new game:
    model.CreateNewGame(newGameInfo);
}

TEST(Model, /*DISABLED_*/IsWon_ValidModel_ThrowsForNow)
{
    LoggerMock logger;
    cxmodel::Model model{std::make_unique<cxmodel::CommandStack>(200), logger};

    ASSERT_THROW(model.IsWon(), std::logic_error);
}

TEST(Model, /*DISABLED_*/IsTie_ValidModel_ThrowsForNow)
{
    LoggerMock logger;
    cxmodel::Model model{std::make_unique<cxmodel::CommandStack>(200), logger};

    ASSERT_THROW(model.IsTie(), std::logic_error);
}

TEST(Model, /*DISABLED_*/Undo_RandomCommand_UndoCalledOnCommandStack)
{
    std::unique_ptr<CommandStackMock> cmdStack = std::make_unique<CommandStackMock>();
    ASSERT_TRUE(cmdStack);

    CommandStackMock& cmdStackMock = *cmdStack;

    // We create a model:
    LoggerMock logger;
    cxmodel::Model model{std::move(cmdStack), logger};

    ASSERT_FALSE(cmdStackMock.IsUndoed());

    // We undo the command:
    model.Undo();

    ASSERT_TRUE(cmdStackMock.IsUndoed());
}

TEST(Model, /*DISABLED_*/Redo_RandomCommand_RedoCalledOnCommandStack)
{
    std::unique_ptr<CommandStackMock> cmdStack = std::make_unique<CommandStackMock>();
    ASSERT_TRUE(cmdStack);

    CommandStackMock& cmdStackMock = *cmdStack;

    // We create a model:
    LoggerMock logger;
    cxmodel::Model model{std::move(cmdStack), logger};

    ASSERT_FALSE(cmdStackMock.IsRedoed());

    // We undo the command:
    model.Redo();

    ASSERT_TRUE(cmdStackMock.IsRedoed());
}

TEST(Model, /*DISABLED_*/SetVerbosityLevel_FromNoneToDebug_VerbosityLevelSet)
{
    // We create a model:
    LoggerMock logger;
    cxmodel::Model model{std::make_unique<cxmodel::CommandStack>(200), logger};

    // Set verbosity level to none:
    model.SetVerbosityLevel(cxlog::VerbosityLevel::NONE);
    ASSERT_EQ(model.GetVerbosityLevel(), cxlog::VerbosityLevel::NONE);

    // We change it to debug and check it has an impact:
    model.SetVerbosityLevel(cxlog::VerbosityLevel::DEBUG);
    ASSERT_EQ(model.GetVerbosityLevel(), cxlog::VerbosityLevel::DEBUG);
}
