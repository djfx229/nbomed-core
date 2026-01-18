#ifndef NBOMED_APPLICATION_H
#define NBOMED_APPLICATION_H

#include "nbomed-core/gadgets/TestGadget.h"
#include "nbomed-core/display.h"

/**
 * @brief Через данный листенер платформа уведомляет приложение о жизненном цикле и состоянии ввода.
 * @memberof onStart
 */
class PlatformEventsListener {
public:
    virtual ~PlatformEventsListener() {}

    virtual void onStart() = 0;
    virtual void onFinish() = 0;
    virtual void onChangeButtonsState(ButtonsState state) = 0;
};

/**
 * @brief Связывает все необходимые сущности друг с другом для выполнения старта и отображения приложения.
 * @details Для запуска приложения необходимо реализовать все абстракции из конструктора данного класса и
 * реализацию @file common.h
 * @memberof onStart
 */
class NbomedApp : public PlatformEventsListener {
private:
    DisplayOutput* displayOutput;
    TestGadget* rootGadget;

public:
    NbomedApp(
        DisplayOutput* display
    );

    // override PlatformEventsListener
    void onStart();

    // override PlatformEventsListener
    void onFinish();

    // override PlatformEventsListener
    void onChangeButtonsState(ButtonsState state);
};

#endif //NBOMED_APPLICATION_H