#ifndef NBOMED_COMMON_H
#define NBOMED_COMMON_H
#include <string>

/**
 * @file common.h
 * @brief Содержит в себе typedef и статичные зависимости, которые необходимо объявить на уровне платформы.
 */

typedef std::wstring String;

typedef unsigned int ButtonsState;

namespace Log {
    void v(const String& text);
    void d(const String& text);
    void w(const String& text);
    void e(const String& text);
}

#endif //NBOMED_COMMON_H