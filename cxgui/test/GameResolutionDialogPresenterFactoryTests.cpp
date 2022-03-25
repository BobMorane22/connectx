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
 * @file GameResolutionDialogPresenterFactoryTests.cpp
 * @date 2020
 *
 *************************************************************************************************/

#include <gtest/gtest.h>

#include <cxmodel/IConnectXGameInformation.h>
#include <cxmodel/GameResolutionStrategyFactory.h>
#include <cxgui/GameResolutionDialogPresenterFactory.h>
#include <cxgui/TieGameResolutionDialogPresenter.h>
#include <cxgui/WinGameResolutionDialogPresenter.h>

namespace
{

class ModelMock final : public cxmodel::IConnectXGameInformation
{

public:

    size_t GetCurrentGridHeight() const override {return 6u;}
    size_t GetCurrentGridWidth() const override {return 7u;}
    size_t GetCurrentInARowValue() const override {return 4u;}
    const cxmodel::IPlayer& GetActivePlayer() const override {return *m_player;}
    const cxmodel::IPlayer& GetNextPlayer() const override {return *m_player;}
    const cxmodel::IChip& GetChip(size_t p_row, size_t p_column) const override
    {
        (void)p_row;
        (void)p_column;

        return m_player->GetChip();
    }

    bool IsWon() const override {return true;}
    bool IsTie() const override {return true;}

private:

    const std::unique_ptr<cxmodel::IPlayer> m_player = cxmodel::CreatePlayer( "Dummy", cxmodel::MakeRed(), cxmodel::PlayerType::HUMAN);

};

} // namespace

TEST(GameResolutionDialogPresenterFactory, Make_WinGameResolution_WinGameResolutionDialogPresenterReturned)
{
    ModelMock model;

    auto presenter = cxgui::GameResolutionDialogPresenterFactory::Make(model, cxmodel::GameResolution::WIN);
    ASSERT_TRUE(presenter);

    ASSERT_TRUE(dynamic_cast<cxgui::WinGameResolutionDialogPresenter*>(presenter.get()));
}

TEST(GameResolutionDialogPresenterFactory, Make_TieGameResolution_TieGameResolutionDialogPresenterReturned)
{
    ModelMock model;

    auto presenter = cxgui::GameResolutionDialogPresenterFactory::Make(model, cxmodel::GameResolution::TIE);
    ASSERT_TRUE(presenter);

    ASSERT_TRUE(dynamic_cast<cxgui::TieGameResolutionDialogPresenter*>(presenter.get()));
}
