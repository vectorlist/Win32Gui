#pragma once

#include <Windows.h>
#include <rect.h>
#include <gdiobj.h>
#include <polygon.h>
#include <string>


class Painter
{
public:
	Painter(HWND handle);
	~Painter();
	HDC			dc;
	PAINTSTRUCT ps;
	//expensive but easy to use
	Brush		brush;
	HWND        mHandle;

	//Brush
	void SetBrush(Brush &b) { brush = b; }
	Brush GetBrush() { return brush; }

	void SetFont(Font &font);
	void SetPen(Pen &p);

	void FillRect(const RECT &rect) { ::FillRect(dc, &rect, brush); }

	void Text(int x, int y, const wchar_t* text);
	void FillText(int x, int y, const std::string &text, Color color = Color(200));

	void SetTextColor(const COLORREF &color) { ::SetTextColor(dc, color); }
	void SetTextBgColor(const COLORREF &color) { ::SetBkColor(dc, color); }

	void PaintPolygon(const Poly& poly);
	void PaintPolygons(int* group, const Poly& poly);

	void PaintLine(const Point& a, const Point& b);

};


