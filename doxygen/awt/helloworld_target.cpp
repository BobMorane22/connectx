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
 * This is the target for the AWT hello world example. To be replaced when all the work will be
 * completed. When completed, the current example should match the code here, and this file
 * should be removed.
 *
 * @file helloworld_target.cpp
 * @date 2024
 *
 *************************************************************************************************/

//! \noop [AWT - Hello World Target]
#include <cstdlib>
#include <iostream>

#include <cxinv/assertion.h>
#include <cxcmnui/IAbstractWidgetsFactory.h>
#include <cxcmnui/IButton.h>
#include <cxcmnui/ILayout.h>
#include <cxcmnui/ISignal.h>
#include <cxcmnui/WidgetsToolkit.h>

int main(int argc, char *argv[])
{
    using namespace cx::cmn::ui;

    // Create an instance of the abstract factory
    const auto gtkApplication = Gtk::Application::create(argc, argv);
    IF_CONDITION_NOT_MET_DO(bool(gtkApplication), return EXIT_FAILURE;);

    const std::unique_ptr<IAbstractWidgetsFactory> factory = CreateFactory(argc, argv, WidgetsToolkit::GTKMM3);
    IF_CONDITION_NOT_MET_DO(factory, return EXIT_FAILURE;);

    std::unique_ptr<IWindow> mainWindow = factory->CreateWindow();
    IF_CONDITION_NOT_MET_DO(mainWindow, return EXIT_FAILURE;);

    std::unique_ptr<ILayout> mainLayout = factory->CreateLayout();
    IF_CONDITION_NOT_MET_DO(mainLayout, return EXIT_FAILURE;);

    mainWindow->RegisterLayout(*mainLayout);

    //! \noop [AWT - Create button target]
    std::unique_ptr<IButton> button = factory->CreateButton("Hello World!");
    //! \noop [AWT - Create button target]
    IF_CONDITION_NOT_MET_DO(button, return EXIT_FAILURE;);

    //! \noop [AWT - Connecting to a signal target]
    button->OnClicked()->Connect(
        []()
        {
            std::cout << "Hello World!\n";
        });
    //! \noop [AWT - Connecting to a signal target]

    mainLayout->Register(
        *button,
        {ILayout::Row{0u}, ILayout::RowSpan{1u}},
        {ILayout::Column{0u}, ILayout::ColumnSpan{1u}});

    return mainWindow->Show();
}
//! \noop [AWT - Hello world target]
