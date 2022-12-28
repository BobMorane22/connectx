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
 * @file MainWindowController.h
 * @date 2019
 *
 *************************************************************************************************/

#ifndef MAINWINDOWCONTROLLER_H_2377676C_13C5_4D43_8AFA_0C90ABC44C5C
#define MAINWINDOWCONTROLLER_H_2377676C_13C5_4D43_8AFA_0C90ABC44C5C

#include <cxmodel/IChip.h>

#include "IMainWindowController.h"

namespace cxmodel
{
    class IConnectXGameActions;
    class IUndoRedo;
}

namespace cxgui
{

/**********************************************************************************************//**
 * @brief Main window controller.
 *
 *************************************************************************************************/
class MainWindowController : public cxgui::IMainWindowController
{

public:

    /******************************************************************************************//**
     * @brief Constructor.
     *
     * @param p_modelAsGameActions
     *      The model (user interactions with the game).
     * @param p_modelAsUndoRedo
     *      The model (undo and redo game actions).
     *
     *********************************************************************************************/
    MainWindowController(cxmodel::IConnectXGameActions& p_modelAsGameActions,
                         cxmodel::IUndoRedo& p_modelAsUndoRedo);

///@{ @name New Game View
// ------------------------------------------------------------------------------------------------

    void OnStart(const cxmodel::NewGameInformation p_gameInformation) override;

///@}

///@{ @name Game View
// ------------------------------------------------------------------------------------------------

    void OnDown(const cxmodel::ChipColor& p_chipColor, size_t p_column) override;
    void OnMoveLeftOneColumn() override;
    void OnMoveRightOneColumn() override;
    void OnNewGame() override;
    void OnReinitializeCurrentGame() override;
    void OnUndo() override;
    void OnRedo() override;

///@}

private:

    cxmodel::IConnectXGameActions& m_modelAsGameActions;
    cxmodel::IUndoRedo& m_modelAsUndoRedo;

    std::unique_ptr<cxmodel::IChip> m_currentChip;
};

} // namespace cxgui

#endif // MAINWINDOWCONTROLLER_H_2377676C_13C5_4D43_8AFA_0C90ABC44C5C
