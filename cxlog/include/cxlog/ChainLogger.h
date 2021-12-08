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
 * @file ChainLogger.h
 * @date 2020
 *
 * Logger using a chain of responsibility to forward its logging information to another logger.
 *
 *************************************************************************************************/

#ifndef CHAINLOGGER_H_AD94F91A_A9BF_4E77_B948_66F0DB32DD91
#define CHAINLOGGER_H_AD94F91A_A9BF_4E77_B948_66F0DB32DD91

#include "IChainLogging.h"
#include "Logger.h"


namespace cxlog
{

/***********************************************************************************************//**
 * Logger using a chain of responsability to forward its logging information to another
 * logger.
 *
 **************************************************************************************************/
class ChainLogger : public Logger,
                    public IChainLogging
{

public:

    /*******************************************************************************************//**
     * @brief Logs an entry.
     *
     * Logs an entry using the information injected as parameters.
     *
     * @param p_verbosityLevel The message verbosity level.
     * @param p_fileName       The source file in which the logging occured.
     * @param p_functionName   The function name in which the logging occured.
     * @param p_lineNumber     The line number in the source file where the logging occured.
     * @param p_message        The message to log.
     *
     **********************************************************************************************/
    void Log(const VerbosityLevel p_verbosityLevel,
             const std::string&   p_fileName,
             const std::string&   p_functionName,
             const size_t         p_lineNumber,
             const std::string&   p_message) override = 0;

    /*******************************************************************************************//**
     * @brief Set which logger (if any) will log the message after the current logger.
     *
     * @param p_sucessor The sucessor logger.
     *
     **********************************************************************************************/
    void SetSucessor(std::unique_ptr<ILogger>&& p_sucessor) override;

    /*******************************************************************************************//**
     * @brief Indicates wether the current logger has a sucessor.
     *
     * @return @c true if the current logger has a sucessor, @c false otherwise.
     *
     **********************************************************************************************/
    bool HasSucessor() const override;


protected:

    std::unique_ptr<ILogger> m_successor;


private:

    VerbosityLevel m_verbosityLevel{VerbosityLevel::NONE};
};

} // namespace cxlog

#endif // CHAINLOGGER_H_AD94F91A_A9BF_4E77_B948_66F0DB32DD91
