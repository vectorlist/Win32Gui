#include <painter.h>
#include <win32utils.h>

Painter::Painter(HWND handle)
	: mHandle(handle)
{
	dc = BeginPaint(mHandle, &ps);
}

Painter::~Painter()
{
	::EndPaint(mHandle, &ps);
}

void Painter::SetFont(Font &font)
{
	::SelectObject(dc, font);
}

void Painter::SetPen(Pen &p)
{
	//release itself by shared ptr
	::SelectObject(dc, p);
}

void Painter::Text(int x, int y, const wchar_t * text)
{
	::TextOut(dc, x, y, text, lstrlen(text));
}

/*fill text with brush bg color*/
void Painter::FillText(int x, int y, const std::string &text, Color color)
{
	::SetTextColor(dc, color);
	::SetBkColor(dc, brush.Color());
	auto code = TO_WSTRING(text);
	::TextOut(dc, x, y, code.c_str(), lstrlen(code.c_str()));
}

/*paint single polygon*/
void Painter::PaintPolygon(const Poly &poly)
{
	Polygon(dc, poly,  poly.Size());
}

/*paint multiple polygon*/
void Painter::PaintPolygons(int* group, const Poly &poly)
{
	PolyPolygon(dc, poly, group, poly.Size());
}

void Painter::PaintLine(const Point &a, const Point &b)
{
	MoveToEx(dc, a.x, a.y, NULL);
	LineTo(dc, b.x, b.y);
}
