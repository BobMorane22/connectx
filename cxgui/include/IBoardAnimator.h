#ifndef IBOARDANIMATOR_H_C5297993_B06E_4707_ABF4_46D42D673DA8
#define IBOARDANIMATOR_H_C5297993_B06E_4707_ABF4_46D42D673DA8

#include <cstddef>

namespace cxgui
{

class Chip;
enum class BoardAnimation;

}

namespace cxgui
{

/**********************************************************************************************//**
 * @brief Animate a Connect X game board.
 *
 * Enables board animations for Connect X. The `PerformChipAnimation
 *
 *************************************************************************************************/
class IBoardAnimator
{

public:

    /******************************************************************************************//**
     * @brief Animates the chip on the board.
     *
     * @param p_direction
     *      The wanted animation.
     *
     *********************************************************************************************/
    virtual void PerformChipAnimation(BoardAnimation p_animation) = 0;

    /******************************************************************************************//**
     * @brief Gets the column in which the chip in the next disc area is currently located.
     *
     * @return The column in which the chip currently is located.
     *
     *********************************************************************************************/
    [[nodiscard]] virtual size_t GetCurrentColumn() const = 0;

    /******************************************************************************************//**
     * @brief Gets the chip currently in the next disc area.
     *
     * @return The disc in the next disc area. If there is none, nullptr.
     *
     *********************************************************************************************/
    [[nodiscard]] virtual const cxgui::Chip* GetCurrentChip() const = 0;

};

} // namespace cxgui

#endif // IBOARDANIMATOR_H_C5297993_B06E_4707_ABF4_46D42D673DA8
