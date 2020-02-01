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
 * @file StdLogTarget.h
 * @date 2020
 *
 * Standard output log target.
 *
 *************************************************************************************************/

#ifndef STDLOGTARGET_H_CC558CE5_FDFE_4E88_AFDB_6B33BD234DC8
#define STDLOGTARGET_H_CC558CE5_FDFE_4E88_AFDB_6B33BD234DC8

#include <iostream>

#include "ILogTarget.h"

namespace cxlog
{

/***********************************************************************************************//**
 * @brief Standard output logging target.
 *
 * Use this logging target if you want to log to the standard output.
 *
 **************************************************************************************************/
class StdLogTarget : public ILogTarget
{

public:

    /*******************************************************************************************//**
     * @brief Log a message to the standard output.
     *
     * Send a textual message to the standard output for logging.
     *
     * @param p_message The message to log.
     *
     **********************************************************************************************/
    void Log(const std::string& p_message) override;


private:

    std::ostream& StdStream() const {return *m_stdStream;};

    std::ostream* m_stdStream{&std::cout};
};

} // namespace cxlog

#endif // STDLOGTARGET_H_CC558CE5_FDFE_4E88_AFDB_6B33BD234DC8
