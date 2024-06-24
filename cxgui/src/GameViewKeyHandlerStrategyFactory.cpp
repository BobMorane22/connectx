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
#include <cxgui/EventPropagation.h>
#include <cxgui/GameViewKeyHandlerStrategyFactory.h>
#include <cxgui/IBoardInformation.h>
#include <cxgui/IGameViewController.h>
#include <cxgui/KeyboardKeyPressedEvent.h>

namespace cxgui
{

class GameViewDownKeyHandlerStrategy : public cxgui::IGameViewKeyHandlerStrategy
{

public:

    [[nodiscard]] EventPropagation Handle(IGameViewController& p_controller, IBoardInformation& p_gameBoard) override;

};

cxgui::EventPropagation GameViewDownKeyHandlerStrategy::Handle(IGameViewController& p_controller, IBoardInformation& p_gameBoard)
{
    const cxmodel::ChipColor chipColor = p_gameBoard.GetCurrentChipColor();
    IF_CONDITION_NOT_MET_DO(chipColor != cxmodel::MakeTransparent(), return cxgui::EventPropagation::PROPAGATE;);

    p_controller.OnDown(chipColor, p_gameBoard.GetCurrentColumn().Get());

    return EventPropagation::STOP;
}

class GameViewLeftKeyHandlerStrategy : public cxgui::IGameViewKeyHandlerStrategy
{

public:

    [[nodiscard]] EventPropagation Handle(IGameViewController& p_controller, IBoardInformation& p_gameBoard) override;

};

cxgui::EventPropagation GameViewLeftKeyHandlerStrategy::Handle(IGameViewController& p_controller, IBoardInformation& /*p_gameBoard*/)
{
    p_controller.OnMoveLeftOneColumn();

    return EventPropagation::STOP;
}

class GameViewRightKeyHandlerStrategy : public cxgui::IGameViewKeyHandlerStrategy
{

public:

    [[nodiscard]] EventPropagation Handle(IGameViewController& p_controller, IBoardInformation& p_gameBoard) override;

};

cxgui::EventPropagation GameViewRightKeyHandlerStrategy::Handle(IGameViewController& p_controller, IBoardInformation& /*p_gameBoard*/)
{
    p_controller.OnMoveRightOneColumn();

    return EventPropagation::STOP;
}

} // namespace cxgui

std::unique_ptr<cxgui::IGameViewKeyHandlerStrategy> cxgui::GameViewKeyHandlerStrategyFactory::Create(cxgui::KeyboardKeyPressedEvent p_event)
{
    switch(p_event)
    {
        case cxgui::KeyboardKeyPressedEvent::KEY_LEFT:
            return std::make_unique<cxgui::GameViewLeftKeyHandlerStrategy>();

        case cxgui::KeyboardKeyPressedEvent::KEY_RIGHT:
            return std::make_unique<cxgui::GameViewRightKeyHandlerStrategy>();

        case cxgui::KeyboardKeyPressedEvent::KEY_DOWN:
            return std::make_unique<cxgui::GameViewDownKeyHandlerStrategy>();

        default:
            return nullptr;
    }
}
