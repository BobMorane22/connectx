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
 * @file ILayout.h
 * @date 2023
 *
 *************************************************************************************************/

#ifndef ILAYOUT_H_D6AEBC20_3580_4018_B083_08451439CC56
#define ILAYOUT_H_D6AEBC20_3580_4018_B083_08451439CC56

#include <cxstd/StrongType.h>
#include <cxmodel/common.h>
#include <cxgui/IWidget.h>

namespace cxgui
{
    struct Margins;
}
 
namespace Gtk
{
    class Widget;
}

namespace cxgui
{

/**********************************************************************************************//**
 * @brief Layout for widgets (and other layouts).
 *
 * In a typical window, more than one widget is shown. In these situations, the widgets need
 * some layout system to position themselves with respect to the other widgets.
 * 
 * Using this interface, one can register widgets by specifying their coordinates (row and column)
 * in the layout and their span (for each coordinate).
 *
 * The layout coordinates are referenced as follow:
 *
 @verbatim

                                  0   1   2   3  (Column)
                                 +---+---+---+---+--- ...
                               0 |   |   |   |   |
                                 +---+---+---+---+--- ...
                               1 |   |   |   |   |
                                 +---+---+---+---+--- ...
                               2 |   |   |   |   |
                                 +---+---+---+---+--- ...
                        (Row)  3 |   |   |   |   |
                                 +---+---+---+---+--- ...
                                 |   |   |   |   |
                                 .
                                 .
                                 .

 @endverbatim
 *
 * For more complex scenarios, already existing layouts can be registered to a new layout, making
 * layouts composition possible.
 *
 * @note The layout does not own the widgets it arranges.
 *
 *************************************************************************************************/
class ILayout : public IWidget
{

public:

    /******************************************************************************************//**
     * @brief Describes a number of rows needed to arrange some widget in a layout.
     *
     * A row span of 2 means that the widget requires two rows in the layout. For example:
     *
     @verbatim
    
                                            +----------+
                                            | Button   |
                                            +----------+
                                            | EditBox  |
                                            +----------+
                                            |          |
                                            | Label    |
                                            +----------+
    
     @endverbatim
     *
     * In this case, both the button and the edit box have a row span of one. The label, however
     * is displayed over two rows and hence has a row span of 2.
     *
     *********************************************************************************************/
    using RowSpan = cxstd::StrongType<size_t, struct RowSpanTag, cxstd::Addable, cxstd::Comparable>;
    
    /******************************************************************************************//**
     * @brief Describes a number of columns needed to arrange some widget in a layout.
     *
     * A column span of 2 means that the widget requires two columns in the layout. For example:
     *
     @verbatim
    
                                       +---------+---------+
                                       | Button  | EditBox |
                                       +---------+---------+
                                       |       Label       |
                                       +-------------------+
    
     @endverbatim
     *
     * In this case, both the button and the edit box have a column span of one. The label, however
     * is displayed over two columns and hence has a column span of 2.
     *
     *********************************************************************************************/
    using ColumnSpan = cxstd::StrongType<size_t, struct RowSpanTag, cxstd::Addable, cxstd::Comparable>;

    /******************************************************************************************//**
     * @brief Necessary information to position a widget in a layout.
     *
     * @tparam Coordinate Coordinate type (row or column).
     * @tparam Span       Span type (row or column).
     *
     *********************************************************************************************/
    template<typename Coordinate, typename Span>
    struct CoordinateDescriptor
    {
        /******************************************************************************************//**
         * @brief Constructor.
         *
         * @param p_coordinate
         *      The coordinate where the widget should be registered in the layout.
         * @param p_span
         *      The number of coordinate unit needed by the widget in the layout.
         *
         *********************************************************************************************/
        constexpr CoordinateDescriptor(const Coordinate& p_coordinate, const Span& p_span)
        : m_coordinate{p_coordinate}
        , m_span{p_span}
        {
        }
    
        Coordinate m_coordinate;
        Span m_span;
    };

    /******************************************************************************************//**
     * @brief Necessary row information to position a widget in a layout.
     *
     *********************************************************************************************/
    using RowDescriptor = CoordinateDescriptor<cxmodel::Row, RowSpan>;
    
    /******************************************************************************************//**
     * @brief Necessary column information to position a widget in a layout.
     *
     *********************************************************************************************/
    using ColumnDescriptor = CoordinateDescriptor<cxmodel::Column, ColumnSpan>;

    /******************************************************************************************//**
     * @brief Row spacing modes.
     *
     *********************************************************************************************/
    enum class RowSpacingMode
    {
        /** All layout rows are equaly spaced. */
        EQUAL, 
    
        /** All layout rows adapt their size according to their children sizes. */
        INDEPENDANT,
    };
    
    /******************************************************************************************//**
     * @brief Column spacing modes.
     *
     *********************************************************************************************/
    enum class ColumnSpacingMode
    {
        /** All layout columns are equaly spaced. */
        EQUAL,
    
        /** All layout columns adapt their size according to their children sizes. */
        INDEPENDANT,
    };

    /******************************************************************************************//**
     * @brief Widget vertical alignement inside the layout.
     *
     *********************************************************************************************/
    enum class VerticalAlignement
    {
        /** Widget is aligned to the top of the layout cell. The widget does not vertically stretch. */
        TOP,

        /** Widget is aligned to the center of the layout cell. The widget does not vertically stretch. */
        CENTER,

        /** Widget is aligned to the bottom of the layout cell. The widget does not vertically stretch. */
        BOTTOM,

        /** Widget vertically stretches to fill the whole layout cell. */
        FILL,
    };

    /******************************************************************************************//**
     * @brief Widget horizontal alignement inside the layout.
     *
     *********************************************************************************************/
    enum class HorizontalAlignement
    {
        /** Widget is aligned to the left of the layout cell. The widget does not horizontally stretch. */
        LEFT,

        /** Widget is aligned to the center of the layout cell. The widget does not horizontally stretch. */
        CENTER,

        /** Widget is aligned to the right of the layout cell. The widget does not horizontally stretch. */
        RIGHT,

        /** Widget horizontally stretches to fill the whole layout cell. */
        FILL,
    };

    /******************************************************************************************//**
     * @brief Widget alignement inside the layout.
     *
     *********************************************************************************************/
    struct Alignement
    {

        /**************************************************************************************//**
         * @brief Default constructor.
         *
         * The widget fills the whole layout cell both vertically and horizontally.
         *
         *****************************************************************************************/
        constexpr Alignement()
        :Alignement(VerticalAlignement::FILL, HorizontalAlignement::FILL)
        {}

        /**************************************************************************************//**
         * @brief Constructor.
         *
         * @param p_vertical
         *      The widget's vertical alignement within its layout cell.
         * @param p_horizontal
         *      The widget's horizontal alignement within its layout cell.
         *
         *****************************************************************************************/
        constexpr Alignement(VerticalAlignement p_vertical, HorizontalAlignement p_horizontal)
        : m_vertical{p_vertical}
        , m_horizontal{p_horizontal}
        {
        }

        VerticalAlignement m_vertical;
        HorizontalAlignement m_horizontal;
    };

public:

    /******************************************************************************************//**
     * @brief Register a widget to the layout.
     *
     * @param p_widget
     *      The widget to register to the layout.
     * @param p_row
     *      Description of where to register the widget, vertically.
     * @param p_column
     *      Description of where to register the widget, horizontally.
     * @param p_alignement
     *      The widget's alignement from within it's layout cell. By default, widgets fill the
     *      entire layout cell.
     *
     *********************************************************************************************/
    virtual void Register(IWidget& p_widget,
                          const RowDescriptor& p_row,
                          const ColumnDescriptor& p_column,
                          const Alignement& p_alignement = {}) = 0;

    /******************************************************************************************//**
     * @brief Register a Gtkmm widget to the layout.
     *
     * @param p_gtkWidget
     *      The Gtkmm widget to register to the layout.
     * @param p_row
     *      Description of where to register the widget, vertically.
     * @param p_column
     *      Description of where to register the widget, horizontally.
     * @param p_alignement
     *      The widget's alignement from within it's layout cell. By default, widgets fill the
     *      entire layout cell.
     *
     * @warning
     *      This call is temporary. It will be removed once all widgets will have been
     *      abstracted away (TG-256).
     *
     *********************************************************************************************/
    virtual void Register(Gtk::Widget& p_gtkWidget,
                          const RowDescriptor& p_row,
                          const ColumnDescriptor& p_column,
                          const Alignement& p_alignement = {}) = 0;

    /******************************************************************************************//**
     * @brief Unregister a widget from the layout.
     *
     * @param p_widget
     *      The widget to unregister from the layout.
     *
     *********************************************************************************************/
    virtual void Unregister(IWidget& p_widget) = 0;

    /******************************************************************************************//**
     * @brief Unregister a Gtkmm widget from the layout.
     *
     * @param p_gtkWidget
     *      The Gtkmm widget to unregister from the layout.
     *
     * @warning
     *      This call is temporary. It will be removed once all widgets will have been
     *      abstracted away (TG-256).
     *
     *********************************************************************************************/
    virtual void Unregister(Gtk::Widget& p_gtkWidget) = 0;

    /******************************************************************************************//**
     * @brief Get the registered widget at the specified location.
     *
     * @param p_row
     *      The row in which the widget is located.
     * @param p_column
     *      The column in which the widget is located.
     *
     * @return
     *      The widget's address, or `nullptr` otherwise.
     *
     *********************************************************************************************/
    [[nodiscard]] virtual const IWidget* GetWidgetAtPosition(const cxmodel::Row& p_row, const cxmodel::Column& p_column) const = 0;

    /******************************************************************************************//**
     * @copydoc cxgui::ILayout::GetWidgetAtPosition
     *
     *********************************************************************************************/
    [[nodiscard]] virtual IWidget* GetWidgetAtPosition(const cxmodel::Row& p_row, const cxmodel::Column& p_column) = 0;

    /******************************************************************************************//**
     * @brief Changes the row spacing mode. Affects all rows in the layout.
     *
     * @param p_newMode
     *      The new row spacing mode.
     *
     *********************************************************************************************/
    virtual void SetRowSpacingMode(RowSpacingMode p_newMode) = 0;

    /******************************************************************************************//**
     * @brief Changes the column spacing mode. Affects all columns in the layout.
     *
     * @param p_newMode
     *      The new column spacing mode.
     *
     *********************************************************************************************/
    virtual void SetColumnSpacingMode(ColumnSpacingMode p_newMode) = 0;

};

} // namespace cxgui

#endif // ILAYOUT_H_D6AEBC20_3580_4018_B083_08451439CC56
