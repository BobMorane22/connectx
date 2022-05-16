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
 * @file Application.h
 * @date 2019
 *
 *************************************************************************************************/

#ifndef APPLICATION_H_3ED6B0E2_2A03_4F6C_AB0C_632A2F6E855D
#define APPLICATION_H_3ED6B0E2_2A03_4F6C_AB0C_632A2F6E855D

#include <memory>

#include <cxmodel/ModelNotificationContext.h>

#include "IApplication.h"
#include "ICmdArgWorkflowStrategy.h"

namespace cxlog
{
    class ILogger;
}

namespace cx
{
    struct ModelReferences;
}

namespace cx
{

/*********************************************************************************************//**
 * @brief Connect X application.
 *
 * @invariant The command line argument workflow is not @c nullptr.
 *
 ************************************************************************************************/
class Application : public IApplication
{

public:

    /******************************************************************************************//**
     * @brief Constructor.
     *
     * @param argc
     *      Command line argument count.
     * @param argv
     *      A C-style array of arguments.
     * @param p_model
     *      References to a Connect X compatible model.
     * @param p_logger
     *      A chain logger.
     *
     * @pre
     *      The argument count is at least 1.
     * @pre
     *      The argument list is not @c nullptr.
     * @post
     *      The command line argument workflow is not @c nullptr.
     *
     ********************************************************************************************/
    Application(int argc, char *argv[], cx::ModelReferences& p_model, cxlog::ILogger& p_logger);

    int Run() override;


private:

    std::unique_ptr<ICmdArgWorkflowStrategy> m_workflow;

};

} // namespace cx

#endif // APPLICATION_H_3ED6B0E2_2A03_4F6C_AB0C_632A2F6E855D
