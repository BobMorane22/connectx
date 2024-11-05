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
/**************************************************************************************************
 * Hello World example using the AWT.
 *
 * @file helloworld.cpp
 * @date 2024
 *
 *************************************************************************************************/

//! \noop [AWT - Hello World]
#include <cstdlib>
#include <iostream>

#include <cxinv/assertion.h>
#include <cxcmnui/IAbstractWidgetsFactory.h>
#include <cxcmnui/IButton.h>
#include <cxcmnui/ILayout.h>
#include <cxcmnui/ISignal.h>
#include <cxcmnuigtkmm3/widgetsFactory.h>

int main(int /*argc*/, char** /*argv*/)
{
    using namespace cx::cmn::ui;

    // Create an instance of the abstract factory
    const std::unique_ptr<IAbstractWidgetsFactory> factory = gtkmm3::CreateFactory();
    IF_CONDITION_NOT_MET_DO(factory, return EXIT_FAILURE;);

    std::unique_ptr<ILayout> mainLayout = factory->CreateLayout();
    IF_CONDITION_NOT_MET_DO(mainLayout, return EXIT_FAILURE;);

    //! \noop [AWT - Create button]
    std::unique_ptr<IButton> button = factory->CreateButton("Hello World!");
    //! \noop [AWT - Create button]
    IF_CONDITION_NOT_MET_DO(button, return EXIT_FAILURE;);

    //! \noop [AWT - Connecting to a signal]
    button->OnClicked()->Connect(
        []()
        {
            std::cout << "Hello World!\n";
        });
    //! \noop [AWT - Connecting to a signal]

    mainLayout->Register(
        *button,
        {ILayout::Row{0u}, ILayout::RowSpan{1u}},
        {ILayout::Column{0u}, ILayout::ColumnSpan{1u}});

    return EXIT_SUCCESS;
}
//! \noop [AWT - Hello World]
