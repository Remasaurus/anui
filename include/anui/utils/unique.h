#pragma once
#include <anui/core.h>
#include <concepts>

ANUI_BEGIN
namespace utils
{

    template <typename...>
    struct all_unique
    {
        static constexpr bool value = true;
    };

    template <typename T1, typename T2, typename... Trest>
    struct all_unique<T1, T2, Trest...>
    {
        static constexpr bool value = all_unique<T1, T2>::value && all_unique<T1, Trest...>::value && all_unique<T2, Trest...>::value;
    };

    template <typename T1, typename T2>
    struct all_unique<T1, T2>
    {
        static constexpr bool value = !std::same_as<T1, T2>;
    };

} // utils
ANUI_END
