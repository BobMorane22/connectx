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
 * @file StringStreamLogTarget.h
 * @date 2020
 *
 * String stream log target. With this target, you can log to a string.
 *
 *************************************************************************************************/

#ifndef STRINGSTREAMLOGTARGET_H_B2ACB60F_9F38_4973_BDF5_1EF2B9ED12A3
#define STRINGSTREAMLOGTARGET_H_B2ACB60F_9F38_4973_BDF5_1EF2B9ED12A3

#include <sstream>

#include "ILogTarget.h"

namespace cxlog
{

/***********************************************************************************************//**
 * @brief String stream logging target.
 *
 * Use this logging target if you want to log to a string stream (and ultimately to a string).
 *
 **************************************************************************************************/
class StringStreamLogTarget : public ILogTarget
{

public:

    /*******************************************************************************************//**
     * @brief Constructor.
     *
     * @param p_stringStream The string stream to log to.
     *
     **********************************************************************************************/
    StringStreamLogTarget(std::ostringstream& p_stringStream);

    /*******************************************************************************************//**
     * @brief Log a message to the string stream.
     *
     * Send a textual message to the string stream for logging.
     *
     * @param p_message The message to log.
     *
     **********************************************************************************************/
    void Log(const std::string& p_message) override;


private:

    std::ostringstream& StringStream() const {return m_stringStream;};

    std::ostringstream& m_stringStream;
};

} // namespace cxlog

#endif // STRINGSTREAMLOGTARGET_H_B2ACB60F_9F38_4973_BDF5_1EF2B9ED12A3
