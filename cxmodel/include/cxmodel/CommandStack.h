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
 * @file CommandStack.h
 * @date 2020
 *
 *************************************************************************************************/

#ifndef COMMANDSTACK_H_EC172719_473B_49A4_9D9B_D99C30B208A7
#define COMMANDSTACK_H_EC172719_473B_49A4_9D9B_D99C30B208A7

#include <vector>

#include <cxmodel/ICommand.h>

#include "ICommandStack.h"

namespace cxmodel
{

/*********************************************************************************************//**
 * @brief A concrete command stack.
 *
 * A basic implementation of a command stack with only the most basic facilities.
 *
 ************************************************************************************************/
class CommandStack : public ICommandStack
{

public:

    /*********************************************************************************************//**
     * @brief Constructor.
     *
     * @param p_capacity
     *      The number of commands the stack will accept to store before being considered full.
     *
     ************************************************************************************************/
    CommandStack(const size_t p_capacity);

    // cxmodel::ICommandStack:
    [[nodiscard]] CommandCompletionStatus Execute(std::unique_ptr<ICommand>&& p_newCommand) override;
    void Clear() override;

    void Undo() override;
    void Redo() override;
    [[nodiscard]] bool CanUndo() const override;
    [[nodiscard]] bool CanRedo() const override;

    [[nodiscard]] bool IsEmpty() const override;
    [[nodiscard]] bool IsFull() const override;
    [[nodiscard]] size_t GetNbCommands() const override;


private:

    [[nodiscard]] size_t GetLastCommandPosition() const;
    [[nodiscard]] bool NoCommandUndoed() const;
    [[nodiscard]] bool SomeCommandUndoed() const;

    void CheckInvariants();

    const std::size_t m_endPosition;
    std::size_t m_currentPosition;
    bool m_allCmdUndoed;

    std::vector<std::unique_ptr<ICommand>> m_commands;
};

} // namespace cxmodel

#endif // COMMANDSTACK_H_EC172719_473B_49A4_9D9B_D99C30B208A7
