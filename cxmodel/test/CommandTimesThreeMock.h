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
 * @file CommandTimesThreeMock.h
 * @date 2020
 *
 *************************************************************************************************/

#ifndef COMMANDTIMESTHREEMOCK_H_B453A60A_CF4C_4C17_AB96_D3E37FF11020
#define COMMANDTIMESTHREEMOCK_H_B453A60A_CF4C_4C17_AB96_D3E37FF11020

#include <cxmodel/ICommand.h>

class CommandTimesThreeMock : public cxmodel::ICommand
{

public:

    CommandTimesThreeMock(double& p_data);

    virtual void Execute() override;
    virtual void Undo() override;


private:

    double& m_data;
};

#endif // COMMANDTIMESTHREEMOCK_H_B453A60A_CF4C_4C17_AB96_D3E37FF11020
