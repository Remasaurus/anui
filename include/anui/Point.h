#pragma once
#include <anui/core.h>

ANUI_BEGIN


struct AnuiPoint {
	int x, y;
	AnuiPoint(int x, int y) : x(x), y(y) {}
	AnuiPoint() = default;
	AnuiPoint(const AnuiPoint&) = default;
	AnuiPoint& operator= (const AnuiPoint& rhs) = default;

	AnuiPoint& operator= (const std::initializer_list<unsigned int>& list) {
		x = list.begin()[0];
		y = list.begin()[1];
		return *this;
	}

	AnuiPoint& operator+= (const AnuiPoint& rhs) {
		x += rhs.x;
		y += rhs.y;
		return *this;
	}
	AnuiPoint& operator-= (const AnuiPoint& rhs) {
		x -= rhs.x;
		y -= rhs.y;
		return *this;
	}


	AnuiPoint operator+ (const AnuiPoint& rhs) {
		return AnuiPoint(x + rhs.x, y + rhs.y);
	}
	AnuiPoint operator- (const AnuiPoint& rhs) {
		return AnuiPoint(x - rhs.x, y - rhs.y);
	}

	
};



ANUI_END