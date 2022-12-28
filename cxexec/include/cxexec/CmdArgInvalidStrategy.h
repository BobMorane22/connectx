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
 * @file CmdArgInvalidStrategy.h
 * @date 2019
 *
 *************************************************************************************************/

#ifndef CMDARGINVALIDSTRATEGY_H_9C44DA78_9CAA_4521_AB76_6944321EEFE5
#define CMDARGINVALIDSTRATEGY_H_9C44DA78_9CAA_4521_AB76_6944321EEFE5

#include <string>

#include "ICmdArgWorkflowStrategy.h"

namespace cx
{

/*********************************************************************************************//**
 * @brief Workflow for when an invalid argument is given to the command line.
 *
 * @invariant The invalid argument string is never empty.
 *
 ************************************************************************************************/
class CmdArgInvalidStrategy : public ICmdArgWorkflowStrategy
{

public:

    /*****************************************************************************************//**
     * @brief Constructor.
     *
     * @param p_invalidArg The invalid command line argument.
     *
     * @pre The invalid argument string is not empty.
     *
     ********************************************************************************************/
    CmdArgInvalidStrategy(const std::string& p_invalidArg);

    // cx::ICmdArgWorkflowStrategy:
    int Handle() override;


private:

    const std::string m_invalidArg;

};

} // namespace cx

#endif // CMDARGINVALIDSTRATEGY_H_9C44DA78_9CAA_4521_AB76_6944321EEFE5
