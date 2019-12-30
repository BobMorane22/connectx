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
 * @file MainWindowPresenter.cpp
 * @date 2019
 *
 *************************************************************************************************/

#include <cxmodel/include/Model.h>

#include <MainWindowPresenter.h>

cxgui::MainWindowPresenter::MainWindowPresenter()
 : m_counterValue{0}
 , m_isIncrementBtnEnabled{false}
{
}

bool cxgui::MainWindowPresenter::IsReinitializeBtnEnabled() const
{
    return m_isIncrementBtnEnabled;
}

unsigned int cxgui::MainWindowPresenter::GetCounterValue() const
{
    return m_counterValue;
}

void cxgui::MainWindowPresenter::Update(cxmodel::Subject* p_subject)
{
    if(p_subject)
    {
        cxmodel::IModel* model = static_cast<cxmodel::Model*>(p_subject);

        const unsigned int value = model->GetCurrentValue();

        m_isIncrementBtnEnabled = value > 0;
        m_counterValue = value;

        Notify();
    }
}

std::string cxgui::MainWindowPresenter::GetIncrementBtnLabel() const
{
    return std::string{m_incrementBtnLabel};
}

std::string cxgui::MainWindowPresenter::GetReinitializeBtnLabel() const
{
    return std::string{m_reinitializeBtnLabel};
}
