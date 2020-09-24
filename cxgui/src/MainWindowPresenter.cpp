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
 * @file MainWindowPresenter.cpp
 * @date 2019
 *
 *************************************************************************************************/

#include <cxinv/include/assertion.h>
#include <cxmodel/include/Disc.h>
#include <cxmodel/include/NewGameInformation.h>
#include <cxmodel/include/IConnectXGameInformation.h>
#include <cxmodel/include/IConnectXLimits.h>

#include <MainWindowPresenter.h>

namespace
{

const cxmodel::Player NO_PLAYER = {"--", cxmodel::MakeTransparent()};

} // namespace

cxgui::MainWindowPresenter::MainWindowPresenter(const cxmodel::IConnectXLimits& p_modealAsLimits,
                                                const cxmodel::IConnectXGameInformation& p_modelAsGameInformation)
 : m_modelAsLimits{p_modealAsLimits}
 , m_modelAsGameInformation{p_modelAsGameInformation}
 , m_currentBoardWidth{p_modealAsLimits.GetMinimumGridWidth()}
 , m_currentBoardHeight{p_modealAsLimits.GetMinimumGridHeight()}
 , m_activePlayer{NO_PLAYER}
 , m_nextPlayer{NO_PLAYER}
{
}

void cxgui::MainWindowPresenter::Update(cxmodel::NotificationContext p_context, cxmodel::Subject* p_subject)
{
    if(p_subject)
    {
        if(p_context == cxmodel::NotificationContext::CREATE_NEW_GAME)
        {
            m_currentBoardWidth = m_modelAsGameInformation.GetCurrentGridWidth();
            m_currentBoardHeight = m_modelAsGameInformation.GetCurrentGridHeight();

            m_activePlayer = m_modelAsGameInformation.GetActivePlayer();
            m_nextPlayer = m_modelAsGameInformation.GetNextPlayer();
        }

        Notify(p_context);
    }
}

std::string cxgui::MainWindowPresenter::GetWindowTitle() const
{
    return "Connect X";
}

std::string cxgui::MainWindowPresenter::GetMenuLabel(MenuItem p_menuItem) const
{
    return MakeLabel(p_menuItem);
}

std::string cxgui::MainWindowPresenter::GetNewGameViewTitle() const
{
    return "New Game";
}

std::string cxgui::MainWindowPresenter::GetNewGameViewGameSectionTitle() const
{
    return "Game";
}

std::string cxgui::MainWindowPresenter::GetNewGameViewInARowLabelText() const
{
    return "In a row:";
}

std::string cxgui::MainWindowPresenter::GetNewGameViewBoardSectionTitle() const
{
    return "Board";
}

std::string cxgui::MainWindowPresenter::GetNewGameViewWidthLabelText() const
{
    return "Width:";
}

std::string cxgui::MainWindowPresenter::GetNewGameViewHeightLabelText() const
{
    return "Height:";
}

std::string cxgui::MainWindowPresenter::GetNewGameViewPlayersSectionTitle() const
{
    return "Players";
}

std::string cxgui::MainWindowPresenter::GetNewGameViewNameColumnHeaderText() const
{
    return "Name";
}

std::string cxgui::MainWindowPresenter::GetNewGameViewDiscColumnHeaderText() const
{
    return "Disc";
}

std::string cxgui::MainWindowPresenter::GetNewGameViewRemovePlayerButtonText() const
{
    return "Remove player";
}

bool cxgui::MainWindowPresenter::CanRemoveAnotherPlayer(std::size_t p_currentNumberOfPlayers) const
{
    PRECONDITION(p_currentNumberOfPlayers >= m_modelAsLimits.GetMinimumNumberOfPlayers());
    PRECONDITION(p_currentNumberOfPlayers < (m_modelAsLimits.GetMaximumNumberOfPlayers() + 1));

    return p_currentNumberOfPlayers > m_modelAsLimits.GetMinimumNumberOfPlayers();
}

std::string cxgui::MainWindowPresenter::GetNewGameViewAddPlayerButtonText() const
{
    return "Add player";
}

bool cxgui::MainWindowPresenter::CanAddAnotherPlayer(std::size_t p_currentNumberOfPlayers) const
{
    PRECONDITION(p_currentNumberOfPlayers >= m_modelAsLimits.GetMinimumNumberOfPlayers());
    PRECONDITION(p_currentNumberOfPlayers < (m_modelAsLimits.GetMaximumNumberOfPlayers() + 1));

    return p_currentNumberOfPlayers < m_modelAsLimits.GetMaximumNumberOfPlayers();
}

std::string cxgui::MainWindowPresenter::GetNewGameViewStartButtonText() const
{
    return "Start";
}

size_t cxgui::MainWindowPresenter::GetNewGameViewMinInARowValue() const
{
    return m_modelAsLimits.GetMinimumInARowValue();
}

size_t cxgui::MainWindowPresenter::GetNewGameViewMaxInARowValue() const
{
    return m_modelAsLimits.GetMaximumInARowValue();
}

size_t cxgui::MainWindowPresenter::GetNewGameViewMinBoardWidthValue() const
{
    return m_modelAsLimits.GetMinimumGridWidth();
}

size_t cxgui::MainWindowPresenter::GetNewGameViewMaxBoardWidthValue() const
{
    return m_modelAsLimits.GetMaximumGridWidth();
}

size_t cxgui::MainWindowPresenter::GetNewGameViewMinBoardHeightValue() const
{
    return m_modelAsLimits.GetMinimumGridHeight();
}

size_t cxgui::MainWindowPresenter::GetNewGameViewMaxBoardHeightValue() const
{
    return m_modelAsLimits.GetMaximumGridHeight();
}

std::string cxgui::MainWindowPresenter::GetGameViewTitle() const
{
    return "Game";
}

std::string cxgui::MainWindowPresenter::GetGameViewMessage() const
{
    return m_gameViewMessage;
}

cxmodel::ChipColor cxgui::MainWindowPresenter::GetActivePlayerChipColor() const
{
    const cxmodel::IChip& activePlayerChip = m_activePlayer.GetChip();

    return activePlayerChip.GetColor();
}

cxmodel::ChipColor cxgui::MainWindowPresenter::GetNextPlayerChipColor() const
{
    const cxmodel::IChip& nextPlayerChip = m_nextPlayer.GetChip();

    return nextPlayerChip.GetColor();
}

std::string cxgui::MainWindowPresenter::GetActivePlayerLabelText() const
{
    return "  Active player: ";
}

std::string cxgui::MainWindowPresenter::GetNextPlayerLabelText() const
{
    return "  Next player: ";
}

std::string cxgui::MainWindowPresenter::GetActivePlayerName() const
{
    return m_activePlayer.GetName();
}

std::string cxgui::MainWindowPresenter::GetNextPlayerName() const
{
    return m_nextPlayer.GetName();
}

size_t cxgui::MainWindowPresenter::GetBoardWidth() const
{
    return m_currentBoardWidth;
}

size_t cxgui::MainWindowPresenter::GetBoardHeight() const
{
    return m_currentBoardHeight;
}
