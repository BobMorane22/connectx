/**************************************************************************************************
 *  This file is part of Connect X.
 *
 *  Connect X is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.
 *
 *  Connect X is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with Connect X. If not, see <https://www.gnu.org/licenses/>.
 *
 *************************************************************************************************/
/**********************************************************************************************//**
 * @file Gtkmm3Label.h
 * @date 2024
 *
 *************************************************************************************************/

#ifndef _H_B84CA49F_51D9_4CCA_944E_42D742A18DDD
#define _H_B84CA49F_51D9_4CCA_944E_42D742A18DDD

#include <gtkmm/label.h>

#include <cxgui/ILabel.h>

namespace cxgui
{

class Gtkmm3Label : public ILabel,
                    public Gtk::Label
{

public:

    /*******************************************************************************************//**
     * @brief Constructor.
     *
     * @param p_contents
     *      The textual contents to appear on the label.
     *
     **********************************************************************************************/
    explicit Gtkmm3Label(const std::string& p_contents);

    /*******************************************************************************************//**
     * @brief Sets the delegate for widget common facilities.
     *
     * The delegate is reponsible to carry the implementation for generic `cxgui::IWidget` operations.
     * It is meant to avoid implementation duplication.
     *
     * @param p_delegate
     *      The widget delegate.
     *
     * @pre
     *      The widget delegate instance given as an argument is valid.
     * @post
     *      The registered widget delegate is valid.
     *
     **********************************************************************************************/
    void SetDelegate(std::unique_ptr<IWidget> p_delegate);

    // cxgui::Ilabel:
    void UpdateContents(const std::string& p_newContents) override;
    [[nodiscard]] std::string GetContents() const override;

    // cxgui::IWidget:
    [[nodiscard]] size_t GetWidth() const override;
    [[nodiscard]] size_t GetHeight() const override;
    void SetEnabled(EnabledState p_enabled) override;
    void SetMargins(const Margins& p_newMarginSizes) override;
    void SetTooltip(const std::string& p_tooltipContents) override;

private:

    std::unique_ptr<IWidget> m_delegate;

};

} // namespace cxgui

#endif // _H_B84CA49F_51D9_4CCA_944E_42D742A18DDD
