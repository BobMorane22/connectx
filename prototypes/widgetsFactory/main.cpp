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

#include "IAbstractWidgetsFactory.h"
#include "IButton.h"
#include "IEditBox.h"
#include "ILayout.h"

class MainWindow : public Gtk::ApplicationWindow
{

public:

    MainWindow();

private:

    std::unique_ptr<IAbstractWidgetsFactory> m_widgetsFactory;

    std::unique_ptr<IButton>  m_button;
    std::unique_ptr<IEditBox> m_editBox;

    std::unique_ptr<ILayout> m_layout;

};

MainWindow::MainWindow()
{
    m_widgetsFactory = CreateAbstractWidgetsFactory(Backend::GTKMM3);

    // Creating a button:
    m_button = m_widgetsFactory->CreateButton();
    m_button->SetText("test");
    m_button->OnClicked()->Connect(
        []()
        {
            std::cout << "Button clicked\n";
        }
    );

    // Creating an edit box:
    m_editBox = m_widgetsFactory->CreateEditBox();
    m_editBox->SetText("Initial contents...");
    m_editBox->OnTextInsert()->Connect(
        [](const std::string& p_newContents)
        {
            std::cout << "New entry contents : " << p_newContents << "\n";
        }
    );

    // Creating a layout (aka container) and adding the widgets to it:
    m_layout = m_widgetsFactory->CreateLayout();
    m_layout->Attach(*m_button,  0, 0);
    m_layout->Attach(*m_editBox, 1, 0);
    
    add(*(dynamic_cast<Gtk::Grid*>(m_layout.get())));
}

int main(int argc, char *argv[])
{
    std::cout << "Gtkmm version : " << gtk_get_major_version() << "."
                                    << gtk_get_minor_version() << "."
                                    << gtk_get_micro_version() << std::endl;

    auto app = Gtk::Application::create(argc, argv, "org.gtkmm.examples.base");
  
    MainWindow window;
    window.show_all();
  
    return app->run(window);
}
