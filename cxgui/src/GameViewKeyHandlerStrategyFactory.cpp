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
 * @file GameViewKeyHandlerStrategyFactory.cpp
 * @date 2020
 *
 *************************************************************************************************/

#include <cxinv/assertion.h>
#include <cxgui/GameViewKeyHandlerStrategyFactory.h>
#include <cxgui/IBoardInformation.h>
#include <cxgui/IGameViewController.h>

namespace cxgui
{

class GameViewDownKeyHandlerStrategy : public cxgui::IGameViewKeyHandlerStrategy
{

public:

    bool Handle(IGameViewController& p_controller, IBoardInformation& p_gameBoard) override;

};

bool GameViewDownKeyHandlerStrategy::Handle(IGameViewController& p_controller, IBoardInformation& p_gameBoard)
{
    const cxmodel::ChipColor chipColor = p_gameBoard.GetCurrentChipColor();
    IF_CONDITION_NOT_MET_DO(chipColor != cxmodel::MakeTransparent(), return false;);

    p_controller.OnDown(chipColor, p_gameBoard.GetCurrentColumn().Get());

    return true;
}

class GameViewLeftKeyHandlerStrategy : public cxgui::IGameViewKeyHandlerStrategy
{

public:

    bool Handle(IGameViewController& p_controller, IBoardInformation& p_gameBoard) override;

};

bool GameViewLeftKeyHandlerStrategy::Handle(IGameViewController& p_controller, IBoardInformation& /*p_gameBoard*/)
{
    p_controller.OnMoveLeft();

    return true;
}

class GameViewRightKeyHandlerStrategy : public cxgui::IGameViewKeyHandlerStrategy
{

public:

    bool Handle(IGameViewController& p_controller, IBoardInformation& p_gameBoard) override;

};

bool GameViewRightKeyHandlerStrategy::Handle(IGameViewController& p_controller, IBoardInformation& /*p_gameBoard*/)
{
    p_controller.OnMoveRight();

    return true;
}

} // namespace cxgui

std::unique_ptr<cxgui::IGameViewKeyHandlerStrategy> cxgui::GameViewKeyHandlerStrategyFactory::Create(GdkEventKey* p_event)
{
    IF_PRECONDITION_NOT_MET_DO(p_event, return nullptr;);

    switch(p_event->keyval)
    {
        case GDK_KEY_Left:
            return std::make_unique<cxgui::GameViewLeftKeyHandlerStrategy>();

        case GDK_KEY_Right:
            return std::make_unique<cxgui::GameViewRightKeyHandlerStrategy>();

        case GDK_KEY_Down:
            return std::make_unique<cxgui::GameViewDownKeyHandlerStrategy>();

        default:
            return nullptr;
    }
}
