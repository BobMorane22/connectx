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

#include <CommandStack.h>
#include <Disc.h>
#include <IObserver.h>
#include <Model.h>

#include "CommandStackMock.h"
#include "DisableStdStreamsRAII.h"
#include "LoggerMock.h"
#include "ModelTestHelpers.h"

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

TEST(Model, /*DISABLED_*/CreateNewGame_ValidNewGameInformation_CreateNewGameNotificationSent)
{
    // We create a model:
    LoggerMock logger;
    cxmodel::Model model{std::make_unique<cxmodel::CommandStack>(200), logger};

    // And attach it to our observer:
    ModelNotificationCatcher createNewGameObserver{cxmodel::NotificationContext::CREATE_NEW_GAME};
    model.Attach(&createNewGameObserver);

    // We create valid new game information:
    cxmodel::NewGameInformation newGameInfo;
    newGameInfo.m_inARowValue = 4u;
    newGameInfo.m_gridWidth = 7u;
    newGameInfo.m_gridHeight = 6u;
    newGameInfo.AddPlayer({"John Doe", cxmodel::MakeRed()});
    newGameInfo.AddPlayer({"Jane Doe", cxmodel::MakeBlue()});

    // Then we create the new game:
    ASSERT_FALSE(createNewGameObserver.WasNotified());
    model.CreateNewGame(newGameInfo);
    ASSERT_TRUE(createNewGameObserver.WasNotified());
}

TEST(Model, /*DISABLED_*/DropChip_ValidModelChipAndColumn_ChipDroppedNotificationSent)
{
    // We create a model:
    LoggerMock logger;
    cxmodel::Model model{std::make_unique<cxmodel::CommandStack>(200), logger};

    // We create valid new game information:
    cxmodel::NewGameInformation newGameInfo;
    newGameInfo.m_inARowValue = 4u;
    newGameInfo.m_gridWidth = 7u;
    newGameInfo.m_gridHeight = 6u;
    newGameInfo.AddPlayer({"John Doe", cxmodel::MakeRed()});
    newGameInfo.AddPlayer({"Jane Doe", cxmodel::MakeBlue()});

    // Then we create the new game:
    model.CreateNewGame(newGameInfo);

    // We then attach the model to our observer:
    ModelNotificationCatcher chipDropObserver{cxmodel::NotificationContext::CHIP_DROPPED};
    model.Attach(&chipDropObserver);

    // We drop a chip. It should trigger a notification since the board is empty:
    const cxmodel::Disc RED_CHIP{cxmodel::MakeRed()};

    ASSERT_FALSE(chipDropObserver.WasNotified());
    model.DropChip(RED_CHIP, 0u);
    ASSERT_TRUE(chipDropObserver.WasNotified());
}

TEST(Model, /*DISABLED_*/DropChip_ValidModelChipAndColumn_GameDataUpdated)
{
    // We create a model:
    LoggerMock logger;
    cxmodel::Model model{std::make_unique<cxmodel::CommandStack>(200), logger};

    // We create valid new game information:
    cxmodel::NewGameInformation newGameInfo;
    newGameInfo.m_inARowValue = 4u;
    newGameInfo.m_gridWidth = 7u;
    newGameInfo.m_gridHeight = 6u;
    newGameInfo.AddPlayer({"John Doe", cxmodel::MakeRed()});
    newGameInfo.AddPlayer({"Jane Doe", cxmodel::MakeBlue()});

    // Then we create the new game:
    model.CreateNewGame(newGameInfo);

    // We drop a chip:
    ASSERT_EQ(model.GetActivePlayer(), cxmodel::Player("John Doe", cxmodel::MakeRed()));
    ASSERT_EQ(model.GetNextPlayer(), cxmodel::Player("Jane Doe", cxmodel::MakeBlue()));

    const cxmodel::Disc RED_CHIP{cxmodel::MakeRed()};
    model.DropChip(RED_CHIP, 0u);

    ASSERT_EQ(model.GetActivePlayer(), cxmodel::Player("Jane Doe", cxmodel::MakeBlue()));
    ASSERT_EQ(model.GetNextPlayer(), cxmodel::Player("John Doe", cxmodel::MakeRed()));
}

TEST(Model, /*DISABLED_*/DropChip_ValidModelTwoSameChipsDropped_GameDataNotUpdated)
{
    DisableStdStreamsRAII streamDisabler;

    // We create a model:
    LoggerMock logger;
    cxmodel::Model model{std::make_unique<cxmodel::CommandStack>(200), logger};

    // We create valid new game information:
    cxmodel::NewGameInformation newGameInfo;
    newGameInfo.m_inARowValue = 4u;
    newGameInfo.m_gridWidth = 7u;
    newGameInfo.m_gridHeight = 6u;
    newGameInfo.AddPlayer({"John Doe", cxmodel::MakeRed()});
    newGameInfo.AddPlayer({"Jane Doe", cxmodel::MakeBlue()});

    // Then we create the new game:
    model.CreateNewGame(newGameInfo);

    // We drop a chip:
    ASSERT_EQ(model.GetActivePlayer(), cxmodel::Player("John Doe", cxmodel::MakeRed()));
    ASSERT_EQ(model.GetNextPlayer(), cxmodel::Player("Jane Doe", cxmodel::MakeBlue()));

    const cxmodel::Disc RED_CHIP{cxmodel::MakeRed()};
    model.DropChip(RED_CHIP, 0u);

    // This will assert:
    model.DropChip(RED_CHIP, 0u);

    ASSERT_EQ(model.GetActivePlayer(), cxmodel::Player("Jane Doe", cxmodel::MakeBlue()));
    ASSERT_EQ(model.GetNextPlayer(), cxmodel::Player("John Doe", cxmodel::MakeRed()));
}

TEST(Model, /*DISABLED_*/DropChip_ValidModelGameIsWon_NotificationsHappen)
{
    // We create a model:
    LoggerMock logger;
    cxmodel::Model model{std::make_unique<cxmodel::CommandStack>(200), logger};

    ModelNotificationCatcher gameWonObserver{cxmodel::NotificationContext::GAME_WON};
    model.Attach(&gameWonObserver);

    // We create valid new game information:
    cxmodel::NewGameInformation newGameInfo;
    newGameInfo.m_inARowValue = 4u;
    newGameInfo.m_gridWidth = 7u;
    newGameInfo.m_gridHeight = 6u;
    newGameInfo.AddPlayer({"John Doe", cxmodel::MakeRed()});
    newGameInfo.AddPlayer({"Jane Doe", cxmodel::MakeBlue()});

    // Then we create the new game:
    model.CreateNewGame(newGameInfo);

    // We drop chips:
    const cxmodel::Disc RED_CHIP{cxmodel::MakeRed()};
    const cxmodel::Disc BLUE_CHIP{cxmodel::MakeBlue()};

    ASSERT_EQ(model.GetActivePlayer(), cxmodel::Player("John Doe", cxmodel::MakeRed()));
    ASSERT_EQ(model.GetNextPlayer(), cxmodel::Player("Jane Doe", cxmodel::MakeBlue()));

    model.DropChip(RED_CHIP, 0u);
    model.DropChip(BLUE_CHIP, 1u);
    model.DropChip(RED_CHIP, 0u);
    model.DropChip(BLUE_CHIP, 1u);
    model.DropChip(RED_CHIP, 0u);
    model.DropChip(BLUE_CHIP, 1u);

    // And the first player wins:
    ASSERT_FALSE(gameWonObserver.WasNotified());
    model.DropChip(RED_CHIP, 0u);
    ASSERT_TRUE(gameWonObserver.WasNotified());
}

TEST(Model, /*DISABLED_*/DropChip_ValidModelGameIsWon_WinnerIsFirstPlayer)
{
    // We create a model:
    LoggerMock logger;
    cxmodel::Model model{std::make_unique<cxmodel::CommandStack>(200), logger};

    // We create valid new game information:
    const cxmodel::ChipColor FIRST_PLAYER_COLOR{cxmodel::MakeRed()};
    const cxmodel::Player FIRST_PLAYER{"John Doe", FIRST_PLAYER_COLOR};

    const cxmodel::ChipColor SECOND_PLAYER_COLOR{cxmodel::MakeBlue()};
    const cxmodel::Player SECOND_PLAYER{"Jane Doe", SECOND_PLAYER_COLOR};

    const cxmodel::ChipColor THRIRD_PLAYER_COLOR{cxmodel::MakeYellow()};
    const cxmodel::Player THIRD_PLAYER{"Bob Morane", THRIRD_PLAYER_COLOR};

    cxmodel::NewGameInformation newGameInfo;
    newGameInfo.m_inARowValue = 4u;
    newGameInfo.m_gridWidth = 7u;
    newGameInfo.m_gridHeight = 6u;
    newGameInfo.AddPlayer(FIRST_PLAYER);
    newGameInfo.AddPlayer(SECOND_PLAYER);
    newGameInfo.AddPlayer(THIRD_PLAYER);

    // Then we create the new game:
    model.CreateNewGame(newGameInfo);

    // We drop chips:
    const cxmodel::Disc FIRST_PLAYER_CHIP{FIRST_PLAYER_COLOR};
    const cxmodel::Disc SECOND_PLAYER_CHIP{SECOND_PLAYER_COLOR};
    const cxmodel::Disc THIRD_PLAYER_CHIP{THRIRD_PLAYER_COLOR};

    ASSERT_EQ(model.GetActivePlayer(), FIRST_PLAYER);
    ASSERT_EQ(model.GetNextPlayer(), SECOND_PLAYER);

    model.DropChip(FIRST_PLAYER_CHIP, 0u);
    model.DropChip(SECOND_PLAYER_CHIP, 1u);
    model.DropChip(THIRD_PLAYER_CHIP, 2u);

    model.DropChip(FIRST_PLAYER_CHIP, 0u);
    model.DropChip(SECOND_PLAYER_CHIP, 1u);
    model.DropChip(THIRD_PLAYER_CHIP, 2u);

    model.DropChip(FIRST_PLAYER_CHIP, 0u);
    model.DropChip(SECOND_PLAYER_CHIP, 1u);
    model.DropChip(THIRD_PLAYER_CHIP, 2u);

    // And the first player wins:
    model.DropChip(FIRST_PLAYER_CHIP, 0u);

    ASSERT_EQ(FIRST_PLAYER, model.GetActivePlayer());
}

TEST(Model, /*DISABLED_*/DropChip_ValidModelGameIsWon_WinnerIsMiddlePlayer)
{
    // We create a model:
    LoggerMock logger;
    cxmodel::Model model{std::make_unique<cxmodel::CommandStack>(200), logger};

    // We create valid new game information:
    const cxmodel::ChipColor FIRST_PLAYER_COLOR{cxmodel::MakeRed()};
    const cxmodel::Player FIRST_PLAYER{"John Doe", FIRST_PLAYER_COLOR};

    const cxmodel::ChipColor SECOND_PLAYER_COLOR{cxmodel::MakeBlue()};
    const cxmodel::Player SECOND_PLAYER{"Jane Doe", SECOND_PLAYER_COLOR};

    const cxmodel::ChipColor THRIRD_PLAYER_COLOR{cxmodel::MakeYellow()};
    const cxmodel::Player THIRD_PLAYER{"Bob Morane", THRIRD_PLAYER_COLOR};

    cxmodel::NewGameInformation newGameInfo;
    newGameInfo.m_inARowValue = 4u;
    newGameInfo.m_gridWidth = 7u;
    newGameInfo.m_gridHeight = 6u;
    newGameInfo.AddPlayer(FIRST_PLAYER);
    newGameInfo.AddPlayer(SECOND_PLAYER);
    newGameInfo.AddPlayer(THIRD_PLAYER);

    // Then we create the new game:
    model.CreateNewGame(newGameInfo);

    // We drop chips:
    const cxmodel::Disc FIRST_PLAYER_CHIP{FIRST_PLAYER_COLOR};
    const cxmodel::Disc SECOND_PLAYER_CHIP{SECOND_PLAYER_COLOR};
    const cxmodel::Disc THIRD_PLAYER_CHIP{THRIRD_PLAYER_COLOR};

    ASSERT_EQ(model.GetActivePlayer(), FIRST_PLAYER);
    ASSERT_EQ(model.GetNextPlayer(), SECOND_PLAYER);

    model.DropChip(FIRST_PLAYER_CHIP, 0u);
    model.DropChip(SECOND_PLAYER_CHIP, 1u);
    model.DropChip(THIRD_PLAYER_CHIP, 2u);

    model.DropChip(FIRST_PLAYER_CHIP, 0u);
    model.DropChip(SECOND_PLAYER_CHIP, 1u);
    model.DropChip(THIRD_PLAYER_CHIP, 2u);

    model.DropChip(FIRST_PLAYER_CHIP, 0u);
    model.DropChip(SECOND_PLAYER_CHIP, 1u);
    model.DropChip(THIRD_PLAYER_CHIP, 2u);

    model.DropChip(FIRST_PLAYER_CHIP, 4u);

    // And the second player wins:
    model.DropChip(SECOND_PLAYER_CHIP, 1u);

    ASSERT_EQ(SECOND_PLAYER, model.GetActivePlayer());
}

TEST(Model, /*DISABLED_*/DropChip_ValidModelGameIsWon_WinnerIsLastPlayer)
{
    // We create a model:
    LoggerMock logger;
    cxmodel::Model model{std::make_unique<cxmodel::CommandStack>(200), logger};

    // We create valid new game information:
    const cxmodel::ChipColor FIRST_PLAYER_COLOR{cxmodel::MakeRed()};
    const cxmodel::Player FIRST_PLAYER{"John Doe", FIRST_PLAYER_COLOR};

    const cxmodel::ChipColor SECOND_PLAYER_COLOR{cxmodel::MakeBlue()};
    const cxmodel::Player SECOND_PLAYER{"Jane Doe", SECOND_PLAYER_COLOR};

    const cxmodel::ChipColor THRIRD_PLAYER_COLOR{cxmodel::MakeYellow()};
    const cxmodel::Player THIRD_PLAYER{"Bob Morane", THRIRD_PLAYER_COLOR};

    cxmodel::NewGameInformation newGameInfo;
    newGameInfo.m_inARowValue = 4u;
    newGameInfo.m_gridWidth = 7u;
    newGameInfo.m_gridHeight = 6u;
    newGameInfo.AddPlayer(FIRST_PLAYER);
    newGameInfo.AddPlayer(SECOND_PLAYER);
    newGameInfo.AddPlayer(THIRD_PLAYER);

    // Then we create the new game:
    model.CreateNewGame(newGameInfo);

    // We drop chips:
    const cxmodel::Disc FIRST_PLAYER_CHIP{FIRST_PLAYER_COLOR};
    const cxmodel::Disc SECOND_PLAYER_CHIP{SECOND_PLAYER_COLOR};
    const cxmodel::Disc THIRD_PLAYER_CHIP{THRIRD_PLAYER_COLOR};

    ASSERT_EQ(model.GetActivePlayer(), FIRST_PLAYER);
    ASSERT_EQ(model.GetNextPlayer(), SECOND_PLAYER);

    model.DropChip(FIRST_PLAYER_CHIP, 0u);
    model.DropChip(SECOND_PLAYER_CHIP, 1u);
    model.DropChip(THIRD_PLAYER_CHIP, 2u);

    model.DropChip(FIRST_PLAYER_CHIP, 0u);
    model.DropChip(SECOND_PLAYER_CHIP, 1u);
    model.DropChip(THIRD_PLAYER_CHIP, 2u);

    model.DropChip(FIRST_PLAYER_CHIP, 0u);
    model.DropChip(SECOND_PLAYER_CHIP, 1u);
    model.DropChip(THIRD_PLAYER_CHIP, 2u);

    model.DropChip(FIRST_PLAYER_CHIP, 4u);
    model.DropChip(SECOND_PLAYER_CHIP, 4u);

    // And the third player wins:
    model.DropChip(THIRD_PLAYER_CHIP, 2u);

    ASSERT_EQ(THIRD_PLAYER, model.GetActivePlayer());
}

TEST(Model, /*DISABLED_*/EndCurrentGame_ValidModel_NotificationsSent)
{
    ModelNotificationCatcher gameEndedObserver{cxmodel::NotificationContext::GAME_ENDED};
    
    // We create a model:
    LoggerMock logger;
    cxmodel::Model model{std::make_unique<cxmodel::CommandStack>(200), logger};

    // We create valid game information:
    cxmodel::NewGameInformation newGameInfo;
    newGameInfo.m_inARowValue = 4u;
    newGameInfo.m_gridWidth = 7u;
    newGameInfo.m_gridHeight = 6u;
    newGameInfo.AddPlayer({"John Doe", cxmodel::MakeRed()});
    newGameInfo.AddPlayer({"Jane Doe", cxmodel::MakeBlue()});

    // Then we create the new game:
    model.CreateNewGame(newGameInfo);

    // We attach our observer:
    model.Attach(&gameEndedObserver);

    ASSERT_FALSE(gameEndedObserver.WasNotified());
    model.EndCurrentGame();
    ASSERT_TRUE(gameEndedObserver.WasNotified());
}

TEST(Model, /*DISABLED_*/EndCurrentGame_ValidModel_CommandStackEmptied)
{
    // We create a model:
    LoggerMock logger;

    auto cmdStack = std::make_unique<cxmodel::CommandStack>(200);
    auto* commands = cmdStack.get();
    cxmodel::Model model{std::move(cmdStack), logger};

    // We create valid game information:
    cxmodel::NewGameInformation newGameInfo;
    newGameInfo.m_inARowValue = 4u;
    newGameInfo.m_gridWidth = 7u;
    newGameInfo.m_gridHeight = 6u;
    newGameInfo.AddPlayer({"John Doe", cxmodel::MakeRed()});
    newGameInfo.AddPlayer({"Jane Doe", cxmodel::MakeBlue()});

    // Then we create the new game:
    model.CreateNewGame(newGameInfo);
    ASSERT_FALSE(commands->IsEmpty());

    // And end it:
    model.EndCurrentGame();

    ASSERT_TRUE(commands->IsEmpty());
}

TEST(Model, /*DISABLED_*/EndCurrentGame_ValidModel_PlayersInfoReset)
{
    DisableStdStreamsRAII m_noStream;

    // We create a model:
    LoggerMock logger;
    cxmodel::Model model{std::make_unique<cxmodel::CommandStack>(200), logger};

    // We create valid game information:
    const cxmodel::Player ACTIVE{"John Doe", cxmodel::MakeRed()};
    const cxmodel::Player NEXT{"Jane Doe", cxmodel::MakeBlue()};

    cxmodel::NewGameInformation newGameInfo;
    newGameInfo.m_inARowValue = 4u;
    newGameInfo.m_gridWidth = 7u;
    newGameInfo.m_gridHeight = 6u;
    newGameInfo.AddPlayer(ACTIVE);
    newGameInfo.AddPlayer(NEXT);

    // Then we create the new game:
    model.CreateNewGame(newGameInfo);
    ASSERT_EQ(ACTIVE, model.GetActivePlayer());
    ASSERT_EQ(NEXT, model.GetNextPlayer());

    // And end it:
    model.EndCurrentGame();

    const cxmodel::Player NO_ACTIVE_PLAYER{"Woops (active)!", {0, 0, 0, 0}};
    const cxmodel::Player NO_NEXT_PLAYER{"Woops! (next)", {0, 0, 0, 0}};

    // Will assert here...
    ASSERT_EQ(NO_ACTIVE_PLAYER, model.GetActivePlayer());
    ASSERT_EQ(NO_NEXT_PLAYER, model.GetNextPlayer());
}

TEST(Model, /*DISABLED_*/EndCurrentGame_ValidModel_InARowValueReset)
{
    // We create a model:
    LoggerMock logger;
    cxmodel::Model model{std::make_unique<cxmodel::CommandStack>(200), logger};

    // We create valid game information:
    cxmodel::NewGameInformation newGameInfo;
    newGameInfo.m_inARowValue = 5u;
    newGameInfo.m_gridWidth = 7u;
    newGameInfo.m_gridHeight = 6u;
    newGameInfo.AddPlayer({"John Doe", cxmodel::MakeRed()});
    newGameInfo.AddPlayer({"Jane Doe", cxmodel::MakeBlue()});

    // Then we create the new game:
    model.CreateNewGame(newGameInfo);
    ASSERT_EQ(5u, model.GetCurrentInARowValue());

    // And end it:
    model.EndCurrentGame();
    ASSERT_EQ(4u, model.GetCurrentInARowValue());
}

TEST(Model, /*DISABLED_*/ReinitializeCurrentGame_ValidModel_NotificationHappens)
{
    ModelNotificationCatcher gameReinitializedObserver{cxmodel::NotificationContext::GAME_REINITIALIZED};
    
    // We create a model:
    LoggerMock logger;
    cxmodel::Model model{std::make_unique<cxmodel::CommandStack>(200), logger};

    // We create valid game information:
    cxmodel::NewGameInformation newGameInfo;
    newGameInfo.m_inARowValue = 4u;
    newGameInfo.m_gridWidth = 7u;
    newGameInfo.m_gridHeight = 6u;
    newGameInfo.AddPlayer({"John Doe", cxmodel::MakeRed()});
    newGameInfo.AddPlayer({"Jane Doe", cxmodel::MakeBlue()});

    // Then we create the new game:
    model.CreateNewGame(newGameInfo);

    // We attach our observer:
    model.Attach(&gameReinitializedObserver);

    ASSERT_FALSE(gameReinitializedObserver.WasNotified());
    model.ReinitializeCurrentGame();
    ASSERT_TRUE(gameReinitializedObserver.WasNotified());
}

TEST(Model, /*DISABLED_*/ReinitializeCurrentGame_ValidModel_CommandStackEmptied)
{
    // We create a model:
    LoggerMock logger;

    auto cmdStack = std::make_unique<cxmodel::CommandStack>(200);
    auto* commands = cmdStack.get();
    cxmodel::Model model{std::move(cmdStack), logger};

    // We create valid game information:
    cxmodel::NewGameInformation newGameInfo;
    newGameInfo.m_inARowValue = 4u;
    newGameInfo.m_gridWidth = 7u;
    newGameInfo.m_gridHeight = 6u;
    newGameInfo.AddPlayer({"John Doe", cxmodel::MakeRed()});
    newGameInfo.AddPlayer({"Jane Doe", cxmodel::MakeBlue()});

    // Then we create the new game:
    model.CreateNewGame(newGameInfo);
    ASSERT_FALSE(commands->IsEmpty());

    // And reinitialize it:
    model.ReinitializeCurrentGame();

    ASSERT_TRUE(commands->IsEmpty());
}

TEST(Model, /*DISABLED_*/ReinitializeCurrentGame_ValidModel_BoardReinitialized)
{
    // We create a model:
    LoggerMock logger;
    cxmodel::Model model{std::make_unique<cxmodel::CommandStack>(200), logger};

    // We create valid new game information:
    const cxmodel::ChipColor FIRST_PLAYER_COLOR{cxmodel::MakeRed()};
    const cxmodel::Player FIRST_PLAYER{"John Doe", FIRST_PLAYER_COLOR};

    const cxmodel::ChipColor SECOND_PLAYER_COLOR{cxmodel::MakeBlue()};
    const cxmodel::Player SECOND_PLAYER{"Jane Doe", SECOND_PLAYER_COLOR};

    cxmodel::NewGameInformation newGameInfo;
    newGameInfo.m_inARowValue = 4u;
    newGameInfo.m_gridWidth = 7u;
    newGameInfo.m_gridHeight = 6u;
    newGameInfo.AddPlayer(FIRST_PLAYER);
    newGameInfo.AddPlayer(SECOND_PLAYER);

    // Then we create the new game:
    model.CreateNewGame(newGameInfo);

    // We drop chips:
    const cxmodel::Disc FIRST_PLAYER_CHIP{FIRST_PLAYER_COLOR};
    const cxmodel::Disc SECOND_PLAYER_CHIP{SECOND_PLAYER_COLOR};

    ASSERT_EQ(model.GetActivePlayer(), FIRST_PLAYER);
    ASSERT_EQ(model.GetNextPlayer(), SECOND_PLAYER);

    model.DropChip(FIRST_PLAYER_CHIP, 0u);
    model.DropChip(SECOND_PLAYER_CHIP, 1u);

    ASSERT_EQ(FIRST_PLAYER_COLOR, model.GetChip(0u, 0u).GetColor());
    ASSERT_EQ(SECOND_PLAYER_COLOR, model.GetChip(0u, 1u).GetColor());

    model.ReinitializeCurrentGame();

    for(size_t row = 0u; row < model.GetCurrentGridHeight(); ++row)
    {
        for(size_t column = 0u; column < model.GetCurrentGridWidth(); ++column)
        {
            ASSERT_EQ(cxmodel::MakeTransparent(), model.GetChip(row, column).GetColor());
        }
    }
}

TEST(Model, /*DISABLED_*/ReinitializeCurrentGame_ValidModel_PlayersReinitialized)
{
    // We create a model:
    LoggerMock logger;
    cxmodel::Model model{std::make_unique<cxmodel::CommandStack>(200), logger};

    // We create valid new game information:
    const cxmodel::ChipColor FIRST_PLAYER_COLOR{cxmodel::MakeRed()};
    const cxmodel::Player FIRST_PLAYER{"John Doe", FIRST_PLAYER_COLOR};

    const cxmodel::ChipColor SECOND_PLAYER_COLOR{cxmodel::MakeBlue()};
    const cxmodel::Player SECOND_PLAYER{"Jane Doe", SECOND_PLAYER_COLOR};

    cxmodel::NewGameInformation newGameInfo;
    newGameInfo.m_inARowValue = 4u;
    newGameInfo.m_gridWidth = 7u;
    newGameInfo.m_gridHeight = 6u;
    newGameInfo.AddPlayer(FIRST_PLAYER);
    newGameInfo.AddPlayer(SECOND_PLAYER);

    // Then we create the new game:
    model.CreateNewGame(newGameInfo);

    // We drop a chip:
    const cxmodel::Disc FIRST_PLAYER_CHIP{FIRST_PLAYER_COLOR};
    model.DropChip(FIRST_PLAYER_CHIP, 0u);

    ASSERT_EQ(model.GetActivePlayer(), SECOND_PLAYER);
    ASSERT_EQ(model.GetNextPlayer(), FIRST_PLAYER);

    model.ReinitializeCurrentGame();

    ASSERT_EQ(model.GetActivePlayer(), FIRST_PLAYER);
    ASSERT_EQ(model.GetNextPlayer(), SECOND_PLAYER);
}

TEST(Model, /*DISABLED_*/ReinitializeCurrentGame_ValidModel_WinResolutionReinitialized)
{
    // We create a model:
    LoggerMock logger;
    cxmodel::Model model{std::make_unique<cxmodel::CommandStack>(200), logger};

    // We create valid new game information:
    const cxmodel::ChipColor FIRST_PLAYER_COLOR{cxmodel::MakeRed()};
    const cxmodel::Player FIRST_PLAYER{"John Doe", FIRST_PLAYER_COLOR};

    const cxmodel::ChipColor SECOND_PLAYER_COLOR{cxmodel::MakeBlue()};
    const cxmodel::Player SECOND_PLAYER{"Jane Doe", SECOND_PLAYER_COLOR};

    const cxmodel::ChipColor THRIRD_PLAYER_COLOR{cxmodel::MakeYellow()};
    const cxmodel::Player THIRD_PLAYER{"Bob Morane", THRIRD_PLAYER_COLOR};

    cxmodel::NewGameInformation newGameInfo;
    newGameInfo.m_inARowValue = 4u;
    newGameInfo.m_gridWidth = 7u;
    newGameInfo.m_gridHeight = 6u;
    newGameInfo.AddPlayer(FIRST_PLAYER);
    newGameInfo.AddPlayer(SECOND_PLAYER);
    newGameInfo.AddPlayer(THIRD_PLAYER);

    // Then we create the new game:
    model.CreateNewGame(newGameInfo);

    // We drop chips:
    const cxmodel::Disc FIRST_PLAYER_CHIP{FIRST_PLAYER_COLOR};
    const cxmodel::Disc SECOND_PLAYER_CHIP{SECOND_PLAYER_COLOR};
    const cxmodel::Disc THIRD_PLAYER_CHIP{THRIRD_PLAYER_COLOR};

    ASSERT_EQ(model.GetActivePlayer(), FIRST_PLAYER);
    ASSERT_EQ(model.GetNextPlayer(), SECOND_PLAYER);

    model.DropChip(FIRST_PLAYER_CHIP, 0u);
    model.DropChip(SECOND_PLAYER_CHIP, 1u);
    model.DropChip(THIRD_PLAYER_CHIP, 2u);

    model.DropChip(FIRST_PLAYER_CHIP, 0u);
    model.DropChip(SECOND_PLAYER_CHIP, 1u);
    model.DropChip(THIRD_PLAYER_CHIP, 2u);

    model.DropChip(FIRST_PLAYER_CHIP, 0u);
    model.DropChip(SECOND_PLAYER_CHIP, 1u);
    model.DropChip(THIRD_PLAYER_CHIP, 2u);

    // At this point, the first player could win by dropping a chip
    // at the first row. Instead, we reinitialize the game:
    model.ReinitializeCurrentGame();

    // Then we play the "what could have been" the winning drop:
    model.DropChip(FIRST_PLAYER_CHIP, 0u);

    // And we check if the game is resolved:
    ASSERT_FALSE(model.IsWon());
}

TEST(Model, /*DISABLED_*/GetChip_ValidModel_ChipReturned)
{
    // We create a model:
    LoggerMock logger;
    cxmodel::Model model{std::make_unique<cxmodel::CommandStack>(200), logger};

    // We create valid new game information:
    cxmodel::NewGameInformation newGameInfo;
    newGameInfo.m_inARowValue = 4u;
    newGameInfo.m_gridWidth = 7u;
    newGameInfo.m_gridHeight = 6u;
    newGameInfo.AddPlayer({"John Doe", cxmodel::MakeRed()});
    newGameInfo.AddPlayer({"Jane Doe", cxmodel::MakeBlue()});

    // Then we create the new game:
    model.CreateNewGame(newGameInfo);

    // For now, no chip has been dropped, all returned chips should be transparent:
    const cxmodel::IChip& chipBefore = model.GetChip(0u, 0u);
    ASSERT_EQ(chipBefore, cxmodel::Disc(cxmodel::MakeTransparent()));

    // We drop a chip:
    const cxmodel::Disc RED_CHIP{cxmodel::MakeRed()};
    model.DropChip(RED_CHIP, 0u);

    // We now have a red chip at (0,0):
    const cxmodel::IChip& chipAfter = model.GetChip(0u, 0u);
    ASSERT_EQ(chipAfter, cxmodel::Disc(cxmodel::MakeRed()));
}

TEST(Model, /*DISABLED_*/GetChip_InvalidRow_ReturnsNoDisc)
{
    // We create a model:
    LoggerMock logger;
    cxmodel::Model model{std::make_unique<cxmodel::CommandStack>(200), logger};

    // We create valid new game information:
    cxmodel::NewGameInformation newGameInfo;
    newGameInfo.m_inARowValue = 4u;
    newGameInfo.m_gridWidth = 7u;
    newGameInfo.m_gridHeight = 6u;
    newGameInfo.AddPlayer({"John Doe", cxmodel::MakeRed()});
    newGameInfo.AddPlayer({"Jane Doe", cxmodel::MakeBlue()});

    // Then we create the new game:
    model.CreateNewGame(newGameInfo);

    // For now, no chip has been dropped, all returned chips should be transparent:
    const cxmodel::IChip& chipBefore = model.GetChip(model.GetCurrentGridHeight(), 0u);
    ASSERT_EQ(chipBefore, cxmodel::Disc(cxmodel::MakeTransparent()));
}

TEST(Model, /*DISABLED_*/GetChip_InvalidColumn_ReturnsNoDisc)
{
    // We create a model:
    LoggerMock logger;
    cxmodel::Model model{std::make_unique<cxmodel::CommandStack>(200), logger};

    // We create valid new game information:
    cxmodel::NewGameInformation newGameInfo;
    newGameInfo.m_inARowValue = 4u;
    newGameInfo.m_gridWidth = 7u;
    newGameInfo.m_gridHeight = 6u;
    newGameInfo.AddPlayer({"John Doe", cxmodel::MakeRed()});
    newGameInfo.AddPlayer({"Jane Doe", cxmodel::MakeBlue()});

    // Then we create the new game:
    model.CreateNewGame(newGameInfo);

    // For now, no chip has been dropped, all returned chips should be transparent:
    const cxmodel::IChip& chipBefore = model.GetChip(0u, model.GetCurrentGridWidth());
    ASSERT_EQ(chipBefore, cxmodel::Disc(cxmodel::MakeTransparent()));
}

TEST(Model, /*DISABLED_*/IsWon_ValidModel_DoesNotThrow)
{
    DisableStdStreamsRAII streamDisabler;

    LoggerMock logger;
    cxmodel::Model model{std::make_unique<cxmodel::CommandStack>(200), logger};

    // This will assert:
    ASSERT_NO_THROW(model.IsWon());
    ASSERT_FALSE(model.IsWon());
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
