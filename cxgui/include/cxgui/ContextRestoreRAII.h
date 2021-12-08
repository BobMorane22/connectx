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
 * @file ContextRestoreRAII.h
 * @date 2021
 *
 *************************************************************************************************/

#ifndef CONTEXTRESTORERAII_H_43F10A87_2AAA_4ED9_86C2_B27FD5590BE7
#define CONTEXTRESTORERAII_H_43F10A87_2AAA_4ED9_86C2_B27FD5590BE7

#include <cairomm/refptr.h>

namespace Cairo
{
    class Context;
}

namespace cxgui
{

/**********************************************************************************************//**
 * @brief RAII that automatically saves and restores a given context.
 *
 * The Cairomm documentation states about Cairo::Context::save():
 * 
 *   Makes a copy of the current state of the Context and saves it on an internal stack
 *   of saved states. When restore() is called, it will be restored to the saved state.
 *   Multiple calls to save() and restore() can be nested; each call to restore() restores
 *   the state from the matching paired save().
 *
 * The goal of this RAII is to make sure that a saved Cairo::Context will be restored by the end  
 * of the RAII scope. The RAII automaticall calls Cairo::Context::save() (upon creation) and
 * Cairo::Context::restore() (upon destruction) on the given context.
 *
 *************************************************************************************************/
class ContextRestoreRAII
{

public:

    /**********************************************************************************************//**
     * @brief Constructor.
     *
     * @oaram p_context The Cairo context to save and restore.
     *
     *************************************************************************************************/
    ContextRestoreRAII(const Cairo::RefPtr<Cairo::Context>& p_context);

    /**********************************************************************************************//**
     * @brief Destructor.
     *
     *************************************************************************************************/
    ~ContextRestoreRAII();

private:

    const Cairo::RefPtr<Cairo::Context>& m_context;

};

} // namespace cxgui


#endif // CONTEXTRESTORERAII_H_43F10A87_2AAA_4ED9_86C2_B27FD5590BE7
