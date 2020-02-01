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
 * @file IChainLogging.h
 * @date 2020
 *
 * Interface to implement logging as a chain of responsibility.
 *
 *************************************************************************************************/

#ifndef ICHAINLOGGING_H_6EBF284E_68F3_4217_A3CB_C3665E9EA8D5
#define ICHAINLOGGING_H_6EBF284E_68F3_4217_A3CB_C3665E9EA8D5

#include <memory>

#include "ILogger.h"

namespace cxlog
{

/***********************************************************************************************//**
 * @brief Interface to implement logging as a chain of responsibility.
 *
 * It adds the successor concept to a general logger.
 *
 **************************************************************************************************/
class IChainLogging
{

public:

    /*******************************************************************************************//**
     * @brief Default destructor.
     *
     **********************************************************************************************/
    virtual ~IChainLogging() = default;

    /*******************************************************************************************//**
     * @brief Set which logger (if any) will log the message after the current logger.
     *
     * @param p_sucessor The successor logger.
     *
     **********************************************************************************************/
    virtual void SetSucessor(std::unique_ptr<ILogger>&& p_sucessor) = 0;

    /*******************************************************************************************//**
     * @brief Indicates whether the current logger has a successor.
     *
     * @return @c true if the current logger has a successor, @c false otherwise.
     *
     **********************************************************************************************/
    virtual bool HasSucessor() const = 0;

};

} // namespace cxlog

#endif // ICHAINLOGGING_H_6EBF284E_68F3_4217_A3CB_C3665E9EA8D5
