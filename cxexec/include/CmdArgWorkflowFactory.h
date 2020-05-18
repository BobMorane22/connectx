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
 * @file CmdArgWorkflowFactory.h
 * @date 2019
 *
 *************************************************************************************************/

#ifndef CMDARGWORKFLOWFACTORY_H_FEECC848_F293_48E7_91FD_E2BF6BA98EC7
#define CMDARGWORKFLOWFACTORY_H_FEECC848_F293_48E7_91FD_E2BF6BA98EC7

#include <memory>

#include "ICmdArgWorkflowStrategy.h"

namespace cxmodel
{
    class IModel;
}

namespace cxlog
{
    class IChainLogging;
}

namespace cx
{

/*********************************************************************************************//**
 * @brief Factory for creating command line arguments dependent workflows.
 *
 ************************************************************************************************/
class CmdArgWorkflowFactory
{

public:

    /******************************************************************************************//**
     * @brief Create a command line dependent workflow.
     *
     * @param argc The number of command line arguments (including the executable).
     * @param argv A C-style array containing the command line argument strings (including the
     *             executable).
     * @param p_model The Connect X compatible model.
     * @param p_logger A chain logger.
     *
     * @post The returned command line dependent workflow is not @c nullptr.
     *
     * @return The command line dependent workflow.
     *
     ********************************************************************************************/
    std::unique_ptr<ICmdArgWorkflowStrategy> Create(int argc, char *argv[], cxmodel::IModel& p_model, cxlog::ILogger& p_logger);

};

} // namespace cx

#endif // CMDARGWORKFLOWFACTORY_H_FEECC848_F293_48E7_91FD_E2BF6BA98EC7
