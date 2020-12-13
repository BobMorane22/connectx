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
 * @file GameResolutionDialogPresenterFactory.cpp
 * @date 2020
 *
 *************************************************************************************************/

#include <cxinv/include/assertion.h>
#include <cxmodel/include/GameResolutionStrategyFactory.h>
#include <cxmodel/include/IConnectXGameInformation.h>

#include <TieGameResolutionDialogPresenter.h>
#include <WinGameResolutionDialogPresenter.h>

#include "GameResolutionDialogPresenterFactory.h"

namespace
{

// Fallback presenter.
class NoGameResolutionDialogPresenter : public cxgui::IGameResolutionDialogPresenter
{
    std::string GetTitle() const override {return "";}                    // LCOV_EXCL_LINE
    std::string GetResolutionMessage() const override {return "";}        // LCOV_EXCL_LINE
    std::string GetStartNewGameButtonText() const override {return "";}   // LCOV_EXCL_LINE
};

} // namespace

std::unique_ptr<cxgui::IGameResolutionDialogPresenter> cxgui::GameResolutionDialogPresenterFactory::Make(const cxmodel::IConnectXGameInformation& p_modelAsInformation,
                                                                                                         cxmodel::GameResolution p_resolution)
{
    std::unique_ptr<cxgui::IGameResolutionDialogPresenter> presenter = std::make_unique<NoGameResolutionDialogPresenter>();
    ASSERT(presenter);

    switch(p_resolution)
    {
        case cxmodel::GameResolution::WIN:
        {
            presenter = std::make_unique<cxgui::WinGameResolutionDialogPresenter>(p_modelAsInformation);
            break;
        }
        case cxmodel::GameResolution::TIE:
        {
            presenter = std::make_unique<cxgui::TieGameResolutionDialogPresenter>();
            break;
        }
        default:
            break; // LCOV_EXCL_LINE
    }

    ASSERT(presenter);
    return presenter;
}
