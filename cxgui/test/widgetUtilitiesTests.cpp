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
 * @file widgetUtilitiesTests.cpp
 * @date 2024
 *
 *************************************************************************************************/

#include <tuple>

#include <gtest/gtest.h>

#include <cxunit/NotImplementedException.h>
#include <cxgui/EnabledState.h>
#include <cxgui/IWidget.h>
#include <cxgui/Margins.h>
#include <cxgui/widgetUtilities.h>

template<typename... MethodArgumentTypes>
struct MethodCallSpy
{
    size_t m_numberOfCalls = 0u;
    std::vector<std::tuple<MethodArgumentTypes...>> m_arguments;
};

class WidgetMock : public cxgui::IWidget
{

public:

    // cxgui::IWidget:
    [[nodiscard]] size_t GetWidth() const override;
    [[nodiscard]] size_t GetHeight() const override;
    void SetEnabled(cxgui::EnabledState p_enabled) override;
    void SetMargins(const cxgui::Margins& p_newMarginSizes) override;
    void SetTooltip(const std::string& p_tooltipContents) override;

    // Mocking:
    [[nodiscard]] const MethodCallSpy<cxgui::EnabledState>& GetSetEnabledSpy() const {return m_setEnabledSpy;}

private:

    MethodCallSpy<cxgui::EnabledState> m_setEnabledSpy;

};

size_t WidgetMock::GetWidth() const
{
    throw cxunit::NotImplementedException();    
}

size_t WidgetMock::GetHeight() const
{
    throw cxunit::NotImplementedException();    
}

void WidgetMock::SetEnabled(cxgui::EnabledState p_enabled)
{
    m_setEnabledSpy.m_numberOfCalls += 1u;
    m_setEnabledSpy.m_arguments.emplace_back(std::tuple<cxgui::EnabledState>(p_enabled));
}

void WidgetMock::SetMargins(const cxgui::Margins& /*p_newMarginSizes*/)
{
    throw cxunit::NotImplementedException();    
}

void WidgetMock::SetTooltip(const std::string& /*p_tooltipContents*/)
{
    throw cxunit::NotImplementedException();    
}

TEST(EnabledStateUpdate, EnabledStateUpdate_ConditionFalse_WidgetDisabled)
{
    WidgetMock widget;
    const auto& spy = widget.GetSetEnabledSpy();

    ASSERT_TRUE(spy.m_numberOfCalls == 0u);

    cxgui::EnabledStateUpdate(widget, false);

    ASSERT_TRUE(spy.m_numberOfCalls == 1u);
    ASSERT_TRUE(std::get<0>(spy.m_arguments[0u]) == cxgui::EnabledState::Disabled);
}

TEST(EnabledStateUpdate, EnabledStateUpdate_ConditionTrue_WidgetEnabled)
{
    WidgetMock widget;
    const auto& spy = widget.GetSetEnabledSpy();

    ASSERT_TRUE(spy.m_numberOfCalls == 0u);

    cxgui::EnabledStateUpdate(widget, true);

    ASSERT_TRUE(spy.m_numberOfCalls == 1u);
    ASSERT_TRUE(std::get<0>(spy.m_arguments[0u]) == cxgui::EnabledState::Enabled);
}
