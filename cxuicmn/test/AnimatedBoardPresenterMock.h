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
 * @file AnimatedBoardPresenterMock.h
 * @date 2022
 *
 *************************************************************************************************/

#ifndef ANIMATEDBOARDPRESENTERMOCK_H_0BBB4EA4_6CE8_46F8_8FBF_62E30E5DEDE0
#define ANIMATEDBOARDPRESENTERMOCK_H_0BBB4EA4_6CE8_46F8_8FBF_62E30E5DEDE0

#include <cxuicmn/IAnimatedBoardPresenter.h>

class AnimatedBoardPresenterMock : public cx::cmn::ui::IAnimatedBoardPresenter
{

public:

    AnimatedBoardPresenterMock();

    // cx::cmn::ui::IAnimatedBoardPresenter:
    void Sync() override;
    [[nodiscard]] cx::model::Height GetBoardHeight() const override;
    [[nodiscard]] cx::model::Width GetBoardWidth() const override;
    [[nodiscard]] cx::cmn::ui::Color GetGameViewBoardColor() const override;
    [[nodiscard]] cx::cmn::ui::Color GetGameViewColumnHighlightColor() const override;
    [[nodiscard]] cx::model::ChipColor GetActivePlayerChipColor() const override;
    [[nodiscard]] const cx::cmn::ui::IGameViewPresenter::ChipColors& GetBoardChipColors() const override;
    [[nodiscard]] cx::model::Column GetBotTarget() const override;

    // Testing:
    void SetBoardDimensions(const cx::model::Height& p_nbRows, const cx::model::Width& p_nbColumns);
    void SetLastBotTarget(const cx::model::Column& p_lastBotTarget);
    void AddChipsToColumn(const cx::model::Column& p_column, size_t p_nbOfChipsToAdd);

    [[nodiscard]] bool WasSyncCalled() const {return m_syncCalled;}

private:

    void ResetBoard();

    bool m_syncCalled = false;

    cx::model::Height m_boardHeight{6u};
    cx::model::Width m_boardWidth{7u};

    cx::cmn::ui::IGameViewPresenter::ChipColors m_chipColors;

    cx::model::Column m_lastBotTarget{5u};
};

#endif // ANIMATEDBOARDPRESENTERMOCK_H_0BBB4EA4_6CE8_46F8_8FBF_62E30E5DEDE0
