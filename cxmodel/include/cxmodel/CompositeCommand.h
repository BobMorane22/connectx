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
 * @file CompositeCommand.h
 * @date 2022
 *
 *************************************************************************************************/

#ifndef COMPOSITECOMMAND_H_2BA36E20_1068_4C28_8551_8BD94851A994
#define COMPOSITECOMMAND_H_2BA36E20_1068_4C28_8551_8BD94851A994

#include <memory>
#include <vector>

#include "ICommand.h"

namespace cxmodel
{

/**********************************************************************************************//**
 * @brief Composite commands.
 *
 * For some commands, it can make sense to group them together and exexecute them is a batch. This
 * class allows such a grouping using the Composite design pattern.
 *
 *************************************************************************************************/
class CompositeCommand : public ICommand
{

public:

    /**********************************************************************************************//**
     * @brief Adds a command to the composite. The composite takes ownership of the child.
     *
     * @pre The child to add is valid.
     *
     * @param p_child
     *      The child command to add to the composite.
     *
     *************************************************************************************************/
    void Add(std::unique_ptr<ICommand> p_child);

    // cxmodel::ICommand
    [[nodiscard]] CommandCompletionStatus Execute() override;
    void Undo() override;

private:

    std::vector<std::unique_ptr<ICommand>> m_children;

};

} // namespace cxmodel

#endif // COMPOSITECOMMAND_H_2BA36E20_1068_4C28_8551_8BD94851A994
