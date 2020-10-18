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
 * @file Chip.cpp
 * @date 2020
 *
 *************************************************************************************************/

#include <algorithm>

#include <Chip.h>

cxgui::Chip::Chip(const cxmodel::ChipColor& p_fillColor, const cxmodel::ChipColor& p_backgroundColor)
: m_fillColor{p_fillColor}
, m_backgroundColor{p_backgroundColor}
{
    set_size_request(40, 40);
}

void cxgui::Chip::ChangeColor(const cxmodel::ChipColor& p_newFillColor)
{
    if(m_fillColor != p_newFillColor)
    {
        m_fillColor = p_newFillColor;
        Redraw();
    }
}

cxmodel::ChipColor cxgui::Chip::GetColor() const
{
    return m_fillColor;
}

void cxgui::Chip::Redraw()
{
    queue_draw();
}

bool cxgui::Chip::on_draw(const Cairo::RefPtr<Cairo::Context>& p_context)
{
    Draw(p_context);

    return true;
}

void cxgui::Chip::Draw(const Cairo::RefPtr<Cairo::Context>& p_context) const
{
    const Gtk::Allocation allocation{get_allocation()};

    const int width{allocation.get_width()};
    const int height{allocation.get_height()};
    const int smallestDimension{std::min(width, height)};

    DrawBackgroundColor(p_context);
    DrawFillColor(p_context);

    p_context->set_line_width(smallestDimension * 2 * 0.02);
    p_context->save();

    DrawBorder(p_context);

    constexpr cxmodel::ChipColor borderColor = cxmodel::ChipColor::MakePredefined(cxmodel::ChipColor::Predefined::BLACK);
    p_context->set_source_rgba(cxmodel::NormalizedR(borderColor),
                               cxmodel::NormalizedG(borderColor),
                               cxmodel::NormalizedB(borderColor),
                               cxmodel::NormalizedA(borderColor));

    p_context->stroke_preserve();
    p_context->restore();
}

void cxgui::Chip::DrawBackgroundColor(const Cairo::RefPtr<Cairo::Context>& p_context) const
{
    p_context->save();
    DrawBorder(p_context);

    p_context->set_source_rgba(cxmodel::NormalizedR(m_backgroundColor),
                               cxmodel::NormalizedG(m_backgroundColor),
                               cxmodel::NormalizedB(m_backgroundColor),
                               cxmodel::NormalizedA(m_backgroundColor));

    const Gtk::Allocation allocation{get_allocation()};
    const int width{allocation.get_width()};
    const int height{allocation.get_height()};

    p_context->move_to(0    , 0     );
    p_context->line_to(width, 0     );
    p_context->line_to(width, height);
    p_context->line_to(0    , height);
    p_context->line_to(0    , 0     );

    p_context->set_fill_rule(Cairo::FILL_RULE_EVEN_ODD);

    p_context->fill();
    p_context->restore();
}

void cxgui::Chip::DrawFillColor(const Cairo::RefPtr<Cairo::Context>& p_context) const
{
    p_context->set_source_rgba(cxmodel::NormalizedR(m_fillColor),
                               cxmodel::NormalizedG(m_fillColor),
                               cxmodel::NormalizedB(m_fillColor),
                               cxmodel::NormalizedA(m_fillColor));

    DrawBorder(p_context);
    p_context->fill();
}
