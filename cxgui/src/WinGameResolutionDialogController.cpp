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
 * @file GameResolutionDialogController.cpp
 * @date 2020
 *
 *************************************************************************************************/

#include <cxmodel/include/IConnectXGameActions.h>

#include <GameResolutionDialogController.h>

cxgui::GameResolutionDialogController::WinGameResolutionDialogController(cxmodel::IConnectXGameActions& p_modelAsActions)
: m_modelAsActions{p_modelAsActions}
{
}

void cxgui::GameResolutionDialogController::OnNewGameRequested()
{
    m_modelAsActions.EndCurrentGame();
}
