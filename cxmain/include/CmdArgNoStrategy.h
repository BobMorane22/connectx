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
 * @file CmdArgNoStrategy.h
 * @date 2019
 *
 *************************************************************************************************/

#ifndef CMDARGNOSTRATEGY_H_25881F6A_566B_4C12_A32C_70E60C30D4E5
#define CMDARGNOSTRATEGY_H_25881F6A_566B_4C12_A32C_70E60C30D4E5

#include <ICmdArgWorkflowStrategy.h>

namespace cx
{

/*********************************************************************************************//**
 * @brief The absence of a workflow.
 *
 ************************************************************************************************/
class CmdArgNoStrategy : public ICmdArgWorkflowStrategy
{

public:

    int Handle() override;

};

} // namespace cx

#endif // CMDARGNOSTRATEGY_H_25881F6A_566B_4C12_A32C_70E60C30D4E5
