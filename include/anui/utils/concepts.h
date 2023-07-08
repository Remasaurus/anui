#pragma once
#include <anui/core.h>
#include <concepts>

ANUI_BEGIN
namespace impl
{
    template <class, template <class> class>
    struct is_instance
    {
        static constexpr bool value = false;
    };

    template <class T, template <class> class U>
    struct is_instance<U<T>, U>
    {
        static constexpr bool value = true;
    };

}; // impl

namespace utils
{

    template <class T, template <typename> typename U>
    concept is_templated_instance = impl::is_instance<T, U>::value;

    template <typename T, typename... Trest>
    concept is_one_of = (std::same_as<T, Trest> || ...);

} // utils
ANUI_END
