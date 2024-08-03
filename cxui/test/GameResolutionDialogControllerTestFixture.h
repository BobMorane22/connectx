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
 * @file GameResolutionDialogControllerTestFixture.h
 * @date 2020
 *
 *************************************************************************************************/

#ifndef GAMERESOLUTIONDIALOGCONTROLLERTESTFIXTURE_H_27CF95E0_02C0_4019_A321_26C5670AB81F
#define GAMERESOLUTIONDIALOGCONTROLLERTESTFIXTURE_H_27CF95E0_02C0_4019_A321_26C5670AB81F

#include <gtest/gtest.h>

#include <cxmodel/IConnectXGameActions.h>
#include <cxui/IGameResolutionDialogController.h>

class GameResolutionDialogControllerTestFixture : public testing::Test
{

public:

    GameResolutionDialogControllerTestFixture();

    bool GetNewGameRequested() const;

    cx::ui::cmn::IGameResolutionDialogController& GetController();

private:

    class GameResolutionDialogControllerMockModel : public cx::model::IConnectXGameActions
    {

    public:

        GameResolutionDialogControllerMockModel(GameResolutionDialogControllerTestFixture& p_outer);

        // IConnectXGameActions:
        void CreateNewGame(cx::model::NewGameInformation p_gameInformation) override;
        void DropChip(const cx::model::IChip& p_chip, size_t p_column) override;
        void MoveLeftOneColumn() override;
        void MoveRightOneColumn() override;
        void EndCurrentGame() override;
        void ReinitializeCurrentGame() override;

    private:

        GameResolutionDialogControllerTestFixture& m_outer;

    };

    bool m_newGameRequested = false;

    std::unique_ptr<GameResolutionDialogControllerMockModel> m_model;
    std::unique_ptr<cx::ui::cmn::IGameResolutionDialogController> m_controller;

};

#endif // GAMERESOLUTIONDIALOGCONTROLLERTESTFIXTURE_H_27CF95E0_02C0_4019_A321_26C5670AB81F
