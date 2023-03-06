#pragma once
#include <anui/Application.h>
ANUI_BEGIN

inline void traceLog() {
	AnuiApp::traceLog();
}
inline void warningLog() {
	AnuiApp::warningLog();
}
inline void errorLog() {
	AnuiApp::errorLog();
}

ANUI_END
