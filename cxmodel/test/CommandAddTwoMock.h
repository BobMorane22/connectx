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
 * @file CommandAddTwoMock.h
 * @date 2020
 *
 *************************************************************************************************/

#ifndef COMMANDADDTWOMOCK_H_7E93C167_1F7F_49B3_9B53_A03CBED755AC
#define COMMANDADDTWOMOCK_H_7E93C167_1F7F_49B3_9B53_A03CBED755AC

#include <cxmodel/ICommand.h>

class CommandAddTwoMock : public cxmodel::ICommand
{

public:

    CommandAddTwoMock(double& p_data);

    // cxmodel::ICommand:
    [[nodiscard]] cxmodel::CommandCompletionStatus Execute() override;
    void Undo() override;


private:

    double& m_data;
};

#endif // COMMANDADDTWOMOCK_H_7E93C167_1F7F_49B3_9B53_A03CBED755AC
