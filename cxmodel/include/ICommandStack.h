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
 * @file ICommandStack.h
 * @date 2020
 *
 *************************************************************************************************/

#ifndef ICOMMANDSTACK_H_5558B486_D3CD_4D16_832D_FFBF37402F13
#define ICOMMANDSTACK_H_5558B486_D3CD_4D16_832D_FFBF37402F13

#include <memory>

#include "ICommand.h"

namespace cxmodel
{

/*********************************************************************************************//**
 * @brief Interface for a stack to treat multiple commands.
 *
 * @invariant The command stack can at least hold two commands.
 *
 * In a program, users sometimes do multiple actions and various commands are executed. This
 * data structure helps the program keep tracks of the last commands that were executed and
 * their order. This facilitates the undoing/redoing of commands.
 *
 * @note This interface assumes that ICommand#Execute has already been called on the commands.
 *       This only deals with post execution.
 * @note This interface assumes that the implementation has a bounded capacity.
 *
 ************************************************************************************************/
class ICommandStack
{

public:

    /******************************************************************************************//**
     * @brief Default destructor.
     *
     ********************************************************************************************/
    virtual ~ICommandStack() = default;

    /******************************************************************************************//**
     * @brief Add a command to the stack and execute it.
     *
     * @pre @c p_newCommand is not @c nullptr
     *
     * @param p_newCommand The command to add to the stack and execute.
     *
     * Adds a new command to the stack (and takes ownership). The new command is then executed.
     *
     ********************************************************************************************/
    virtual void Execute(std::unique_ptr<ICommand>&& p_newCommand) = 0;

    /******************************************************************************************//**
     * @brief Clear the stack.
     *
     * @post There are no more commands in the stack.
     *
     * Clears the stack of all its commands.
     *
     ********************************************************************************************/
    virtual void Clear() = 0;

    /******************************************************************************************//**
     * @brief Undo the current command in the stack.
     *
     * Reverses the actions of the current command in the stack. If there are no commands in the
     * stack, this is a noop. If all commands in the stack have been undoed, this call has no
     * effect.
     *
     ********************************************************************************************/
    virtual void Undo() = 0;

    /******************************************************************************************//**
     * @brief Redo the action of the last undoed command in the stack.
     *
     * Re-executes the action of the last undoed command in the stack. If there are no commands
     * in the stack, this is a noop. If the current command is the last added command in the
     * stack, this call has no effect.
     *
     ********************************************************************************************/
    virtual void Redo() = 0;

    /******************************************************************************************//**
     * @brief Check is there are commands than can be undone in the stack.
     *
     * @return @c true if there is at least one command that can be undone in the stack and
     *         @c false otherwise.
     *
     ********************************************************************************************/
    virtual bool CanUndo() const = 0;

    /******************************************************************************************//**
     * @brief Check is there are commands in the stack that can be redone.
     *
     * @return @c true if there is at least one command that can be redone in the stack and
     *         @c false otherwise.
     *
     ********************************************************************************************/
    virtual bool CanRedo() const = 0;

    /******************************************************************************************//**
     * @brief Check is there are commands in the stack.
     *
     * @return @c true if there is at least one command in the stack and @c false otherwise.
     *
     ********************************************************************************************/
    virtual bool IsEmpty() const = 0;

    /******************************************************************************************//**
     * @brief Check if the command stack is full.
     *
     * @return @c true if the command stack is full, @c false otherwise.
     *
     ********************************************************************************************/
    virtual bool IsFull() const = 0;

    /******************************************************************************************//**
     * @brief Get the number of commands currently stored in the stack.
     *
     * @return The number of commands currently stored in the stack.
     *
     ********************************************************************************************/
    virtual size_t GetNbCommands() const = 0;

};

} // namespace cxmodel

#endif // ICOMMANDSTACK_H_5558B486_D3CD_4D16_832D_FFBF37402F13
