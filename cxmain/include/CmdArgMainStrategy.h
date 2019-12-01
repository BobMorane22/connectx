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
 * @file CmdArgMainStrategy.h
 * @date 2019
 *
 *************************************************************************************************/

#ifndef CMDARGMAINSTRATEGY_H_687BF302_DBF1_4EB7_B096_8DD7B233614A
#define CMDARGMAINSTRATEGY_H_687BF302_DBF1_4EB7_B096_8DD7B233614A

#include <ICmdArgWorkflowStrategy.h>

namespace cx
{

/*********************************************************************************************//**
 * @brief DESCRIPTION
 *
 * @invariant
 * @invariant
 *
 * DESCRIPTION
 *
 ************************************************************************************************/
class CmdArgMainStrategy : public ICmdArgWorkflowStrategy
{

public:

    int Handle() override;

};

} // namespace cx

#endif // CMDARGMAINSTRATEGY_H_687BF302_DBF1_4EB7_B096_8DD7B233614A
