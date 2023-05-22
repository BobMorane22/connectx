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
 * @file AnimatedBoardPresenter.h
 * @date 2021
 *
 *************************************************************************************************/

#ifndef ANIMATEDBOARDPRESENTER_H_CEED52F8_D734_4808_A833_448D61C817D9
#define ANIMATEDBOARDPRESENTER_H_CEED52F8_D734_4808_A833_448D61C817D9

#include "IAnimatedBoardPresenter.h"

namespace cxgui
{

/**********************************************************************************************//**
 * @brief Presenter for the animated board.
 * 
 * Since animations happen after the model is updated, when its values for board information
 * are read by the animation logic, they no longer represent what the animation should be.
 * Because of this, this presenter has been introduced to hold on to the information necessary
 * for the animation logic to work appropriately.
 *
 * This presenter needs to be updated by hand, using the `Sync` method. Call it to update the
 * cached values in between animations.
 *
 *************************************************************************************************/
class AnimatedBoardPresenter : public cxgui::IAnimatedBoardPresenter
{

public:

    /******************************************************************************************//**
     * @brief Constructor.
     * 
     * @param p_presenter The Game View presenter.
     *
     *********************************************************************************************/
    explicit AnimatedBoardPresenter(const IGameViewPresenter& p_presenter);

    // cxgui::IAnimatedBoardPresenter:
    void Sync() override;
    [[nodiscard]] cxmodel::Height GetBoardHeight() const override;
    [[nodiscard]] cxmodel::Width GetBoardWidth() const override;
    [[nodiscard]] cxgui::Color GetGameViewBoardColor() const override;
    [[nodiscard]] cxgui::Color GetGameViewColumnHighlightColor() const override;
    [[nodiscard]] cxmodel::ChipColor GetActivePlayerChipColor() const override;
    [[nodiscard]] const IGameViewPresenter::ChipColors& GetBoardChipColors() const override;
    [[nodiscard]] cxmodel::Column GetBotTarget() const override;

private:

    // Cache the old information, needed by the animation logic.
    struct Cache
    {
        cxmodel::Height m_boardHeight{0u};
        cxmodel::Width m_boardWidth{0u};
        cxmodel::ChipColor m_activePlayerChipColor = cxmodel::MakeTransparent();
        IGameViewPresenter::ChipColors m_boardColors;
        cxmodel::Column m_botTarget{0u};
    };

    const IGameViewPresenter& m_gameVewPresenter;
    Cache m_cache;

};

} // namespace cxgui

#endif // ANIMATEDBOARDPRESENTER_H_CEED52F8_D734_4808_A833_448D61C817D9
