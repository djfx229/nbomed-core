#include "nbomed-core/input.h"

bool isPressed(const ButtonsState buttonsState, ButtonEvent button) {
    return (buttonsState & button) != 0;
}
