#include <anui/core.h>
#include <type_traits>
#include <concepts>

ANUI_BEGIN

enum class EventType {

};

// Set bit at location i to 1
// starting from least significant bit
constexpr unsigned int bit(unsigned int i) {
	return 1 << i;
}

// Set all bits up until and including i to 1
// starting from least significant bit
constexpr unsigned int everyBit(unsigned int i) {
	return (1 << (i + 1)) - 1;
}

enum EventCategory {
	None = 0,
	Mouse = bit(0),
	MouseButton = bit(1),
	KeyBoard = bit(2),
	Application = bit(3),
	Any = everyBit(3),
};



class Event {
public:
	using return_type = void;

	// True by default
	
	//
	// Stops the propogation of an event
	//
	void handle() {
		m_Handled = true;
	}

	
private:
	bool m_Handled = false;
};

struct KeyDownEvent : public Event {
	int keyCode;
};


template<typename T>
concept EventConcept = std::is_base_of_v<Event, T>;



ANUI_END