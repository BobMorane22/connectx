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
 * @file StatusBarPresenter.h
 * @date 2020
 *
 *************************************************************************************************/

#ifndef STATUSBARPRESENTER_H_8AA4CA20_8179_4812_944C_7029B25AE1DC
#define STATUSBARPRESENTER_H_8AA4CA20_8179_4812_944C_7029B25AE1DC

#include "IStatusBarPresenter.h"

namespace cxgui
{

/*********************************************************************************************//**
 * @brief Status bar presenter.
 *
 ************************************************************************************************/
class StatusBarPresenter : public IStatusBarPresenter
{

public:

    std::string GetStatusBarMessage() const override;

    virtual void Update(cxmodel::ModelNotificationContext p_context, cxmodel::ModelSubject* p_subject) override;


private:

    std::string m_statusBarMessage;

};


/**********************************************************************************************//**
 * @brief Generates a formatted string associated to a model notification context.
 *
 * Each model notification context is loggued to the status bar for the user to see. This function
 * takes a model notification context and generates the associated formatted string to show the
 * user. Some notification contexts are not shown to the user and in these cases, an empty string
 * is returned by this function.
 *
 * @param p_context The model notification context.
 *
 * @return The formatted string related to the model notification context (can be empty).
 *
 *************************************************************************************************/
[[nodiscard]] std::string MakeStatusBarContextString(cxmodel::ModelNotificationContext p_context);

} // namespace cxgui



#endif // STATUSBARPRESENTER_H_8AA4CA20_8179_4812_944C_7029B25AE1DC
