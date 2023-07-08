#pragma once
#include <anui/core.h>
#include <anui/impl/types.h>

// Top bottom right left
#define tbrl(name) struct name##_top {}; \
    struct name##_bottom {}; \
    struct name##_right {}; \
    struct name##_left {}


ANUI_BEGIN

struct x {};
struct y {};
struct width {};
struct height {};

tbrl(margin);
tbrl(padding);

ANUI_END

#undef tbrl
