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

#include <cxmodel/include/IConnectXGameActions.h>
#include <cxmodel/include/IConnectXGameInformation.h>
#include <cxmodel/include/IConnectXLimits.h>
#include <cxmodel/include/IVersioning.h>
#include <cxmodel/include/Subject.h>

#include "DisableStdStreamsRAII.h"
#include "LoggerMock.h"

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
    cxmodel::Subject& GetSubjectModel();
    cxmodel::IConnectXGameActions& GetGameActionsModel();
    cxmodel::IConnectXGameInformation& GetGameInformationModel();
    cxmodel::IConnectXLimits& GetLimitsModel();
    cxmodel::IVersioning& GetVersionningModel();

    std::string GetStdOutContents() const;
    std::string GetStdErrContents() const;


private:

    class ModelApplicationMock : public cxmodel::Subject,
                                 public cxmodel::IConnectXGameActions,
                                 public cxmodel::IConnectXGameInformation,
                                 public cxmodel::IConnectXLimits,
                                 public cxmodel::IVersioning
    {

    public:

        // IConnectXGameActions:
        void CreateNewGame(const cxmodel::NewGameInformation& p_gameInformation) override;
        void DropChip(const cxmodel::IChip& p_chip, size_t p_column) override;

        // IConnectXGameInformation:
        size_t GetCurrentGridHeight() const override {return 6u;}
        size_t GetCurrentGridWidth() const override {return 7u;};
        size_t GetCurrentInARowValue() const override {return 4u;};
        const cxmodel::Player& GetActivePlayer() const override {return m_ACTIVE_PLAYER;};
        const cxmodel::Player& GetNextPlayer() const override {return m_NEXT_PLAYER;};
        const cxmodel::IChip& GetChip(size_t p_row, size_t p_column) const override;
        bool IsWon() const override {throw std::logic_error("Not implemented!");};
        bool IsTie() const override {throw std::logic_error("Not implemented!");};

        // IConnectXLimits:
        size_t GetMinimumGridHeight() const override {return 7u;};
        size_t GetMinimumGridWidth() const override {return 6u;};
        size_t GetMinimumInARowValue() const override {return 3u;};
        size_t GetMaximumGridHeight() const override {return 64u;};
        size_t GetMaximumGridWidth() const override {return 7u;};
        size_t GetMaximumInARowValue() const override {return 8u;};
        size_t GetMinimumNumberOfPlayers() const override {return 2u;};
        size_t GetMaximumNumberOfPlayers() const override {return 10u;};

        // IVersionning:
        std::string GetName() const override {return "Connect X";};
        std::string GetVersionNumber() const override {return "v0.0";};

    private:

        const cxmodel::Player m_ACTIVE_PLAYER{"John Doe", cxmodel::MakeRed()};
        const cxmodel::Player m_NEXT_PLAYER{"Jane Doe", cxmodel::MakeBlue()};
    };

    LoggerMock m_logger;
    std::unique_ptr<ModelApplicationMock> m_model;
    DisableStdStreamsRAII m_disableStreamsRAII;
};

#endif // APPLICATIONTESTFIXTURE_H_91B6841E_7598_474B_BE68_991DB1816418
