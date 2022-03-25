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
 * @file CommandCreateNewGame.h
 * @date 2020
 *
 *************************************************************************************************/

#ifndef COMMANDCREATENEWGAME_H_42E0AF3C_C0D0_44F7_B472_9F2E0E11216D
#define COMMANDCREATENEWGAME_H_42E0AF3C_C0D0_44F7_B472_9F2E0E11216D

#include <vector>

#include <cxlog/ILogger.h>
#include <cxmodel/IBoard.h>
#include <cxmodel/ICommand.h>
#include <cxmodel/NewGameInformation.h>
#include <cxmodel/IPlayer.h>

namespace cxmodel
{
    class IConnectXLimits;
}

namespace cxmodel
{

class CommandCreateNewGame : public ICommand
{

public:

    /******************************************************************************************//**
     * @brief Constructor.
     *
     * @param p_modelAsLimits       A Connect X compliant model (limits).
     * @param p_board               The model's game board.
     * @param p_players             The model's list of players.
     * @param p_inARowValue         The model's in-a-row value.
     * @param p_newGameInformation  The new game information from which to initialize a game.
     *
     ********************************************************************************************/
    CommandCreateNewGame(const IConnectXLimits& p_modelAsLimits,
                         std::unique_ptr<IBoard>& p_board,
                         std::vector<std::shared_ptr<IPlayer>>& p_players,
                         size_t& p_inARowValue,
                         NewGameInformation p_newGameInformation);

    virtual void Execute() override;
    virtual void Undo() override;

private:

    const IConnectXLimits& m_modelAsLimits;

    std::unique_ptr<IBoard>& m_board;
    std::vector<std::shared_ptr<IPlayer>>& m_modelPlayers;
    size_t& m_inARowValue;

    NewGameInformation m_newGameInformation;

};

} // namespace cxmodel

#endif // COMMANDCREATENEWGAME_H_42E0AF3C_C0D0_44F7_B472_9F2E0E11216D
