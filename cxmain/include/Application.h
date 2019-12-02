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
 * @file Application.h
 * @date 2019
 *
 *************************************************************************************************/

#ifndef APPLICATION_H_3ED6B0E2_2A03_4F6C_AB0C_632A2F6E855D
#define APPLICATION_H_3ED6B0E2_2A03_4F6C_AB0C_632A2F6E855D

#include <memory>

#include <IApplication.h>
#include <ICmdArgWorkflowStrategy.h>

namespace cx
{

/*********************************************************************************************//**
 * @brief Connect X application.
 *
 ************************************************************************************************/
class Application : public IApplication
{

public:

    Application(int argc, char const *argv[]);

    int Run() override;


private:

    std::unique_ptr<ICmdArgWorkflowStrategy> m_workflow;

};

} // namespace cx

#endif // APPLICATION_H_3ED6B0E2_2A03_4F6C_AB0C_632A2F6E855D
