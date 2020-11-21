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

TEST(Model, /*DISABLED_*/CreateNewGame_ValidNewGameInformation_CreateNewGameNotificationSent)
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

TEST(Model, /*DISABLED_*/DropChip_ValidModelChipAndColumn_ChipDroppedNotificationSent)
{
    // We create an observer specific to the CHIP_DROPPED notification context:
    class SignalObserver : public cxmodel::IObserver
    {
        void Update(cxmodel::NotificationContext p_context, cxmodel::Subject* p_subject) override
        {
            ASSERT_TRUE(p_subject);
            ASSERT_TRUE(p_context == cxmodel::NotificationContext::CHIP_DROPPED);
        }
    };

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
    SignalObserver observer;
    model.Attach(&observer);

    // We drop a chip. It should trigger a notification since the board is empty:
    const cxmodel::Disc RED_CHIP{cxmodel::MakeRed()};
    model.DropChip(RED_CHIP, 0u);
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
    model.DropChip(RED_CHIP, 0u);

    ASSERT_EQ(model.GetActivePlayer(), cxmodel::Player("Jane Doe", cxmodel::MakeBlue()));
    ASSERT_EQ(model.GetNextPlayer(), cxmodel::Player("John Doe", cxmodel::MakeRed()));
}

TEST(Model, /*DISABLED_*/DropChip_ValidModelGameIsWon_NotificationsHappen)
{
    // We create an observer specific to the CHIP_DROPPED notification context:
    class DropChipObserver : public cxmodel::IObserver
    {

    private:

        bool m_wasNotified = false;

        void Update(cxmodel::NotificationContext p_context, cxmodel::Subject* p_subject) override
        {
            ASSERT_TRUE(p_subject);

            if(p_context == cxmodel::NotificationContext::CHIP_DROPPED)
            {
                m_wasNotified = true;
            }
        }

    public:

        bool WasNotified() const {return m_wasNotified;}

    };

    // We create an observer specific to the GAME_WON notification context:
    class GameWonObserver : public cxmodel::IObserver
    {

    private:

        bool m_wasNotified = false;

        void Update(cxmodel::NotificationContext p_context, cxmodel::Subject* p_subject) override
        {
            ASSERT_TRUE(p_subject);

            if(p_context == cxmodel::NotificationContext::GAME_WON)
            {
                m_wasNotified = true;
            }
        }

    public:

        bool WasNotified() const {return m_wasNotified;}

    };

    // We create a model:
    LoggerMock logger;
    cxmodel::Model model{std::make_unique<cxmodel::CommandStack>(200), logger};

    // We attach our observers to it:
    DropChipObserver dropChipObserver;
    GameWonObserver gameWonObserver;

    ASSERT_FALSE(dropChipObserver.WasNotified());
    ASSERT_FALSE(gameWonObserver.WasNotified());

    model.Attach(&dropChipObserver);
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
    model.DropChip(RED_CHIP, 0u);

    // Finally, we check our observers:
    ASSERT_TRUE(dropChipObserver.WasNotified());
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
    // We create an observer specific to the END_GAME notification context:
    class EndGameObserver : public cxmodel::IObserver
    {
        void Update(cxmodel::NotificationContext p_context, cxmodel::Subject* p_subject) override
        {
            ASSERT_TRUE(p_subject);
            ASSERT_TRUE(p_context == cxmodel::NotificationContext::GAME_ENDED);
        }
    };
    
    // We create a model:
    LoggerMock logger;
    cxmodel::Model model{std::make_unique<cxmodel::CommandStack>(200), logger};

    model.EndCurrentGame();
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
    LoggerMock logger;
    cxmodel::Model model{std::make_unique<cxmodel::CommandStack>(200), logger};

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
