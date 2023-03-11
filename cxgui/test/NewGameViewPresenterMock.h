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
#include <cxgui/INewGameViewPresenter.h>

/*********************************************************************************************//**
 * @brief Base class for creating New Game View presenter mocks.
 *        
 * When creating new mocks for the New Game View presenter, inheriting from this class makes
 * it possible to only override the necessary members.
 *
 ************************************************************************************************/
class NewGameViewPresenterMock : public cxgui::INewGameViewPresenter
{

public:

    [[nodiscard]] std::string GetNewGameViewTitle() const override
    {
        throw cxunit::NotImplementedException();
    }

    [[nodiscard]] std::string GetNewGameViewGameSectionTitle() const override
    {
        throw cxunit::NotImplementedException();
    }

    [[nodiscard]] std::string GetNewGameViewInARowLabelText() const override
    {
        throw cxunit::NotImplementedException();
    }

    [[nodiscard]] std::string GetNewGameViewBoardSectionTitle() const override
    {
        throw cxunit::NotImplementedException();
    }

    [[nodiscard]] std::string GetNewGameViewWidthLabelText() const override
    {
        throw cxunit::NotImplementedException();
    }

    [[nodiscard]] std::string GetNewGameViewHeightLabelText() const override
    {
        throw cxunit::NotImplementedException();
    }

    [[nodiscard]] std::string GetNewGameViewPlayersSectionTitle() const override
    {
        throw cxunit::NotImplementedException();
    }

    [[nodiscard]] std::string GetNewGameViewNameColumnHeaderText() const override
    {
        throw cxunit::NotImplementedException();
    }

    [[nodiscard]] std::string GetNewGameViewDiscColumnHeaderText() const override
    {
        throw cxunit::NotImplementedException();
    }

    [[nodiscard]] std::string GetNewGameViewIsManagedColumnHeaderText() const override
    {
        throw cxunit::NotImplementedException();
    }

    [[nodiscard]] std::string GetNewGameViewRemovePlayerButtonText() const override
    {
        throw cxunit::NotImplementedException();
    }

    [[nodiscard]] bool CanRemoveAnotherPlayer(std::size_t /*p_currentNumberOfPlayers*/) const override
    {
        throw cxunit::NotImplementedException();
    }

    [[nodiscard]] std::string GetNewGameViewAddPlayerButtonText() const override
    {
        throw cxunit::NotImplementedException();
    }

    [[nodiscard]] bool CanAddAnotherPlayer(std::size_t /*p_currentNumberOfPlayers*/) const override
    {
        throw cxunit::NotImplementedException();
    }

    [[nodiscard]] std::string GetNewGameViewStartButtonText() const override
    {
        throw cxunit::NotImplementedException();
    }

    [[nodiscard]] size_t GetNewGameViewMinInARowValue() const override
    {
        throw cxunit::NotImplementedException();
    }

    [[nodiscard]] size_t GetNewGameViewMaxInARowValue() const override
    {
        throw cxunit::NotImplementedException();
    }

    [[nodiscard]] size_t GetNewGameViewMinBoardWidthValue() const override
    {
        throw cxunit::NotImplementedException();
    }

    [[nodiscard]] size_t GetNewGameViewMaxBoardWidthValue() const override
    {
        throw cxunit::NotImplementedException();
    }

    [[nodiscard]] size_t GetNewGameViewMinBoardHeightValue() const override
    {
        throw cxunit::NotImplementedException();
    }

    [[nodiscard]] size_t GetNewGameViewMaxBoardHeightValue() const override
    {
        throw cxunit::NotImplementedException();
    }

    [[nodiscard]] size_t GetDefaultInARowValue() const override
    {
        throw cxunit::NotImplementedException();
    }

    [[nodiscard]] size_t GetDefaultBoardHeightValue() const override
    {
        throw cxunit::NotImplementedException();
    }

    [[nodiscard]] size_t GetDefaultBoardWidthValue() const override
    {
        throw cxunit::NotImplementedException();
    }

    [[nodiscard]] cxmodel::Status IsInARowValueValid(size_t /*p_inARowValue*/) const override
    {
        throw cxunit::NotImplementedException();
    }

    [[nodiscard]] cxmodel::Status AreBoardDimensionsValid(size_t /*p_boardHeight*/, size_t /*p_boardWidth*/) const override
    {
        throw cxunit::NotImplementedException();
    }

    [[nodiscard]] cxmodel::Status ArePlayerNamesValid(const std::vector<std::string>& /*p_playerNames*/) const override
    {
        throw cxunit::NotImplementedException();
    }

    [[nodiscard]] cxmodel::Status ArePlayerChipColorsValid(const std::vector<cxmodel::ChipColor>& /*p_playerChipColors*/) const override
    {
        throw cxunit::NotImplementedException();
    }

    [[nodiscard]] cxmodel::Status ArePlayerTypesValid(const std::vector<cxmodel::PlayerType>& /*p_playerTypes*/) const override
    {
        throw cxunit::NotImplementedException();
    }

    [[nodiscard]] cxmodel::Status IsNewGameWinnable(size_t /*p_inARowValue*/, size_t /*p_nbOfPlayers*/, size_t /*p_boardHeight*/, size_t /*p_boardWidth*/) const override
    {
        throw cxunit::NotImplementedException();
    }

};


#endif // NEWGAMEVIEWPRESENTERMOCK_H_9363FAA4_AF6E_49B2_9EE3_53BC34ED3E56
