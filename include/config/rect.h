#pragma once

#include <windows.h>

class Rect : public RECT
{
public:
	Rect() { left = top = right = bottom = 0; }
	Rect(int l, int r, int t, int b) { left = l; right = r; top = t; bottom = b; }
	Rect(const RECT &rect) { *this = rect; }

	int GetWidth() const { return right - left; }
	int GetHeight() const { return bottom - top; }

};

