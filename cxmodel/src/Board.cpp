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
 * @file Board.cpp
 * @date 2020
 *
 *************************************************************************************************/

#include <cxinv/include/assertion.h>

#include <Board.h>
#include <Disc.h>

namespace
{

std::unique_ptr<cxmodel::IChip> NoChip()
{
    return std::make_unique<cxmodel::Disc>(cxmodel::Disc::MakeTransparentDisc());
}

} // namespace

cxmodel::Board::Board(size_t p_nbRows,
                      size_t p_nbColumns,
                      const cxmodel::IConnectXLimits& p_modelAsLimits)
: m_nbRows{p_nbRows}
, m_nbColumns{p_nbColumns}
, m_modelAsLimits{p_modelAsLimits}
{
    PRECONDITION(p_nbRows >= p_modelAsLimits.GetMinimumGridHeight());
    PRECONDITION(p_nbRows <= p_modelAsLimits.GetMaximumGridHeight());

    PRECONDITION(p_nbColumns >= p_modelAsLimits.GetMinimumGridWidth());
    PRECONDITION(p_nbColumns <= p_modelAsLimits.GetMaximumGridWidth());

    for(size_t row = 0; row < m_nbRows; ++row)
    {
        std::vector<std::unique_ptr<IChip>> chipRow;
        m_grid.push_back(std::move(chipRow));

        for(size_t column = 0; column < m_nbColumns; ++column)
        {
            m_grid[row].push_back(NoChip());
        }
    }

    CheckInvariants();
}

size_t cxmodel::Board::GetNbColumns() const
{
    return m_nbColumns;
}

size_t cxmodel::Board::GetNbRows() const
{
    return m_nbRows;
}

size_t cxmodel::Board::GetNbPositions() const
{
    return m_nbColumns * m_nbRows;
}

const cxmodel::IChip& cxmodel::Board::GetChip(const Position& p_position) const
{
    PRECONDITION(p_position.m_row    < m_nbRows);
    PRECONDITION(p_position.m_column < m_nbColumns);

    return *m_grid[p_position.m_row][p_position.m_column];
}

bool cxmodel::Board::DropChip(size_t p_column, const cxmodel::IChip& p_disc, Position& p_droppedPosition)
{
    PRECONDITION(p_column < m_nbColumns);

    if(IsColumnFull(p_column))
    {
        return false;
    }

    size_t rowSubscript = 0;

    for(auto row = m_grid.begin(); row != m_grid.end(); ++row)
    {
        const cxmodel::IChip& chip = GetChip({rowSubscript, p_column});
        if(chip == *NoChip())
        {
            m_grid[rowSubscript][p_column] = std::move(std::make_unique<cxmodel::Disc>(p_disc.GetColor()));
            break;
        }

        ++rowSubscript;
    }

    CheckInvariants();

    p_droppedPosition = {rowSubscript, p_column};

    return true;
}

bool cxmodel::Board::IsColumnFull(size_t p_column) const
{
    PRECONDITION(p_column < m_nbColumns);

    bool isPlayable = false;
    size_t  rowSubscript = m_nbRows - 1;

    for(auto row = m_grid.rbegin(); row != m_grid.rend(); ++row)
    {
        const cxmodel::IChip& chip = GetChip({rowSubscript, p_column});
        if(chip == *NoChip())
        {
            isPlayable = true;
            break;
        }

        --rowSubscript;
    }

    return !isPlayable;
}

void cxmodel::Board::CheckInvariants() const
{
    INVARIANT(m_nbRows >= m_modelAsLimits.GetMinimumGridHeight());
    INVARIANT(m_nbRows <= m_modelAsLimits.GetMaximumGridHeight());

    INVARIANT(m_nbColumns >= m_modelAsLimits.GetMinimumGridWidth());
    INVARIANT(m_nbColumns <= m_modelAsLimits.GetMaximumGridWidth());
}
