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
 * @file IMainWindowPresenter.h
 * @date 2019
 *
 *************************************************************************************************/

#ifndef IMAINWINDOWPRESENTER_H_D8C76920_83D9_4D15_B95A_63282E742221
#define IMAINWINDOWPRESENTER_H_D8C76920_83D9_4D15_B95A_63282E742221

#include <cxmodel/ModelNotificationContext.h>

#include "IGameViewPresenter.h"
#include "INewGameViewPresenter.h"
#include "MenuItem.h"

namespace cxgui
{

/*********************************************************************************************//**
 * @brief Interface for creating a main window presenter.
 *
 * The main window presenter is responsible for making sure the UI logic is up to date, in
 * a UI framework independent fashion. This makes it possible to create a main window with
 * minimal logic.
 *
 * @note Because the class inherits the cxmodel::Subject class, which is an abstract class,
 *       this class is not a pure interface. It is named as if it were a pure interface
 *       because conceptually, it acts like one as far as the presenter is concerned.
 *
 ************************************************************************************************/
class IMainWindowPresenter : public cxmodel::IModelObserver,
                             public cxmodel::ModelSubject,
                             public IGameViewPresenter,
                             public INewGameViewPresenter
{

public:

///@{ @name Main Window
// -----------------------------------------------------------------------------------------------

    /******************************************************************************************//**
     * @brief Main window title accessor.
     *
     * @return The main window title.
     *
     ********************************************************************************************/
    virtual std::string GetWindowTitle() const = 0;

    /******************************************************************************************//**
     * @brief Menu item label accessor.
     *
     * @param p_menuItem The item to get the label of.
     *
     * @return The label for the given item.
     *
     ********************************************************************************************/
    virtual std::string GetMenuLabel(MenuItem p_menuItem) const = 0;

    /******************************************************************************************//**
     * @brief Indicates if a new game request is possible.
     *
     * @return `true` if the new game request is possible, `false` otherwise.
     *
     ********************************************************************************************/
    virtual bool IsNewGamePossible() const = 0;

    /******************************************************************************************//**
     * @brief Indicates if the current game (if any) can be reinitialized.
     *
     * @return `true` if the current game can be reinitialized, `false` otherwise. If there is
     *         no current game, `false` is returned.
     *
     ********************************************************************************************/
    virtual bool IsCurrentGameReinitializationPossible() const = 0;

    /******************************************************************************************//**
     * @brief Indicates if undoing is possible.
     *
     * @return `true` if undoing is possible, `false` otherwise.
     *
     ********************************************************************************************/
    virtual bool IsUndoPossible() const = 0;

    /******************************************************************************************//**
     * @brief Indicates if redoing is possible.
     *
     * @return `true` if redoing is possible, `false` otherwise.
     *
     ********************************************************************************************/
    virtual bool IsRedoPossible() const = 0;

///@}

///@{ @name New Game View
// -----------------------------------------------------------------------------------------------
    std::string GetNewGameViewTitle() const override = 0;

    std::string GetNewGameViewGameSectionTitle() const override = 0;
    std::string GetNewGameViewInARowLabelText() const override = 0;

    std::string GetNewGameViewBoardSectionTitle() const override = 0;
    std::string GetNewGameViewWidthLabelText() const override = 0;
    std::string GetNewGameViewHeightLabelText() const override = 0;

    std::string GetNewGameViewPlayersSectionTitle() const override = 0;
    std::string GetNewGameViewNameColumnHeaderText() const override = 0;
    std::string GetNewGameViewDiscColumnHeaderText() const override = 0;
    std::string GetNewGameViewStartButtonText() const override = 0;

    size_t GetNewGameViewMinInARowValue() const override = 0;
    size_t GetNewGameViewMaxInARowValue() const override = 0;
    size_t GetNewGameViewMinBoardWidthValue() const override = 0;
    size_t GetNewGameViewMaxBoardWidthValue() const override = 0;
    size_t GetNewGameViewMinBoardHeightValue() const override = 0;
    size_t GetNewGameViewMaxBoardHeightValue() const override = 0;

    cxmodel::Status IsInARowValueValid(size_t p_inARowValue) const override = 0;
    cxmodel::Status AreBoardDimensionsValid(size_t p_boardHeight, size_t p_boardWidth) const override = 0;
    cxmodel::Status ArePlayersInformationValid(const std::vector<std::string>& p_playerNames,
                                               const std::vector<cxmodel::ChipColor>& p_chipColors) const override = 0;

    cxmodel::Status ArePlayerNamesValid(const std::vector<std::string>& p_playerNames) const override = 0;
    cxmodel::Status ArePlayerChipColorsValid(const std::vector<cxmodel::ChipColor>& p_playerChipColors) const override = 0;
    cxmodel::Status ArePlayerTypesValid(const std::vector<cxmodel::PlayerType>& p_playerTypes) const override = 0;

    cxmodel::Status IsNewGameWinnable(size_t p_inARowValue,
                                      size_t p_nbOfPlayers,
                                      size_t p_boardHeight,
                                      size_t p_boardWidth) const override = 0;

///@}

///@{ @name Game View
// -----------------------------------------------------------------------------------------------
    std::string GetGameViewTitle() const override = 0;

    cxmodel::ChipColor GetGameViewActivePlayerChipColor() const override = 0;
    cxmodel::ChipColor GetGameViewNextPlayerChipColor() const override = 0;

    std::string GetGameViewActivePlayerLabelText() const override = 0;
    std::string GetGameViewNextPlayerLabelText() const override = 0;

    std::string GetGameViewActivePlayerName() const override = 0;
    std::string GetGameViewNextPlayerName() const override = 0;

    size_t GetGameViewBoardWidth() const override = 0;
    size_t GetGameViewBoardHeight() const override = 0;

    const ChipColors& GetGameViewChipColors() const override = 0;

///@}

};

} // namespace cxgui

#endif // IMAINWINDOWPRESENTER_H_D8C76920_83D9_4D15_B95A_63282E742221
