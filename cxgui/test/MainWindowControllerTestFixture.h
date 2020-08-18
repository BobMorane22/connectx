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
 * @file MainWindowControllerTestFixture.h
 * @date 2019
 *
 *************************************************************************************************/

#ifndef MAINWINDOWCONTROLLERTESTFIXTURE_H_797225B7_98E8_412C_BF3D_6976E0C5B6AD
#define MAINWINDOWCONTROLLERTESTFIXTURE_H_797225B7_98E8_412C_BF3D_6976E0C5B6AD

#include <memory>

#include <gtest/gtest.h>

#include <cxmodel/include/IConnectXGameActions.h>
#include <cxgui/include/IMainWindowController.h>

class MainWindowControllerMockModel : public cxmodel::IConnectXGameActions
{

public:

    // IConnectXGameActions:
    void CreateNewGame(const cxmodel::NewGameInformation& p_gameInformation) override;

    bool GetNewGameCreated() const;

private:

    bool m_newGameCreated = false;
};

class MainWindowControllerTestFixture : public testing::Test
{

public:

    MainWindowControllerTestFixture();

    MainWindowControllerMockModel& GetModel();
    cxgui::IMainWindowController& GetController();
    cxgui::INewGameViewController& GetNewGameViewController();

private:

    std::unique_ptr<cxgui::IMainWindowController> m_controller;
    std::unique_ptr<MainWindowControllerMockModel> m_model;

};

#endif // MAINWINDOWCONTROLLERTESTFIXTURE_H_797225B7_98E8_412C_BF3D_6976E0C5B6AD
