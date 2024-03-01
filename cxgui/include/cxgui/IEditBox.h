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
 * @file IEditBox.h
 * @date 2024
 *
 *************************************************************************************************/

#ifndef IEDITBOX_H_D31E12BC_892F_4930_BF5C_41C904B92362
#define IEDITBOX_H_D31E12BC_892F_4930_BF5C_41C904B92362

#include <cxgui/ISignal.h>
#include <cxgui/IWidget.h>

namespace cxgui
{

class IEditBox : public IWidget
{

public:

    /******************************************************************************************//**
     * @brief Destructor.
     *
     *********************************************************************************************/
    virtual ~IEditBox() = default;
    
    /******************************************************************************************//**
     * @brief Updates the edit box's contents.
     *
     * @param p_newContents
     *      The contents to update the edit box with.
     *
     *********************************************************************************************/
    virtual void UpdateContents(const std::string& p_newContents) = 0;

    /******************************************************************************************//**
     * @brief Get the edit box's contents.
     *
     * @return
     *      The edit's actual contents.
     *
     *********************************************************************************************/
    [[nodiscard]] virtual std::string GetContents() const = 0;

    /******************************************************************************************//**
     * @brief Get the signal for when the edit box contents is changed by the user.
     *
     * @return
     *      A signal to connect to for when the edit box's contents is changed.
     *
     *********************************************************************************************/
    [[nodiscard]] virtual std::unique_ptr<ISignal<void>> OnContentsChanged() = 0;

};

} // namespace cxgui

#endif // IEDITBOX_H_D31E12BC_892F_4930_BF5C_41C904B92362
