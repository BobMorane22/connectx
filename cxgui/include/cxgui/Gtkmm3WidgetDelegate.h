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
 * @file Gtkmm3WidgetDelegate.h
 * @date 2023
 *
 *************************************************************************************************/

#ifndef GTKMM3WIDGETDELEGATE_H_9F639EAC_D67C_40B9_8652_436419A7E59E
#define GTKMM3WIDGETDELEGATE_H_9F639EAC_D67C_40B9_8652_436419A7E59E

#include <memory>

#include <cxstd/helpers.h>
#include <cxgui/IWidget.h>

namespace Gtk
{
    class Widget;
}

namespace cxgui
{
    enum class EnabledState;
    struct Margins;
}

namespace cxgui
{

/**********************************************************************************************//**
 * @brief Delegate for generic widget facilities.
 *
 * This delegate contains the implementation for all generic widget facilities. All
 * Widgets implementing the `cxgui::IWidget` interface should use this delegate to
 * avoid duplicating implementations. The delegate also implements this inteface
 * so direct delegation is always possible (i.e no additionnal work is needed, calls
 * may simply be forwarded to the delegate).
 *
 *************************************************************************************************/
class Gtkmm3WidgetDelegate : public IWidget
{

public:

    /******************************************************************************************//**
     * @brief Sets the underlying Gtkmm3 widget instance to operate on.
     *
     * @param p_underling.
     *      The address of the underlying Gtkmm 3 widget instance.
     *
     * @pre
     *      The supplied address is valid.
     *
     * @post
     *      The underlying address is valid.
     *
     *********************************************************************************************/
    void SetUnderlying(Gtk::Widget* p_underlying);

    // cxgui::IWidget:
    [[nodiscard]] size_t GetWidth() const override;
    [[nodiscard]] size_t GetHeight() const override;
    void SetEnabled(EnabledState p_enabled) override;
    void SetMargins(const Margins& p_newMarginSizes) override;
    void SetTooltip(const std::string& p_tooltipContents) override;

private:

    Gtk::Widget* m_underlying = nullptr;

};

/**********************************************************************************************//**
 * @brief Creates a widget with a valid widget delegate.
 *
 * @tparam Widget
 *      The target widget type.
 * @tparam Args  
 *      The parameters types needed to create the widget, in the same order as what
 *      is requested by the widget's contructor.
 *
 * @param p_args
 *      Parameters needed to create the widget. These are the same parameters you would
 *      use to call the widget's constrcutor (in the same order).
 *
 * @return
 *      A widget of type `Widget` configured with a valid widget delegate.
 *
 *************************************************************************************************/
template<typename Widget, typename... Args>
[[nodiscard]] std::unique_ptr<Widget> CreateWidget(Args&&... p_args)
{
    auto widget = std::make_unique<Widget>(std::forward<Args>(p_args)...);
    IF_CONDITION_NOT_MET_DO(widget, return nullptr;);

    auto* gtkWidget = dynamic_cast<Gtk::Widget*>(widget.get());
    IF_CONDITION_NOT_MET_DO(gtkWidget, return nullptr;);

    auto delegate = std::make_unique<Gtkmm3WidgetDelegate>();
    IF_CONDITION_NOT_MET_DO(delegate, return nullptr;);

    delegate->SetUnderlying(gtkWidget);
    widget->SetDelegate(std::move(delegate));

    return widget;
}

} // namespace cxgui

#endif // GTKMM3WIDGETDELEGATE_H_9F639EAC_D67C_40B9_8652_436419A7E59E
