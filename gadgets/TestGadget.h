#ifndef NBOMED_TESTGADGET_H
#define NBOMED_TESTGADGET_H

#include "nbomed-core/gadgets/TextGadget.h"
#include "nbomed-core/display.h"

/**
 * @brief Временный гаджет для проверки работы ввода и отрисовки.
 * @memberof buttonsState Текущее состояние ввода дожно записываться в эту переменную.
 */
class TestGadget : public Gadget {
private:
    int m_startPosition;
    TextGadget* m_gadgetLeft;
    TextGadget* m_gadgetUp;
    TextGadget* m_gadgetDown;
    TextGadget* m_gadgetRight;
    TextGadget* m_gadgetSelect;
    TextGadget* m_gadgetPlay;
    TextGadget* m_gadgetA;
    TextGadget* m_gadgetB;
public:
    ButtonsState buttonsState;

    TestGadget();

    void draw(IDisplayCanvas* canvas, GridDimension* dimension);

    static TextGadget* buildGadget(int position, const String& charIcon);
};

#endif //NBOMED_TESTGADGET_H