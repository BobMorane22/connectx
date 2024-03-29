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
 * @file UIManagerFactory.h
 * @date 2024
 *
 *************************************************************************************************/

#ifndef UIMANAGERFACTORY_H_0F42DD83_2399_4359_B3B2_904735C690AE
#define UIMANAGERFACTORY_H_0F42DD83_2399_4359_B3B2_904735C690AE

#include <memory>

namespace cxgui
{
    enum class WidgetsToolkit;
}

namespace cx
{
    class IUIManager;
    class ModelReferences;
}

namespace cx
{

/**********************************************************************************************//**
 * @brief Factory for User Interface (UI) managers.
 *
 *************************************************************************************************/
class UIManagerFactory final
{

public:

    /******************************************************************************************//**
     * @brief Constructor.
     *
     * @param argc
     *      Command line argument count.
     * @param argv
     *      A C-style array of arguments.
     * @param p_model
     *      References to a Connect X compatible model.
     *
     * @pre
     *      The argument count is at least 1.
     * @pre
     *      The argument list is not @c nullptr.
     *
     ********************************************************************************************/
    UIManagerFactory(int argc, char *argv[], cx::ModelReferences& p_model);

    /******************************************************************************************//**
     * @brief Create a UI manager related to some UI toolkit.
     *
     * @param p_toolkit
     *      The UI toolkit for which to create a manager.
     *
     * @return
     *      The manager.
     *
     ********************************************************************************************/
    [[nodiscard]] std::unique_ptr<IUIManager> Create(cxgui::WidgetsToolkit p_toolkit) const;

private:

    int m_argc;
    char** m_argv;
    cx::ModelReferences& m_model;

};

} // namespace cx

#endif // UIMANAGERFACTORY_H_0F42DD83_2399_4359_B3B2_904735C690AE
