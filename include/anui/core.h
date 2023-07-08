#pragma once
#define ANUI_BEGIN \
    namespace anui \
    {
#define ANUI_END }

#if !defined(ANUI_MSW) && !defined(ANUI_UNIX) && !defined(ANUI_APPLE)
#if defined(_WIN32) || defined(_WIN64) || defined(__CYGWIN__)
#define ANUI_MSW
#elif defined(__linux__)
#define ANUI_UNIX
#else
#error "OS is not supported"
#endif

#endif

#ifdef ANUI_MSW
#define ANUI_OS_INCLUDE(file) <anui/msw/##file.h>
#elif ANUI_UNIX
#define ANUI_OS_INCLUDE
#elif ANUI_APPLE
#define ANUI_OS_INCLUDE
#else
#endif
