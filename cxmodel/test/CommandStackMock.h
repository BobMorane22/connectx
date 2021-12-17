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
 * @file CommandStackMock.h
 * @date 2020
 *
 *************************************************************************************************/

#include <cxmodel/ICommandStack.h>

#ifndef COMMANDSTACKMOCK_H_1C1D7FE3_9103_4716_9765_AF876798E1CB
#define COMMANDSTACKMOCK_H_1C1D7FE3_9103_4716_9765_AF876798E1CB

class CommandStackMock : public cxmodel::ICommandStack
{

public:

    bool IsRedoed() const;
    bool IsUndoed() const;

    void SetCanUndo(bool p_canUndo);
    void SetCanRedo(bool p_canRedo);

    // cxmodel::ICommandStack:
    void Execute(std::unique_ptr<cxmodel::ICommand>&& p_newCommand) override;
    void Clear() override;
    void Undo() override;
    void Redo() override;
    bool CanUndo() const override;
    bool CanRedo() const override;
    bool IsEmpty() const override;
    bool IsFull() const override;
    size_t GetNbCommands() const override;

private:

    bool m_isRedoed{false};
    bool m_isUndoed{false};

    bool m_canUndo{false};
    bool m_canRedo{false};
};

#endif // COMMANDSTACKMOCK_H_1C1D7FE3_9103_4716_9765_AF876798E1CB
