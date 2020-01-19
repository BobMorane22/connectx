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
 * @file CommandIncrementByOne.h
 * @date 2020
 *
 *************************************************************************************************/

#ifndef COMMANDINCREMENTBYONE_H_940FBEA4_4F38_4D83_960D_B7316380C018
#define COMMANDINCREMENTBYONE_H_940FBEA4_4F38_4D83_960D_B7316380C018

#include "ICommand.h"

namespace cxmodel
{

class CommandIncrementByOne : public ICommand
{

public:

    CommandIncrementByOne(unsigned int& p_value);

    void Execute() override;
    void Undo() override;


private:

    unsigned int& m_value;
    const unsigned int m_undoValue;

};

} // namespace cxmodel

#endif // COMMANDINCREMENTBYONE_H_940FBEA4_4F38_4D83_960D_B7316380C018
