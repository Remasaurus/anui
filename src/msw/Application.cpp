#include <anuiApplication.h>
#include <anui/msw/Windows.h>


using namespace anui;

int anui::Application::runMainLoop() {
	MSG msg;

	while (true) {
		if (GetMessage(&msg, nullptr, 0, 0)) {
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
		
		while (PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE)) {
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}

		// Render
	}


	return 0;
}

