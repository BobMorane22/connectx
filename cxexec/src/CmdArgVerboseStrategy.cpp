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
 * @file CmdArgVerboseStrategy.cpp
 * @date 2020
 *
 *************************************************************************************************/

#include <type_traits>

#include <cxinv/include/assertion.h>
#include <cxlog/include/CSVMessageFormatter.h>
#include <cxlog/include/StdLogTarget.h>
#include <cxlog/include/IChainLogging.h>
#include <cxlog/include/IncrementalChainedLogger.h>
#include <cxlog/include/ISO8601TimestampFormatter.h>

#include <CmdArgMainStrategy.h>
#include <CmdArgVerboseStrategy.h>

/******************************************************************************************//**
 * @brief Creates a logger for the standard output.
 *
 * @post The logger is not @c nullptr
 *
 * @param p_verbosity The logger's verbosity level.
 *
 * @return The newly created logger.
 *
 ********************************************************************************************/
std::unique_ptr<cxlog::ILogger> CreateVerboseLogger(cxlog::VerbosityLevel p_verbosity)
{
    std::unique_ptr<cxlog::ITimestampFormatter> timestampFormatter = std::make_unique<cxlog::ISO8601TimestampFormatter>(cxlog::TimePrecision::MILLISECONDS);
    std::unique_ptr<cxlog::ILogTarget> logTarget = std::make_unique<cxlog::StdLogTarget>();
    std::unique_ptr<cxlog::IMessageFormatter> formatter = std::make_unique<cxlog::CSVMessageFormatter>(std::move(timestampFormatter));
    std::unique_ptr<cxlog::ILogger> logger = std::make_unique<cxlog::IncrementalChainedLogger>(std::move(formatter), std::move(logTarget));

    logger->SetVerbosityLevel(p_verbosity);

    POSTCONDITION(logger != nullptr);

    return std::move(logger);
}

cx::CmdArgVerboseStrategy::CmdArgVerboseStrategy(int argc, char *argv[], cxmodel::IModel& p_model, cxlog::ILogger* p_logger)
 : m_argc{argc}
 , m_argv{argv}
 , m_model{p_model}
 , m_logger{p_logger}
{
    PRECONDITION(p_logger != nullptr);
}

int cx::CmdArgVerboseStrategy::Handle()
{
    if(!ASSERT(m_logger))
    {
        return EXIT_FAILURE;
    }

    cxlog::IChainLogging* chainLogger = dynamic_cast<cxlog::IChainLogging*>(m_logger);

    // Should never happen if the code compiles (see static_asset above):
    if(!ASSERT(chainLogger))
    {
        return EXIT_FAILURE;
    }

    const cxlog::VerbosityLevel verbosityLevel = m_logger->GetVerbosityLevel();
    chainLogger->SetSucessor(CreateVerboseLogger(verbosityLevel));

    ASSERT_MSG(chainLogger->HasSucessor(), "Setting a logger successor failed.");

    // Now that the verbose logger is set, we go on with the standard execution:
    cx::CmdArgMainStrategy mainStrategy{m_argc, m_argv, m_model};

    return mainStrategy.Handle();
}
