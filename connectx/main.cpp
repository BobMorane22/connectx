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
 * @file main.cpp
 * @date 2019
 *
 *************************************************************************************************/

#include <memory>

#include <cxinv/assertion.h>
#include <cxlog/CSVMessageFormatter.h>
#include <cxlog/FileLogTarget.h>
#include <cxlog/IncrementalChainedLogger.h>
#include <cxlog/ISO8601TimestampFormatter.h>
#include <cxmodel/CommandStack.h>
#include <cxmodel/Model.h>
#include <cxexec/Application.h>

constexpr size_t CMD_STACK_SIZE = 200;

/******************************************************************************************//**
 * @brief Creates a logger that logs to a file.
 *
 * @post The logger is not @c nullptr
 *
 * @param p_verbosity The logger's verbosity level.
 *
 * @return The newly created logger.
 *
 ********************************************************************************************/
std::unique_ptr<cxlog::ILogger> CreateFileLogger(cxlog::VerbosityLevel p_verbosity)
{
    std::unique_ptr<cxlog::ITimestampFormatter> timestampFormatter = std::make_unique<cxlog::ISO8601TimestampFormatter>(cxlog::TimePrecision::MILLISECONDS);
    std::unique_ptr<cxlog::ILogTarget> logTarget = std::make_unique<cxlog::FileLogTarget>("connectx.log");
    std::unique_ptr<cxlog::IMessageFormatter> formatter = std::make_unique<cxlog::CSVMessageFormatter>(std::move(timestampFormatter));
    std::unique_ptr<cxlog::ILogger> logger = std::make_unique<cxlog::IncrementalChainedLogger>(std::move(formatter), std::move(logTarget), true);

    IF_CONDITION_NOT_MET_DO(logger, return nullptr;);

    logger->SetVerbosityLevel(p_verbosity);

    POSTCONDITION(logger);

    return logger;
}

int main(int argc, char *argv[])
{
    int result = EXIT_FAILURE;

    try
    {
        std::unique_ptr<cxlog::ILogger> logger = CreateFileLogger(cxlog::VerbosityLevel::DEBUG);

        if(!logger)
        {
            return EXIT_FAILURE;
        }

        cxmodel::Model concreteModel{std::make_unique<cxmodel::CommandStack>(CMD_STACK_SIZE), *logger};
        cxmodel::ModelSubject& modelAsSubject = concreteModel;
        cxmodel::IConnectXGameActions& modelAsGameActions = concreteModel;
        cxmodel::IConnectXGameInformation& modelAsGameInformation = concreteModel;
        cxmodel::IConnectXLimits& modelAsLimits = concreteModel;
        cxmodel::IVersioning& modelAsVersionning = concreteModel;
        cxmodel::IUndoRedo& modelAsUndoRedo = concreteModel;

        std::unique_ptr<cx::IApplication> app = std::make_unique<cx::Application>(argc,
                                                                                  argv,
                                                                                  modelAsSubject,
                                                                                  modelAsGameActions,
                                                                                  modelAsGameInformation,
                                                                                  modelAsLimits,
                                                                                  modelAsVersionning,
                                                                                  modelAsUndoRedo,
                                                                                  *logger);

        result = app->Run();
    }
    catch(const std::exception& p_exception)
    {
        ASSERT_ERROR_MSG(p_exception.what());
    }
    catch(...)
    {
        ASSERT_ERROR_MSG("Unhandled exception.");
    }

    return result;
}
