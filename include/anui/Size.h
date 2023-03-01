#pragma once
#include <Anui/core.h>
#include <initializer_list>

ANUI_BEGIN

struct AnuiSize {
	unsigned int width, height;
	AnuiSize() = default;

	AnuiSize& operator= (const std::initializer_list<unsigned int>& list) {
		width = list.begin()[0];
		height = list.begin()[1];
	}
};


ANUI_END