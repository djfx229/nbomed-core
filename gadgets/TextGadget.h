#ifndef NBOMED_TEXT_GADGET_H
#define NBOMED_TEXT_GADGET_H

#include "nbomed-core/display.h"

/**
 * @brief Отображает текстовую строку в заданной ISapInGrid позиции.
 * @details Отрисовывается только одна строка, перенос отсутствует.
 */
class TextGadget : public Gadget {
private:
    String m_text;
    Color m_backgroundColor;

public:
    TextGadget(
        ISapInGrid *sap,
        const String &text,
        const Color &backgroundColor = COLOR_TEXT_BACKGROUND
    );

    void draw(IDisplayCanvas *canvas, GridDimension *dimension);
};

#endif //NBOMED_TEXT_GADGET_H