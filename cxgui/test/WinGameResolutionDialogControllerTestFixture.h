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
 * @file WinGameResolutionDialogControllerTestFixture.h
 * @date 2020
 *
 *************************************************************************************************/

#ifndef WINGAMERESOLUTIONDIALOGCONTROLLERTESTFIXTURE_H_27CF95E0_02C0_4019_A321_26C5670AB81F
#define WINGAMERESOLUTIONDIALOGCONTROLLERTESTFIXTURE_H_27CF95E0_02C0_4019_A321_26C5670AB81F

#include <gtest/gtest.h>

#include <cxmodel/include/IConnectXGameActions.h>

#include <IGameResolutionDialogController.h>

class WinGameResolutionDialogControllerTestFixture : public testing::Test
{

public:

    WinGameResolutionDialogControllerTestFixture();

    bool GetNewGameRequested() const;

    cxgui::IGameResolutionDialogController& GetController();

private:

    class GameResolutionDialogControllerMockModel : public cxmodel::IConnectXGameActions
    {

    public:

        GameResolutionDialogControllerMockModel(WinGameResolutionDialogControllerTestFixture& p_outer);

        // IConnectXGameActions:
        void CreateNewGame(const cxmodel::NewGameInformation& p_gameInformation) override;
        void DropChip(const cxmodel::IChip& p_chip, size_t p_column) override;
        void EndCurrentGame() override;
        void ReinitializeCurrentGame() override;

    private:

        WinGameResolutionDialogControllerTestFixture& m_outer;

    };

    bool m_newGameRequested = false;

    std::unique_ptr<GameResolutionDialogControllerMockModel> m_model;
    std::unique_ptr<cxgui::IGameResolutionDialogController> m_controller;

};

#endif // WINGAMERESOLUTIONDIALOGCONTROLLERTESTFIXTURE_H_27CF95E0_02C0_4019_A321_26C5670AB81F
