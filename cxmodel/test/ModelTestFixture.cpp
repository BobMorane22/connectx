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
 * @file ModelTestFixture.cpp
 * @date 2020
 *
 *************************************************************************************************/

#include <array>
#include <type_traits>

#include "LoggerMock.h"
#include "ModelTestFixture.h"

namespace
{

constexpr char FIRST_PLAYER_NAME[] = "John Doe";
constexpr cxmodel::ChipColor FIRST_PLAYER_CHIP_COLOR = cxmodel::MakeRed();

constexpr char SECOND_PLAYER_NAME[] = "Mary Foo";
constexpr cxmodel::ChipColor SECOND_PLAYER_CHIP_COLOR = cxmodel::MakeBlue();

constexpr char THIRD_PLAYER_NAME[] = "Donald Foo-Bar";
constexpr cxmodel::ChipColor THIRD_PLAYER_CHIP_COLOR = cxmodel::MakeYellow();

std::array<std::shared_ptr<cxmodel::IPlayer>, 3u> PLAYERS
{
    cxmodel::CreatePlayer(FIRST_PLAYER_NAME, FIRST_PLAYER_CHIP_COLOR, cxmodel::PlayerType::HUMAN),
    cxmodel::CreatePlayer(SECOND_PLAYER_NAME, SECOND_PLAYER_CHIP_COLOR, cxmodel::PlayerType::HUMAN),
    cxmodel::CreatePlayer(THIRD_PLAYER_NAME, THIRD_PLAYER_CHIP_COLOR, cxmodel::PlayerType::HUMAN),
};

// Gets the underlying enum value:
template<typename T>
size_t GetUnderlyingValue(T p_enumValue)
{
    static_assert(std::is_same_v<std::underlying_type_t<T>, size_t>);

    return static_cast<size_t>(p_enumValue);
}

} // namespace

ModelTestFixture::ModelTestFixture()
: m_nbOfPlayersInCurrentGame{0u}
{
    m_logger = std::make_unique<LoggerMock>();
    EXPECT_TRUE(m_logger);

    // We create a command stack unique pointer to be moved later,
    // but we keep a reference on its managed command stack, in case
    // we need to access it for a test later:
    auto commandStack = std::make_unique<cxmodel::CommandStack>(200);
    EXPECT_TRUE(commandStack);
    m_commandStack = commandStack.get();
    EXPECT_TRUE(m_commandStack);
    
    m_model = std::make_unique<cxmodel::Model>(std::move(commandStack), *m_logger);
    EXPECT_TRUE(m_model);
}

ModelTestFixture::~ModelTestFixture() = default;

cxmodel::Model& ModelTestFixture::GetModel()
{
    EXPECT_TRUE(m_model);
    return *m_model;
}

cxmodel::ICommandStack& ModelTestFixture::GetInternalCommandStack()
{
    EXPECT_TRUE(m_commandStack);
    return *m_commandStack;
}

void ModelTestFixture::CreateNewGame(size_t p_boardHeight,
                                     size_t p_boardWidth,
                                     ModelTestFixture::NbPlayers p_nbPlayers,
                                     ModelTestFixture::InARowValue p_inARowValue)
{
    EXPECT_TRUE(m_model);

    EXPECT_TRUE(p_boardHeight >= m_model->GetMinimumGridHeight());
    EXPECT_TRUE(p_boardHeight <= m_model->GetMaximumGridHeight());

    EXPECT_TRUE(p_boardWidth >= m_model->GetMinimumGridWidth());
    EXPECT_TRUE(p_boardWidth <= m_model->GetMaximumGridWidth());

    const size_t nbOfPlayers = GetUnderlyingValue(p_nbPlayers);
    EXPECT_TRUE(nbOfPlayers >= m_model->GetMinimumNumberOfPlayers());
    EXPECT_TRUE(nbOfPlayers <= m_model->GetMaximumNumberOfPlayers());
    m_nbOfPlayersInCurrentGame = nbOfPlayers;

    const size_t inARow = GetUnderlyingValue(p_inARowValue);
    EXPECT_TRUE(inARow >= m_model->GetMinimumInARowValue());
    EXPECT_TRUE(inARow <= m_model->GetMaximumInARowValue());

    cxmodel::NewGameInformation newGameInfo;
    newGameInfo.m_gridWidth = p_boardWidth;
    newGameInfo.m_gridHeight = p_boardHeight;
    newGameInfo.m_inARowValue = inARow;

    EXPECT_TRUE(nbOfPlayers <= PLAYERS.size());
    for(size_t index = 0u; index < nbOfPlayers; ++index)
    {
        newGameInfo.m_players.push_back(PLAYERS[index]);
    }

    // We create a new game:
    m_model->CreateNewGame(std::move(newGameInfo));
}

const cxmodel::IPlayer& ModelTestFixture::GetPlayer(size_t p_playerIndex) const
{
    try
    {
        return *PLAYERS.at(p_playerIndex);
    }
    catch(...)
    {
        EXPECT_TRUE(false);
        return *PLAYERS.at(0u);
    }
}

void ModelTestFixture::DropChips(size_t p_nbOfDrops)
{
    EXPECT_TRUE(p_nbOfDrops > 0u);
    EXPECT_TRUE(p_nbOfDrops <= m_model->GetCurrentGridHeight() * m_model->GetCurrentGridWidth());
    EXPECT_TRUE(m_nbOfPlayersInCurrentGame >= 2u);
    EXPECT_TRUE(m_nbOfPlayersInCurrentGame <= PLAYERS.size());

    for(size_t index = 0u; index < p_nbOfDrops; ++index)
    {
        const size_t column = index % m_nbOfPlayersInCurrentGame;
        m_model->DropChip(PLAYERS[column]->GetChip(), column);
    }
}
