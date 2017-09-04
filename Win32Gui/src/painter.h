#pragma once

#include <Windows.h>
#include <cwchar>
#include <rect.h>
#include <brush.h>

struct Painter
{
	HDC			dc;
	PAINTSTRUCT ps;
	void Begin(HWND handle) { dc = BeginPaint(handle, &ps); }
	void End(HWND handle) { EndPaint(handle, &ps); }
	void FillRect(const RECT& rect, Brush& b) { ::FillRect(dc, &rect, b); }
	void Text(int x, int y, const wchar_t* text) { TextOut(dc, x, y, text, std::wcslen(text)); }
	void SetTextColor(const COLORREF &color) { ::SetTextColor(dc, color); }
	void SetTextBgColor(const COLORREF &color) { ::SetBkColor(dc, color); }
};