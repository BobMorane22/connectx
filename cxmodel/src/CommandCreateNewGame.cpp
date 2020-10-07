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
 * @file CommandCreateNewGame.cpp
 * @date 2020
 *
 *************************************************************************************************/

#include <memory>
#include <sstream>

#include <cxinv/include/assertion.h>

#include <Board.h>
#include <CommandCreateNewGame.h>

cxmodel::CommandCreateNewGame::CommandCreateNewGame(const IConnectXLimits& p_modelAsLimits,
                                                    std::unique_ptr<IBoard>& p_board,
                                                    std::vector<Player>& p_players,
                                                    size_t& p_inARowValue,
                                                    NewGameInformation p_newGameInformation)
 : m_modelAsLimits{p_modelAsLimits}
 , m_board{p_board}
 , m_modelPlayers{p_players}
 , m_inARowValue{p_inARowValue}
 , m_newGameInformation{p_newGameInformation}
{
    // Nothing to do...
}

void cxmodel::CommandCreateNewGame::Execute()
{
    // Players:
    m_modelPlayers.clear();
    ASSERT(m_newGameInformation.GetNbOfNewPlayers() >= 2);
    const auto& players = m_newGameInformation.GetNewPlayers();
    std::copy(players.cbegin(), players.cend(), std::back_inserter(m_modelPlayers));

    // Board:
    m_board = std::make_unique<cxmodel::Board>(m_newGameInformation.m_gridHeight, m_newGameInformation.m_gridWidth, m_modelAsLimits);

    // In-a-row value:
    m_inARowValue = m_newGameInformation.m_inARowValue;
}

void cxmodel::CommandCreateNewGame::Undo()
{
    // Nothing to do...
}
