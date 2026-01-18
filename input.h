#ifndef NBOMED_INPUT_H
#define NBOMED_INPUT_H
#include "nbomed-core/common.h"

/**
 * @brief Состояние нажатия кнопок в виде битовой маски.
 */
enum ButtonEvent {
    BUTTON_D_PAD_UP  = 1 << 0,
    BUTTON_D_PAD_DOWN  = 1 << 1,
    BUTTON_D_PAD_LEFT  = 1 << 2,
    BUTTON_D_PAD_RIGHT  = 1 << 3,
    BUTTON_SELECT  = 1 << 4,
    BUTTON_PLAY_OR_PAUSE  = 1 << 5,
    BUTTON_A  = 1 << 6,
    BUTTON_B  = 1 << 7,
};

/**
 * @brief Проверяет, была ли нажата @param button в текущем @param buttonsState
 */
bool isPressed(ButtonsState buttonsState, ButtonEvent button);

#endif //NBOMED_INPUT_H