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
 * @file FileLogTarget.h
 * @date 2020
 *
 *************************************************************************************************/

#ifndef FILELOGTARGET_H_880DA1BC_C2BA_42A2_B1D8_EA6172C15CC0
#define FILELOGTARGET_H_880DA1BC_C2BA_42A2_B1D8_EA6172C15CC0

#include <fstream>

#include "ILogTarget.h"

namespace cxlog
{

/***********************************************************************************************//**
 * @brief File log target.
 *
 **************************************************************************************************/
class FileLogTarget : public ILogTarget
{

public:

    /*******************************************************************************************//**
     * Constructor.
     *
     * @param p_logFileName The name (i.e. full path) of the file to log to.
     *
     **********************************************************************************************/
    FileLogTarget(const std::string& p_logFileName);

    /*******************************************************************************************//**
     * @brief Log a message.
     *
     * Send a textual message to the log target for logging. After a call to this, the message
     * should be in the hand of the target.
     *
     * @param p_message The message to log.
     *
     **********************************************************************************************/
    void Log(const std::string& p_message) override;


private:

    std::ofstream& FileStream() {return m_fileStream;};

    std::ofstream m_fileStream;
};

} // namespace cxlog

#endif // FILELOGTARGET_H_880DA1BC_C2BA_42A2_B1D8_EA6172C15CC0
