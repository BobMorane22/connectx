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
 * @file ModelTestFixture.h
 * @date 2020
 *
 *************************************************************************************************/

#ifndef MODELTESTFIXTURE_H_6497DE9C_2D19_4A9D_92AF_C48DBD06DF40
#define MODELTESTFIXTURE_H_6497DE9C_2D19_4A9D_92AF_C48DBD06DF40

#include <gtest/gtest.h>

#include <cxunit/include/StdStreamRedirector.h>
#include <cxlog/include/ILogger.h>

#include <CommandStack.h>
#include <Model.h>

/*********************************************************************************************//**
 * @brief Fixture for the cxmodel::Model class.
 *
 * The cxmodel::Model class is a critical piece of Connect X. It has a lot of dependencies and
 * a lot of repetitive code has to be written for a lot of tests. This fixture aims at removing
 * from the tester the burden of writing all this code. Mostly, the fixture provides services
 * to:
 *     - create and assemble dependencies to form a valid model;
 *     - handle the creation of a game;
 *     - handle the winning of a game;
 *     - etc.
 *
 ************************************************************************************************/
class ModelTestFixture : public ::testing::Test
{

public:

    /*****************************************************************************************//**
     * @brief Number of players for a game.
     *
     * Provides a readable way to parametrize the number of players in a game.
     *
     *********************************************************************************************/
    enum class NbPlayers : size_t
    {
        TWO = 2u,
        THREE
    };

    /*****************************************************************************************//**
     * @brief In-a-row value for a game.
     *
     * Provides a readable way to parametrize the in-a-row value in a game.
     *
     *********************************************************************************************/
    enum class InARowValue : size_t
    {
        THREE = 3u,
        FOUR,
        FIVE,
        SIX,
        SEVEN
    };

    /******************************************************************************************//**
     * @brief Constructor.
     *
     * @return A valid model.
     *
     * Creates a valid model with the following parameters:
     *
     *     - A command stack with a 200 commands capacity.
     *     - A fake logger (which logs nothing).
     *
     ********************************************************************************************/
    ModelTestFixture();

    /******************************************************************************************//**
     * @brief Destructor.
     *
     ********************************************************************************************/
    ~ModelTestFixture();

    /******************************************************************************************//**
     * @brief Access the configured model.
     *
     * @return The configured model.
     *
     ********************************************************************************************/
    cxmodel::Model& GetModel();

    /******************************************************************************************//**
     * @brief Access the configured model's internal command stack.
     *
     * @return The configured model's internal command stack.
     *
     ********************************************************************************************/
    cxmodel::ICommandStack& GetInternalCommandStack();

    /******************************************************************************************//**
     * @brief Creates a valid new game.
     *
     * @pre The board's dimensions must respect the model's limits.
     *
     * @param p_boardHeight  The new game's board height.
     * @param p_boardWidth   The new game's board width.
     * @param p_nbPlayers    The new game's number of players.
     * @param p_inARowValue  The new game's in-a-row value.
     *
     * Creates a new game with the specified parameters. Note that some parameters, such as player
     * names and chip colors are fixed (they cannot be specified). If more flexibility is needed,
     * one should not use this fixture and create a game directly. Here is what to expect about
     * these fixed parameters:
     *
     *     | Player | Name           | Chip color |
     *     | ------ | -------------- | ---------- |
     *     | 1      | John Doe       | Red        |
     *     | 2      | Mary Foo       | Blue       |
     *     | 3      | Donald Foo-Bar | Yellow     |
     *
     * Also note that when this method is called and the model limits are respected, the
     * ModelNotificationContext::CREATE_NEW_GAME is emitted.
     *
     ********************************************************************************************/
    void CreateNewGame(size_t p_boardHeight,
                       size_t p_boardWidth,
                       NbPlayers p_nbPlayers,
                       InARowValue p_inARowValue);

    /******************************************************************************************//**
     * @brief Get the player at the specific index.
     *
     * @pre The player index is valid.
     *
     * @param p_playerIndex The player index.
     *
     * @return The player at the specified index.
     *
     ********************************************************************************************/
    const cxmodel::Player& GetPlayer(size_t p_playerIndex) const;

    /******************************************************************************************//**
     * @brief Drops the specified number of chips in alternate rows.
     *
     * @pre A game has previously been created.
     * @pre The specified number of drops respects the model's limits.
     *
     * @param p_nbOfDrops The number of chip drops to perform.
     *
     * Performs the speficied number of chip drops in alternate rows. Each player is assigned a
     * different row, so that each drop fills the active player's assigned row. For example, in
     * a three player game, passing the value '5' to this function on a classic Connect 4 board
     * would yield the following configuration:
     *
     *
     *     |   |   |   |   |   |   |   |
     *     |   |   |   |   |   |   |   |
     *     |   |   |   |   |   |   |   |
     *     |   |   |   |   |   |   |   |
     *     | R | B |   |   |   |   |   |
     *     | R | B | Y |   |   |   |   |
     *
     * Where R = 'Red', B = 'Blue' and Y = 'Yellow. In this example, the last dropped chip would
     * be the blue chip on top.
     *
     ********************************************************************************************/
    void DropChips(size_t p_nbOfDrops);

private:

    std::unique_ptr<cxlog::ILogger> m_logger;
    cxmodel::CommandStack* m_commandStack;

    std::unique_ptr<cxmodel::Model> m_model;
    size_t m_nbOfPlayersInCurrentGame;

};

ADD_STREAM_REDIRECTORS(ModelTestFixture);

#endif // MODELTESTFIXTURE_H_6497DE9C_2D19_4A9D_92AF_C48DBD06DF40
