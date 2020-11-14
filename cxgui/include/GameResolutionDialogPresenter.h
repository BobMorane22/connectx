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
 * @file GameResolutionDialogPresenter.h
 * @date 2020
 *
 *************************************************************************************************/

#ifndef GAMERESOLUTIONDIALOGPRESENTER_H_FEF07B2E_B0F6_4FAC_88B7_FE78EC4007CE
#define GAMERESOLUTIONDIALOGPRESENTER_H_FEF07B2E_B0F6_4FAC_88B7_FE78EC4007CE

#include "IGameResolutionDialogPresenter.h"

namespace cxgui
{

/*********************************************************************************************//**
 * @brief Presenter for the game resolution window.
 *
 ************************************************************************************************/
class GameResolutionDialogPresenter : public IGameResolutionDialogPresenter
{

public:

    /******************************************************************************************//**
     * @brief Constructor.
     *
     * @param p_modelAsInformation The model (Game informations).
     *
     ********************************************************************************************/
    GameResolutionDialogPresenter(const cxmodel::IConnectXGameInformation& p_modelAsInformation);

    // IGameResolutionDialogPresenter:
    std::string GetResolutionMessage() const override;

private:

    const cxmodel::IConnectXGameInformation& m_modelAsInformation;

    std::string m_resolutionMessage;
};

} // namespace cxgui

#endif // GAMERESOLUTIONDIALOGPRESENTER_H_FEF07B2E_B0F6_4FAC_88B7_FE78EC4007CE
