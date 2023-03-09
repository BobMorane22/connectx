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
 * @file INewGameViewPresenter.cpp
 * @date 2023
 *
 *************************************************************************************************/

#include <vector>

#include <cxstd/helpers.h>
#include <cxmodel/ChipColor.h>
#include <cxmodel/IChip.h>
#include <cxmodel/IPlayer.h>
#include <cxmodel/NewGameInformation.h>
#include <cxgui/INewGameViewPresenter.h>


cxmodel::Status cxgui::Validate(const cxmodel::NewGameInformation& p_gameInformation, const cxgui::INewGameViewPresenter& p_presenter)
{
    const auto inARowInputStatus = p_presenter.IsInARowValueValid(p_gameInformation.m_inARowValue);
    RETURN_IF(!inARowInputStatus.IsSuccess(), inARowInputStatus);

    const auto boardDimensionInputStatus = p_presenter.AreBoardDimensionsValid(p_gameInformation.m_gridHeight, p_gameInformation.m_gridWidth);
    RETURN_IF(!boardDimensionInputStatus.IsSuccess(), boardDimensionInputStatus);

    std::vector<std::string> playerNames;
    for(const auto player : p_gameInformation.m_players)
    {
        playerNames.push_back(player->GetName());
    }
    const auto playerNamesInputStatus = p_presenter.ArePlayerNamesValid(playerNames);
    RETURN_IF(!playerNamesInputStatus.IsSuccess(), playerNamesInputStatus);

    std::vector<cxmodel::ChipColor> playerChipColors;
    for(const auto player : p_gameInformation.m_players)
    {
        playerChipColors.push_back(player->GetChip().GetColor());
    }
    const auto playerChipColorsInputStatus = p_presenter.ArePlayerChipColorsValid(playerChipColors);
    RETURN_IF(!playerChipColorsInputStatus.IsSuccess(), playerChipColorsInputStatus);

    std::vector<cxmodel::PlayerType> playerTypes;
    for(const auto player : p_gameInformation.m_players)
    {
        playerTypes.push_back(player->IsManaged() ? cxmodel::PlayerType::BOT : cxmodel::PlayerType::HUMAN );
    }
    const auto playerTypesInputStatus = p_presenter.ArePlayerTypesValid(playerTypes);
    RETURN_IF(!playerTypesInputStatus.IsSuccess(), playerTypesInputStatus);

    const auto newGameIsWinnableStatus = p_presenter.IsNewGameWinnable(p_gameInformation.m_inARowValue,
                                                                       playerNames.size(),
                                                                       p_gameInformation.m_gridHeight,
                                                                       p_gameInformation.m_gridWidth);

    RETURN_IF(!newGameIsWinnableStatus.IsSuccess(), newGameIsWinnableStatus);

    return cxmodel::MakeSuccess();
}
