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

#include <cxmodel/CommandStack.h>
#include <cxmodel/Disc.h>
#include <cxmodel/IObserver.h>
#include <cxmodel/Model.h>

#include "CommandStackMock.h"
#include "LoggerMock.h"
#include "ModelTestFixture.h"
#include "ModelTestHelpers.h"

TEST_F(ModelTestFixture, /*DISABLED*/_Update_ValidModel_CalledOnUndoChipDrop)
{
    CreateNewGame(6u, 7u, ModelTestFixture::NbPlayers::TWO, ModelTestFixture::InARowValue::FOUR);

    ModelNotificationCatcher undoDropChipObserver{cxmodel::ModelNotificationContext::UNDO_CHIP_DROPPED};
    GetModel().Attach(&undoDropChipObserver);

    DropChips(1u);
    ASSERT_FALSE(undoDropChipObserver.WasNotified());

    // When calling undo, the model should be notified and
    // forward the notification:
    GetModel().Undo();
    ASSERT_TRUE(undoDropChipObserver.WasNotified());
}

TEST_F(ModelTestFixture, /*DISABLED_*/Update_ValidModel_CalledOnRedoChipDrop)
{
    CreateNewGame(6u, 7u, ModelTestFixture::NbPlayers::TWO, ModelTestFixture::InARowValue::FOUR);

    ModelNotificationCatcher redoDropChipObserver{cxmodel::ModelNotificationContext::REDO_CHIP_DROPPED};
    GetModel().Attach(&redoDropChipObserver);

    // Drop a chip. This is an initial drop, so no "redo" notification occurs:
    DropChips(1u);
    ASSERT_FALSE(redoDropChipObserver.WasNotified());

    // The drop is undone: 
    GetModel().Undo();
    ASSERT_FALSE(redoDropChipObserver.WasNotified());

    // We redo the last undone chip dropped. This time, since the same drop
    // is performed again, a redo notification occurs:
    GetModel().Redo();
    ASSERT_TRUE(redoDropChipObserver.WasNotified());
}

TEST_F(ModelTestFixture, /*DISABLED_*/GetName_ValidModel_NameReturned)
{
    ASSERT_EQ(GetModel().GetName(), "Connect X");
}

TEST_F(ModelTestFixture, /*DISABLED_*/GetVersionNumber_ValidModel_ValidVersionNumberReturned)
{
    std::regex expected{"v(\\d)\\.(\\d)+"};

    ASSERT_TRUE(std::regex_match(GetModel().GetVersionNumber(), expected));
}

TEST_F(ModelTestFixture, /*DISABLED_*/GetMinimumGridHeight_ValidModel_ValueReturned)
{
    ASSERT_EQ(GetModel().GetMinimumGridHeight(), 6u);
}

TEST_F(ModelTestFixture, /*DISABLED_*/GetMinimumGridWidth_ValidModel_ValueReturned)
{
    LoggerMock logger;
    cxmodel::Model model{std::make_unique<cxmodel::CommandStack>(200), logger};

    ASSERT_EQ(GetModel().GetMinimumGridWidth(), 7u);
}

TEST_F(ModelTestFixture, /*DISABLED_*/GetMinimumInARowValue_ValidModel_ValueReturned)
{
    ASSERT_EQ(GetModel().GetMinimumInARowValue(), 3u);
}

TEST_F(ModelTestFixture, /*DISABLED_*/GetMaximumGridHeight_ValidModel_ValueReturned)
{
    ASSERT_EQ(GetModel().GetMaximumGridHeight(), 64u);
}

TEST_F(ModelTestFixture, /*DISABLED_*/GetMaximumGridWidth_ValidModel_ValueReturned)
{
    ASSERT_EQ(GetModel().GetMaximumGridWidth(), 64u);
}

TEST_F(ModelTestFixture, /*DISABLED_*/GetMaximumInARowValue_ValidModel_ValueReturned)
{
    ASSERT_EQ(GetModel().GetMaximumInARowValue(), 8u);
}

TEST_F(ModelTestFixture, /*DISABLED_*/GetMinimumNumberOfPlayers_ValidModel_ValueReturned)
{
    ASSERT_EQ(GetModel().GetMinimumNumberOfPlayers(), 2u);
}

TEST_F(ModelTestFixture, /*DISABLED_*/GetMaximumNumberOfPlayers_ValidModel_ValueReturned)
{
    ASSERT_EQ(GetModel().GetMaximumNumberOfPlayers(), 10u);
}

TEST_F(ModelTestFixture, /*DISABLED_*/CreateNewGame_ValidNewGameInformation_NewGameCreated)
{
    CreateNewGame(6u, 7u, ModelTestFixture::NbPlayers::TWO, ModelTestFixture::InARowValue::FOUR);

    const cxmodel::Player JOHN_DOE{"John Doe", cxmodel::MakeRed()};
    const cxmodel::Player JANE_DOE{"Mary Doe", cxmodel::MakeBlue()};

    ASSERT_EQ(GetModel().GetActivePlayer(), JOHN_DOE);
    ASSERT_EQ(GetModel().GetNextPlayer(), JANE_DOE);
    ASSERT_EQ(GetModel().GetCurrentGridWidth(), 7u);
    ASSERT_EQ(GetModel().GetCurrentGridHeight(), 6u);
    ASSERT_EQ(GetModel().GetCurrentInARowValue(), 4u);
}

TEST_F(ModelTestFixture, /*DISABLED_*/CreateNewGame_ValidNewGameInformation_CreateNewGameNotificationSent)
{
    ModelNotificationCatcher createNewGameObserver{cxmodel::ModelNotificationContext::CREATE_NEW_GAME};
    GetModel().Attach(&createNewGameObserver);

    ASSERT_FALSE(createNewGameObserver.WasNotified());
    CreateNewGame(6u, 7u, ModelTestFixture::NbPlayers::TWO, ModelTestFixture::InARowValue::FOUR);
    ASSERT_TRUE(createNewGameObserver.WasNotified());
}

TEST_F(ModelTestFixture, /*DISABLED_*/DropChip_ValidModelChipAndColumn_ChipDroppedNotificationSent)
{
    CreateNewGame(6u, 7u, ModelTestFixture::NbPlayers::TWO, ModelTestFixture::InARowValue::FOUR);

    // We then attach the model to our observer:
    ModelNotificationCatcher chipDropObserver{cxmodel::ModelNotificationContext::CHIP_DROPPED};
    GetModel().Attach(&chipDropObserver);

    // We drop a chip. It should trigger a notification since the board is empty:
    ASSERT_FALSE(chipDropObserver.WasNotified());
    DropChips(1u);
    ASSERT_TRUE(chipDropObserver.WasNotified());
}

TEST_F(ModelTestFixture, /*DISABLED_*/DropChip_ValidModelChipAndColumn_ChipDroppedOnFullColumnDropNotificationNotSent)
{
    CreateNewGame(6u, 7u, ModelTestFixture::NbPlayers::TWO, ModelTestFixture::InARowValue::FOUR);

    // We then attach the model to our observer:
    ModelNotificationCatcher chipDropObserverNotFull{cxmodel::ModelNotificationContext::CHIP_DROPPED};
    ModelNotificationCatcher chipDropObserverFull{cxmodel::ModelNotificationContext::CHIP_DROPPED};

    const int column = 0u;
    GetModel().DropChip(GetPlayer(0u).GetChip(), column);
    GetModel().DropChip(GetPlayer(1u).GetChip(), column);
    GetModel().DropChip(GetPlayer(0u).GetChip(), column);
    GetModel().DropChip(GetPlayer(1u).GetChip(), column);
    GetModel().DropChip(GetPlayer(0u).GetChip(), column);

    // At this point, a notification is sent, but it's the last one for this
    // column:
    GetModel().Attach(&chipDropObserverNotFull);
    GetModel().DropChip(GetPlayer(1u).GetChip(), column);
    ASSERT_TRUE(chipDropObserverNotFull.WasNotified());

    // No more notification:
    GetModel().Attach(&chipDropObserverFull);
    GetModel().DropChip(GetPlayer(0u).GetChip(), column);
    ASSERT_FALSE(chipDropObserverFull.WasNotified());

    // This drop is necessary only to make sure the test passes. If no notification
    // occurs on chipDropObserverFull, the test will fail:
    GetModel().DropChip(GetPlayer(0u).GetChip(), column + 1u);
}

TEST_F(ModelTestFixture, /*DISABLED_*/DropChip_ValidModelChipAndColumn_ChipDroppedOnFullColumnDropFailNotificationNotSent)
{
    CreateNewGame(6u, 7u, ModelTestFixture::NbPlayers::TWO, ModelTestFixture::InARowValue::FOUR);

    // We then attach the model to our observer:
    ModelNotificationCatcher chipDropObserverNotFull{cxmodel::ModelNotificationContext::CHIP_DROPPED_FAILED};

    const int column = 0u;
    GetModel().DropChip(GetPlayer(0u).GetChip(), column);
    GetModel().DropChip(GetPlayer(1u).GetChip(), column);
    GetModel().DropChip(GetPlayer(0u).GetChip(), column);
    GetModel().DropChip(GetPlayer(1u).GetChip(), column);
    GetModel().DropChip(GetPlayer(0u).GetChip(), column);

    // At this point, no notification is sent, but the column is now full:
    GetModel().Attach(&chipDropObserverNotFull);
    GetModel().DropChip(GetPlayer(1u).GetChip(), column);
    ASSERT_FALSE(chipDropObserverNotFull.WasNotified());

    // Now the failed notification is sent:
    GetModel().DropChip(GetPlayer(0u).GetChip(), column);
    ASSERT_TRUE(chipDropObserverNotFull.WasNotified());
}

TEST_F(ModelTestFixture, /*DISABLED_*/DropChip_ValidModelChipAndColumn_GameDataUpdated)
{
    CreateNewGame(6u, 7u, NbPlayers::TWO, InARowValue::FOUR);

    ASSERT_EQ(GetModel().GetActivePlayer(), cxmodel::Player("John Doe", cxmodel::MakeRed()));
    ASSERT_EQ(GetModel().GetNextPlayer(), cxmodel::Player("Mary Foo", cxmodel::MakeBlue()));

    // We drop a chip:
    DropChips(1u);

    ASSERT_EQ(GetModel().GetActivePlayer(), cxmodel::Player("Mary Foo", cxmodel::MakeBlue()));
    ASSERT_EQ(GetModel().GetNextPlayer(), cxmodel::Player("John Doe", cxmodel::MakeRed()));
}

TEST_F(ModelTestFixtureStdErrStreamRedirector, /*DISABLED_*/DropChip_ValidModelTwoSameChipsDropped_GameDataNotUpdated)
{
    CreateNewGame(6u, 7u, NbPlayers::TWO, InARowValue::FOUR);

    // We drop a chip:
    ASSERT_EQ(GetModel().GetActivePlayer(), cxmodel::Player("John Doe", cxmodel::MakeRed()));
    ASSERT_EQ(GetModel().GetNextPlayer(), cxmodel::Player("Mary Foo", cxmodel::MakeBlue()));

    const cxmodel::Disc RED_CHIP{cxmodel::MakeRed()};
    GetModel().DropChip(RED_CHIP, 0u);

    // This will assert:
    GetModel().DropChip(RED_CHIP, 0u);

    ASSERT_EQ(GetModel().GetActivePlayer(), cxmodel::Player("Jane Doe", cxmodel::MakeBlue()));
    ASSERT_EQ(GetModel().GetNextPlayer(), cxmodel::Player("John Doe", cxmodel::MakeRed()));
}

TEST_F(ModelTestFixture, /*DISABLED_*/DropChip_ValidModelGameIsWon_NotificationsHappen)
{
    ModelNotificationCatcher gameWonObserver{cxmodel::ModelNotificationContext::GAME_WON};

    GetModel().Attach(&gameWonObserver);
    CreateNewGame(6u, 7u, NbPlayers::TWO, InARowValue::FOUR);

    // We drop chips:
    const cxmodel::Disc RED_CHIP{cxmodel::MakeRed()};
    const cxmodel::Disc BLUE_CHIP{cxmodel::MakeBlue()};

    ASSERT_EQ(GetModel().GetActivePlayer(), cxmodel::Player("John Doe", cxmodel::MakeRed()));
    ASSERT_EQ(GetModel().GetNextPlayer(), cxmodel::Player("Mary Foo", cxmodel::MakeBlue()));

    DropChips(6u);

    // And the first player wins:
    ASSERT_FALSE(gameWonObserver.WasNotified());
    DropChips(1u);
    ASSERT_TRUE(gameWonObserver.WasNotified());
}

TEST_F(ModelTestFixture, /*DISABLED_*/DropChip_ValidModelGameIsWon_WinnerIsFirstPlayer)
{
    CreateNewGame(6u, 7u, NbPlayers::THREE, InARowValue::FOUR);

    const cxmodel::Player FIRST_PLAYER = GetPlayer(0u);
    const cxmodel::Player SECOND_PLAYER = GetPlayer(1u);

    ASSERT_EQ(GetModel().GetActivePlayer(), FIRST_PLAYER);
    ASSERT_EQ(GetModel().GetNextPlayer(), SECOND_PLAYER);

    // We drop chips, and the first player wins:
    DropChips(10u);

    ASSERT_EQ(FIRST_PLAYER, GetModel().GetActivePlayer());
}

TEST_F(ModelTestFixture, /*DISABLED_*/DropChip_ValidModelGameIsWon_WinnerIsMiddlePlayer)
{
    CreateNewGame(6u, 7u, NbPlayers::THREE, InARowValue::FOUR);

    // We drop chips:
    const cxmodel::Player& FIRST_PLAYER = GetPlayer(0u);
    const cxmodel::Player& SECOND_PLAYER = GetPlayer(1u);
    ASSERT_EQ(GetModel().GetActivePlayer(), FIRST_PLAYER);
    ASSERT_EQ(GetModel().GetNextPlayer(), SECOND_PLAYER);

    // DropChips...
    const cxmodel::IChip& FIRST_PLAYER_CHIP = FIRST_PLAYER.GetChip();
    const cxmodel::IChip& SECOND_PLAYER_CHIP = SECOND_PLAYER.GetChip();

    DropChips(9u);
    GetModel().DropChip(FIRST_PLAYER_CHIP, 4u);

    // And the second player wins:
    GetModel().DropChip(SECOND_PLAYER_CHIP, 1u);

    ASSERT_EQ(SECOND_PLAYER, GetModel().GetActivePlayer());
}

TEST_F(ModelTestFixture, /*DISABLED_*/DropChip_ValidModelGameIsWon_WinnerIsLastPlayer)
{
    CreateNewGame(6u, 7u, NbPlayers::THREE, InARowValue::FOUR);

    // We drop chips:
    const cxmodel::Player& FIRST_PLAYER = GetPlayer(0u);
    const cxmodel::Player& SECOND_PLAYER = GetPlayer(1u);
    const cxmodel::Player& THIRD_PLAYER = GetPlayer(2u);

    const cxmodel::IChip& FIRST_PLAYER_CHIP = FIRST_PLAYER.GetChip();
    const cxmodel::IChip& SECOND_PLAYER_CHIP = SECOND_PLAYER.GetChip();
    const cxmodel::IChip& THIRD_PLAYER_CHIP = THIRD_PLAYER.GetChip();

    ASSERT_EQ(GetModel().GetActivePlayer(), FIRST_PLAYER);
    ASSERT_EQ(GetModel().GetNextPlayer(), SECOND_PLAYER);

    DropChips(9u);
    GetModel().DropChip(FIRST_PLAYER_CHIP, 4u);
    GetModel().DropChip(SECOND_PLAYER_CHIP, 4u);

    // And the third player wins:
    GetModel().DropChip(THIRD_PLAYER_CHIP, 2u);

    ASSERT_EQ(THIRD_PLAYER, GetModel().GetActivePlayer());
}

TEST_F(ModelTestFixture, /*DISABLED_*/DropChip_ValidModelGameIsTied_NotificationsHappen)
{
    ModelNotificationCatcher gameTiedObserver{cxmodel::ModelNotificationContext::GAME_TIED};

    GetModel().Attach(&gameTiedObserver);
    CreateNewGame(6u, 7u, NbPlayers::TWO, InARowValue::FOUR);

    // We drop chips:
    const cxmodel::Disc RED_CHIP{cxmodel::MakeRed()};
    const cxmodel::Disc BLUE_CHIP{cxmodel::MakeBlue()};

    ASSERT_EQ(GetModel().GetActivePlayer(), cxmodel::Player("John Doe", cxmodel::MakeRed()));
    ASSERT_EQ(GetModel().GetNextPlayer(), cxmodel::Player("Mary Foo", cxmodel::MakeBlue()));

    GetModel().DropChip(RED_CHIP, 0u);
    GetModel().DropChip(BLUE_CHIP, 1u);

    GetModel().DropChip(RED_CHIP, 1u);
    GetModel().DropChip(BLUE_CHIP, 0u);

    GetModel().DropChip(RED_CHIP, 0u);
    GetModel().DropChip(BLUE_CHIP, 1u);

    GetModel().DropChip(RED_CHIP, 1u);
    GetModel().DropChip(BLUE_CHIP, 0u);

    GetModel().DropChip(RED_CHIP, 0u);
    GetModel().DropChip(BLUE_CHIP, 1u);

    GetModel().DropChip(RED_CHIP, 1u);
    GetModel().DropChip(BLUE_CHIP, 0u);

    GetModel().DropChip(RED_CHIP, 2u);
    GetModel().DropChip(BLUE_CHIP, 2u);

    GetModel().DropChip(RED_CHIP, 2u);
    GetModel().DropChip(BLUE_CHIP, 2u);

    GetModel().DropChip(RED_CHIP, 2u);
    GetModel().DropChip(BLUE_CHIP, 2u);

    GetModel().DropChip(RED_CHIP, 3u);
    GetModel().DropChip(BLUE_CHIP, 3u);

    GetModel().DropChip(RED_CHIP, 3u);
    GetModel().DropChip(BLUE_CHIP, 3u);

    GetModel().DropChip(RED_CHIP, 3u);
    GetModel().DropChip(BLUE_CHIP, 3u);

    GetModel().DropChip(RED_CHIP, 4u);
    GetModel().DropChip(BLUE_CHIP, 5u);

    GetModel().DropChip(RED_CHIP, 5u);
    GetModel().DropChip(BLUE_CHIP, 4u);

    GetModel().DropChip(RED_CHIP, 4u);
    GetModel().DropChip(BLUE_CHIP, 5u);

    GetModel().DropChip(RED_CHIP, 5u);
    GetModel().DropChip(BLUE_CHIP, 4u);

    GetModel().DropChip(RED_CHIP, 4u);
    GetModel().DropChip(BLUE_CHIP, 5u);

    ASSERT_FALSE(gameTiedObserver.WasNotified());
    GetModel().DropChip(RED_CHIP, 4u);
    ASSERT_TRUE(gameTiedObserver.WasNotified());
}

TEST_F(ModelTestFixture, /*DISABLED_*/MoveLeft_ValidModel_NotificationsSent)
{
    ModelNotificationCatcher gameEndedObserver{cxmodel::ModelNotificationContext::CHIP_MOVED_LEFT};
    
    CreateNewGame(6u, 7u, NbPlayers::TWO, InARowValue::FOUR);

    // We attach our observer:
    GetModel().Attach(&gameEndedObserver);

    ASSERT_FALSE(gameEndedObserver.WasNotified());
    GetModel().MoveLeft();
    ASSERT_TRUE(gameEndedObserver.WasNotified());
}

TEST_F(ModelTestFixture, /*DISABLED_*/MoveRight_ValidModel_NotificationsSent)
{
    ModelNotificationCatcher gameEndedObserver{cxmodel::ModelNotificationContext::CHIP_MOVED_RIGHT};
    
    CreateNewGame(6u, 7u, NbPlayers::TWO, InARowValue::FOUR);

    // We attach our observer:
    GetModel().Attach(&gameEndedObserver);

    ASSERT_FALSE(gameEndedObserver.WasNotified());
    GetModel().MoveRight();
    ASSERT_TRUE(gameEndedObserver.WasNotified());
}

TEST_F(ModelTestFixture, /*DISABLED_*/EndCurrentGame_ValidModel_NotificationsSent)
{
    ModelNotificationCatcher gameEndedObserver{cxmodel::ModelNotificationContext::GAME_ENDED};
    
    CreateNewGame(6u, 7u, NbPlayers::TWO, InARowValue::FOUR);

    // We attach our observer:
    GetModel().Attach(&gameEndedObserver);

    ASSERT_FALSE(gameEndedObserver.WasNotified());
    GetModel().EndCurrentGame();
    ASSERT_TRUE(gameEndedObserver.WasNotified());
}

TEST_F(ModelTestFixture, /*DISABLED_*/EndCurrentGame_ValidModel_CommandStackEmptied)
{
    CreateNewGame(6u, 7u, NbPlayers::TWO, InARowValue::FOUR);

    // We add a command to the stack:
    const cxmodel::Player firstPlayer = GetPlayer(0u);
    GetModel().DropChip(firstPlayer.GetChip(), 0u);
    ASSERT_FALSE(GetInternalCommandStack().IsEmpty());

    // And end the game:
    GetModel().EndCurrentGame();

    ASSERT_TRUE(GetInternalCommandStack().IsEmpty());
}

TEST_F(ModelTestFixtureStdErrStreamRedirector, /*DISABLED_*/EndCurrentGame_ValidModel_PlayersInfoReset)
{
    // We create a new game:
    CreateNewGame(6u, 7u, NbPlayers::TWO, InARowValue::FOUR);

    const cxmodel::Player ACTIVE = GetPlayer(0u);
    const cxmodel::Player NEXT = GetPlayer(1u);
    ASSERT_EQ(ACTIVE, GetModel().GetActivePlayer());
    ASSERT_EQ(NEXT, GetModel().GetNextPlayer());

    // And end it:
    GetModel().EndCurrentGame();

    const cxmodel::Player NO_ACTIVE_PLAYER{"Woops (active)!", {0, 0, 0, 0}};
    const cxmodel::Player NO_NEXT_PLAYER{"Woops! (next)", {0, 0, 0, 0}};

    // Will assert here...
    ASSERT_EQ(NO_ACTIVE_PLAYER, GetModel().GetActivePlayer());
    ASSERT_EQ(NO_NEXT_PLAYER, GetModel().GetNextPlayer());
}

TEST_F(ModelTestFixture, /*DISABLED_*/EndCurrentGame_ValidModel_InARowValueReset)
{
    CreateNewGame(6u, 7u, NbPlayers::TWO, InARowValue::FIVE);
    ASSERT_EQ(5u, GetModel().GetCurrentInARowValue());

    GetModel().EndCurrentGame();
    ASSERT_EQ(4u, GetModel().GetCurrentInARowValue());
}

TEST_F(ModelTestFixture, /*DISABLED_*/ReinitializeCurrentGame_ValidModel_NotificationHappens)
{
    ModelNotificationCatcher gameReinitializedObserver{cxmodel::ModelNotificationContext::GAME_REINITIALIZED};
    
    CreateNewGame(6u, 7u, NbPlayers::TWO, InARowValue::FOUR);

    // We attach our observer:
    GetModel().Attach(&gameReinitializedObserver);

    ASSERT_FALSE(gameReinitializedObserver.WasNotified());
    GetModel().ReinitializeCurrentGame();
    ASSERT_TRUE(gameReinitializedObserver.WasNotified());
}

TEST_F(ModelTestFixture, /*DISABLED_*/ReinitializeCurrentGame_ValidModel_CommandStackEmptied)
{
    CreateNewGame(6u, 7u, NbPlayers::TWO, InARowValue::FOUR);

    // We add a command to the stack:
    const cxmodel::Player firstPlayer = GetPlayer(0u);
    GetModel().DropChip(firstPlayer.GetChip(), 0u);
    ASSERT_FALSE(GetInternalCommandStack().IsEmpty());

    // And reinitialize the game:
    GetModel().ReinitializeCurrentGame();

    ASSERT_TRUE(GetInternalCommandStack().IsEmpty());
}

TEST_F(ModelTestFixture, /*DISABLED_*/ReinitializeCurrentGame_ValidModel_BoardReinitialized)
{
    CreateNewGame(6u, 7u, NbPlayers::TWO, InARowValue::FOUR);

    // We create valid new game information:
    const cxmodel::Player FIRST_PLAYER = GetPlayer(0u);
    const cxmodel::Player SECOND_PLAYER = GetPlayer(1u);
    ASSERT_EQ(GetModel().GetActivePlayer(), FIRST_PLAYER);
    ASSERT_EQ(GetModel().GetNextPlayer(), SECOND_PLAYER);

    // We drop chips:
    DropChips(2u);

    const cxmodel::IChip& FIRST_PLAYER_CHIP = FIRST_PLAYER.GetChip();
    const cxmodel::IChip& SECOND_PLAYER_CHIP = SECOND_PLAYER.GetChip();

    ASSERT_EQ(FIRST_PLAYER_CHIP.GetColor(), GetModel().GetChip(0u, 0u).GetColor());
    ASSERT_EQ(SECOND_PLAYER_CHIP.GetColor(), GetModel().GetChip(0u, 1u).GetColor());

    GetModel().ReinitializeCurrentGame();

    for(size_t row = 0u; row < GetModel().GetCurrentGridHeight(); ++row)
    {
        for(size_t column = 0u; column < GetModel().GetCurrentGridWidth(); ++column)
        {
            ASSERT_EQ(cxmodel::MakeTransparent(), GetModel().GetChip(row, column).GetColor());
        }
    }
}

TEST_F(ModelTestFixture, /*DISABLED_*/ReinitializeCurrentGame_ValidModel_PlayersReinitialized)
{
    CreateNewGame(6u, 7u, NbPlayers::TWO, InARowValue::FOUR);

    const cxmodel::Player FIRST_PLAYER = GetPlayer(0u);
    const cxmodel::Player SECOND_PLAYER = GetPlayer(1u);

    // DropChips...
    const cxmodel::IChip& FIRST_PLAYER_CHIP = FIRST_PLAYER.GetChip();
    GetModel().DropChip(FIRST_PLAYER_CHIP, 0u);

    ASSERT_EQ(GetModel().GetActivePlayer(), SECOND_PLAYER);
    ASSERT_EQ(GetModel().GetNextPlayer(), FIRST_PLAYER);

    GetModel().ReinitializeCurrentGame();

    ASSERT_EQ(GetModel().GetActivePlayer(), FIRST_PLAYER);
    ASSERT_EQ(GetModel().GetNextPlayer(), SECOND_PLAYER);
}

TEST_F(ModelTestFixture, /*DISABLED_*/ReinitializeCurrentGame_ValidModel_WinResolutionReinitialized)
{
    CreateNewGame(6u, 7u, NbPlayers::THREE, InARowValue::FOUR);

    const cxmodel::Player FIRST_PLAYER = GetPlayer(0u);
    const cxmodel::Player SECOND_PLAYER = GetPlayer(1u);
    ASSERT_EQ(GetModel().GetActivePlayer(), FIRST_PLAYER);
    ASSERT_EQ(GetModel().GetNextPlayer(), SECOND_PLAYER);

    DropChips(9u);

    // At this point, the first player could win by dropping a chip
    // at the first row. Instead, we reinitialize the game:
    GetModel().ReinitializeCurrentGame();

    // Then we play the "what could have been" the winning drop:
    DropChips(1u);

    // And we check if the game is resolved:
    ASSERT_FALSE(GetModel().IsWon());
}

TEST_F(ModelTestFixture, /*DISABLED_*/GetChip_ValidModel_ChipReturned)
{
    CreateNewGame(6u, 7u, NbPlayers::TWO, InARowValue::FOUR);

    // For now, no chip has been dropped, all returned chips should be transparent:
    const cxmodel::IChip& chipBefore = GetModel().GetChip(0u, 0u);
    ASSERT_EQ(chipBefore, cxmodel::Disc(cxmodel::MakeTransparent()));

    // We drop a chip:
    const cxmodel::Disc RED_CHIP{cxmodel::MakeRed()};
    GetModel().DropChip(RED_CHIP, 0u);

    // We now have a red chip at (0,0):
    const cxmodel::IChip& chipAfter = GetModel().GetChip(0u, 0u);
    ASSERT_EQ(chipAfter, cxmodel::Disc(cxmodel::MakeRed()));
}

TEST_F(ModelTestFixture, /*DISABLED_*/GetChip_InvalidRow_ReturnsNoDisc)
{
    CreateNewGame(6u, 7u, NbPlayers::TWO, InARowValue::FOUR);

    // For now, no chip has been dropped, all returned chips should be transparent:
    const cxmodel::IChip& chipBefore = GetModel().GetChip(GetModel().GetCurrentGridHeight(), 0u);
    ASSERT_EQ(chipBefore, cxmodel::Disc(cxmodel::MakeTransparent()));
}

TEST_F(ModelTestFixture, /*DISABLED_*/GetChip_InvalidColumn_ReturnsNoDisc)
{
    CreateNewGame(6u, 7u, NbPlayers::TWO, InARowValue::FOUR);

    // For now, no chip has been dropped, all returned chips should be transparent:
    const cxmodel::IChip& chipBefore = GetModel().GetChip(0u, GetModel().GetCurrentGridWidth());
    ASSERT_EQ(chipBefore, cxmodel::Disc(cxmodel::MakeTransparent()));
}

TEST_F(ModelTestFixtureStdErrStreamRedirector, /*DISABLED_*/IsWon_ValidModel_DoesNotThrow)
{
    // This will assert:
    ASSERT_NO_THROW(GetModel().IsWon());
    ASSERT_FALSE(GetModel().IsWon());
}

TEST_F(ModelTestFixtureStdErrStreamRedirector, /*DISABLED_*/IsTie_ValidModel_ThrowsForNow)
{
    // This will assert:
    ASSERT_NO_THROW(GetModel().IsTie());
    ASSERT_FALSE(GetModel().IsTie());
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

TEST_F(ModelTestFixture, /*DISABLED_*/Undo_CommandDropChip_PreviousStateRecovered)
{
    CreateNewGame(6u, 7u, NbPlayers::TWO, InARowValue::FOUR);

    // We record the initial state here:
    const std::string activePlayerName = GetModel().GetActivePlayer().GetName();
    const std::string nextPlayerName = GetModel().GetNextPlayer().GetName();
    const cxmodel::ChipColor colorAt00 = GetModel().GetChip(0u, 0u).GetColor();

    // We drop a chip at (0, 0) and check that the state has changed:
    DropChips(1u);
    const std::string activePlayerNameAfterDrop = GetModel().GetActivePlayer().GetName();
    ASSERT_FALSE(activePlayerName == activePlayerNameAfterDrop);

    const std::string nextPlayerNameAfterDrop = GetModel().GetNextPlayer().GetName();
    ASSERT_FALSE(nextPlayerName == nextPlayerNameAfterDrop);

    const cxmodel::ChipColor colorAt00AfterDrop = GetModel().GetChip(0u, 0u).GetColor();
    ASSERT_FALSE(colorAt00 == colorAt00AfterDrop);
    
    // We undo the drop and check that the previous state has been recovered:
    GetModel().Undo();
    const std::string activePlayerNameAfterUndo = GetModel().GetActivePlayer().GetName();
    ASSERT_TRUE(activePlayerName == activePlayerNameAfterUndo);

    const std::string nextPlayerNameAfterUndo = GetModel().GetNextPlayer().GetName();
    ASSERT_TRUE(nextPlayerName == nextPlayerNameAfterUndo);

    const cxmodel::ChipColor colorAt00AfterUndo = GetModel().GetChip(0u, 0u).GetColor();
    ASSERT_TRUE(colorAt00 == colorAt00AfterUndo);
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

TEST(Model, /*DISABLED_*/CanUndo_CmdStackCannotUndo_ReturnsFalse)
{
    std::unique_ptr<CommandStackMock> cmdStack = std::make_unique<CommandStackMock>();
    ASSERT_TRUE(cmdStack);

    CommandStackMock& cmdStackMock = *cmdStack;
    cmdStackMock.SetCanUndo(false);

    // We create a model:
    LoggerMock logger;
    cxmodel::Model model{std::move(cmdStack), logger};

    ASSERT_FALSE(model.CanUndo());
}

TEST(Model, /*DISABLED_*/CanUndo_CmdStackCanUndo_ReturnsTrue)
{
    std::unique_ptr<CommandStackMock> cmdStack = std::make_unique<CommandStackMock>();
    ASSERT_TRUE(cmdStack);

    CommandStackMock& cmdStackMock = *cmdStack;
    cmdStackMock.SetCanUndo(true);

    // We create a model:
    LoggerMock logger;
    cxmodel::Model model{std::move(cmdStack), logger};

    ASSERT_TRUE(model.CanUndo());
}

TEST(Model, /*DISABLED_*/CanRedo_CmdStackCannotRedo_ReturnsFalse)
{
    std::unique_ptr<CommandStackMock> cmdStack = std::make_unique<CommandStackMock>();
    ASSERT_TRUE(cmdStack);

    CommandStackMock& cmdStackMock = *cmdStack;
    cmdStackMock.SetCanRedo(false);

    // We create a model:
    LoggerMock logger;
    cxmodel::Model model{std::move(cmdStack), logger};

    ASSERT_FALSE(model.CanUndo());
}

TEST(Model, /*DISABLED_*/CanRedo_CmdStackCanRedo_ReturnsTrue)
{
    std::unique_ptr<CommandStackMock> cmdStack = std::make_unique<CommandStackMock>();
    ASSERT_TRUE(cmdStack);

    CommandStackMock& cmdStackMock = *cmdStack;
    cmdStackMock.SetCanRedo(true);

    // We create a model:
    LoggerMock logger;
    cxmodel::Model model{std::move(cmdStack), logger};

    ASSERT_TRUE(model.CanRedo());
}

TEST_F(ModelTestFixture, /*DISABLED_*/SetVerbosityLevel_FromNoneToDebug_VerbosityLevelSet)
{
    // Set verbosity level to none:
    GetModel().SetVerbosityLevel(cxlog::VerbosityLevel::NONE);
    ASSERT_EQ(GetModel().GetVerbosityLevel(), cxlog::VerbosityLevel::NONE);

    // We change it to debug and check it has an impact:
    GetModel().SetVerbosityLevel(cxlog::VerbosityLevel::DEBUG);
    ASSERT_EQ(GetModel().GetVerbosityLevel(), cxlog::VerbosityLevel::DEBUG);
}
