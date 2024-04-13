#include <anui/anui.h>

using anui::geometry;
using namespace anui::unit_literals;
using namespace std::chrono_literals;

class RedWidget : anui::widget {
public:
	using widget::widget;

	void init() {
		bind(draw, this);
	}

	void draw(anui::draw_event evt) {
		anui::begin_batch(this);

		anui::quad(
			evt.rect, 
			anui::shade(anui::color::red));

		anui::end_batch();
	}
	
};


class Window : anui::window {
public:
	using window::window;

	void init() {
		bind(draw, this);
		widget.update(
			geometry(anui::center(), anui::center(), 50_pct, anui::aspect(1));
		);
	}

	void draw(anui::draw_event _) {
		anui::begin_batch(this);
		anui::fill(anui::rgb(255, 255, 255));
		anui::end_batch();
	}

private:
	RedWidget widget;
};


int main() {
	Window window {
		anui::size(500_px, 500_px),
		anui::border(2_px),
		anui::resizable,

		anui::title("My cute little window!"),
	};


	return 0;
}
