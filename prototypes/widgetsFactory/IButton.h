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
 * @file IButton.h
 * @date 2023
 *
 *************************************************************************************************/
#pragma once

#include <memory>
#include <string>

#include "IWidget.h"

template<typename ReturnType, typename... Arguments>
class ISignal;

/**************************************************************************************************
 * Clickable button.
 *
 *************************************************************************************************/
class IButton : public IWidget
{

public:

    virtual ~IButton() = default;

    // IWidget:
    void Show() override = 0;

    // IButton:
    virtual void SetText(const std::string& p_text) = 0;
    virtual std::unique_ptr<ISignal<void>> OnClicked() = 0;
};
