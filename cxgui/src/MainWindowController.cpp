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

#include <cxmodel/include/IModel.h>

#include <MainWindowController.h>

cxgui::MainWindowController::MainWindowController(cxmodel::IModel& p_model)
 : m_model{p_model}
{
}

void cxgui::MainWindowController::OnIncrementBtnPressed()
{
    m_model.Increment();
}

void cxgui::MainWindowController::OnReinitializeBtnPressed()
{
    m_model.Reinitialize();
}

void cxgui::MainWindowController::OnUndoBtnPressed()
{
    m_model.Undo();
}

void cxgui::MainWindowController::OnRedoBtnPressed()
{
    m_model.Redo();
}
