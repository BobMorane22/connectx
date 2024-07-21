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
#include <memory>

#include <cxinv/assertion.h>
#include <cxmodel/Disc.h>
#include <cxmodel/IConnectXGameActions.h>
#include <cxmodel/IUndoRedo.h>
#include <cxgui/MainWindowController.h>

cx::gui::MainWindowController::MainWindowController(cxmodel::IConnectXGameActions& p_modelAsGameActions,
                                                  cxmodel::IUndoRedo& p_modelAsUndoRedo)
: m_modelAsGameActions{p_modelAsGameActions}
, m_modelAsUndoRedo{p_modelAsUndoRedo}
, m_currentChip{std::make_unique<cxmodel::Disc>(cxmodel::Disc::MakeTransparentDisc())}
{
}

void cx::gui::MainWindowController::OnStart(cxmodel::NewGameInformation p_gameInformation)
{
    m_modelAsGameActions.CreateNewGame(std::move(p_gameInformation));
}

void cx::gui::MainWindowController::OnDown(const cxmodel::ChipColor& p_chipColor, size_t p_column)
{
    IF_PRECONDITION_NOT_MET_DO(p_chipColor != cxmodel::MakeTransparent(), return;);

    m_currentChip = std::make_unique<cxmodel::Disc>(p_chipColor);
    m_modelAsGameActions.DropChip(*m_currentChip, p_column);
}

void cx::gui::MainWindowController::OnMoveLeftOneColumn()
{
    m_modelAsGameActions.MoveLeftOneColumn();
}

void cx::gui::MainWindowController::OnMoveRightOneColumn()
{
    m_modelAsGameActions.MoveRightOneColumn();
}

void cx::gui::MainWindowController::OnNewGame()
{
    m_modelAsGameActions.EndCurrentGame(); 
}

void cx::gui::MainWindowController::OnReinitializeCurrentGame()
{
    m_modelAsGameActions.ReinitializeCurrentGame();
}

void cx::gui::MainWindowController::OnUndo()
{
    m_modelAsUndoRedo.Undo();
}

void cx::gui::MainWindowController::OnRedo()
{
    m_modelAsUndoRedo.Redo();
}
