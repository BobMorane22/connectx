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
 * @file widgetsFactory.cpp
 * @date 2024
 *
 *************************************************************************************************/

#include <gtkmm/application.h>

#include <cxui/WidgetsFactories.h>
#include <cxcmnuigtkmm3/AbstractWidgetsFactory.h>
#include <cxuigtkmm3/AbstractConnectXWidgetsFactory.h>
#include <cxuigtkmm3/widgetsFactory.h>

[[nodiscard]] std::unique_ptr<cx::ui::IAbstractConnectXWidgetsFactory> cx::ui::gtkmm3::CreateFactory(
    cx::cmn::ui::IAbstractWidgetsFactory& p_stdAbstractWidgetsFactory)
{
    auto* standardAbstractWidgetsFactory = dynamic_cast<cx::cmn::ui::gtkmm3::AbstractWidgetsFactory*>(&p_stdAbstractWidgetsFactory);
    IF_CONDITION_NOT_MET_DO(standardAbstractWidgetsFactory, return nullptr;);

    Glib::RefPtr<Gtk::Application> gtkApplication = standardAbstractWidgetsFactory->GetGtkApplication();
    IF_CONDITION_NOT_MET_DO(bool(gtkApplication), return nullptr;);

    auto factory = std::make_unique<AbstractConnectXWidgetsFactory>(gtkApplication);
    IF_PRECONDITION_NOT_MET_DO(factory, return nullptr;);

    factory->RegisterStandardWidgetsFactory(p_stdAbstractWidgetsFactory);

    POSTCONDITION(factory != nullptr);

    return factory;
}
