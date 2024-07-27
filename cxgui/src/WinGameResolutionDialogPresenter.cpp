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
 * @file WinGameResolutionDialogPresenter.cpp
 * @date 2020
 *
 *************************************************************************************************/

#include <cxinv/assertion.h>
#include <cxmodel/IConnectXGameInformation.h>
#include <cxmodel/IPlayer.h>
#include <cxgui/WinGameResolutionDialogPresenter.h>

cx::cmn::ui::WinGameResolutionDialogPresenter::WinGameResolutionDialogPresenter(const cx::model::IConnectXGameInformation& p_modelAsInformation)
: m_modelAsInformation{p_modelAsInformation}
{

}

std::string cx::cmn::ui::WinGameResolutionDialogPresenter::GetTitle() const
{
    return "Game won!";
}

std::string cx::cmn::ui::WinGameResolutionDialogPresenter::GetResolutionMessage() const
{
    if(INL_ASSERT(m_modelAsInformation.IsWon()))
    {
        return "Congratulations to " + m_modelAsInformation.GetActivePlayer().GetName() + "!";
    }

    return "";
}

std::string cx::cmn::ui::WinGameResolutionDialogPresenter::GetStartNewGameButtonText() const
{
    return "Start new game";
}
