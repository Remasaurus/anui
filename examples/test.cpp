#include <anui/unit.h>
#include <anui/event_handler.h>
#include <anui/window.h>
#include <iostream>


using namespace anui::unit_literals;

void lol(const float x) {
	std::cout << "lol(float) was given " << x << std::endl;
}

class Window : public anui::window {
public:
	Window() {
		
		bind(lol);
		bind(&Window::print, this);
		bind([](char x) {
			std::cout << "char x: " << x << std::endl;
		});
	}


	void print(const int& x) const {
		std::cout << "Hello from print! x: " << x << std::endl;
	}

private:


};

void o(const float& x) {
	std::cout << "New function for x: " << x << std::endl;
}

int main() {

	float x = 3.14159;
	int y = 18;
	char z = 'b';

	Window window;
	std::function p([](const float& x) {
		std::cout << "New function for x: " << x << std::endl;
	});

	window.send(x);
	window.send(y);
	window.send(z);

	window.bind(o);

	float& d = x;
	window.send(d);
		
	const char* str= "Hjskadh";
	window.send(str);

	window.bind(p);

	window.send(x);
	




	return 0;
}
