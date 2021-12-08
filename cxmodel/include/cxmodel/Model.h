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
 * @file Model.h
 * @date 2019
 *
 *************************************************************************************************/

#ifndef MODEL_H_8CC20E7E_7466_4977_9435_7E09ADBD10FC
#define MODEL_H_8CC20E7E_7466_4977_9435_7E09ADBD10FC

#include <string>
#include <memory>

#include <cxlog/ILogger.h>

#include "IBoard.h"
#include "ICommandStack.h"
#include "IConnectXGameActions.h"
#include "IConnectXGameInformation.h"
#include "IConnectXLimits.h"
#include "IGameResolutionStrategy.h"
#include "IUndoRedo.h"
#include "IVersioning.h"
#include "ModelNotificationContext.h"
#include "PlayerInformation.h"

namespace cxmodel
{

/*********************************************************************************************//**
 * @brief Connect X model.
 *
 * @invariant The command stack is valid.
 *
 * This class holds the Connect X related business rules.
 *
 ************************************************************************************************/
class Model : public cxlog::ILogger,
              public ModelSubject,
              public IModelObserver,
              public IVersioning,
              public IUndoRedo,
              public IConnectXLimits,
              public IConnectXGameInformation,
              public IConnectXGameActions
{

public:

    /******************************************************************************************//**
     * @brief Constructor.
     *
     * @pre p_cmdStack is valid.
     * @pre p_cmdStack is empty.
     *
     * @param p_cmdStack The command stack.
     *
     ********************************************************************************************/
    Model(std::unique_ptr<ICommandStack>&& p_cmdStack, cxlog::ILogger& p_logger);
    ~Model() override;

///@{ @name cxlog::ILogger

    void Log(const cxlog::VerbosityLevel p_verbosityLevel, const std::string& p_fileName, const std::string& p_functionName, const size_t p_lineNumber, const std::string& p_message) override;
    void SetVerbosityLevel(const cxlog::VerbosityLevel p_verbosityLevel) override;
    cxlog::VerbosityLevel GetVerbosityLevel() const override;

///@}

///@{ @name IObserver

    void Update(ModelNotificationContext p_context, ModelSubject* p_subject) override;

///@}

///@{ @name IVersioning

    std::string GetName() const override;
    std::string GetVersionNumber() const override;

///@}

///@{ @name IUndoRedo

    void Undo() override;
    void Redo() override;
    bool CanUndo() const override;
    bool CanRedo() const override;

///@}

///@{ @name IConnectXLimits

    size_t GetMinimumGridHeight() const override;
    size_t GetMinimumGridWidth() const override;
    size_t GetMinimumInARowValue() const override;
    size_t GetMaximumGridHeight() const override;
    size_t GetMaximumGridWidth() const override;
    size_t GetMaximumInARowValue() const override;
    size_t GetMinimumNumberOfPlayers() const override;
    size_t GetMaximumNumberOfPlayers() const override;

///@}

///@{ @name IConnectXGameInformation

    size_t GetCurrentGridHeight() const override;
    size_t GetCurrentGridWidth() const override;
    size_t GetCurrentInARowValue() const override;
    const Player& GetActivePlayer() const override;
    const Player& GetNextPlayer() const override;
    const IChip& GetChip(size_t p_row, size_t p_column) const override;
    bool IsWon() const override;
    bool IsTie() const override;

///@}

///@{ @name IConnectXGameActions

    void CreateNewGame(const NewGameInformation& p_gameInformation) override;
    void DropChip(const cxmodel::IChip& p_chip, size_t p_column) override;
    void MoveLeft() override;
    void MoveRight() override;
    void EndCurrentGame() override;
    void ReinitializeCurrentGame() override;

///@}

private:

    void CheckInvariants();

    std::unique_ptr<ICommandStack> m_cmdStack;
    cxlog::ILogger& m_logger;

    std::unique_ptr<cxmodel::IBoard> m_board;
    PlayerInformation m_playersInfo;
    size_t m_inARowValue;
    std::vector<IBoard::Position> m_takenPositions;

    std::unique_ptr<IGameResolutionStrategy> m_winResolutionStrategy;
    std::unique_ptr<IGameResolutionStrategy> m_tieResolutionStrategy;
};

} // namespace cxmodel

#endif // MODEL_H_8CC20E7E_7466_4977_9435_7E09ADBD10FC
