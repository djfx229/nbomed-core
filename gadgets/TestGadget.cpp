#include "nbomed-core/gadgets/TestGadget.h"

TestGadget::TestGadget() : m_startPosition(0),
                           m_gadgetLeft(buildGadget(m_startPosition++, L"←")),
                           m_gadgetUp(buildGadget(m_startPosition++, L"↑")),
                           m_gadgetDown(buildGadget(m_startPosition++, L"↓")),
                           m_gadgetRight(buildGadget(m_startPosition++, L"→")),
                           m_gadgetSelect(buildGadget(m_startPosition++, L"S")),
                           m_gadgetPlay(buildGadget(m_startPosition++, L"P")),
                           m_gadgetA(buildGadget(m_startPosition++, L"A")),
                           m_gadgetB(buildGadget(m_startPosition++, L"B")),
                           buttonsState(0) {
}

void TestGadget::draw(IDisplayCanvas *canvas, GridDimension* dimension) {
    int globalCount = 0;
    Color color;
    for (int paintX = 0; paintX < dimension->tileCountW; paintX++) {
        for (int paintY = 0; paintY < dimension->tileCountH; paintY++) {
            if (globalCount % 2 == 0) {
                color = COLOR_RANDOM;
            } else {
                color = COLOR_TEXT_BACKGROUND;
            }
            RectPixels rect = {
                paintX * dimension->tileSizeW,
                paintY * dimension->tileSizeH,
                dimension->tileSizeW,
                dimension->tileSizeH,
            };
            canvas->fillColor(&rect, color);
            globalCount++;
        }
        globalCount++;
    }

    RectPixels nativeRect = {
        0,
        0,
        dimension->getScreenWidth(),
        dimension->tileSizeH,
    };

    canvas->fillColor(&nativeRect, COLOR_TEXT_BACKGROUND);

    if (isPressed(buttonsState, BUTTON_D_PAD_LEFT)) {
        m_gadgetLeft->draw(canvas, dimension);
    }

    if (isPressed(buttonsState, BUTTON_D_PAD_UP)) {
        m_gadgetUp->draw(canvas, dimension);
    }

    if (isPressed(buttonsState, BUTTON_D_PAD_DOWN)) {
        m_gadgetDown->draw(canvas, dimension);
    }

    if (isPressed(buttonsState, BUTTON_D_PAD_RIGHT)) {
        m_gadgetRight->draw(canvas, dimension);
    }

    if (isPressed(buttonsState, BUTTON_SELECT)) {
        m_gadgetSelect->draw(canvas, dimension);
    }

    if (isPressed(buttonsState, BUTTON_PLAY_OR_PAUSE)) {
        m_gadgetPlay->draw(canvas, dimension);
    }

    if (isPressed(buttonsState, BUTTON_A)) {
        m_gadgetA->draw(canvas, dimension);
    }

    if (isPressed(buttonsState, BUTTON_B)) {
        m_gadgetB->draw(canvas, dimension);
    }
}

TextGadget* TestGadget::buildGadget(int position, const String& charIcon) {
    XywhSap* sap = new XywhSap();
    sap->x = position;
    sap->y = 0;
    sap->width = 1;
    sap->height = 1;
    TextGadget* gadget = new TextGadget(sap, charIcon);
    return gadget;
}
