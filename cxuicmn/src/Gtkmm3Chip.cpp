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
 * @file Gtkmm3Chip.cpp
 * @date 2020
 *
 *************************************************************************************************/

#include <cxinv/assertion.h>
#include <cxuicmn/EventPropagation.h>
#include <cxuicmn/Gtkmm3Chip.h>
#include <cxuicmn/KeyboardKeyPressedEvent.h>

cx::ui::cmn::Gtkmm3Chip::Gtkmm3Chip(const cx::model::ChipColor& p_fillColor,
                              const cx::model::ChipColor& p_backgroundColor,
                              int p_width,
                              int p_height)
: m_fillColor{p_fillColor}
, m_backgroundColor{p_backgroundColor}
, m_initialBackgroundColor{p_backgroundColor}
{
    set_size_request(p_width, p_height);
}

void cx::ui::cmn::Gtkmm3Chip::SetDelegate(std::unique_ptr<IWidget> p_delegate)
{
    IF_PRECONDITION_NOT_MET_DO(p_delegate, return;);

    m_delegate = std::move(p_delegate);

    POSTCONDITION(m_delegate);
}

void cx::ui::cmn::Gtkmm3Chip::ChangeColor(const cx::model::ChipColor& p_newFillColor)
{
    if(m_fillColor != p_newFillColor)
    {
        m_fillColor = p_newFillColor;
        Redraw();
    }
}

cx::model::ChipColor cx::ui::cmn::Gtkmm3Chip::GetColor() const
{
    return m_fillColor;
}

void cx::ui::cmn::Gtkmm3Chip::Highlight()
{
    const double hue = cx::model::ComputeHue(m_backgroundColor);
    const double saturation = cx::model::ComputeSaturation(m_backgroundColor);
    double luminosity = cx::model::ComputeLuminosity(m_backgroundColor);

    luminosity *= 1.4;

    m_backgroundColor = cx::model::MakeFromHSL(hue, saturation, luminosity);
    Redraw();
}

void cx::ui::cmn::Gtkmm3Chip::UnHighlight()
{
    m_backgroundColor = m_initialBackgroundColor;
    Redraw();
}

size_t cx::ui::cmn::Gtkmm3Chip::GetWidth() const 
{
    IF_CONDITION_NOT_MET_DO(m_delegate, return 0u;);
    return m_delegate->GetWidth();
}

size_t cx::ui::cmn::Gtkmm3Chip::GetHeight() const 
{
    IF_CONDITION_NOT_MET_DO(m_delegate, return 0u;);
    return m_delegate->GetHeight();
}

void cx::ui::cmn::Gtkmm3Chip::SetEnabled(EnabledState p_enabled) 
{
    IF_CONDITION_NOT_MET_DO(m_delegate, return;);
    m_delegate->SetEnabled(p_enabled);
}

void cx::ui::cmn::Gtkmm3Chip::SetMargins(const Margins& p_newMarginSizes) 
{
    IF_CONDITION_NOT_MET_DO(m_delegate, return;);
    m_delegate->SetMargins(p_newMarginSizes);
}

void cx::ui::cmn::Gtkmm3Chip::SetTooltip(const std::string& p_tooltipContents)
{
    IF_CONDITION_NOT_MET_DO(m_delegate, return;);
    m_delegate->SetTooltip(p_tooltipContents);
}

std::unique_ptr<cx::ui::cmn::ISignal<cx::ui::cmn::EventPropagation, cx::ui::cmn::KeyboardKeyPressedEvent>> cx::ui::cmn::Gtkmm3Chip::OnKeyPressed()
{
    IF_CONDITION_NOT_MET_DO(m_delegate, return nullptr;);
    return m_delegate->OnKeyPressed();
}

void cx::ui::cmn::Gtkmm3Chip::Redraw()
{
    queue_draw();
}

bool cx::ui::cmn::Gtkmm3Chip::on_draw(const Cairo::RefPtr<Cairo::Context>& p_context)
{
    Draw(p_context);

    return true;
}

void cx::ui::cmn::Gtkmm3Chip::Draw(const Cairo::RefPtr<Cairo::Context>& p_context) const
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

    constexpr cx::model::ChipColor borderColor = cx::model::ChipColor::MakePredefined(cx::model::ChipColor::Predefined::BLACK);
    p_context->set_source_rgba(cx::model::NormalizedR(borderColor),
                               cx::model::NormalizedG(borderColor),
                               cx::model::NormalizedB(borderColor),
                               cx::model::NormalizedA(borderColor));

    p_context->stroke_preserve();
    p_context->restore();
}

void cx::ui::cmn::Gtkmm3Chip::DrawBackgroundColor(const Cairo::RefPtr<Cairo::Context>& p_context) const
{
    p_context->save();
    DrawBorder(p_context);

    p_context->set_source_rgba(cx::model::NormalizedR(m_backgroundColor),
                               cx::model::NormalizedG(m_backgroundColor),
                               cx::model::NormalizedB(m_backgroundColor),
                               cx::model::NormalizedA(m_backgroundColor));

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

void cx::ui::cmn::Gtkmm3Chip::DrawFillColor(const Cairo::RefPtr<Cairo::Context>& p_context) const
{
    p_context->set_source_rgba(cx::model::NormalizedR(m_fillColor),
                               cx::model::NormalizedG(m_fillColor),
                               cx::model::NormalizedB(m_fillColor),
                               cx::model::NormalizedA(m_fillColor));

    DrawBorder(p_context);
    p_context->fill();
}
