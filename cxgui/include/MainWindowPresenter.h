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
 * @file MainWindowPresenter.h
 * @date 2019
 *
 *************************************************************************************************/

#ifndef MAINWINDOWPRESENTER_H_B80CACC4_E075_49C0_9DFD_29C6C1BCFE67
#define MAINWINDOWPRESENTER_H_B80CACC4_E075_49C0_9DFD_29C6C1BCFE67

#include <string>

#include "IMainWindowPresenter.h"

namespace cxgui
{

class MainWindowPresenter : public cxgui::IMainWindowPresenter
{

public:

///@{ @name Main Window
// -----------------------------------------------------------------------------------------------

    std::string GetWindowTitle() const override;
    std::string GetMenuLabel(MenuItem p_menuItem) const override;

///@}

///@{ @name New Game View
// -----------------------------------------------------------------------------------------------

    virtual std::string GetNewGameViewTitle() const override;

    virtual std::string GetNewGameViewGameSectionTitle() const override;
    virtual std::string GetNewGameViewInARowLabelText() const override;

    virtual std::string GetNewGameViewGridSectionTitle() const override;
    virtual std::string GetNewGameViewWidthLabelText() const override;
    virtual std::string GetNewGameViewHeightLabelText() const override;

    virtual std::string GetNewGameViewPlayersSectionTitle() const override;
    virtual std::string GetNewGameViewNameColumnHeaderText() const override;
    virtual std::string GetNewGameViewDiscColumnHeaderText() const override;
    virtual std::string GetNewGameViewStartButtonText() const override;

///@}

private:

    void Update(cxmodel::NotificationContext p_context, cxmodel::Subject* p_subject) override;

};

} // namespace cxgui

#endif // MAINWINDOWPRESENTER_H_B80CACC4_E075_49C0_9DFD_29C6C1BCFE67
