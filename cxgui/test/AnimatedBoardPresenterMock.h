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

#include <cxgui/IAnimatedBoardPresenter.h>

class AnimatedBoardPresenterMock : public cxgui::IAnimatedBoardPresenter
{

public:

    AnimatedBoardPresenterMock();

    // cxgui::IAnimatedBoardPresenter:
    void Sync() override;
    [[nodiscard]] cxmodel::Height GetBoardHeight() const override;
    [[nodiscard]] cxmodel::Width GetBoardWidth() const override;
    [[nodiscard]] cxmodel::ChipColor GetActivePlayerChipColor() const override;
    [[nodiscard]] const cxgui::IGameViewPresenter::ChipColors& GetBoardChipColors() const override;

    // Testing:
    void SetBoardDimensions(const cxmodel::Height& p_nbRows, const cxmodel::Width& p_nbColumns);
    void AddChipsToColumn(const cxmodel::Column& p_column, size_t p_nbOfChipsToAdd);

    [[nodiscard]] bool WasSyncCalled() const {return m_syncCalled;}

private:

    void ResetBoard();

    bool m_syncCalled = false;

    cxmodel::Height m_boardHeight{6u};
    cxmodel::Width m_boardWidth{7u};

    cxgui::IGameViewPresenter::ChipColors m_chipColors;
};

#endif // ANIMATEDBOARDPRESENTERMOCK_H_0BBB4EA4_6CE8_46F8_8FBF_62E30E5DEDE0
