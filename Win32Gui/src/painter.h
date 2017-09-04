#pragma once

#include <Windows.h>
//#include <cwchar>
#include <rect.h>
#include <brush.h>

class Painter
{
public:
	Painter() : dc(NULL), brush(NULL){}
	HDC			dc;
	PAINTSTRUCT ps;
	Brush*		brush;

	void Begin(HWND handle) { dc = BeginPaint(handle, &ps); }
	void End(HWND handle) { EndPaint(handle, &ps); }

	void SetBrush(Brush &b) { brush = &b; }
	void FillRect(const RECT &rect) { ::FillRect(dc, &rect, *brush); }
	void Text(int x, int y, const wchar_t* text) { TextOut(dc, x, y, text, lstrlen(text)); }
	void SetTextColor(const COLORREF &color) { ::SetTextColor(dc, color); }
	void SetTextBgColor(const COLORREF &color) { ::SetBkColor(dc, color); }
};

struct Font
{
	
};