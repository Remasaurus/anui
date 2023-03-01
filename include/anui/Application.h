#include <Anui/core.h>

ANUI_BEGIN

class Application {
public:

	int runMainLoop();

	// Return false if initialization failed
	bool onInit() {
		return true;
	}

private:

};

class ConsoleApplication : public Application {
public:
	static ConsoleApplication*& get() {
		static ConsoleApplication* app;
		return app;
	}
};

class WindowApplication : public Application {
public:
	static WindowApplication*& get() {
		static WindowApplication* app;
		return app;
	}
};




#if defined(ANUI_CONSOLE)
using AnuiApp = ConsoleApplication;
#define AnuiImplementApp(App)			\
int main() {							\
	App* app = new App();				\
	anui::AnuiApp::get() = app;			\
	if (app->onInit()) {				\
		return app->runMainLoop();		\
										\
	}									\
	return -1;							\
}

#else
using AnuiApp = WindowApplication;

#ifdef defined(ANUI_WIN32)
#define AnuiImplementApp(App)			\
int wWinMain() {						\
	AnuiApp* app = AnuiApp::get();		\
	if (app->onInit()) {				\
		return app->runMainLoop();		\
	}									\
										\
	return -1;							\
}

#endif // ANUI_WIN32
#endif // ANUI_CONSOLE




ANUI_END