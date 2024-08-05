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

#include <cxui/AnimatedBoardPresenter.h>

cx::ui::AnimatedBoardPresenter::AnimatedBoardPresenter(const IGameViewPresenter& p_presenter)
: m_gameVewPresenter{p_presenter}
{
    Sync();
}

void cx::ui::AnimatedBoardPresenter::Sync()
{
    m_cache.m_boardHeight = cx::model::Height{m_gameVewPresenter.GetGameViewBoardHeight()};
    m_cache.m_boardWidth = cx::model::Width{m_gameVewPresenter.GetGameViewBoardWidth()};
    m_cache.m_activePlayerChipColor = m_gameVewPresenter.GetGameViewActivePlayerChipColor();
    m_cache.m_boardColors = m_gameVewPresenter.GetGameViewChipColors();
    m_cache.m_botTarget = cx::model::Column{m_gameVewPresenter.GetBotTarget()};
}

cx::model::Height cx::ui::AnimatedBoardPresenter::GetBoardHeight() const
{
    return m_cache.m_boardHeight;
}

cx::model::Width cx::ui::AnimatedBoardPresenter::GetBoardWidth() const
{
    return m_cache.m_boardWidth;
}

cx::ui::cmn::Color cx::ui::AnimatedBoardPresenter::GetGameViewBoardColor() const
{
    return m_gameVewPresenter.GetGameViewBoardColor();
}

cx::ui::cmn::Color cx::ui::AnimatedBoardPresenter::GetGameViewColumnHighlightColor() const
{
    return m_gameVewPresenter.GetGameViewColumnHighlightColor();
}

cx::model::ChipColor cx::ui::AnimatedBoardPresenter::GetActivePlayerChipColor() const
{
    return m_cache.m_activePlayerChipColor;
}

const cx::ui::IGameViewPresenter::ChipColors& cx::ui::AnimatedBoardPresenter::GetBoardChipColors() const
{
    return m_cache.m_boardColors;
}

cx::model::Column cx::ui::AnimatedBoardPresenter::GetBotTarget() const
{
    return m_cache.m_botTarget;
}
