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
 * @file IVersionning.h
 * @date 2020
 *
 *************************************************************************************************/

#ifndef IVERSIONNING_H_776139B1_BE1B_4469_95F0_2DE9A0E4C816
#define IVERSIONNING_H_776139B1_BE1B_4469_95F0_2DE9A0E4C816

#include <string>

namespace cxmodel
{

/*********************************************************************************************//**
 * @brief Interface for versioning an API.
 *
 ************************************************************************************************/
class IVersionning
{

public:

    /******************************************************************************************//**
     * @brief Destructor.
     *
     ********************************************************************************************/
    virtual ~IVersionning() = default;

    /******************************************************************************************//**
     * @brief Get the API name.
     *
     ********************************************************************************************/
    virtual std::string GetName() const = 0;

    /******************************************************************************************//**
     * @brief Get the API version number, formatted as a string.
     *
     ********************************************************************************************/
    virtual std::string GetVersionNumber() const = 0;

};

} // namespace cxmodel

#endif // IVERSIONNING_H_776139B1_BE1B_4469_95F0_2DE9A0E4C816
