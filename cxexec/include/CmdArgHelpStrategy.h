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
 * @file CmdArgHelpStrategy.h
 * @date 2019
 *
 *************************************************************************************************/

#ifndef CMDARGHELPSTRATEGY_H_3362D6BD_3ADC_4D59_9E62_1B7E12B40C48
#define CMDARGHELPSTRATEGY_H_3362D6BD_3ADC_4D59_9E62_1B7E12B40C48

#include "ICmdArgWorkflowStrategy.h"

namespace cx
{

/*********************************************************************************************//**
 * @brief Workflow for the @c --help command line argument.
 *
 ************************************************************************************************/
class CmdArgHelpStrategy : public ICmdArgWorkflowStrategy
{

public:

    int Handle() override;

};

} // namespace cx

#endif // CMDARGHELPSTRATEGY_H_3362D6BD_3ADC_4D59_9E62_1B7E12B40C48
