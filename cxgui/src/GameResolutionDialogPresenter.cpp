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
 * @file GameResolutionDialogPresenter.cpp
 * @date 2020
 *
 *************************************************************************************************/

#include <cxinv/include/assertion.h>
#include <cxmodel/include/IConnectXGameInformation.h>

#include <GameResolutionDialogPresenter.h>

cxgui::GameResolutionDialogPresenter::GameResolutionDialogPresenter(const cxmodel::IConnectXGameInformation& p_modelAsInformation)
: m_modelAsInformation{p_modelAsInformation}
{

}

std::string cxgui::GameResolutionDialogPresenter::GetResolutionMessage() const
{
    if(ASSERT(m_modelAsInformation.IsWon()))
    {
        return "Congratulations to " + m_modelAsInformation.GetActivePlayer().GetName() + " for winning the game!";
    }

    return "";
}
