#pragma once

#define ANUI_BEGIN namespace anui {
#define ANUI_END }

#if defined(ANUI_WIN32)
#define ANUI_PATH(header) <anui/msw/header.h> 
#define ANUI_RENAME(type, name) using type = MSW##name
#elif defined(ANUI_CACOA)
#define ANUI_PATH(header) <anui/cacoa/header>
#define ANUI_RENAME(type, name) using type = Cacoa##name
#elif defined(ANUI_X11)
#define ANUI_PATH(header) <anui/x11/header>
#define ANUI_RENAME(type, name) using type = X11##name
#endif

#define ANUI_BIND(memberFunc) std::bind(&memberFunc, this, std::placeholders::_1)


ANUI_BEGIN
constexpr int USE_DEFAULTX = -1;
constexpr int USE_DEFAULTY = -1;
constexpr unsigned int USE_DEFAULT_WIDTH = 0;
constexpr unsigned int USE_DEFAULT_HEIGHT = 0;
ANUI_END