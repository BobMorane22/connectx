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
 * @file AnimatedBoardPresenterMock.cpp
 * @date 2022
 *
 *************************************************************************************************/

#include "AnimatedBoardPresenterMock.h"

AnimatedBoardPresenterMock::AnimatedBoardPresenterMock()
{
    ResetBoard();
}

void AnimatedBoardPresenterMock::Sync()
{
    m_syncCalled = true;
}

cxmodel::Height AnimatedBoardPresenterMock::GetBoardHeight() const
{
    return m_boardHeight;
}

cxmodel::Width AnimatedBoardPresenterMock::GetBoardWidth() const
{
    return m_boardWidth;
}

cxmodel::ChipColor AnimatedBoardPresenterMock::GetActivePlayerChipColor() const
{
    return cxmodel::MakeTransparent();
}

const cxgui::IGameViewPresenter::ChipColors& AnimatedBoardPresenterMock::GetBoardChipColors() const
{
    return m_chipColors;
}

cxmodel::Column AnimatedBoardPresenterMock::GetBotTarget() const
{
    return m_lastBotTarget;
}

void AnimatedBoardPresenterMock::SetBoardDimensions(const cxmodel::Height& p_nbRows, const cxmodel::Width& p_nbColumns)
{
    m_boardHeight = p_nbRows;
    m_boardWidth = p_nbColumns;

    ResetBoard();
}

void AnimatedBoardPresenterMock::SetLastBotTarget(const cxmodel::Column& p_lastBotTarget)
{
    m_lastBotTarget = p_lastBotTarget;
}

void AnimatedBoardPresenterMock::AddChipsToColumn(const cxmodel::Column& p_column, size_t p_nbOfChipsToAdd)
{
    size_t chipsDropped = 0u;
    for(int row = m_boardHeight.Get() - 1; row >= 0; --row)
    {
        if(chipsDropped < p_nbOfChipsToAdd)
        {
            m_chipColors[row][p_column.Get()] = cxmodel::MakeRed();
            ++chipsDropped;
        }
        else
        {
            return;
        }
    }
}

void AnimatedBoardPresenterMock::ResetBoard()
{
    for(size_t row = 0u; row < m_boardHeight.Get(); ++row)
    {
        m_chipColors.push_back(std::vector<cxmodel::ChipColor>());

        for(size_t column = 0u; column < m_boardWidth.Get(); ++column)
        {
            m_chipColors[row].push_back(cxmodel::MakeTransparent());
        }
    }
}
