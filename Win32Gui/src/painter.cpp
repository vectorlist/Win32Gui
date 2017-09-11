#include <painter.h>

void Painter::SetPen(Pen p)
{
	//release itself by shared ptr
	::SelectObject(dc, p);
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
