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
 * @file NewGameViewPresenterMock.h
 * @date 2023
 *
 *************************************************************************************************/

#ifndef NEWGAMEVIEWPRESENTERMOCK_H_9363FAA4_AF6E_49B2_9EE3_53BC34ED3E56
#define NEWGAMEVIEWPRESENTERMOCK_H_9363FAA4_AF6E_49B2_9EE3_53BC34ED3E56

#include <cxunit/NotImplementedException.h>
#include <cxui/INewGameViewPresenter.h>

/*********************************************************************************************//**
 * @brief Base class for creating New Game View presenter mocks.
 *        
 * When creating new mocks for the New Game View presenter, inheriting from this class makes
 * it possible to only override the necessary members.
 *
 ************************************************************************************************/
class NewGameViewPresenterMock : public cx::ui::cmn::INewGameViewPresenter
{

public:

    [[nodiscard]] std::string GetNewGameViewTitle() const override
    {
        throw cx::unit::NotImplementedException();
    }

    [[nodiscard]] std::string GetNewGameViewGameSectionTitle() const override
    {
        throw cx::unit::NotImplementedException();
    }

    [[nodiscard]] std::string GetNewGameViewInARowLabelText() const override
    {
        throw cx::unit::NotImplementedException();
    }

    [[nodiscard]] std::string GetNewGameViewBoardSectionTitle() const override
    {
        throw cx::unit::NotImplementedException();
    }

    [[nodiscard]] std::string GetNewGameViewWidthLabelText() const override
    {
        throw cx::unit::NotImplementedException();
    }

    [[nodiscard]] std::string GetNewGameViewHeightLabelText() const override
    {
        throw cx::unit::NotImplementedException();
    }

    [[nodiscard]] std::string GetNewGameViewPlayersSectionTitle() const override
    {
        throw cx::unit::NotImplementedException();
    }

    [[nodiscard]] std::string GetNewGameViewNameColumnHeaderText() const override
    {
        throw cx::unit::NotImplementedException();
    }

    [[nodiscard]] std::string GetNewGameViewDiscColumnHeaderText() const override
    {
        throw cx::unit::NotImplementedException();
    }

    [[nodiscard]] std::string GetNewGameViewIsManagedColumnHeaderText() const override
    {
        throw cx::unit::NotImplementedException();
    }

    [[nodiscard]] std::string GetNewGameViewRemovePlayerButtonText() const override
    {
        throw cx::unit::NotImplementedException();
    }

    [[nodiscard]] bool CanRemoveAnotherPlayer(std::size_t /*p_currentNumberOfPlayers*/) const override
    {
        throw cx::unit::NotImplementedException();
    }

    [[nodiscard]] std::string GetNewGameViewAddPlayerButtonText() const override
    {
        throw cx::unit::NotImplementedException();
    }

    [[nodiscard]] bool CanAddAnotherPlayer(std::size_t /*p_currentNumberOfPlayers*/) const override
    {
        throw cx::unit::NotImplementedException();
    }

    [[nodiscard]] std::string GetNewGameViewStartButtonText() const override
    {
        throw cx::unit::NotImplementedException();
    }

    [[nodiscard]] size_t GetNewGameViewMinInARowValue() const override
    {
        throw cx::unit::NotImplementedException();
    }

    [[nodiscard]] size_t GetNewGameViewMaxInARowValue() const override
    {
        throw cx::unit::NotImplementedException();
    }

    [[nodiscard]] size_t GetNewGameViewMinBoardWidthValue() const override
    {
        throw cx::unit::NotImplementedException();
    }

    [[nodiscard]] size_t GetNewGameViewMaxBoardWidthValue() const override
    {
        throw cx::unit::NotImplementedException();
    }

    [[nodiscard]] size_t GetNewGameViewMinBoardHeightValue() const override
    {
        throw cx::unit::NotImplementedException();
    }

    [[nodiscard]] size_t GetNewGameViewMaxBoardHeightValue() const override
    {
        throw cx::unit::NotImplementedException();
    }

    [[nodiscard]] size_t GetDefaultInARowValue() const override
    {
        throw cx::unit::NotImplementedException();
    }

    [[nodiscard]] size_t GetDefaultBoardHeightValue() const override
    {
        throw cx::unit::NotImplementedException();
    }

    [[nodiscard]] size_t GetDefaultBoardWidthValue() const override
    {
        throw cx::unit::NotImplementedException();
    }

    [[nodiscard]] std::string GetDefaultPlayerName(size_t /*p_playerIndex*/) const override
    {
        throw cx::unit::NotImplementedException();
    }

    [[nodiscard]] cx::model::ChipColor GetDefaultChipColor(size_t /*p_playerIndex*/) const override
    {
        throw cx::unit::NotImplementedException();
    }

    [[nodiscard]] std::vector<cx::model::ChipColor> GetDefaultChipColors() const override
    {
        throw cx::unit::NotImplementedException();
    }

    [[nodiscard]] cx::model::PlayerType GetDefaultPlayerType(size_t /*p_playerIndex*/) const override
    {
        throw cx::unit::NotImplementedException();
    }

    [[nodiscard]] cx::model::Status IsInARowValueValid(size_t /*p_inARowValue*/) const override
    {
        throw cx::unit::NotImplementedException();
    }

    [[nodiscard]] cx::model::Status AreBoardDimensionsValid(size_t /*p_boardHeight*/, size_t /*p_boardWidth*/) const override
    {
        throw cx::unit::NotImplementedException();
    }

    [[nodiscard]] cx::model::Status ArePlayerNamesValid(const std::vector<std::string>& /*p_playerNames*/) const override
    {
        throw cx::unit::NotImplementedException();
    }

    [[nodiscard]] cx::model::Status ArePlayerChipColorsValid(const std::vector<cx::model::ChipColor>& /*p_playerChipColors*/) const override
    {
        throw cx::unit::NotImplementedException();
    }

    [[nodiscard]] cx::model::Status ArePlayerTypesValid(const std::vector<cx::model::PlayerType>& /*p_playerTypes*/) const override
    {
        throw cx::unit::NotImplementedException();
    }

    [[nodiscard]] cx::model::Status IsNewGameWinnable(size_t /*p_inARowValue*/, size_t /*p_nbOfPlayers*/, size_t /*p_boardHeight*/, size_t /*p_boardWidth*/) const override
    {
        throw cx::unit::NotImplementedException();
    }

};


#endif // NEWGAMEVIEWPRESENTERMOCK_H_9363FAA4_AF6E_49B2_9EE3_53BC34ED3E56
