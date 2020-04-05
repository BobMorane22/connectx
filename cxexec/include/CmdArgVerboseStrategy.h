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
 * @file CmdArgVerboseStrategy.h
 * @date 2020
 *
 *************************************************************************************************/

#ifndef CMDARGVERBOSESTRATEGY_H_B2A8C38D_7DA1_4B38_9D16_B317EBF164A5
#define CMDARGVERBOSESTRATEGY_H_B2A8C38D_7DA1_4B38_9D16_B317EBF164A5

#include <ICmdArgWorkflowStrategy.h>

namespace cxlog
{
    class ILogger;
}

namespace cx
{

/*********************************************************************************************//**
 * @brief Workflow for when the @c --verbose command line argument is passed.
 *
 ************************************************************************************************/
class CmdArgVerboseStrategy : public ICmdArgWorkflowStrategy
{

public:

    /******************************************************************************************//**
     * @brief Constructor.
     *
     * @param argc Command line argument count.
     * @param argv A C-style array of arguments.
     * @param p_model The Connect X compatible model.
     * @param p_logger A chain logger.
     *
     ********************************************************************************************/
    CmdArgVerboseStrategy(int argc, char *argv[], cxmodel::IModel& p_model, cxlog::ILogger* p_logger);

    int Handle() override;


private:

    int m_argc;
    char **m_argv;
    cxmodel::IModel& m_model;
    cxlog::ILogger* m_logger;

};

} // namespace cx

#endif // CMDARGVERBOSESTRATEGY_H_B2A8C38D_7DA1_4B38_9D16_B317EBF164A5
