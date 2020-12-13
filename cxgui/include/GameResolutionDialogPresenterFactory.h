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
 * @file GameResolutionDialogPresenterFactory.h
 * @date 2020
 *
 *************************************************************************************************/

#ifndef GAMERESOLUTIONDIALOGPRESENTERFACTORY_H_0DEB58AF_5E6C_41B3_BDA0_DE2C38CE8416
#define GAMERESOLUTIONDIALOGPRESENTERFACTORY_H_0DEB58AF_5E6C_41B3_BDA0_DE2C38CE8416

#include <memory>

#include "IGameResolutionDialogPresenter.h"

namespace cxmodel
{
    enum class GameResolution;
    class IConnectXGameInformation;
}

namespace cxgui
{

/*********************************************************************************************//**
 * @brief Factory for creating game resolution dialog presenters.
 *
 ************************************************************************************************/
class GameResolutionDialogPresenterFactory
{

public:

    /******************************************************************************************//**
     * @brief Creates a game resolution dialog presenter.
     *
     * @param p_modelAsInformation The model.
     * @param p_resolution         The game resolution type.
     *
     * @return The game resolution dialog presenter.
     *
     ********************************************************************************************/
    static std::unique_ptr<IGameResolutionDialogPresenter> Make(const cxmodel::IConnectXGameInformation& p_modelAsInformation,
                                                                cxmodel::GameResolution p_resolution);

};

} // namespace cxgui

#endif // GAMERESOLUTIONDIALOGPRESENTERFACTORY_H_0DEB58AF_5E6C_41B3_BDA0_DE2C38CE8416
