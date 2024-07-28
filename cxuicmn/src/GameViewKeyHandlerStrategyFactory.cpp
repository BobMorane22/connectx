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
#include <cxuicmn/EventPropagation.h>
#include <cxuicmn/GameViewKeyHandlerStrategyFactory.h>
#include <cxuicmn/IBoardInformation.h>
#include <cxuicmn/IGameViewController.h>
#include <cxuicmn/KeyboardKeyPressedEvent.h>

namespace cx::ui::cmn
{

class GameViewDownKeyHandlerStrategy : public cx::ui::cmn::IGameViewKeyHandlerStrategy
{

public:

    [[nodiscard]] EventPropagation Handle(IGameViewController& p_controller, IBoardInformation& p_gameBoard) override;

};

cx::ui::cmn::EventPropagation GameViewDownKeyHandlerStrategy::Handle(IGameViewController& p_controller, IBoardInformation& p_gameBoard)
{
    const cx::model::ChipColor chipColor = p_gameBoard.GetCurrentChipColor();
    IF_CONDITION_NOT_MET_DO(chipColor != cx::model::MakeTransparent(), return cx::ui::cmn::EventPropagation::PROPAGATE;);

    p_controller.OnDown(chipColor, p_gameBoard.GetCurrentColumn().Get());

    return EventPropagation::STOP;
}

class GameViewLeftKeyHandlerStrategy : public cx::ui::cmn::IGameViewKeyHandlerStrategy
{

public:

    [[nodiscard]] EventPropagation Handle(IGameViewController& p_controller, IBoardInformation& p_gameBoard) override;

};

cx::ui::cmn::EventPropagation GameViewLeftKeyHandlerStrategy::Handle(IGameViewController& p_controller, IBoardInformation& /*p_gameBoard*/)
{
    p_controller.OnMoveLeftOneColumn();

    return EventPropagation::STOP;
}

class GameViewRightKeyHandlerStrategy : public cx::ui::cmn::IGameViewKeyHandlerStrategy
{

public:

    [[nodiscard]] EventPropagation Handle(IGameViewController& p_controller, IBoardInformation& p_gameBoard) override;

};

cx::ui::cmn::EventPropagation GameViewRightKeyHandlerStrategy::Handle(IGameViewController& p_controller, IBoardInformation& /*p_gameBoard*/)
{
    p_controller.OnMoveRightOneColumn();

    return EventPropagation::STOP;
}

} // namespace cx::ui::cmn

std::unique_ptr<cx::ui::cmn::IGameViewKeyHandlerStrategy> cx::ui::cmn::GameViewKeyHandlerStrategyFactory::Create(cx::ui::cmn::KeyboardKeyPressedEvent p_event)
{
    switch(p_event)
    {
        case cx::ui::cmn::KeyboardKeyPressedEvent::KEY_LEFT:
            return std::make_unique<cx::ui::cmn::GameViewLeftKeyHandlerStrategy>();

        case cx::ui::cmn::KeyboardKeyPressedEvent::KEY_RIGHT:
            return std::make_unique<cx::ui::cmn::GameViewRightKeyHandlerStrategy>();

        case cx::ui::cmn::KeyboardKeyPressedEvent::KEY_DOWN:
            return std::make_unique<cx::ui::cmn::GameViewDownKeyHandlerStrategy>();

        default:
            return nullptr;
    }
}
