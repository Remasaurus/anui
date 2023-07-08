#pragma once
#include <anui/core.h>
#include <sys/types.h>

ANUI_BEGIN
namespace impl
{

    using small_number_t = int16_t;
    using small_unsigned_t = uint16_t;

    using number_t = int32_t;
    using unsigned_t = uint32_t;

    using big_number_t = int64_t;
    using big_unigned_t = uint64_t;

}
ANUI_END
