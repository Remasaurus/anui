#pragma once
#include <Anui/Window.h>


ANUI_BEGIN

class FloatingWindowBase : public NativeWindow {
public:
	void setTitle(std::wstring_view title) { return setLabel(title); }
	std::wstring_view getTitle() const { return getLabel(); }


private:

};

#include ANUI_PATH(FloatingWindow)
ANUI_RENAME(FloatingWindow, FloatingWindow);


ANUI_END