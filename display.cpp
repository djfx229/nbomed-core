#include "nbomed-core/display.h"

XywhSap::XywhSap() : x(0), y(0), width(0), height(0) {
}

int XywhSap::getX() {
    return x;
}

int XywhSap::getY() {
    return y;
}

int XywhSap::getWidth() {
    return width;
}

int XywhSap::getHeight() {
    return height;
}

DisplayOutput::DisplayOutput()
    : attachedGadgets(std::set<Gadget *>()) {
};

void DisplayOutput::add(Gadget *gadget) {
    attachedGadgets.insert(gadget);
}

void DisplayOutput::remove(Gadget *gadget) {
    attachedGadgets.erase(gadget);
}

void DisplayOutput::onHostStartDraw(IDisplayCanvas *canvas) const {
    for (std::set<Gadget *>::iterator it = attachedGadgets.begin(); it != attachedGadgets.end(); ++it) {
        (*it)->draw(canvas, getGridDimension());
    }
}

Gadget::Gadget()
    : dirty(true),
      sizeAndPosition(defaultSap()) {}

void Gadget::setSap(ISapInGrid* sap) {
    sizeAndPosition = sap;
}

ISapInGrid* Gadget::getSap() const {
    return sizeAndPosition;
}

XywhSap* Gadget::defaultSap() {
    XywhSap* sap = new XywhSap();
    sap->x = 0;
    sap->y = 0;
    sap->width = 1;
    sap->height = 1;
    return sap;
}
