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
 * @file MainWindowController.h
 * @date 2019
 *
 *************************************************************************************************/

#ifndef MAINWINDOWCONTROLLER_H_2377676C_13C5_4D43_8AFA_0C90ABC44C5C
#define MAINWINDOWCONTROLLER_H_2377676C_13C5_4D43_8AFA_0C90ABC44C5C

#include "IMainWindowController.h"

namespace cxmodel
{
    class IModel;
}

namespace cxgui
{

class MainWindowController : public cxgui::IMainWindowController
{

public:

    MainWindowController(cxmodel::IModel& p_model);

    void OnIncrementBtnPressed() override;
    void OnReinitializeBtnPressed() override;
    void OnUndoBtnPressed() override;
    void OnRedoBtnPressed() override;
    void OnAboutMenuPressed() override;


private:

    cxmodel::IModel& m_model;
};

} // namespace cxgui

#endif // MAINWINDOWCONTROLLER_H_2377676C_13C5_4D43_8AFA_0C90ABC44C5C
