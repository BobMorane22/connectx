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
 * @file IMainWindowPresenter.h
 * @date 2019
 *
 *************************************************************************************************/

#ifndef IMAINWINDOWPRESENTER_H_D8C76920_83D9_4D15_B95A_63282E742221
#define IMAINWINDOWPRESENTER_H_D8C76920_83D9_4D15_B95A_63282E742221

#include <cxmodel/include/IObserver.h>
#include <cxmodel/include/Subject.h>

#include "IGameViewPresenter.h"
#include "INewGameViewPresenter.h"
#include "MenuItem.h"

namespace cxgui
{

/*********************************************************************************************//**
 * @brief Interface for creating a main window presenter.
 *
 * The main window presenter is responsible for making sure the UI logic is up to date, in
 * a UI framework independent fashion. This makes it possible to create a main window with
 * minimal logic.
 *
 * @note Because the class inherits the cxmodel::Subject class, which is an abstract class,
 *       this class is not a pure interface. It is named as if it were a pure interface
 *       because conceptually, it acts like one as far as the presenter is concerned.
 *
 ************************************************************************************************/
class IMainWindowPresenter : public cxmodel::IObserver,
                             public cxmodel::Subject,
                             public IGameViewPresenter,
                             public INewGameViewPresenter
{

public:

///@{ @name Main Window
// -----------------------------------------------------------------------------------------------
    virtual std::string GetWindowTitle() const = 0;
    virtual std::string GetMenuLabel(MenuItem p_menuItem) const = 0;
///@}

///@{ @name New Game View
// -----------------------------------------------------------------------------------------------
    std::string GetNewGameViewTitle() const override = 0;

    std::string GetNewGameViewGameSectionTitle() const override = 0;
    std::string GetNewGameViewInARowLabelText() const override = 0;

    std::string GetNewGameViewGridSectionTitle() const override = 0;
    std::string GetNewGameViewWidthLabelText() const override = 0;
    std::string GetNewGameViewHeightLabelText() const override = 0;

    std::string GetNewGameViewPlayersSectionTitle() const override = 0;
    std::string GetNewGameViewNameColumnHeaderText() const override = 0;
    std::string GetNewGameViewDiscColumnHeaderText() const override = 0;
    std::string GetNewGameViewStartButtonText() const override = 0;

///@}

///@{ @name Game View
// -----------------------------------------------------------------------------------------------
    std::string GetGameViewTitle() const override = 0;
    std::string GetGameViewMessage() const override = 0;
///@}

};

} // namespace cxgui

#endif // IMAINWINDOWPRESENTER_H_D8C76920_83D9_4D15_B95A_63282E742221
