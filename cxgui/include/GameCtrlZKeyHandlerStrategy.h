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
 * @file GameCtrlZKeyHandlerStrategy.h
 * @date 2021
 *
 *************************************************************************************************/

#ifndef GAMECTRLZKEYHANDLERSTRATEGY_H_234AC57C_5E0C_45A9_85BF_03867FDDFEA6
#define GAMECTRLZKEYHANDLERSTRATEGY_H_234AC57C_5E0C_45A9_85BF_03867FDDFEA6

#include "IGameKeyHandlerStrategy.h"

namespace cxgui
{

/*********************************************************************************************//**
 * @brief DESCRIPTION
 *
 * @invariant
 * @invariant
 *
 * DESCRIPTION
 *
 ************************************************************************************************/
class GameCtrlZKeyHandlerStrategy : public IGameKeyHandlerStrategy
{

public:

    bool Handle(Board& p_gameBoard) override;

};

} // namespace cxgui

#endif // GAMECTRLZKEYHANDLERSTRATEGY_H_234AC57C_5E0C_45A9_85BF_03867FDDFEA6
