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
 * @date 2019
 *
 *************************************************************************************************/

#include <memory>

#include <cxmodel/include/Model.h>

#include <Application.h>

int main(int argc, char *argv[])
{
    cxmodel::Model concreteModel;
    cxmodel::IModel& model = concreteModel;

    std::unique_ptr<cx::IApplication> app = std::make_unique<cx::Application>(argc, argv, model);

    return app->Run();
}
