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

    MainWindowPresenter();

    bool IsReinitializeBtnEnabled() const override;
    unsigned int GetCounterValue() const override;
    std::string GetIncrementBtnLabel() const override;
    std::string GetReinitializeBtnLabel() const override;

    void Update(cxmodel::Subject* p_subject) override;


private:

    unsigned int m_counterValue;
    bool m_isIncrementBtnEnabled;

    static constexpr char m_incrementBtnLabel[] = "Increment";
    static constexpr char m_reinitializeBtnLabel[] = "Reinitialize";

};

} // namespace cxgui

#endif // MAINWINDOWPRESENTER_H_B80CACC4_E075_49C0_9DFD_29C6C1BCFE67
