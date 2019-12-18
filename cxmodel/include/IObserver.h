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
 * @file IObserver.h
 * @date 2019
 *
 *************************************************************************************************/

#ifndef IOBSERVER_H_CB32427D_3430_41D8_BE7A_992F2D139BB2
#define IOBSERVER_H_CB32427D_3430_41D8_BE7A_992F2D139BB2

namespace cxmodel
{
    class Subject;
}

namespace cxmodel
{

/*********************************************************************************************//**
 * @brief DESCRIPTION
 *
 * @invariant
 * @invariant
 *
 * DESCRIPTION
 *
 ************************************************************************************************/
class IObserver
{

public:

    /******************************************************************************************//**
     * @brief DESCRIPTION
     *
     * @pre
     * @post
     *
     * @param
     * @param
     *
     * @return
     *
     * DESCRIPTION
     *
     ********************************************************************************************/
    virtual ~IObserver() = default;

    /******************************************************************************************//**
     * @brief DESCRIPTION
     *
     * @pre
     * @post
     *
     * @param
     * @param
     *
     * @return
     *
     * DESCRIPTION
     *
     ********************************************************************************************/
    virtual void Update(Subject* p_subject) = 0;

};

} // namespace cxmodel

#endif // IOBSERVER_H_CB32427D_3430_41D8_BE7A_992F2D139BB2
