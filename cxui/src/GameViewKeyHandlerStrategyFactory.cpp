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
#include <cxcmnui/EventPropagation.h>
#include <cxui/GameViewKeyHandlerStrategyFactory.h>
#include <cxui/IBoardInformation.h>
#include <cxui/IGameViewController.h>
#include <cxcmnui/KeyboardKeyPressedEvent.h>

namespace cx::ui
{

class GameViewDownKeyHandlerStrategy : public cx::ui::IGameViewKeyHandlerStrategy
{

public:

    [[nodiscard]] cx::cmn::ui::EventPropagation Handle(IGameViewController& p_controller, IBoardInformation& p_gameBoard) override;

};

cx::cmn::ui::EventPropagation GameViewDownKeyHandlerStrategy::Handle(IGameViewController& p_controller, IBoardInformation& p_gameBoard)
{
    const cx::model::ChipColor chipColor = p_gameBoard.GetCurrentChipColor();
    IF_CONDITION_NOT_MET_DO(chipColor != cx::model::MakeTransparent(), return cx::cmn::ui::EventPropagation::PROPAGATE;);

    p_controller.OnDown(chipColor, p_gameBoard.GetCurrentColumn().Get());

    return cx::cmn::ui::EventPropagation::STOP;
}

class GameViewLeftKeyHandlerStrategy : public cx::ui::IGameViewKeyHandlerStrategy
{

public:

    [[nodiscard]] cx::cmn::ui::EventPropagation Handle(IGameViewController& p_controller, IBoardInformation& p_gameBoard) override;

};

cx::cmn::ui::EventPropagation GameViewLeftKeyHandlerStrategy::Handle(IGameViewController& p_controller, IBoardInformation& /*p_gameBoard*/)
{
    p_controller.OnMoveLeftOneColumn();

    return cx::cmn::ui::EventPropagation::STOP;
}

class GameViewRightKeyHandlerStrategy : public cx::ui::IGameViewKeyHandlerStrategy
{

public:

    [[nodiscard]] cx::cmn::ui::EventPropagation Handle(IGameViewController& p_controller, IBoardInformation& p_gameBoard) override;

};

cx::cmn::ui::EventPropagation GameViewRightKeyHandlerStrategy::Handle(IGameViewController& p_controller, IBoardInformation& /*p_gameBoard*/)
{
    p_controller.OnMoveRightOneColumn();

    return cx::cmn::ui::EventPropagation::STOP;
}

} // namespace cx::ui

std::unique_ptr<cx::ui::IGameViewKeyHandlerStrategy> cx::ui::GameViewKeyHandlerStrategyFactory::Create(cx::cmn::ui::KeyboardKeyPressedEvent p_event)
{
    switch(p_event)
    {
        case cx::cmn::ui::KeyboardKeyPressedEvent::KEY_LEFT:
            return std::make_unique<cx::ui::GameViewLeftKeyHandlerStrategy>();

        case cx::cmn::ui::KeyboardKeyPressedEvent::KEY_RIGHT:
            return std::make_unique<cx::ui::GameViewRightKeyHandlerStrategy>();

        case cx::cmn::ui::KeyboardKeyPressedEvent::KEY_DOWN:
            return std::make_unique<cx::ui::GameViewDownKeyHandlerStrategy>();

        default:
            return nullptr;
    }
}
