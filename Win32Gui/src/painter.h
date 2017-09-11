#pragma once

#include <Windows.h>
//#include <cwchar>
#include <rect.h>
#include <brush.h>
#include <polygon.h>


class Painter
{
public:
	Painter() : dc(NULL) {}
	HDC			dc;
	PAINTSTRUCT ps;
	//expensive but easy to use
	Brush		brush;
	//Pen			pen;
	

	void Begin(HWND handle) { dc = BeginPaint(handle, &ps); }
	void End(HWND handle) { EndPaint(handle, &ps); }

	//Brush
	void SetBrush(Brush b) { brush = b; }
	Brush GetBrush() { return brush; }

	//Pen
	void SetPen(Pen p);

	void FillRect(const RECT &rect) { ::FillRect(dc, &rect, brush); }
	void Text(int x, int y, const wchar_t* text) { TextOut(dc, x, y, text, lstrlen(text)); }
	void SetTextColor(const COLORREF &color) { ::SetTextColor(dc, color); }
	void SetTextBgColor(const COLORREF &color) { ::SetBkColor(dc, color); }

	void PaintPolygon(const Poly& poly);
	void PaintPolygons(int* group, const Poly& poly);

	void PaintLine(const Point& a, const Point& b);

};


