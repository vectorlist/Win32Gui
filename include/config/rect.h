#pragma once

#include <windows.h>

struct Margin
{
	int spacing;
	Margin() : spacing(10) {}
};

class Rect : public RECT
{
public:
	Rect() { left = top = right = bottom = 0; }
	Rect(int l, int r, int t, int b) { left = l; right = r; top = t; bottom = b; }
	Rect(const RECT &rect) { *this = rect; }

	int GetWidth() const { return right - left; }
	int GetHeight() const { return bottom - top; }

	//operator

	operator RECT() { return *this; }
	operator LPRECT() { return this; }

	Rect& operator-(const Margin& m)
	{
		left += m.spacing;
		right -= m.spacing;
		top += m.spacing;
		bottom -= m.spacing;
		return *this;
	}

};

