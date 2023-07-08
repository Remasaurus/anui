#pragma once
#include <utility>
#include <iostream> // Only for testing
#include <anui/core.h>
#include <anui/utils/concepts.h>
#include <anui/utils/unique.h>
#include <anui/impl/types.h>

ANUI_BEGIN




class window {
public:
    template<typename... Args>
    window(Args... args) {
        style(std::forward<Args>(args)...);
    }
 
    template<typename T>
    void send_event(T event) {
        

    }

    template<typename T>
    void handle_event() {}

    template<utils::is_one_of<impl::small_number_t, float, double, long>... Args>
    void style(Args&& ... args) {
        static_assert(utils::all_unique<Args...>::value, "All types must be unique!");

        std::cout << "Hello world!\n";
    }

    template<utils::is_one_of<impl::small_number_t> T>
    T get() {
        return T{};
    }



private:
    impl::small_number_t padding_left;
    impl::small_number_t padding_right;
    impl::small_number_t padding_top;
    impl::small_number_t padding_bottom;

    impl::small_number_t margin_left;
    impl::small_number_t margin_top;
    impl::small_number_t margin_bottom;
    impl::small_number_t margin_right;
};


ANUI_END
