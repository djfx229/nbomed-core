#ifndef NBOMED_DISPLAY_H
#define NBOMED_DISPLAY_H

#include <set>

#include "nbomed-core/input.h" // IWYU pragma: keep
#include "nbomed-core/common.h"

struct RectPixels;
class Gadget;

/**
 * @brief Контейнер, который может содержать в себе Gadget'ы.
 * @details В данный момент времени нет многослойной отрисовки, и реализация данного интерфейса есть только в
 * DisplayOutput.
 * @memberof needRedrawing Отправляет сигнал, что когда будет отрисовываться следующий кадр, необходимо перерисовать
 * гаджеты, отмеченные как грязные.
 */
class IGadgetContainer {
public:
    virtual ~IGadgetContainer() {}
    virtual void add(Gadget* gadget) = 0;
    virtual void remove(Gadget* gadget) = 0;
    virtual void needRedrawing() = 0;
};

/**
 * @brief Константы цветов, их реальные значения реализуются на уровне платформы.
 */
enum Color {
    COLOR_SCREEN_BACKGROUND,
    COLOR_TEXT_PLAIN,
    COLOR_TEXT_SELECTED,
    COLOR_TEXT_BACKGROUND,
    COLOR_RANDOM,
};

/**
 * @brief С помощью данной абстракции, гаджеты могут рисовать своё содержимое на экране на холсте платформы.
 * @details Всё позиционирование выполняется в пикселях, ответственность на преобразование значений из ISapInGrid
 * ложится на плечи гаджетов.
 */
class IDisplayCanvas {
public:
    virtual ~IDisplayCanvas() {}
    virtual void fillColor(RectPixels* rect, Color color) = 0;
    virtual void drawString(RectPixels* rect, String text) = 0;
};

/**
 * @brief Для приложения экран представляет собой сетку тайлов. Данная модель хранит действующие размеры экрана в
 * тайлах и размер отдельного взятого тайла в пикселях.
 * @details Под экраном подразумевается доступная для отрисовки на уровне платформы область.
 */
struct GridDimension {
    int tileCountW;
    int tileCountH;
    int tileSizeW;
    int tileSizeH;

    int getScreenWidth() const {
        return tileSizeW * tileCountW;
    }

    int getScreenHeight() const {
        return tileSizeH * tileCountH;
    }
};

/**
 * @brief Описывает позицию внутри сетки интерфейса.
 * @details Позиция и размер задаются в количестве тайлов (см. GridDimension и DisplayOutput).
 */
class ISapInGrid {
public:
    virtual ~ISapInGrid() {}

    virtual int getX() = 0;
    virtual int getY() = 0;
    virtual int getWidth() = 0;
    virtual int getHeight() = 0;
};

/**
 * @brief реализация ISapInGrid, позволяющая вручную указать позицию по X Y, и размеры (ширину/высоту).
 */
class XywhSap : public ISapInGrid {
public:
    int x;
    int y;
    int width;
    int height;

    XywhSap();

    int getX();
    int getY();
    int getWidth();
    int getHeight();
};

/**
 * @brief В отличие от ISapInGrid хранит данные в пикселях.
 */
struct RectPixels {
    int x;
    int y;
    int width;
    int height;
};

/**
 * @brief Абстрактный класс для доступа к дисплею платформы из приложения.
 * @details Графический интерфейс приложения устроен следующим образом:
 * - каждый элемент интерфейса - это Gadget;
 * - для того, чтобы отобразить гаджет на экране, его нужно добавить в DisplayOutput (который от гаджетов отделён
 * фасадом DisplayOutput);
 * - теперь, когда необходимо отрисовать кадр (см. @memberof onHostStartDraw), приложение отправит гаджетам
 * IDisplayCanvas, чтобы они могли перерисовать своё содержимое;
 * - экран приложения это сетка тайлов, позиционирование гаджетов выполняется не в пикселях, ни в dip, оно указывается
 * в позиции в этой сетке;
 * - размер доступного пространства в сетке и величина одного тайла определяется [GridDimension];
 * - существующая реализация в тайле рисует только строковые символы.
 */
class DisplayOutput : public IGadgetContainer {
    std::set<Gadget*> attachedGadgets;

public:
    DisplayOutput();

    void add(Gadget *gadget);

    void remove(Gadget *gadget);

    virtual GridDimension* getGridDimension() const = 0;

    /**
     * Платформа выполняет перерисовку содержимого экрана (например, мы отправить запрос на это из @memberof
     * needRedrawing).
     */
    void onHostStartDraw(IDisplayCanvas *canvas) const;
};

/**
 * @brief Элемент графического интерфейса.
 * @details Для отрисовки на экране, должен быть добавлен в IGadgetContainer (см. DisplayOutput).
 * Чтобы гаджет был перерисован при отрисовке следующего кадра на экране, необходимо указать @memberof dirty == true
 * @memberof dirty данный флаг указывает, что когда будет отрисовка следующего кадра, будет вызван метод @memberof draw
 */
class Gadget {
private:
    ISapInGrid* sizeAndPosition;
public:
    virtual ~Gadget() {}

    /**
     * Если гаджет грязный, значит его нужно перерисовать во время отрисовки следующего кадра.
     */
    bool dirty;

    Gadget();

    /**
     * Задаёт позицию и размер гаджета.
     */
    void setSap(ISapInGrid* sap);

    /**
     * Доступ к sizeAndPosition из реализаций гаджетов.
     */
    ISapInGrid* getSap() const;

    /**
     * Для того чтобы при каждой операции отрисовки на холсте не требовалось вызывать операции по преобразованию сетки
     * в реальные значения пикселей, ответственность за преобразование ложится на плечи гаджетов.
     */
    virtual void draw(IDisplayCanvas* canvas, GridDimension* dimension) = 0;

    static XywhSap* defaultSap();
};

#endif //NBOMED_DISPLAY_H