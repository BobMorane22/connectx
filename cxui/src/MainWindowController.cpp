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
#include <cxui/MainWindowController.h>

cx::ui::MainWindowController::MainWindowController(cx::model::IConnectXGameActions& p_modelAsGameActions,
                                                  cx::model::IUndoRedo& p_modelAsUndoRedo)
: m_modelAsGameActions{p_modelAsGameActions}
, m_modelAsUndoRedo{p_modelAsUndoRedo}
, m_currentChip{std::make_unique<cx::model::Disc>(cx::model::Disc::MakeTransparentDisc())}
{
}

void cx::ui::MainWindowController::OnStart(cx::model::NewGameInformation p_gameInformation)
{
    m_modelAsGameActions.CreateNewGame(std::move(p_gameInformation));
}

void cx::ui::MainWindowController::OnDown(const cx::model::ChipColor& p_chipColor, size_t p_column)
{
    IF_PRECONDITION_NOT_MET_DO(p_chipColor != cx::model::MakeTransparent(), return;);

    m_currentChip = std::make_unique<cx::model::Disc>(p_chipColor);
    m_modelAsGameActions.DropChip(*m_currentChip, p_column);
}

void cx::ui::MainWindowController::OnMoveLeftOneColumn()
{
    m_modelAsGameActions.MoveLeftOneColumn();
}

void cx::ui::MainWindowController::OnMoveRightOneColumn()
{
    m_modelAsGameActions.MoveRightOneColumn();
}

void cx::ui::MainWindowController::OnNewGame()
{
    m_modelAsGameActions.EndCurrentGame(); 
}

void cx::ui::MainWindowController::OnReinitializeCurrentGame()
{
    m_modelAsGameActions.ReinitializeCurrentGame();
}

void cx::ui::MainWindowController::OnUndo()
{
    m_modelAsUndoRedo.Undo();
}

void cx::ui::MainWindowController::OnRedo()
{
    m_modelAsUndoRedo.Redo();
}
