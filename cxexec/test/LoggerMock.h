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
 * @file LoggerMock.h
 * @date 2020
 *
 *************************************************************************************************/

#ifndef LOGGERMOCK_H_D51FFCF0_E2EC_411A_9612_6EB6A529B13A
#define LOGGERMOCK_H_D51FFCF0_E2EC_411A_9612_6EB6A529B13A

#include <cxlog/IChainLogging.h>
#include <cxlog/ILogger.h>

class LoggerMock : public cxlog::ILogger,
                   public cxlog::IChainLogging
{
public:

    ~LoggerMock() override = default;

    // ILogger
    void Log(const cxlog::VerbosityLevel p_verbosityLevel,
             const std::string&   p_fileName,
             const std::string&   p_functionName,
             const size_t         p_lineNumber,
             const std::string&   p_message) override;
    void SetVerbosityLevel(const cxlog::VerbosityLevel p_verbosityLevel) override;
    cxlog::VerbosityLevel GetVerbosityLevel() const override;

    // IChainLogging
    void SetSucessor(std::unique_ptr<ILogger>&& p_sucessor) override;
    bool HasSucessor() const override;
};

#endif // LOGGERMOCK_H_D51FFCF0_E2EC_411A_9612_6EB6A529B13A
