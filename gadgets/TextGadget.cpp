#include "nbomed-core/gadgets/TextGadget.h"

TextGadget::TextGadget(
    ISapInGrid *sap,
    const String &text,
    const Color &backgroundColor
) : m_text(text),
    m_backgroundColor(backgroundColor) {
    setSap(sap);
}

void TextGadget::draw(IDisplayCanvas *canvas, GridDimension* dimension) {
    ISapInGrid* sap = getSap();
    RectPixels nativeRect = {
        sap->getX() * dimension->tileSizeW,
        sap->getY() * dimension->tileSizeH,
        sap->getWidth() * dimension->tileSizeW,
        sap->getHeight() * dimension->tileSizeH,
    };

    canvas->fillColor(&nativeRect, m_backgroundColor);
    canvas->drawString(&nativeRect, m_text);
}
