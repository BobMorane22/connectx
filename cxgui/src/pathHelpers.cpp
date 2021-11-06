#include <cairomm/context.h>

#include <cxmath/include/math.h>
#include <cxmath/include/Position.h>

#include "pathHelpers.h"

void cxgui::MakeRectanglarPath(const Cairo::RefPtr<Cairo::Context>& p_context,
                               const cxmath::Position& p_topLeft,
                               double p_height,
                               double p_width)
{
    p_context->move_to(p_topLeft.m_x, p_topLeft.m_y);
    p_context->line_to(p_topLeft.m_x + p_width, p_topLeft.m_y);
    p_context->line_to(p_topLeft.m_x + p_width, p_topLeft.m_y + p_height);
    p_context->line_to(p_topLeft.m_x, p_topLeft.m_y + p_height);
    p_context->line_to(p_topLeft.m_x, p_topLeft.m_y);
}

void cxgui::MakeCircularPath(const Cairo::RefPtr<Cairo::Context>& p_context,
                             const cxmath::Position& p_centerPosition,
                             double p_radius)
{
    
    // We draw an arc from 0 to 2pi at the specified center position:
    p_context->arc(p_centerPosition.m_x,
                   p_centerPosition.m_y,
                   p_radius,
                   0.0,
                   2.0 * cxmath::pi<double>);
}
