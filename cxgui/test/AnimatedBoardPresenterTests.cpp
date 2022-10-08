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
 * @file AnimatedBoardPresenterTests.cpp
 * @date 2021
 *
 *************************************************************************************************/

#include <memory>

#include <gtest/gtest.h>

#include <cxunit/NotImplementedException.h>
#include <cxgui/AnimatedBoardPresenter.h>

namespace
{

class GameViewPresenterMock : public cxgui::IGameViewPresenter
{

public:

    GameViewPresenterMock()
    {
        FillBoardColors(cxmodel::MakeRed());
    }

    void UpdateWrapedValues()
    {
        m_boardHeight = 8u;
        m_boardWidth = 9u;
        m_activePlayerChipColor = cxmodel::MakeBlue();
        FillBoardColors(cxmodel::MakeBlue());
        m_botTarget = 5u;
    }

    // cxgui::IGameViewPresenter (not used):
    std::string GetGameViewTitle() const override {throw cxunit::NotImplementedException();}
    cxmodel::ChipColor GetGameViewNextPlayerChipColor() const override {throw cxunit::NotImplementedException();}
    std::string GetGameViewActivePlayerLabelText() const override {throw cxunit::NotImplementedException();}
    std::string GetGameViewNextPlayerLabelText() const override {throw cxunit::NotImplementedException();}
    std::string GetGameViewActivePlayerName() const override {throw cxunit::NotImplementedException();}
    std::string GetGameViewNextPlayerName() const override {throw cxunit::NotImplementedException();}

    // cxgui::IGameViewPresenter (wrapped by the cxgui::AnimatedBoardPresenter):
    cxmodel::ChipColor GetGameViewActivePlayerChipColor() const override {return m_activePlayerChipColor;}
    size_t GetGameViewBoardWidth() const override {return m_boardWidth;}
    size_t GetGameViewBoardHeight() const override {return m_boardHeight;}
    const ChipColors& GetGameViewChipColors() const override {return m_boardColors;}
    [[nodiscard]] virtual bool IsCurrentPlayerABot() const {return false;};
    [[nodiscard]] virtual size_t GetBotTarget() const {return m_botTarget;};

private:

    void FillBoardColors(const cxmodel::ChipColor& p_newColor)
    {
        m_boardColors.erase(m_boardColors.begin(), m_boardColors.end());

        for(size_t row = 0u; row < m_boardHeight; ++row)
        {
            m_boardColors.push_back(std::vector<cxmodel::ChipColor>());
            for(size_t column = 0u; column < m_boardWidth; ++column)
            {
                m_boardColors[row].push_back(p_newColor);
            }
        }
    }

    size_t m_boardHeight = 6u;
    size_t m_boardWidth = 7u;
    cxmodel::ChipColor m_activePlayerChipColor = cxmodel::MakeRed();
    IGameViewPresenter::ChipColors m_boardColors;
    size_t m_botTarget = 0u;

};

class AnimatedBoardPresenterTestFixture : public ::testing::Test
{

public:

    AnimatedBoardPresenterTestFixture()
    {
        m_underlyingPresenter = std::make_unique<GameViewPresenterMock>();
        EXPECT_TRUE(m_underlyingPresenter);

        m_presenter = std::make_unique<cxgui::AnimatedBoardPresenter>(*m_underlyingPresenter);
        EXPECT_TRUE(m_presenter);
    }

    cxgui::AnimatedBoardPresenter& GetPresenter()
    {
        EXPECT_TRUE(m_presenter);
        return *m_presenter;
    }

    GameViewPresenterMock& GetUnderlyingPresenter()
    {
        EXPECT_TRUE(m_underlyingPresenter);
        return *m_underlyingPresenter;
    }

private:

    std::unique_ptr<cxgui::AnimatedBoardPresenter> m_presenter;
    std::unique_ptr<GameViewPresenterMock> m_underlyingPresenter;

};

} // namespace

TEST_F(AnimatedBoardPresenterTestFixture, /*DISABLED_*/Sync_NoChangeToModel_SyncDoesNothing)
{
    auto presenter = GetPresenter();

    // We take a copy of what is returned before...
    const cxmodel::Height boardHeightBefore = presenter.GetBoardHeight();
    const cxmodel::Width boardWidthBefore = presenter.GetBoardWidth();
    const cxmodel::ChipColor activePlayerChipColorBefore = presenter.GetActivePlayerChipColor();
    const cxgui::IGameViewPresenter::ChipColors boardColorsBefore = presenter.GetBoardChipColors();
    const cxmodel::Column botTargetBefore = presenter.GetBotTarget();

    // No changes were made to the underlying presenter, but we sync anyway:
    presenter.Sync();

    // We take a copy of what is returned after the sync:
    const cxmodel::Height boardHeightAfter = presenter.GetBoardHeight();
    const cxmodel::Width boardWidthAfter = presenter.GetBoardWidth();
    const cxmodel::ChipColor activePlayerChipColorAfter = presenter.GetActivePlayerChipColor();
    const cxgui::IGameViewPresenter::ChipColors boardColorsAfter = presenter.GetBoardChipColors();
    const cxmodel::Column botTargetAfter = presenter.GetBotTarget();

    // Everything should match:
    ASSERT_TRUE(boardHeightBefore == boardHeightAfter);
    ASSERT_TRUE(boardWidthBefore == boardWidthAfter);
    ASSERT_TRUE(activePlayerChipColorBefore == activePlayerChipColorAfter);
    for(size_t row = 0u; row < boardHeightBefore.Get(); ++row)
    {
        for(size_t column = 0u; column < boardWidthBefore.Get(); ++column)
        {
            ASSERT_TRUE(boardColorsBefore[row][column] == boardColorsAfter[row][column]);
        }
    }
    ASSERT_TRUE(botTargetBefore == botTargetAfter);
}

TEST_F(AnimatedBoardPresenterTestFixture, /*DISABLED_*/Sync_ChangesToModel_Syncs)
{
    auto presenter = GetPresenter();

    // We take a copy of what is returned before...
    const cxmodel::Height boardHeightBefore = presenter.GetBoardHeight();
    const cxmodel::Width boardWidthBefore = presenter.GetBoardWidth();
    const cxmodel::ChipColor activePlayerChipColorBefore = presenter.GetActivePlayerChipColor();
    const cxgui::IGameViewPresenter::ChipColors boardColorsBefore = presenter.GetBoardChipColors();
    const cxmodel::Column botTargetBefore = presenter.GetBotTarget();

    // We update the underlying presenter and sync:
    GetUnderlyingPresenter().UpdateWrapedValues();
    presenter.Sync();

    // We take a copy of what is returned after the sync:
    const cxmodel::Height boardHeightAfter = presenter.GetBoardHeight();
    const cxmodel::Width boardWidthAfter = presenter.GetBoardWidth();
    const cxmodel::ChipColor activePlayerChipColorAfter = presenter.GetActivePlayerChipColor();
    const cxgui::IGameViewPresenter::ChipColors boardColorsAfter = presenter.GetBoardChipColors();
    const cxmodel::Column botTargetAfter = presenter.GetBotTarget();

    // Returned values should be updated:
    ASSERT_TRUE(boardHeightBefore != boardHeightAfter);
    ASSERT_TRUE(boardWidthBefore != boardWidthAfter);
    ASSERT_TRUE(activePlayerChipColorBefore != activePlayerChipColorAfter);
    for(size_t row = 0u; row < boardHeightBefore.Get(); ++row)
    {
        for(size_t column = 0u; column < boardWidthBefore.Get(); ++column)
        {
            ASSERT_TRUE(boardColorsBefore[row][column] != boardColorsAfter[row][column]);
        }
    }
    ASSERT_TRUE(botTargetBefore != botTargetAfter);
}

TEST_F(AnimatedBoardPresenterTestFixture, /*DISABLED_*/GetBoardHeight_ValidPresenter_BoardHeightReturned)
{
    ASSERT_TRUE(GetPresenter().GetBoardHeight() == cxmodel::Height{6u});
}

TEST_F(AnimatedBoardPresenterTestFixture, /*DISABLED_*/GetBoardWidth_ValidPresenter_BoardWidthReturned)
{
    ASSERT_TRUE(GetPresenter().GetBoardWidth() == cxmodel::Width{7u});
}

TEST_F(AnimatedBoardPresenterTestFixture, /*DISABLED_*/GetActivePlayerChipColor_ValidPresenter_ActivePlayerChipColorReturned)
{
    ASSERT_TRUE(GetPresenter().GetActivePlayerChipColor() == cxmodel::MakeRed());
}

TEST_F(AnimatedBoardPresenterTestFixture, /*DISABLED_*/GetBoardChipColors_ValidPresenter_BoardChipColorsReturned)
{
    const auto& boardColors = GetPresenter().GetBoardChipColors();
    for(size_t row = 0u; row < GetPresenter().GetBoardHeight().Get(); ++row)
    {
        for(size_t column = 0u; column < GetPresenter().GetBoardWidth().Get(); ++column)
        {
            ASSERT_TRUE(boardColors[row][column] == cxmodel::MakeRed());
        }
    }
}

TEST_F(AnimatedBoardPresenterTestFixture, /*DISABLED_*/GetBotTarget_ValidPresenter_BotTargetReturned)
{
    ASSERT_TRUE(GetPresenter().GetBotTarget() == cxmodel::Column{0u});
}
