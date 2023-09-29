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
 * @file main.cpp
 * @date 2023
 *
 * Prototype for creating widgets using an abstract factory.
 *
 *************************************************************************************************/

#include <iostream>

#include <gtkmm.h>

#include "Backend.h"
#include "IAbstractWidgetsFactory.h"
#include "IButton.h"
#include "IEditBox.h"
#include "IGreenLabel.h"
#include "ILayout.h"
#include "IWindow.h"
#include "WidgetsFactories.h"

class MainWindow : public Gtk::ApplicationWindow
{

public:

    MainWindow(WidgetsFactories& p_widgetFactories);

    void Show();

    Gtk::Window& ToGtk();

private:

    WidgetsFactories& m_widgetsFactories;

    std::unique_ptr<IGreenLabel> m_label;
    std::unique_ptr<IButton>     m_button;
    std::unique_ptr<IEditBox>    m_editBox;

    std::unique_ptr<IWindow> m_window;

};

MainWindow::MainWindow(WidgetsFactories& p_widgetsFactories)
: m_widgetsFactories{p_widgetsFactories}
{
    // Creating a Connect X specific green label:
    m_label = m_widgetsFactories.GetConnectXSpecific()->CreateGreenLabel();

    // Creating a button:
    m_button = m_widgetsFactories->CreateButton();
    m_button->SetText("test");
    m_button->OnClicked()->Connect(
        []()
        {
            std::cout << "Button clicked\n";
        }
    );

    // Creating an edit box:
    m_editBox = m_widgetsFactories->CreateEditBox();
    m_editBox->SetText("Initial contents...");
    m_editBox->OnTextInsert()->Connect(
        [](const std::string& p_newContents)
        {
            std::cout << "New entry contents : " << p_newContents << "\n";
        }
    );

    // Creating a layout (aka container) and adding the widgets to it:
    auto layout = m_widgetsFactories->CreateLayout();
    layout->Attach(*m_label,   0, 0);
    layout->Attach(*m_button,  1, 0);
    layout->Attach(*m_editBox, 2, 0);
    
    // Creating the window:
    m_window = m_widgetsFactories->CreateWindow();
    m_window->RegisterLayout(std::move(layout));
}

void MainWindow::Show()
{
    if(m_window)
    {
        m_window->Show();
    }
}

Gtk::Window& MainWindow::ToGtk()
{
    Gtk::Window* window = dynamic_cast<Gtk::Window*>(m_window.get());
    return *window;
}

int main(int argc, char *argv[])
{
    std::cout << "Gtkmm version : " << gtk_get_major_version() << "."
                                    << gtk_get_minor_version() << "."
                                    << gtk_get_micro_version() << std::endl;

    auto app = Gtk::Application::create(argc, argv, "org.gtkmm.examples.base");
  
    const auto backendImplementation = Backend::GTKMM3;
    std::unique_ptr<IAbstractWidgetsFactory> toolkitWidgetsFactory = CreateAbstractWidgetsFactory(backendImplementation);
    std::unique_ptr<IConnectXAbstractWidgetsFactory> connectXWidgetsFactory = CreateConnectXAbstractWidgetsFactory(backendImplementation);

    WidgetsFactories factories(std::move(toolkitWidgetsFactory), std::move(connectXWidgetsFactory));

    MainWindow window{factories};
    window.Show();
  
    return app->run(window.ToGtk());
}
