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
 * @file INewGameViewPresenter.h
 * @date 2020
 *
 *************************************************************************************************/

#ifndef INEWVIEWPRESENTER_H_8159479B_ECAB_4CD5_9CC6_B818FCBC26C8
#define INEWVIEWPRESENTER_H_8159479B_ECAB_4CD5_9CC6_B818FCBC26C8

#include <string>

#include <cxmodel/Status.h>

namespace cxmodel
{

class NewGameInformation;

}

namespace cxgui
{

/*********************************************************************************************//**
 * @brief Presenter for the 'New Game' view.
 *
 ************************************************************************************************/
class INewGameViewPresenter
{

public:

    /******************************************************************************************//**
     * @brief Destructor.
     *
     ********************************************************************************************/
    virtual ~INewGameViewPresenter() = default;

    /******************************************************************************************//**
     * @brief New Game view title accessor.
     *
     * @return The New Game view title.
     *
     ********************************************************************************************/
    virtual std::string GetNewGameViewTitle() const = 0;

    /******************************************************************************************//**
     * @brief Game section title accessor.
     *
     * @return The Game section title.
     *
     ********************************************************************************************/
    virtual std::string GetNewGameViewGameSectionTitle() const = 0;

    /******************************************************************************************//**
     * @brief In-a-row label accessor.
     *
     * @return the in-a-row label text.
     *
     ********************************************************************************************/
    virtual std::string GetNewGameViewInARowLabelText() const = 0;

    /******************************************************************************************//**
     * @brief Board section title accessor.
     *
     * @return The board section title.
     *
     ********************************************************************************************/
    virtual std::string GetNewGameViewBoardSectionTitle() const = 0;

    /******************************************************************************************//**
     * @brief Width label accessor.
     *
     * @return The Width label text.
     *
     ********************************************************************************************/
    virtual std::string GetNewGameViewWidthLabelText() const = 0;

    /******************************************************************************************//**
     * @brief Height label accessor.
     *
     * @return The height label text.
     *
     ********************************************************************************************/
    virtual std::string GetNewGameViewHeightLabelText() const = 0;

    /******************************************************************************************//**
     * @brief Players section title accessor.
     *
     * @return The Players section title.
     *
     ********************************************************************************************/
    virtual std::string GetNewGameViewPlayersSectionTitle() const = 0;

    /******************************************************************************************//**
     * @brief Name column header text accessor.
     *
     * @return The Name column header text.
     *
     ********************************************************************************************/
    virtual std::string GetNewGameViewNameColumnHeaderText() const = 0;

    /******************************************************************************************//**
     * @brief Disc column header text accessor.
     *
     * @return The Disc column header text.
     *
     ********************************************************************************************/
    virtual std::string GetNewGameViewDiscColumnHeaderText() const = 0;

    /******************************************************************************************//**
     * @brief Player management column header text accessor.
     *
     * @return The player management column header text.
     *
     ********************************************************************************************/
    virtual std::string GetNewGameViewIsManagedColumnHeaderText() const = 0;

    /******************************************************************************************//**
     * @brief Remove player button text accessor.
     *
     * @return Remove player button text.
     *
     ********************************************************************************************/
    virtual std::string GetNewGameViewRemovePlayerButtonText() const = 0;

    /******************************************************************************************//**
     * @brief Indicates if, according to the current number of players, another one can be removed.
     *
     * @param p_currentNumberOfPlayers The current number of players in the game.
     *
     * @return `true` if another player can be removed, `false` otherwise.
     *
     ********************************************************************************************/
    virtual bool CanRemoveAnotherPlayer(std::size_t p_currentNumberOfPlayers) const = 0;

    /******************************************************************************************//**
     * @brief Add player button text accessor.
     *
     * @return Add player button text.
     *
     ********************************************************************************************/
    virtual std::string GetNewGameViewAddPlayerButtonText() const = 0;

    /******************************************************************************************//**
     * @brief Indicates if, according to the current number of players, another one can be added.
     *
     * @param p_currentNumberOfPlayers The current number of players in the game.
     *
     * @return `true` if another player can be added, `false` otherwise.
     *
     ********************************************************************************************/
    virtual bool CanAddAnotherPlayer(std::size_t p_currentNumberOfPlayers) const = 0;

    /******************************************************************************************//**
     * @brief Start button text accessor.
     *
     * @return Start button text.
     *
     ********************************************************************************************/
    virtual std::string GetNewGameViewStartButtonText() const = 0;

    /******************************************************************************************//**
     * @brief Minimum in-a-row value accessor.
     *
     * @return The minimum in-a-row value.
     *
     ********************************************************************************************/
    virtual size_t GetNewGameViewMinInARowValue() const = 0;

    /******************************************************************************************//**
     * @brief Maximum in-a-row value accessor.
     *
     * @return The maximum in-a-row value.
     *
     ********************************************************************************************/
    virtual size_t GetNewGameViewMaxInARowValue() const = 0;

    /******************************************************************************************//**
     * @brief Minimum board width value accessor.
     *
     * @return The minimum board width value.
     *
     ********************************************************************************************/
    virtual size_t GetNewGameViewMinBoardWidthValue() const = 0;

    /******************************************************************************************//**
     * @brief Maximum board width value accessor.
     *
     * @return The maximum board width value.
     *
     ********************************************************************************************/
    virtual size_t GetNewGameViewMaxBoardWidthValue() const = 0;

    /******************************************************************************************//**
     * @brief Minimum board height value accessor.
     *
     * @return The minimum board height value.
     *
     ********************************************************************************************/
    virtual size_t GetNewGameViewMinBoardHeightValue() const = 0;

    /******************************************************************************************//**
     * @brief Maximum board height value accessor.
     *
     * @return The maximum board height value.
     *
     ********************************************************************************************/
    virtual size_t GetNewGameViewMaxBoardHeightValue() const = 0;

    /******************************************************************************************//**
     * @brief Default in-a-row value accessor.
     *
     * This is the value that will be suggested to the user in the view.
     *
     * @return The default in-a-row value.
     *
     ********************************************************************************************/
    [[nodiscard]] virtual size_t GetDefaultInARowValue() const  = 0;

    /******************************************************************************************//**
     * @brief Default board height value accessor.
     *
     * This is the value that will be suggested to the user in the view.
     *
     * @return The default board height value.
     *
     ********************************************************************************************/
    [[nodiscard]] virtual size_t GetDefaultBoardHeightValue() const  = 0;

    /******************************************************************************************//**
     * @brief Default board width value accessor.
     *
     * This is the value that will be suggested to the user in the view.
     *
     * @return The default board width value.
     *
     ********************************************************************************************/
    [[nodiscard]] virtual size_t GetDefaultBoardWidthValue() const  = 0;

    /******************************************************************************************//**
     * @brief Checks if the in-a-row value is valid.
     *
     * @param p_inARowValue The in-a-row value to check.
     *
     * @return `Success` if the value is valid, `Error` otherwise.
     *
     ********************************************************************************************/
    virtual cxmodel::Status IsInARowValueValid(size_t p_inARowValue) const = 0;

    /******************************************************************************************//**
     * @brief Checks if the board dimensions passed as arguments are valid.
     *
     * @param p_boardHeight The board height value to check.
     * @param p_boardWidth  The board width value to check.
     *
     * @return `Success` if both height and width are valid, `Error` otherwise.
     *
     ********************************************************************************************/
    virtual cxmodel::Status AreBoardDimensionsValid(size_t p_boardHeight, size_t p_boardWidth) const = 0;

    /******************************************************************************************//**
     * @brief Checks if the player names passed as arguments are valid.
     *
     * @param p_playerNames A list of player names.
     *
     * @return `Success` if the list of player names is valid, `Error` otherwise.
     *
     ********************************************************************************************/
    virtual cxmodel::Status ArePlayerNamesValid(const std::vector<std::string>& p_playerNames) const = 0;

    /******************************************************************************************//**
     * @brief Checks if the player chip colors passed as arguments are valid.
     *
     * @param p_playerChipColors A list of player chip colors.
     *
     * @return `Success` if the list of player chip colors is valid, `Error` otherwise.
     *
     ********************************************************************************************/
    virtual cxmodel::Status ArePlayerChipColorsValid(const std::vector<cxmodel::ChipColor>& p_playerChipColors) const = 0;

    /******************************************************************************************//**
     * @brief Checks if the player types passed as arguments are valid.
     *
     * @param p_playerTypes A list of player types.
     *
     * @return `Success` if the list of player types is valid, `Error` otherwise.
     *
     ********************************************************************************************/
    virtual cxmodel::Status ArePlayerTypesValid(const std::vector<cxmodel::PlayerType>& p_playerTypes) const = 0;

    /******************************************************************************************//**
     * @brief Checks if the new game created by the user is winnable (i.e. do the parameters
     *        make it possible for the game to be winnable).
     *
     * @param p_inARowValue The in-a-row value for the new game.
     * @param p_nbOfPlayers Then number of players for the new game.
     * @param p_boardHeight The board height for the new game.
     * @param p_boardWidth  The board width for the new game.
     *
     * @return `Success` if the game is winnable, `Error` otherwise.
     *
     ********************************************************************************************/
    virtual cxmodel::Status IsNewGameWinnable(size_t p_inARowValue,
                                              size_t p_nbOfPlayers,
                                              size_t p_boardHeight,
                                              size_t p_boardWidth) const = 0;
};

/*********************************************************************************************//**
 * @brief Validates new game information.
 *
 * @param p_gameInformation
 *      The new game information to validate.
 *
 * @param p_presenter
 *      A New Game View compatible presenter.
 *
 * @return A status instance, indicating if the new game information is valid.
 *
 ************************************************************************************************/
[[nodiscard]] cxmodel::Status Validate(const cxmodel::NewGameInformation& p_gameInformation,
                                       const cxgui::INewGameViewPresenter& p_presenter);


}

#endif // INEWVIEWPRESENTER_H_8159479B_ECAB_4CD5_9CC6_B818FCBC26C8
