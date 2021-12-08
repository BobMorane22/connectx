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
 * @file BoardElementCache.h
 * @date 2021
 *
 *************************************************************************************************/

#ifndef BOARDELEMENTCACHE_H_04E2F9C3_26E9_49C3_99BB_A2D2F75C3DC5
#define BOARDELEMENTCACHE_H_04E2F9C3_26E9_49C3_99BB_A2D2F75C3DC5

#include <vector>

#include <cxmodel/ChipColor.h>

namespace Gdk
{
    class Pixbuf;
}

namespace Glib
{
    template<typename T>
    class RefPtr;
}

namespace cxgui
{

/**********************************************************************************************//**
 * @brief Cache for board element surfaces previously drawn.
 *
 * Redrawing everything with Cairo is very expensive and can rapidly lead to CPU and X Server
 * overloads, as all drawing is done on the CPU and when a lot of drawing is done, there is also
 * a lot of exchange with the X Server. The aim of this cache is to save already drawn board
 * elements (on surfaces) for later use without having to redraw the whole thing every time.
 *
 * A board element is a part of the board board that represents a disc and its surrounding
 * area. Something like:
 *
 *                                     +------------------+
 *                                     |       +  +       |
 *                                     |    +        +    |
 *                                     |   +          +   |
 *                                     |  +            +  |
 *                                     |  +            +  |
 *                                     |   +          +   |
 *                                     |    +       +     |
 *                                     |       +  +       |
 *                                     +------------------+
 *
 * Before entering the cache, these board elements must first be drawn onto a Gtk::Pixbuf
 * surface. In the cache, the board element is stored with its corresponding disc color as
 * the key. Using this key, one can later retreive the board element and reuse it instead
 * of redrawing everything.
 *
 * Note that the keys must be unique in the cache. Adding an element with an existing key and
 * will result in nothing : the new element will be rejected. It is the responsibility of the
 * user to look if the key is already in the cache.
 *
 *************************************************************************************************/
class BoardElementCache
{

public:

    /******************************************************************************************//**
     * @brief Adds a new element (key/board element) into the cache.
     *
     * @pre The key is not already in the cache.
     *
     * @param p_color
     *      The key. It is meant to represent the disc color on the surface.
     *
     * @param p_surface
     *      The board element to cache.
     *
     *********************************************************************************************/
    void Add(const cxmodel::ChipColor& p_color, const Glib::RefPtr<Gdk::Pixbuf> p_surface);

    /******************************************************************************************//**
     * @brief Gets the correspondig cached board element from a key.
     *
     * @pre The key must exist in the cache. It is the responsibility of the user to make sure
     *      it does before calling this.
     *
     * @param p_color
     *      The key. It should represent the color of the disc on the correspondig cached board
     *      element.
     *
     * @return The cached board element.
     *
     *********************************************************************************************/
    Glib::RefPtr<Gdk::Pixbuf> Get(const cxmodel::ChipColor& p_color) const;

    /******************************************************************************************//**
     * @brief Clears all key/elements pairs from the cache.
     *
     *********************************************************************************************/
    void Clear();

    /******************************************************************************************//**
     * @brief Checks if a specific element exist, by key.
     *
     * @param p_color
     *      The key to look for in the cache.
     *
     * @return `true` if the element was found, `false` otherwise.
     *
     *********************************************************************************************/
    bool HasElement(const cxmodel::ChipColor& p_color);

private:

    std::vector<cxmodel::ChipColor> m_keys;
    std::vector<Glib::RefPtr<Gdk::Pixbuf>> m_surfaces;

};

} // namespace cxgui

#endif // BOARDELEMENTCACHE_H_04E2F9C3_26E9_49C3_99BB_A2D2F75C3DC5
