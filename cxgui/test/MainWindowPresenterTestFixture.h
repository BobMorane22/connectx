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
 * @file MainWindowPresenterTestFixture.h
 * @date 2019
 *
 *************************************************************************************************/

#ifndef MAINWINDOWPRESENTERTESTFIXTURE_H_BF5C449E_46ED_4C25_A8AE_98F606AEC840
#define MAINWINDOWPRESENTERTESTFIXTURE_H_BF5C449E_46ED_4C25_A8AE_98F606AEC840

#include <memory>

#include <cxgui/include/IMainWindowPresenter.h>
#include <cxmodel/include/IModel.h>

class MainWindowPresenterTestFixture : public testing::Test
{

public:

    MainWindowPresenterTestFixture();

    cxgui::IMainWindowPresenter& GetPresenter();
    cxgui::IGameViewPresenter& GetGameViewPresenter();
    cxgui::INewGameViewPresenter& GetNewGameViewPresenter();

    cxmodel::IModel& GetModel();

private:

    std::unique_ptr<cxgui::IMainWindowPresenter> m_presenter;
    std::unique_ptr<cxmodel::IModel> m_model;
};

#endif // MAINWINDOWPRESENTERTESTFIXTURE_H_BF5C449E_46ED_4C25_A8AE_98F606AEC840
