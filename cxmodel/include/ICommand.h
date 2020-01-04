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
 * @file ICommand.h
 * @date 2020
 *
 *************************************************************************************************/

#ifndef ICOMMAND_H_65CCB8C8_B685_4720_8172_C50ED8C4909D
#define ICOMMAND_H_65CCB8C8_B685_4720_8172_C50ED8C4909D

namespace cxmodel
{

/*********************************************************************************************//**
 * @brief Interface for creating commands.
 *
 * As described in the book <i>Design Patterns : Elements of Reusable Object-Oriented Software</i>,
 * p. 233, A command encapsulates "[...] a request as an object, thereby letting you parameterize
 * clients with different requests, queue or log requests, and support undoable operations."
 *
 ************************************************************************************************/
class ICommand
{

public:

    /******************************************************************************************//**
     * @brief Default destructor.
     *
     ********************************************************************************************/
    virtual ~ICommand() = default;

    /******************************************************************************************//**
     * @brief Execute a command action.
     *
     * Execute the actions registered in a command.
     *
     ********************************************************************************************/
    virtual void Execute() = 0;

    /******************************************************************************************//**
     * @brief Undo a command action.
     *
     * Reverse the actions performed by a command when ICommand#Execute is called. Calling this
     * should put the program back in the state it was before ICommand#Execute was called.
     *
     ********************************************************************************************/
    virtual void Undo() = 0;

};

} // namespace cxmodel

#endif // ICOMMAND_H_65CCB8C8_B685_4720_8172_C50ED8C4909D
