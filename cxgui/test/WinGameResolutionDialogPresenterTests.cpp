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
 * @file GameResolutionDialogPresenterTests.cpp
 * @date 2020
 *
 *************************************************************************************************/

#include <gtest/gtest.h>

#include <cxunit/DisableStdStreamsRAII.h>
#include <cxmodel/Disc.h>
#include <cxmodel/IConnectXGameInformation.h>
#include <cxmodel/Player.h>
#include <cxgui/WinGameResolutionDialogPresenter.h>

namespace
{

class ModelMock : public cxmodel::IConnectXGameInformation
{

public:

    void SetIsWon(bool p_isWon){m_isWon = p_isWon;}
    void SetActivePlayer(const cxmodel::Player& p_activePlayer){m_activePlayer = p_activePlayer;}

    // IConnectXGameInformation:
    size_t GetCurrentGridHeight() const override {return 6u;}
    size_t GetCurrentGridWidth() const override {return 7u;}
    size_t GetCurrentInARowValue() const override {return 4u;}
    const cxmodel::Player& GetActivePlayer() const override {return m_activePlayer;}
    const cxmodel::Player& GetNextPlayer() const override {return m_nextPlayer;}
    const cxmodel::IChip& GetChip(size_t p_row, size_t p_column) const override
    {
        (void)p_row;
        (void)p_column;

        return m_disc;
    }

    bool IsWon() const override {return m_isWon;}
    bool IsTie() const override {return false;}

private:


    bool m_isWon = false;
    cxmodel::Player m_activePlayer{"No player!", cxmodel::MakeTransparent()};
    cxmodel::Player m_nextPlayer{"No player!", cxmodel::MakeTransparent()};

    const cxmodel::Disc m_disc{cxmodel::MakeTransparent()};
};

} // namespace

TEST(WinGameResolutionDialogPresenter, GetTitle_ValidModel_TitleReturned)
{
    ModelMock model;
    cxgui::WinGameResolutionDialogPresenter presenter{model};

    ASSERT_EQ("Game won!", presenter.GetTitle());
}

TEST(WinGameResolutionDialogPresenter, GetResolutionMessage_GameWon_GameWonResolutionMessageReturned)
{
    ModelMock model;

    model.SetIsWon(true);
    model.SetActivePlayer({"John Doe", cxmodel::MakeRed()});

    cxgui::WinGameResolutionDialogPresenter presenter{model};

    ASSERT_EQ("Congratulations to John Doe!", presenter.GetResolutionMessage());
}

TEST(WinGameResolutionDialogPresenter, GetResolutionMessage_GameNotWon_NoMessageReturnedAndAssertion)
{
    cxunit::DisableStdStreamsRAII streamDisabler;

    ModelMock model;

    model.SetIsWon(false);
    model.SetActivePlayer({"John Doe", cxmodel::MakeRed()});

    cxgui::WinGameResolutionDialogPresenter presenter{model};

    ASSERT_EQ("", streamDisabler.GetStdErrContents());
    ASSERT_EQ("", presenter.GetResolutionMessage());

    ASSERT_ASSERTION_FAILED(streamDisabler);
}

TEST(WinGameResolutionDialogPresenter, GetStartNewGameButtonText_ValidModel_StartNewGameButtonTextReturned)
{
    ModelMock model;
    cxgui::WinGameResolutionDialogPresenter presenter{model};

    ASSERT_EQ("Start new game", presenter.GetStartNewGameButtonText());
}
