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
 * @file ModelTestHelpers.h
 * @date 2020
 *
 *************************************************************************************************/

#include <NotificationContext.h>

/*********************************************************************************************//**
 * @brief Make sure a notification has been sent by the model.
 *
 * Use this class to attach to the model as an observer and check for some specific context.
 * Usual usage is to make sure that when a certain method is called on the model, some specific
 * notification is sent.
 *
 ************************************************************************************************/
class ModelNotificationCatcher : public cxmodel::IModelObserver
{

public:

    /*****************************************************************************************//**
     * @brief Constructor.
     *
     * @param p_contextUnderTest The notification context to catch.
     *
     ********************************************************************************************/
    ModelNotificationCatcher(cxmodel::NotificationContext p_contextUnderTest);

    /*****************************************************************************************//**
     * @brief Destructor.
     *
     ********************************************************************************************/
    ~ModelNotificationCatcher() override;

    /*****************************************************************************************//**
     * @brief Indicates if the notification context under test has been caught.
     *
     * @return `true` if it has, `false` otherwise.
     *
     ********************************************************************************************/
    bool WasNotified() const;

    // cxmodel::IObserver:
    void Update(cxmodel::NotificationContext p_context, cxmodel::ModelSubject* p_subject) override;

private:

    const cxmodel::NotificationContext m_contextUnderTest;
    bool m_wasNotified = false;
};
