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
 * @file ApplicationTestFixture.h
 * @date 2019
 *
 *************************************************************************************************/

#ifndef APPLICATIONTESTFIXTURE_H_91B6841E_7598_474B_BE68_991DB1816418
#define APPLICATIONTESTFIXTURE_H_91B6841E_7598_474B_BE68_991DB1816418

#include <gtest/gtest.h>

#include <cxunit/StdStreamRedirector.h>

#include <cxmodel/IConnectXGameActions.h>
#include <cxmodel/IConnectXGameInformation.h>
#include <cxmodel/IConnectXLimits.h>
#include <cxmodel/IUndoRedo.h>
#include <cxmodel/IVersioning.h>

#include <cxmodel/ModelNotificationContext.h>
#include <cxexec/ModelReferences.h>

#include "LoggerMock.h"

namespace cxmodel
{
    enum class DropColumnComputation;
}

/*********************************************************************************************//**
 * @brief Test fixture for the class @c cx::Application
 *
 * This fixture guarantees correct disabling/enabling of the standard streams through RAII.
 *
 ************************************************************************************************/
class ApplicationTestFixture : public ::testing::Test
{
public:

    ApplicationTestFixture();

    cxlog::ILogger& GetLogger();

    cxmodel::ModelSubject& GetSubjectModel();
    cxmodel::IConnectXGameActions& GetGameActionsModel();
    cxmodel::IConnectXGameInformation& GetGameInformationModel();
    cxmodel::IConnectXLimits& GetLimitsModel();
    cxmodel::IUndoRedo& GetUndoRedoModel();
    cxmodel::IVersioning& GetVersionningModel();

    cx::ModelReferences GetModelReferences();

private:

    class ModelApplicationMock : public cxmodel::ModelSubject,
                                 public cxmodel::IConnectXGameActions,
                                 public cxmodel::IConnectXGameInformation,
                                 public cxmodel::IConnectXLimits,
                                 public cxmodel::IUndoRedo,
                                 public cxmodel::IVersioning,
                                 public cxmodel::IConnectXAI
    {

    public:

        // IConnectXGameActions:
        void CreateNewGame(cxmodel::NewGameInformation p_gameInformation) override;
        void DropChip(const cxmodel::IChip& p_chip, size_t p_column) override;
        void MoveLeftOneColumn() override;
        void MoveRightOneColumn() override;
        void EndCurrentGame() override;
        void ReinitializeCurrentGame() override;

        // IConnectXGameInformation:
        size_t GetCurrentGridHeight() const override {return 6u;}
        size_t GetCurrentGridWidth() const override {return 7u;}
        size_t GetCurrentInARowValue() const override {return 4u;}
        const cxmodel::IPlayer& GetActivePlayer() const override {return *m_ACTIVE_PLAYER;}
        const cxmodel::IPlayer& GetNextPlayer() const override {return *m_NEXT_PLAYER;}
        const cxmodel::IChip& GetChip(size_t p_row, size_t p_column) const override;
        bool IsWon() const override {throw std::logic_error("Not implemented!");}
        bool IsTie() const override {throw std::logic_error("Not implemented!");}

        // IConnectXLimits:
        size_t GetMinimumGridHeight() const override {return 7u;}
        size_t GetMinimumGridWidth() const override {return 6u;}
        size_t GetMinimumInARowValue() const override {return 3u;}
        size_t GetMaximumGridHeight() const override {return 64u;}
        size_t GetMaximumGridWidth() const override {return 7u;}
        size_t GetMaximumInARowValue() const override {return 8u;}
        size_t GetMinimumNumberOfPlayers() const override {return 2u;}
        size_t GetMaximumNumberOfPlayers() const override {return 10u;}

        // IUndoRedo:
        void Undo() override {}
        void Redo() override {}
        bool CanUndo() const override {return true;}
        bool CanRedo() const override {return true;}

        // IVersionning:
        std::string GetName() const override {return "Connect X";}
        std::string GetVersionNumber() const override {return "v0.0";}

        // IConnectXAI:
        void ComputeNextDropColumn(cxmodel::DropColumnComputation /*p_algorithm*/) override {}
        [[nodiscard]] size_t GetCurrentBotTarget() const override {return 5u;};


    private:

        const std::unique_ptr<cxmodel::IPlayer> m_ACTIVE_PLAYER = cxmodel::CreatePlayer("John Doe", cxmodel::MakeRed(), cxmodel::PlayerType::HUMAN);
        const std::unique_ptr<cxmodel::IPlayer> m_NEXT_PLAYER = cxmodel::CreatePlayer("Jane Doe", cxmodel::MakeBlue(), cxmodel::PlayerType::HUMAN);
    };

    LoggerMock m_logger;
    std::unique_ptr<ModelApplicationMock> m_model;
};

ADD_STREAM_REDIRECTORS(ApplicationTestFixture);

#endif // APPLICATIONTESTFIXTURE_H_91B6841E_7598_474B_BE68_991DB1816418
