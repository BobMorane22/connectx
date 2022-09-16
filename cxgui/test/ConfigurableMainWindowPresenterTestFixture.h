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
 * @file ConfigurableMainWindowPresenterTestFixture.h
 * @date 2021
 *
 *************************************************************************************************/

#ifndef CONFIGURABLEMAINWINDOWPRESENTERTESTFIXTURE_H_90BB4F4D_5BA9_4C29_8CF0_C4E131AC80A3
#define CONFIGURABLEMAINWINDOWPRESENTERTESTFIXTURE_H_90BB4F4D_5BA9_4C29_8CF0_C4E131AC80A3

#include <gtest/gtest.h>

#include <cxunit/NotImplementedException.h>
#include <cxmodel/IConnectXAI.h>
#include <cxmodel/IConnectXGameInformation.h>
#include <cxmodel/IConnectXLimits.h>
#include <cxmodel/IUndoRedo.h>
#include <cxgui/IMainWindowPresenter.h>

/*********************************************************************************************//**
 * @brief Configurable `MainWindowPresenter` test fixture.
 *
 * This fixture allows the configuring of different models to meet the needs of some unit tests.
 * This fixture should only be used when really needed, to avoid unnecessary mocks.
 *
 ************************************************************************************************/
class ConfigurableMainWindowPresenterTestFixture : public ::testing::Test
{

public:

    /******************************************************************************************//**
     * @brief Constructor.
     *
     * Constructs a basic fixture. Not all model methods are implemented.
     *
     ********************************************************************************************/
    ConfigurableMainWindowPresenterTestFixture();

    /******************************************************************************************//**
     * @brief Retreive the underlying presenter.
     *
     * @return The presenter.
     *
     ********************************************************************************************/
    cxgui::IMainWindowPresenter& GetPresenter();

    /******************************************************************************************//**
     * @brief Sets a new `IConnectXGameInformation` compatible model.
     *
     * @param p_model A `IConnectXGameInformation` compatible model.
     *
     * @warning When this method is called, the presenter's state is reset to its initial state.
     *
     ********************************************************************************************/
    void SetGameInformationModel(std::unique_ptr<cxmodel::IConnectXGameInformation>&& p_model);

    /******************************************************************************************//**
     * @brief Sets a new `IConnectXLimits` compatible model.
     *
     * @param p_model A `IConnectXLimits` compatible model.
     *
     * @warning When this method is called, the presenter's state is reset to its initial state.
     *
     ********************************************************************************************/
    void SetLimitsModel(std::unique_ptr<cxmodel::IConnectXLimits>&& p_model);

    /******************************************************************************************//**
     * @brief Sets a new `IUndoRedo` compatible model.
     *
     * @param p_model A `IUndoRedo` compatible model.
     *
     * @warning When this method is called, the presenter's state is reset to its initial state.
     *
     ********************************************************************************************/
    void SetUndoRedoModel(std::unique_ptr<cxmodel::IUndoRedo>&& p_model);

    /******************************************************************************************//**
     * @brief Sets a new `IConnectXAI` compatible model.
     *
     * @param p_model A `IConnectXAI` compatible model.
     *
     * @warning When this method is called, the presenter's state is reset to its initial state.
     *
     ********************************************************************************************/
    void SetAIModel(std::unique_ptr<cxmodel::IConnectXAI>&& p_model);

    /******************************************************************************************//**
     * @brief Access to the underlying `IConnectXGameInformation` model.
     *
     * @return The `IConnectXGameInformation` model.
     *
     ********************************************************************************************/
    [[nodiscard]] cxmodel::IConnectXGameInformation& GetGameInformationModel();

    /******************************************************************************************//**
     * @brief Access to the underlying `IConnectXLimits` model.
     *
     * @return The `IConnectXLimits` model.
     *
     ********************************************************************************************/
    [[nodiscard]] cxmodel::IConnectXLimits& GetLimitsModel();

    /******************************************************************************************//**
     * @brief Access to the underlying `IConnectXAI` model.
     *
     * @return The `IConnectXAI` model.
     *
     ********************************************************************************************/
    [[nodiscard]] cxmodel::IConnectXAI& GetAIModel();

private:

    std::unique_ptr<cxgui::IMainWindowPresenter> m_presenter;

    std::unique_ptr<cxmodel::IConnectXGameInformation> m_modelAsGameInformation;
    std::unique_ptr<cxmodel::IConnectXLimits> m_modelAsLimits;
    std::unique_ptr<cxmodel::IUndoRedo> m_modelAsUndoRedo;
    std::unique_ptr<cxmodel::IConnectXAI> m_modelAsAI;

};

#endif // CONFIGURABLEMAINWINDOWPRESENTERTESTFIXTURE_H_90BB4F4D_5BA9_4C29_8CF0_C4E131AC80A3
