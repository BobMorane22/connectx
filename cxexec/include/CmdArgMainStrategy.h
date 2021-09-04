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
 * @file CmdArgMainStrategy.h
 * @date 2019
 *
 *************************************************************************************************/

#ifndef CMDARGMAINSTRATEGY_H_687BF302_DBF1_4EB7_B096_8DD7B233614A
#define CMDARGMAINSTRATEGY_H_687BF302_DBF1_4EB7_B096_8DD7B233614A

#include <cxmodel/include/ModelNotificationContext.h>

#include "GtkmmUIManager.h"
#include "ICmdArgWorkflowStrategy.h"

namespace cxmodel
{
    class IConnectXGameActions;
    class IConnectXGameInformation;
    class IConnectXLimits;
    class IUndoRedo;
}

namespace cx
{

/*********************************************************************************************//**
 * @brief Main application workflow. This represents when the standard application logic is ran.
 *
 * @invariant The UI manager is not @c nullptr.
 *
 ************************************************************************************************/
class CmdArgMainStrategy : public ICmdArgWorkflowStrategy
{

public:

    /******************************************************************************************//**
     * @brief Constructor.
     *
     * @pre The argument count is at least 1.
     * @pre The argument list is not @c nullptr.
     *
     * @post m_uiMgr is not @c nullptr
     *
     * @param argc                     Command line argument count.
     * @param argv                     A C-style array of arguments.
     * @param p_modelAsSubject         The Connect X compatible model (Subject).
     * @param p_modelAsGameActions     The Connect X compatible model (Game actions).
     * @param p_modelAsGameInformation The Connect X compatible model (Game information).
     * @param p_modelAsLimits          The Connect X compatible model (Limits).
     * @param p_modelAsUndoRedo        The Connect X compatible model (Undo/redo).
     *
     ********************************************************************************************/
    CmdArgMainStrategy(int argc,
                       char *argv[],
                       cxmodel::ModelSubject& p_modelAsSubject,
                       cxmodel::IConnectXGameActions& p_modelAsGameActions,
                       cxmodel::IConnectXGameInformation& p_modelAsGameInformation,
                       cxmodel::IConnectXLimits& p_modelAsLimits,
                       cxmodel::IUndoRedo& p_modelAsUndoRedo);

    int Handle() override;


private:

    std::unique_ptr<cx::IUIManager> m_uiMgr;

};

} // namespace cx

#endif // CMDARGMAINSTRATEGY_H_687BF302_DBF1_4EB7_B096_8DD7B233614A
