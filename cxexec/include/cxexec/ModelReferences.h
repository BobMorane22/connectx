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
 * @file ModelReferences.h
 * @date 2022
 *
 *************************************************************************************************/
 
#ifndef MODELREFERENCES_H_B4CBAD24_EFCC_429A_8293_DAE7B2FA8D9E
#define MODELREFERENCES_H_B4CBAD24_EFCC_429A_8293_DAE7B2FA8D9E

#include <cxmodel/Model.h>

namespace cx
{

/**********************************************************************************************//**
 * @brief Holds different abstract references to the Connect X model.
 *
 * The goal of this structure is to remove the need for huge parameters lists when constructing
 * the application.
 *
 *************************************************************************************************/
struct ModelReferences
{

public:

   /******************************************************************************************//**
    * @brief Constructor.
    *
    * A structure holding all necessary abstract references to some concrete model.
    *
    * @param p_concreteModel
    *      A concrete, Connect X compatible, model.
    *
    ********************************************************************************************/
    ModelReferences(cxmodel::ModelSubject& p_asSubject,
                    cxmodel::IConnectXGameActions& p_asGameActions,
                    cxmodel::IConnectXGameInformation& p_asGameInformation,
                    cxmodel::IConnectXLimits& p_asLimits,
                    cxmodel::IVersioning& p_asVersionning,
                    cxmodel::IUndoRedo& p_asUndoRedo)
    : m_asSubject{p_asSubject}
    , m_asGameActions{p_asGameActions}
    , m_asGameInformation{p_asGameInformation}
    , m_asLimits{p_asLimits}
    , m_asVersionning{p_asVersionning}
    , m_asUndoRedo{p_asUndoRedo}
    {
        // Nothing to do...
    }

    cxmodel::ModelSubject& m_asSubject;
    cxmodel::IConnectXGameActions& m_asGameActions;
    cxmodel::IConnectXGameInformation& m_asGameInformation;
    cxmodel::IConnectXLimits& m_asLimits;
    cxmodel::IVersioning& m_asVersionning;
    cxmodel::IUndoRedo& m_asUndoRedo;

};

} // namespace cx

#endif // MODELREFERENCES_H_B4CBAD24_EFCC_429A_8293_DAE7B2FA8D9E
