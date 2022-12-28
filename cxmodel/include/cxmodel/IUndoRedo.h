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
 * @file IUndoRedo.h * @date 2020
 *
 *************************************************************************************************/

#ifndef IUNDOREDO_H_C750BB28_D806_4806_8DEB_B796D85DA799
#define IUNDOREDO_H_C750BB28_D806_4806_8DEB_B796D85DA799

namespace cxmodel
{

/**********************************************************************************************//**
 * @brief Interface for undoing and redoing commands.
 *
 ************************************************************************************************/
class IUndoRedo
{

public:

    /******************************************************************************************//**
     * @brief Destructor.
     *
     ********************************************************************************************/
    virtual ~IUndoRedo() = default;

    /******************************************************************************************//**
     * @brief Undo the last action, if possible.
     *
     * If some undoeable actions were done, the last one will be undoed.
     *
     * @note
     *     An action that is undoed must put the model back at the same state is was before
     *     the action was ever done.
     *
     ********************************************************************************************/
    virtual void Undo() = 0;

    /******************************************************************************************//**
     * @brief Redo the last action, if possible.
     *
     * If some redoable actions were undoed, the last one that was undoed will be redoed.
     * Otherwise, nothing happens.
     *
     * @note
     *     An action that is redoed must put the model back at the same state it was before
     *     the action was undoed.
     *
     ********************************************************************************************/
    virtual void Redo() = 0;

    /******************************************************************************************//**
     * @brief Check is there are commands than can be undone in the stack.
     *
     * @return 
     *     `true` if there is at least one command that can be undone in the stack and `false` otherwise.
     *
     ********************************************************************************************/
    virtual bool CanUndo() const = 0;

    /******************************************************************************************//**
     * @brief Check is there are commands in the stack that can be redone.
     *
     * @return
     *      `true` if there is at least one command that can be redone in the stack and `false` otherwise.
     *
     ********************************************************************************************/
    virtual bool CanRedo() const = 0;

};

} // namespace cxmodel

#endif // IUNDOREDO_H_C750BB28_D806_4806_8DEB_B796D85DA799
