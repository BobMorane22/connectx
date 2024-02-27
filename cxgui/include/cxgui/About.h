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
 * @file About.h
 * @date 2020
 *
 *************************************************************************************************/

#ifndef ABOUT_H_396864CD_88A3_43F2_B08B_3F9FEBE89DE1
#define ABOUT_H_396864CD_88A3_43F2_B08B_3F9FEBE89DE1

#include <gtkmm/window.h>

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
 * @brief About window.
 *
 *************************************************************************************************/
class About : public Gtkmm3Window
{

public:

    /******************************************************************************************//**
     * @brief Constructor.
     *
     * @param p_presenter
     *      An about window presenter implemetation.
     *
     *********************************************************************************************/
    About(std::unique_ptr<IAboutWindowPresenter>&& p_presenter);

    // cxmodel::IModelObserver:
    void Update(cxmodel::ModelNotificationContext p_context, cxmodel::ModelSubject* p_subject) override;


private:

    void ConfigureWindow() override;
    void RegisterLayouts() override;
    void RegisterWidgets() override;
    void ConfigureLayouts() override;
    void ConfigureWidgets() override;
    void ConfigureSignalHandlers() override;

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

#endif // ABOUT_H_396864CD_88A3_43F2_B08B_3F9FEBE89DE1
