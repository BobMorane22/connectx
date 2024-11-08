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
#include <cxcmnui/IAbstractWidgetsFactory.h>
#include <cxcmnui/IWindow.h>
#include <cxcmnui/WidgetsToolkit.h>
#include <cxui/IAbstractConnectXWidgetsFactory.h>
#include <cxui/MainWindowController.h>
#include <cxui/MainWindowPresenter.h>
#include <cxui/WidgetsFactories.h>
#include <cxcmnuigtkmm3/widgetsFactory.h>
#include <cxuigtkmm3/widgetsFactory.h>
#include <cxexec/IUIManager.h>
#include <cxexec/ModelReferences.h>
#include <cxexec/UIManagerFactory.h>

namespace
{

/*************************************************************************************************
 * @brief No UI manager.
 *
 * Null object for UI managers. Should never be available in a normal context.
 *
 ************************************************************************************************/
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


/*************************************************************************************************
 * @brief A Gtkmm UI manager compatible with Gtkmm 3.24.5.
 *
 ************************************************************************************************/
class Gtkmm3UIManager : public cx::IUIManager
{

public:

    /**********************************************************************************************
     * @brief Constructor.
     *
     * @param p_model
     *      References to a Connect X compatible model.
     *
     * @post
     *      The standard widgets abstract factory is valid.
     *
     * @post
     *      The Connect X specific widgets abstract factory is valid.
     *
     * @post
     *     The widget factories container is valid.
     *
     * @post
     *     The main window is valid.
     *
     ********************************************************************************************/
    explicit Gtkmm3UIManager(cx::ModelReferences& p_model);

    // cx::IUIManager:
    [[nodiscard]] int Manage() override;


private:

    void CheckInvariants();

private:

    // Widgets factories.
    std::unique_ptr<cx::cmn::ui::IAbstractWidgetsFactory> m_abstractWidgetsFactory;
    std::unique_ptr<cx::ui::IAbstractConnectXWidgetsFactory> m_abstractConnectXWidgetsFactory;
    std::unique_ptr<cx::ui::WidgetsFactories> m_widgetsFactories;

    // Main window.
    std::unique_ptr<cx::cmn::ui::IWindow> m_mainWindow;
    std::unique_ptr<cx::ui::IMainWindowController> m_controller;
    std::unique_ptr<cx::ui::IMainWindowPresenter> m_presenter;

};

Gtkmm3UIManager::Gtkmm3UIManager(cx::ModelReferences& p_model)
{
    {
        m_abstractWidgetsFactory = cx::cmn::ui::gtkmm3::CreateFactory();
        ASSERT(m_abstractWidgetsFactory);

        {
            auto abstractConnectXWidgetsFactory = cx::ui::gtkmm3::CreateFactory(*m_abstractWidgetsFactory);
            ASSERT(abstractConnectXWidgetsFactory);

            m_abstractConnectXWidgetsFactory = std::move(abstractConnectXWidgetsFactory);
            ASSERT(m_abstractConnectXWidgetsFactory);
        }

        m_widgetsFactories = std::make_unique<cx::ui::WidgetsFactories>(*m_abstractWidgetsFactory, *m_abstractConnectXWidgetsFactory);
        ASSERT(m_widgetsFactories);
    }

    m_controller = std::make_unique<cx::ui::MainWindowController>(p_model.m_asGameActions, p_model.m_asUndoRedo);
    m_presenter = std::make_unique<cx::ui::MainWindowPresenter>(p_model.m_asLimits, p_model.m_asGameInformation, p_model.m_asUndoRedo, p_model.m_asAi);

    m_mainWindow = m_abstractConnectXWidgetsFactory->CreateMainWindow(p_model.m_asSubject, *m_controller, *m_presenter);
    ASSERT(m_mainWindow);

    POSTCONDITION(m_abstractWidgetsFactory);
    POSTCONDITION(m_abstractConnectXWidgetsFactory);
    POSTCONDITION(m_widgetsFactories);
    POSTCONDITION(m_mainWindow);

    CheckInvariants();
}

int Gtkmm3UIManager::Manage()
{
    CheckInvariants();

    if(m_mainWindow)
    {
        return m_mainWindow->Show();
    }

    return EXIT_FAILURE;
}

void Gtkmm3UIManager::CheckInvariants()
{
    INVARIANT(m_controller);
    INVARIANT(m_presenter);
    INVARIANT(m_mainWindow);
}

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

std::unique_ptr<cx::IUIManager> cx::UIManagerFactory::Create(cx::cmn::ui::WidgetsToolkit p_toolkit) const
{
    switch(p_toolkit)
    {
        case cx::cmn::ui::WidgetsToolkit::GTKMM3:
            return std::make_unique<Gtkmm3UIManager>(m_model);

        default:
            break;
    }

    return std::make_unique<NoUIManager>();
}
