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
 * @file INewGameViewPresenter.h
 * @date 2020
 *
 *************************************************************************************************/

#ifndef INEWVIEWPRESENTER_H_8159479B_ECAB_4CD5_9CC6_B818FCBC26C8
#define INEWVIEWPRESENTER_H_8159479B_ECAB_4CD5_9CC6_B818FCBC26C8

#include <string>

namespace cxgui
{

/*********************************************************************************************//**
 * @brief Presenter for the 'New Game' view.
 *
 ************************************************************************************************/
class INewGameViewPresenter
{

public:

    virtual ~INewGameViewPresenter() = default;

    virtual std::string GetNewGameViewTitle() const = 0;

    virtual std::string GetNewGameViewGameSectionTitle() const = 0;
    virtual std::string GetNewGameViewInARowLabelText() const = 0;

    virtual std::string GetNewGameViewGridSectionTitle() const = 0;
    virtual std::string GetNewGameViewWidthLabelText() const = 0;
    virtual std::string GetNewGameViewHeightLabelText() const = 0;

    virtual std::string GetNewGameViewPlayersSectionTitle() const = 0;
    virtual std::string GetNewGameViewNameColumnHeaderText() const = 0;
    virtual std::string GetNewGameViewDiscColumnHeaderText() const = 0;
    virtual std::string GetNewGameViewStartButtonText() const = 0;

};

}

#endif // INEWVIEWPRESENTER_H_8159479B_ECAB_4CD5_9CC6_B818FCBC26C8
