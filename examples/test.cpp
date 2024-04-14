#include <anui/unit.h>
#include <anui/event_handler.h>
#include <anui/window.h>
#include <iostream>


using namespace anui::unit_literals;

void lol(float x) {
	std::cout << "lol(float) was given " << x << std::endl;
}

class Window : public anui::window {
public:
	Window() {
		
		bind(lol);
		bind(&Window::print, this);
		bind([](char x) {
			std::cout << "Booba char x: " << x << std::endl;
		});
	}


	void print(int x) const {
		std::cout << "Hello from print! x: " << x << std::endl;
	}

private:


};

int main() {

	float x = 3.14159;
	int y = 18;
	char z = 'b';

	Window window;

	window.send(x);
	window.send(y);
	window.send(z);

	return 0;
}
