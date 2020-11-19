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
 * @file WinGameResolutionDialogController.h
 * @date 2020
 *
 *************************************************************************************************/

#ifndef WINGAMERESOLUTIONDIALOGCONTROLLER_H_021D83A0_55DA_4155_B5F6_3AA46D5A6BF8
#define WINGAMERESOLUTIONDIALOGCONTROLLER_H_021D83A0_55DA_4155_B5F6_3AA46D5A6BF8

#include "IGameResolutionDialogController.h"

namespace cxmodel
{
    class IConnectXGameActions;
}

namespace cxgui
{

/*********************************************************************************************//**
 * @brief DESCRIPTION
 *
 * @invariant
 * @invariant
 *
 * DESCRIPTION
 *
 ************************************************************************************************/
class WinGameResolutionDialogController : public IGameResolutionDialogController
{

public:

    WinGameResolutionDialogController(cxmodel::IConnectXGameActions& p_modelAsActions);

    void OnNewGameRequested();

private:

    cxmodel::IConnectXGameActions& m_modelAsActions;

};

} // namespace cxgui

#endif // WINGAMERESOLUTIONDIALOGCONTROLLER_H_021D83A0_55DA_4155_B5F6_3AA46D5A6BF8
