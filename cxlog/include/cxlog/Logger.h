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
 * @file Logger.h
 * @date 2020
 *
 *************************************************************************************************/

#ifndef LOGGER_H_A906454D_E729_4DBF_85EB_2EB1BCD186AE
#define LOGGER_H_A906454D_E729_4DBF_85EB_2EB1BCD186AE


#include <memory>

#include "ILogger.h"

namespace cxlog
{

/***********************************************************************************************//**
 * @brief A basic logger.
 *
 **************************************************************************************************/
class Logger : public ILogger
{

public:

    /*******************************************************************************************//**
     * @brief Logs an entry.
     *
     * Logs an entry using the information injected as parameters.
     *
     * @param p_verbosityLevel
     *      The message verbosity level.
     * @param p_fileName
     *      The source file in which the logging occurred.
     * @param p_functionName
     *      The function name in which the logging occurred.
     * @param p_lineNumber
     *      The line number in the source file where the logging occurred.
     * @param p_message
     *      The message to log.
     *
     **********************************************************************************************/
    void Log( const VerbosityLevel p_verbosityLevel,
              const std::string&   p_fileName,
              const std::string&   p_functionName,
              const size_t         p_lineNumber,
              const std::string&   p_message ) override = 0;

    /*******************************************************************************************//**
     * @brief Mutates the logger general verbosity level.
     *
     * @param p_verbosityLevel
     *      The new logger-wide verbosity level.
     *
     *********************************************************************************************/
    void SetVerbosityLevel(const VerbosityLevel p_verbosityLevel) override;

    /*******************************************************************************************//**
     * @brief Indicates the logger general verbosity level.
     *
     * @return
     *      The verbosity level.
     *
     *********************************************************************************************/
    VerbosityLevel GetVerbosityLevel() const override;

private:

    VerbosityLevel m_verbosityLevel{VerbosityLevel::NONE};
};

} // namespace cxlog

#endif // LOGGER_H_A906454D_E729_4DBF_85EB_2EB1BCD186AE
