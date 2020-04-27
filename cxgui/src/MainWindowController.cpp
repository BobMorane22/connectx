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
 * @file MainWindowController.cpp
 * @date 2019
 *
 *************************************************************************************************/

#include <iostream>

#include <cxmodel/include/IModel.h>

#include <MainWindowController.h>

cxgui::MainWindowController::MainWindowController(cxmodel::IModel& p_model)
 : m_model{p_model}
{
}

void cxgui::MainWindowController::OnAboutMenuPressed()
{
    m_model.Signal();
}

void cxgui::MainWindowController::OnStart(const cxmodel::GameInformation p_gameInformation)
{
    m_model.CreateNewGame(p_gameInformation);
}
