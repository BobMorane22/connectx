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
 * @file AnimatedBoardPresenter.cpp
 * @date 2021
 *
 *************************************************************************************************/

#include <cxgui/AnimatedBoardPresenter.h>

cxgui::AnimatedBoardPresenter::AnimatedBoardPresenter(const IGameViewPresenter& p_presenter)
: m_gameVewPresenter{p_presenter}
{
    Sync();
}

void cxgui::AnimatedBoardPresenter::Sync()
{
    m_cache.m_boardHeight = cxmodel::Height{m_gameVewPresenter.GetGameViewBoardHeight()};
    m_cache.m_boardWidth = cxmodel::Width{m_gameVewPresenter.GetGameViewBoardWidth()};
    m_cache.m_activePlayerChipColor = m_gameVewPresenter.GetGameViewActivePlayerChipColor();
    m_cache.m_boardColors = m_gameVewPresenter.GetGameViewChipColors();
}

cxmodel::Height cxgui::AnimatedBoardPresenter::GetBoardHeight() const
{
    return m_cache.m_boardHeight;
}

cxmodel::Width cxgui::AnimatedBoardPresenter::GetBoardWidth() const
{
    return m_cache.m_boardWidth;
}

cxmodel::ChipColor cxgui::AnimatedBoardPresenter::GetActivePlayerChipColor() const
{
    return m_cache.m_activePlayerChipColor;
}

const cxgui::IGameViewPresenter::ChipColors& cxgui::AnimatedBoardPresenter::GetBoardChipColors() const
{
    return m_cache.m_boardColors;
}

cxmodel::Column cxgui::AnimatedBoardPresenter::GetBotTarget() const
{
    // TG-262 : link to the model...
    return cxmodel::Column{5u};
}
