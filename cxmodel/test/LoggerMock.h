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
 * @file LoggerMock.cpp
 * @date 2020
 *
 *************************************************************************************************/

#include <cxlog/include/ILogger.h>

class LoggerMock : public cxlog::ILogger
{
    void Log(const cxlog::VerbosityLevel p_verbosityLevel, const std::string& p_fileName, const std::string& p_functionName, const size_t p_lineNumber, const std::string& p_message) override;
    void SetVerbosityLevel(const cxlog::VerbosityLevel p_verbosityLevel) override;
    cxlog::VerbosityLevel GetVerbosityLevel() const override;
};
