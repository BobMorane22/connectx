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
 * @file Gtkmm3AboutWindow.h
 * @date 2020
 *
 *************************************************************************************************/

#ifndef GTKMM3ABOUTWINDOW_H_396864CD_88A3_43F2_B08B_3F9FEBE89DE1
#define GTKMM3ABOUTWINDOW_H_396864CD_88A3_43F2_B08B_3F9FEBE89DE1

#include "IAboutWindowPresenter.h"
#include "Gtkmm3Window.h"

namespace cxgui
{
    class IButton;
    class ILabel;
}

namespace cxgui
{

/**********************************************************************************************//**
 * @brief Gtkmm3 About window.
 *
 *************************************************************************************************/
class Gtkmm3AboutWindow : public Gtkmm3Window
{

public:

    /******************************************************************************************//**
     * @brief Constructor.
     *
     * @param p_presenter
     *      An about window presenter implemetation.
     *
     *********************************************************************************************/
    explicit Gtkmm3AboutWindow(std::unique_ptr<IAboutWindowPresenter> p_presenter);

    // cxmodel::IModelObserver:
    void Update(cxmodel::ModelNotificationContext p_context, cxmodel::ModelSubject* p_subject) final;

private:

    void ConfigureWindow() final;
    void RegisterLayouts() final;
    void RegisterWidgets() final;
    void ConfigureLayouts() final;
    void ConfigureWidgets() final;
    void ConfigureSignalHandlers() final;

    std::unique_ptr<IAboutWindowPresenter> m_presenter;

    std::unique_ptr<ILabel> m_name;
    std::unique_ptr<ILabel> m_version;
    std::unique_ptr<ILabel> m_description;
    std::unique_ptr<ILabel> m_website;
    std::unique_ptr<ILabel> m_license;
    std::unique_ptr<ILabel> m_copyright;

    std::unique_ptr<IButton> m_close;

};

} // namespace cxgui

#endif // GTKMM3ABOUTWINDOW_H_396864CD_88A3_43F2_B08B_3F9FEBE89DE1
