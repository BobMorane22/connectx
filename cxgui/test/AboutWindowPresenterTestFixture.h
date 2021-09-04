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
 * @file AboutWindowPresenterTestFixture.h
 * @date 2020
 *
 *************************************************************************************************/

#ifndef ABOUTWINDOWPRESENTERTESTFIXTURE_H_5D562FE4_BBBF_47B1_A39F_3A64389FB0CF
#define ABOUTWINDOWPRESENTERTESTFIXTURE_H_5D562FE4_BBBF_47B1_A39F_3A64389FB0CF

#include <memory>

#include <gtest/gtest.h>

#include <cxmodel/include/IVersioning.h>
#include <cxmodel/include/NotificationContext.h>

#include <IAboutWindowPresenter.h>


class AboutWindowPresenterTestFixture : public testing::Test
{

public:

    AboutWindowPresenterTestFixture();

    cxgui::IAboutWindowPresenter& GetPresenter();
    cxmodel::IVersioning& GetModel();

private:

    class AboutWindowPresenterModelMock : public cxmodel::ModelSubject,
                                          public cxmodel::IVersioning
    {

    public:

        // Subject:
        ~AboutWindowPresenterModelMock() = default;

        // IVersionning:
        virtual std::string GetName() const
        {
            return "Connect X";
        }

        virtual std::string GetVersionNumber() const
        {
            return "v0.0";
        }
    };

    std::unique_ptr<cxgui::IAboutWindowPresenter> m_presenter;
    std::unique_ptr<AboutWindowPresenterModelMock> m_model;

};

#endif // ABOUTWINDOWPRESENTERTESTFIXTURE_H_5D562FE4_BBBF_47B1_A39F_3A64389FB0CF
