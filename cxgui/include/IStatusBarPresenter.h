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
 * @file IStatusBarPresenter.h
 * @date 2020
 *
 *************************************************************************************************/

#ifndef ISTATUSBARPRESENTER_H_ABE6731E_14D3_4B54_B017_22D806A7BC0B
#define ISTATUSBARPRESENTER_H_ABE6731E_14D3_4B54_B017_22D806A7BC0B

#include <string>

#include <cxmodel/include/IObserver.h>
#include <cxmodel/include/Subject.h>

namespace cxgui
{

/*********************************************************************************************//**
 * @brief Interface for status bar presenters.
 *
 ************************************************************************************************/
class IStatusBarPresenter : public cxmodel::IObserver, public cxmodel::Subject
{

public:

    /******************************************************************************************//**
     * @brief Retrieves the message to display in the status bar.
     *
     * @return The message to display in the status bar.
     *
     ********************************************************************************************/
    virtual std::string GetStatusBarMessage() const = 0;

};

} // namespace cxgui

#endif // ISTATUSBARPRESENTER_H_ABE6731E_14D3_4B54_B017_22D806A7BC0B
