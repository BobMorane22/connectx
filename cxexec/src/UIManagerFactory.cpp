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
 * @file UIManagerFactory.cpp
 * @date 2024
 *
 *************************************************************************************************/

#include <cstdlib>
#include <cxinv/assertion.h>
#include <cxgui/IAbstractWidgetsFactory.h>
#include <cxgui/IAbstractConnectXWidgetsFactory.h>
#include <cxgui/IMainWindowController.h>
#include <cxgui/IMainWindowPresenter.h>
#include <cxgui/IWindow.h>
#include <cxgui/WidgetsFactories.h>
#include <cxgui/WidgetsToolkit.h>
#include <cxexec/Gtkmm3UIManager.h>
#include <cxexec/IUIManager.h>
#include <cxexec/UIManagerFactory.h>

namespace
{

// Represents no manager. Used to return an error to the caller
// without having to deal with `nullptr`.
class NoUIManager : public cx::IUIManager
{

public:

    // cx::IUIManager:
    [[nodiscard]] int Manage() override
    {
        ASSERT_ERROR_MSG("Unknown widget toolkit");
        return EXIT_FAILURE;
    }
};

} // namespace

cx::UIManagerFactory::UIManagerFactory(int argc, char *argv[], cx::ModelReferences& p_model)
: m_argc{argc}
, m_argv{argv}
, m_model{p_model}
{
    PRECONDITION(argc > 0);
    PRECONDITION(argv);

    POSTCONDITION(m_argc > 0);
    POSTCONDITION(m_argv);
}

std::unique_ptr<cx::IUIManager> cx::UIManagerFactory::Create(cxgui::WidgetsToolkit p_toolkit) const
{
    switch(p_toolkit)
    {
        case cxgui::WidgetsToolkit::GTKMM3:
            return std::make_unique<cx::Gtkmm3UIManager>(m_argc, m_argv, m_model);

        default:
            break;
    }

    return std::make_unique<NoUIManager>();
}
