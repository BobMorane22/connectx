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

class StatusBarPresenter : public IStatusBarPresenter
{

public:

    std::string GetStatusBarMessage() const override;

    virtual void Update(cxmodel::ModelNotificationContext p_context, cxmodel::ModelSubject* p_subject) override;


private:

    std::string m_statusBarMessage;

};

std::string MakeStatusBarContextString(cxmodel::ModelNotificationContext p_context);

} // namespace cxgui



#endif // STATUSBARPRESENTER_H_8AA4CA20_8179_4812_944C_7029B25AE1DC
