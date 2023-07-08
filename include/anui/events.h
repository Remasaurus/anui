#pragma once
#include <anui/core.h>
#include <optional>


ANUI_BEGIN


// ----------- events -----------
class event {
public:
    event() {


    }

private:

};


class button_event {
public:
};





// ---------- defaults ---------

void await_event_and_send();
event await_event();
std::optional<event> peek_event();


void default_loop(bool render_thread = true);



ANUI_END
