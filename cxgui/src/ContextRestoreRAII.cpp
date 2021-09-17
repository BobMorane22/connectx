#include <cairomm/context.h>

#include <cxinv/include/assertion.h>

#include "ContextRestoreRAII.h"

cxgui::ContextRestoreRAII::ContextRestoreRAII(const Cairo::RefPtr<Cairo::Context>& p_context)
: m_context{p_context}
{
    ASSERT_MSG(bool(m_context), "Invalid context.");
    m_context->save();
}

cxgui::ContextRestoreRAII:: ~ContextRestoreRAII()
{
    ASSERT_MSG(bool(m_context), "Invalid context.");
    m_context->restore();
}

