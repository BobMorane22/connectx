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
     * @brief Remove player button text accessor.
     *
     * @return Remove player button text.
     *
     ********************************************************************************************/
    virtual std::string GetNewGameViewRemovePlayerButtonText() const = 0;

    /******************************************************************************************//**
     * @brief Indicates if, according to the current number of players, another one can be removed.
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
     * @brief Get a message explaining that numerical values were expected for in-a-row
     *        or board dimension values.
     *
     * @return The message.
     *
     ********************************************************************************************/
    virtual std::string GetNumericalValuesExpectedMessage() const = 0;

    /******************************************************************************************//**
     * @brief Get a message explaining that numerical values are out of range (i.e they fall out
     *        of the range of the converted-to type) for in-a-row or board dimension values.
     *
     * @return The message.
     *
     ********************************************************************************************/
    virtual std::string GetNumericalValuesOutOfRangeMessage() const = 0;

    /******************************************************************************************//**
     * @brief Gets a message explaining that the input for the in-a-row value is not valid. For
     *        the input to be valid, it must fall between the model limits.
     *
     * @return The message.
     *
     ********************************************************************************************/
    virtual std::string GetInARowInvalidInputMessage() const = 0;

    /******************************************************************************************//**
     * @brief Gets a message explaining that the input for the board dimension values is not
     *        valid.
     *
     * @return The message.
     *
     ********************************************************************************************/
    virtual std::string GetBoardDimensionsInvalidInputMessage() const = 0;

    /******************************************************************************************//**
     * @brief Gets a message explaining that the player information supplied by the is not
     *        valid.
     *
     * @return The message.
     *
     ********************************************************************************************/
    virtual std::string GetPlayersInformationInvalidInputMessage() const = 0;

    /******************************************************************************************//**
     * @brief Checks if the in-a-row value is valid.
     *
     * @param p_inARowValue The in-a-row value to check.
     *
     * @return `true` if the value is valid, `false` otherwise.
     *
     ********************************************************************************************/
    virtual bool IsInARowValueValid(size_t p_inARowValue) const = 0;

    /******************************************************************************************//**
     * @brief Checks if the board dimensions passed as arguments are valid.
     *
     * @param p_boardHeight The board height value to check.
     * @param p_boardWidth  The board width value to check.
     *
     * @note Upon returning `false`, a message can be retrieved by calling the
     *       GetBoardDimensionsInvalidInputMessage function immediately after.
     *       If both values are invalid, the message will only contain the first
     *       value to have failed the check.
     *
     * @return `true` if both height and width are valid, `false` otherwise.
     *
     ********************************************************************************************/
    virtual bool AreBoardDimensionsValid(size_t p_boardHeight, size_t p_boardWidth) = 0;

    /******************************************************************************************//**
     * @brief Checks if the player information passed as arguments are valid.
     *
     * @param p_playerNames A list of player names.
     * @param p_chipColors  A list of chip colors.
     *
     * @note Upon returning `false`, a message can be retrieved by calling the
     *       GetPlayersInformationInvalidInputMessage function immediately after. If
     *       both values are invalid, the message will only contain the first value
     *       to have failed the check.
     *
     * @return `true` if both player names and chip colors are valid, `false` otherwise.
     *
     ********************************************************************************************/
    virtual bool ArePlayersInformationValid(const std::vector<std::string>& p_playerNames,
                                            const std::vector<cxmodel::ChipColor>& p_chipColors) = 0;

};

}

#endif // INEWVIEWPRESENTER_H_8159479B_ECAB_4CD5_9CC6_B818FCBC26C8
