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

#include <sstream>

#include <cxinv/include/assertion.h>
#include <cxmodel/include/Disc.h>
#include <cxmodel/include/NewGameInformation.h>
#include <cxmodel/include/IConnectXGameInformation.h>
#include <cxmodel/include/IConnectXLimits.h>

#include <MainWindowPresenter.h>

namespace
{

} // namespace

cxgui::MainWindowPresenter::MainWindowPresenter(const cxmodel::IConnectXLimits& p_modealAsLimits)
 : m_modelAsLimits{p_modealAsLimits}
 , m_activePlayerChipColor{cxmodel::MakeTransparent()}
 , m_nextPlayerChipColor{cxmodel::MakeTransparent()}
{
}

void cxgui::MainWindowPresenter::Update(cxmodel::NotificationContext p_context, cxmodel::Subject* p_subject)
{
    if(p_subject)
    {
        if(p_context == cxmodel::NotificationContext::CREATE_NEW_GAME)
        {
            cxmodel::IConnectXGameInformation* model = dynamic_cast<cxmodel::IConnectXGameInformation*>(p_subject);

            std::ostringstream stream;

            stream << "A new game has been created with the following parameters: " << std::endl
                   << std::endl
                   << "  In-a-row value : " << model->GetCurrentInARowValue() << std::endl
                   << "  Grid width     : " << model->GetCurrentGridWidth() << std::endl
                   << "  Grid height    : " << model->GetCurrentGridHeight() << std::endl
                   << "  Players        : " << std::endl
                   << "    Active       : " << model->GetActivePlayer().GetName() << std::endl
                   << "    Next         : " << model->GetNextPlayer().GetName() << std::endl;

            m_gameViewMessage = stream.str();

            m_activePlayerChipColor = model->GetActivePlayer().GetChip().GetColor();
            m_nextPlayerChipColor = model->GetNextPlayer().GetChip().GetColor();
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

std::string cxgui::MainWindowPresenter::GetNewGameViewGridSectionTitle() const
{
    return "Grid";
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
    return m_activePlayerChipColor;
}

cxmodel::ChipColor cxgui::MainWindowPresenter::GetNextPlayerChipColor() const
{
    return m_nextPlayerChipColor;
}
