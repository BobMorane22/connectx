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
 * @file CmdArgVersionStrategy.h
 * @date 2019
 *
 *************************************************************************************************/

#ifndef CMDARGVERSIONSTRATEGY_H_5A1B3137_4CCC_43BC_B86B_5CFD2649C858
#define CMDARGVERSIONSTRATEGY_H_5A1B3137_4CCC_43BC_B86B_5CFD2649C858

#include <ICmdArgWorkflowStrategy.h>

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
class CmdArgVersionStrategy : public ICmdArgWorkflowStrategy
{

public:

    int Handle() override;

};

} // namespace cx

#endif // CMDARGVERSIONSTRATEGY_H_5A1B3137_4CCC_43BC_B86B_5CFD2649C858
