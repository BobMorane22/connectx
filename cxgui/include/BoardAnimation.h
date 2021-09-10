#ifndef BOARDANIMATION_H_6A5C10D5_BDB2_4709_8B3F_3493764805CC
#define BOARDANIMATION_H_6A5C10D5_BDB2_4709_8B3F_3493764805CC

namespace cxgui
{

/******************************************************************************************//**
 * @brief Animations the board can perform.
 *
 *********************************************************************************************/
enum class BoardAnimation
{
    GAME_REINITIALIZED,
    GAME_WON,
    MOVE_CHIP_LEFT_ONE_COLUMN,
    MOVE_CHIP_RIGHT_ONE_COLUMN,
    DROP_CHIP,
    UNDO_DROP_CHIP,
};

} // namespace cxgui

#endif // BOARDANIMATION_H_6A5C10D5_BDB2_4709_8B3F_3493764805CC
