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
 * @file ILabel.h
 * @date 2024
 *
 *************************************************************************************************/

#ifndef ILABEL_H_30710FC9_8E82_412E_8023_809CA23BC187
#define ILABEL_H_30710FC9_8E82_412E_8023_809CA23BC187

#include <cxgui/IWidget.h>

namespace cxgui
{

/**********************************************************************************************//**
 * @brief A read only label.
 *
 *************************************************************************************************/
class ILabel : public IWidget
{

public:

    /******************************************************************************************//**
     * @brief Destructor.
     *
     *********************************************************************************************/
     ~ILabel() override = default;

    /******************************************************************************************//**
     * @brief Updates the label's contents.
     *
     * @param p_newContents
     *      The contents to update the label with.
     *
     *********************************************************************************************/
    virtual void UpdateContents(const std::string& p_newContents) = 0;

    /******************************************************************************************//**
     * @brief Get the label's contents.
     *
     * @return
     *      The label's actuel contents.
     *
     *********************************************************************************************/
    [[nodiscard]] virtual std::string GetContents() const = 0;

};

} // namespace cxgui

#endif // ILABEL_H_30710FC9_8E82_412E_8023_809CA23BC187
