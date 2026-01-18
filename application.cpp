#include "nbomed-core/application.h"
#include "gadgets/TestGadget.h"

NbomedApp::NbomedApp(DisplayOutput* display)
        : displayOutput(display),
          rootGadget(new TestGadget()) {
}

void NbomedApp::onStart() {
    Log::d(L"Application: start");
    displayOutput->add(rootGadget);
    displayOutput->needRedrawing();
}

void NbomedApp::onFinish() {
    Log::d(L"Application: finish");
}

void NbomedApp::onChangeButtonsState(ButtonsState state) {
    rootGadget->buttonsState = state;
    rootGadget->dirty = true;
    displayOutput->needRedrawing();
}
