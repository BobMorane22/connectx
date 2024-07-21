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

#include <cxinv/assertion.h>
#include <cxlog/CSVMessageFormatter.h>
#include <cxlog/StdLogTarget.h>
#include <cxlog/IChainLogging.h>
#include <cxlog/IncrementalChainedLogger.h>
#include <cxlog/ISO8601TimestampFormatter.h>
#include <cxexec/CmdArgMainStrategy.h>
#include <cxexec/CmdArgVerboseStrategy.h>
#include <cxexec/IUIManager.h>

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
std::unique_ptr<cx::log::ILogger> CreateVerboseLogger(cx::log::VerbosityLevel p_verbosity)
{
    std::unique_ptr<cx::log::ITimestampFormatter> timestampFormatter = std::make_unique<cx::log::ISO8601TimestampFormatter>(cx::log::TimePrecision::MILLISECONDS);
    std::unique_ptr<cx::log::ILogTarget> logTarget = std::make_unique<cx::log::StdLogTarget>();
    std::unique_ptr<cx::log::IMessageFormatter> formatter = std::make_unique<cx::log::CSVMessageFormatter>(std::move(timestampFormatter));
    std::unique_ptr<cx::log::ILogger> logger = std::make_unique<cx::log::IncrementalChainedLogger>(std::move(formatter), std::move(logTarget));

    logger->SetVerbosityLevel(p_verbosity);

    POSTCONDITION(logger);

    return logger;
}

cx::CmdArgVerboseStrategy::CmdArgVerboseStrategy(int argc, char *argv[], cx::ModelReferences& p_model, cx::log::ILogger* p_logger)
: m_argc{argc}
, m_argv{argv}
, m_model{p_model}
, m_logger{p_logger}
{
    PRECONDITION(p_logger);
}

int cx::CmdArgVerboseStrategy::Handle()
{
    IF_CONDITION_NOT_MET_DO(m_logger, return EXIT_FAILURE;);

    cx::log::IChainLogging* chainLogger = dynamic_cast<cx::log::IChainLogging*>(m_logger);

    // Should never happen if the code compiles (see static_asset above):
    IF_CONDITION_NOT_MET_DO(chainLogger, return EXIT_FAILURE;);

    const cx::log::VerbosityLevel verbosityLevel = m_logger->GetVerbosityLevel();
    chainLogger->SetSucessor(CreateVerboseLogger(verbosityLevel));

    ASSERT_MSG(chainLogger->HasSucessor(), "Setting a logger successor failed.");

    // Now that the verbose logger is set, we go on with the standard execution:
    cx::CmdArgMainStrategy mainStrategy{m_argc, m_argv, m_model};

    return mainStrategy.Handle();
}
