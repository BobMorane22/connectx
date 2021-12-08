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
 * @file Status.h
 * @date 2020
 *
 *************************************************************************************************/

#ifndef STATUS_H_E80A96D0_7F2D_4F3D_8AAB_2B059BA8D895
#define STATUS_H_E80A96D0_7F2D_4F3D_8AAB_2B059BA8D895

#include <string>

/******************************************************************************************//**
 * @brief Perform an action when a result is an error.
 *
 * @param p_status The status to check.
 * @param p_action The action to perform.
 *
 ********************************************************************************************/
#define ON_ERROR(p_status, p_action) if(!p_status.IsSuccess()) \
                                     {                         \
                                         p_action;             \
                                     }                         \
                                     void(0)                   \

namespace cxmodel
{

/*********************************************************************************************//**
 * @brief Status of an operation
 *
 * @invariant A success status never has an attached error message, while an error status always
 *            has an error message attached.
 *
 * Describes the status (outcome) of an operation. An operation can have two outcome: either is
 * has succeeded, or it has failed. In the same way, an object of type Status can have two state:
 * either a success, or an error. In the case where it is an error, an error message is attached
 * to the status, hopefully supplying interesting details on the error and/or its context.
 *
 ************************************************************************************************/
class Status final
{

public:

    /******************************************************************************************//**
     * @brief indicates if the status is a success.
     *
     * @return `true` if the status is a success, `false` otherwise.
     *
     ********************************************************************************************/
    [[nodiscard]] bool IsSuccess() const;

    /******************************************************************************************//**
     * @brief Retrieves the error message associated with the status (if any).
     *
     * @pre The status is an error.
     *
     * @return The error message associated with the status. If the status message is a success,
     *         no error message is associated with it and an empty message is returned.
     *
     ********************************************************************************************/
    [[nodiscard]] const std::string& GetMessage() const;

    friend Status MakeSuccess();
    friend Status MakeError(const std::string& p_errorMessage);

private:

    void CheckInvariants();

    Status();
    explicit Status(const std::string& p_errorMessage);

    bool m_status;
    std::string m_errorMessage;

};

/******************************************************************************************//**
 * @brief Creates a success status.
 *
 * @return The success status.
 *
 ********************************************************************************************/
[[nodiscard]] Status MakeSuccess();

/******************************************************************************************//**
 * @brief Creates an error status.
 *
 * @pre The error message passed as an argument is not empty.
 *
 * @param p_errorMessage The error message to associate with the status.
 *
 * @return The error status.
 *
 ********************************************************************************************/
[[nodiscard]] Status MakeError(const std::string& p_errorMessage);

} // namespace cxmodel

#endif // STATUS_H_E80A96D0_7F2D_4F3D_8AAB_2B059BA8D895
