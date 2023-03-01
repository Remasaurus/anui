#pragma once

namespace wnd {

constexpr int LEFT_MOUSE_BUTTON = 1;
constexpr int RIGHT_MOUSE_BUTTON = 2;
constexpr int MIDDLE_MOUSE_BUTTON = 3;
constexpr int XMOUSE_BUTTON1 = 4;
constexpr int XMOUSE_BUTTON2 = 5;

#ifdef _WIN32

#include "window/MSW/keyCodes.h"

#endif
}