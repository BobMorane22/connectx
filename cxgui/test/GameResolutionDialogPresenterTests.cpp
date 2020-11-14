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

#include <cxmodel/include/Disc.h>
#include <cxmodel/include/IConnectXGameInformation.h>
#include <cxmodel/include/Player.h>

#include <GameResolutionDialogPresenter.h>

#include "DisableStdStreamsRAII.h"

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

TEST(GameResolutionDialogPresenter, GetResolutionMessage_GameWon_GameWonResolutionMessageReturned)
{
    ModelMock model;

    model.SetIsWon(true);
    model.SetActivePlayer({"John Doe", cxmodel::MakeRed()});

    cxgui::GameResolutionDialogPresenter presenter{model};

    ASSERT_EQ("Congratulations to John Doe for winning the game!", presenter.GetResolutionMessage());
}

TEST(GameResolutionDialogPresenter, GetResolutionMessage_GameNotWon_NoMessageReturnedAndAssertion)
{
    DisableStdStreamsRAII m_streamDisabler;

    ModelMock model;

    model.SetIsWon(false);
    model.SetActivePlayer({"John Doe", cxmodel::MakeRed()});

    cxgui::GameResolutionDialogPresenter presenter{model};

    ASSERT_EQ("", m_streamDisabler.GetStdErrContents());
    ASSERT_EQ("", presenter.GetResolutionMessage());

    const std::string stdErrContents = m_streamDisabler.GetStdErrContents();
    ASSERT_TRUE(stdErrContents.find("Assertion") != std::string::npos);
}
