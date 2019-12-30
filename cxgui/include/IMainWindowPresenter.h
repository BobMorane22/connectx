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
 * @file IMainWindowPresenter.h
 * @date 2019
 *
 *************************************************************************************************/

#ifndef IMAINWINDOWPRESENTER_H_D8C76920_83D9_4D15_B95A_63282E742221
#define IMAINWINDOWPRESENTER_H_D8C76920_83D9_4D15_B95A_63282E742221

#include <cxmodel/include/IObserver.h>
#include <cxmodel/include/Subject.h>

namespace cxgui
{

/*********************************************************************************************//**
 * @brief Interface for creating a main window presenter.
 *
 * The main window presenter is responsible for making sure the UI logic is up to date, in
 * a UI framework independent fashion. This makes it possible to create a main window with
 * minimal logic.
 *
 * @note Because the class inherits the cxmodel::Subject class, which is an abstract class,
 *       this class is not a pure interface. It is named as if it were a pure interface
 *       because conceptually, it acts like one as far as the presenter is concerned.
 *
 ************************************************************************************************/
class IMainWindowPresenter : public cxmodel::IObserver, public cxmodel::Subject
{

public:

    /******************************************************************************************//**
     * @brief Default destructor.
     *
     ********************************************************************************************/
    virtual ~IMainWindowPresenter() = default;

    /******************************************************************************************//**
     * @brief Checks if the "Reinitialize" button is enabled.
     *
     * @return @c true if the button is enabled, @c false otherwise.
     *
     ********************************************************************************************/
    virtual bool IsReinitializeBtnEnabled() const = 0;

    /******************************************************************************************//**
     * @brief Accesses the current counter value.
     *
     * @return The current counter value.
     *
     ********************************************************************************************/
    virtual unsigned int GetCounterValue() const = 0;

    /******************************************************************************************//**
     * @brief Accesses the "Increment" button label.
     *
     * @return The "Increment" button label.
     *
     ********************************************************************************************/
    virtual std::string GetIncrementBtnLabel() const = 0;

    /******************************************************************************************//**
     * @brief Accesses the "Reinitialize" button label.
     *
     * @return The "Reinitialize" button label.
     *
     ********************************************************************************************/
    virtual std::string GetReinitializeBtnLabel() const = 0;

};

} // namespace cxgui

#endif // IMAINWINDOWPRESENTER_H_D8C76920_83D9_4D15_B95A_63282E742221
