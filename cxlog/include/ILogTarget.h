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
 * @file ILogTarget.h
 * @date 2020
 *
 *************************************************************************************************/

#ifndef ILOGTARGET_H_0453E7CF_945A_428B_9979_55AE34F85946
#define ILOGTARGET_H_0453E7CF_945A_428B_9979_55AE34F85946

#include <string>

namespace cxlog
{

/***********************************************************************************************//**
 * @brief Logging target.
 *
 * Specifies a common interface that every target for a logger (file, standard output, network,
 * etc) must share.
 *
 **************************************************************************************************/
class ILogTarget
{

public:

    /*******************************************************************************************//**
     * @brief Default destructor.
     *
     **********************************************************************************************/
    virtual ~ILogTarget() = default;

    /*******************************************************************************************//**
     * @brief Log a message.
     *
     * Send a textual message to the log target for logging. After a call to this, the message
     * should be in the hand of the target.
     *
     * @param p_message The message to log.
     *
     **********************************************************************************************/
    virtual void Log(const std::string& p_message) = 0;

};

} // namespace cxlog

#endif // ILOGTARGET_H_0453E7CF_945A_428B_9979_55AE34F85946
