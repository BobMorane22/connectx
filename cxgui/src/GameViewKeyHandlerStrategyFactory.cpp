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

namespace cx::gui
{

class GameViewDownKeyHandlerStrategy : public cx::gui::IGameViewKeyHandlerStrategy
{

public:

    [[nodiscard]] EventPropagation Handle(IGameViewController& p_controller, IBoardInformation& p_gameBoard) override;

};

cx::gui::EventPropagation GameViewDownKeyHandlerStrategy::Handle(IGameViewController& p_controller, IBoardInformation& p_gameBoard)
{
    const cx::model::ChipColor chipColor = p_gameBoard.GetCurrentChipColor();
    IF_CONDITION_NOT_MET_DO(chipColor != cx::model::MakeTransparent(), return cx::gui::EventPropagation::PROPAGATE;);

    p_controller.OnDown(chipColor, p_gameBoard.GetCurrentColumn().Get());

    return EventPropagation::STOP;
}

class GameViewLeftKeyHandlerStrategy : public cx::gui::IGameViewKeyHandlerStrategy
{

public:

    [[nodiscard]] EventPropagation Handle(IGameViewController& p_controller, IBoardInformation& p_gameBoard) override;

};

cx::gui::EventPropagation GameViewLeftKeyHandlerStrategy::Handle(IGameViewController& p_controller, IBoardInformation& /*p_gameBoard*/)
{
    p_controller.OnMoveLeftOneColumn();

    return EventPropagation::STOP;
}

class GameViewRightKeyHandlerStrategy : public cx::gui::IGameViewKeyHandlerStrategy
{

public:

    [[nodiscard]] EventPropagation Handle(IGameViewController& p_controller, IBoardInformation& p_gameBoard) override;

};

cx::gui::EventPropagation GameViewRightKeyHandlerStrategy::Handle(IGameViewController& p_controller, IBoardInformation& /*p_gameBoard*/)
{
    p_controller.OnMoveRightOneColumn();

    return EventPropagation::STOP;
}

} // namespace cx::gui

std::unique_ptr<cx::gui::IGameViewKeyHandlerStrategy> cx::gui::GameViewKeyHandlerStrategyFactory::Create(cx::gui::KeyboardKeyPressedEvent p_event)
{
    switch(p_event)
    {
        case cx::gui::KeyboardKeyPressedEvent::KEY_LEFT:
            return std::make_unique<cx::gui::GameViewLeftKeyHandlerStrategy>();

        case cx::gui::KeyboardKeyPressedEvent::KEY_RIGHT:
            return std::make_unique<cx::gui::GameViewRightKeyHandlerStrategy>();

        case cx::gui::KeyboardKeyPressedEvent::KEY_DOWN:
            return std::make_unique<cx::gui::GameViewDownKeyHandlerStrategy>();

        default:
            return nullptr;
    }
}
