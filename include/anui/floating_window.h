#pragma once
#include <anui/window.h>

ANUI_BEGIN
namespace base
{

    class floating_window : public window
    {
        using window::window;
    };

}

#include ANUI_OS_INCLUDE(floating_window)

ANUI_END
