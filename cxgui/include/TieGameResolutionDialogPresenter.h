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
 * @file TieGameResolutionDialogPresenter.h
 * @date 2020
 *
 *************************************************************************************************/

#ifndef TIEGAMERESOLUTIONDIALOGPRESENTER_H_A74AF7F6_BBD5_464F_BDC4_EE45E452F226
#define TIEGAMERESOLUTIONDIALOGPRESENTER_H_A74AF7F6_BBD5_464F_BDC4_EE45E452F226

#include "IGameResolutionDialogPresenter.h"

namespace cxgui
{

/*********************************************************************************************//**
 * @brief Presenter for the game resolution window when a tie has occured.
 *
 ************************************************************************************************/
class TieGameResolutionDialogPresenter : public IGameResolutionDialogPresenter
{

public:

    std::string GetTitle() const override;
    std::string GetResolutionMessage() const override;
    std::string GetStartNewGameButtonText() const override;

};

} // namespace cxgui

#endif // TIEGAMERESOLUTIONDIALOGPRESENTER_H_A74AF7F6_BBD5_464F_BDC4_EE45E452F226
