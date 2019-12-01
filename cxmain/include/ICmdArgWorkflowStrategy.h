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
 * @file ICmdArgWorkflowStrategy.h
 * @date 2019
 *
 *************************************************************************************************/

#ifndef ICMDARGWORKFLOWSTRATEGY_H_22B11697_3758_4728_939D_3709D3F9C64E
#define ICMDARGWORKFLOWSTRATEGY_H_22B11697_3758_4728_939D_3709D3F9C64E

namespace cx
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
class ICmdArgWorkflowStrategy
{

public:

    virtual ~ICmdArgWorkflowStrategy() = default;

    virtual int Handle() = 0;

private:

};

} // namespace cx

#endif // ICMDARGWORKFLOWSTRATEGY_H_22B11697_3758_4728_939D_3709D3F9C64E
