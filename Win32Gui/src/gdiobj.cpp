#include <gdiobj.h>

/*----------------------- Brush  ---------------------*/

Brush Brush::WindowBrush = Brush(80, 80, 80);
Brush Brush::WidgetBrush = Brush(60, 60, 60);
Brush Brush::TitleBrush = Brush(60, 63, 65);

Brush::Brush()
{

	mBrush = std::make_shared<GdiObj>();
	mColor = RGB(0, 0, 0);
	mBrush->mData = CreateSolidBrush(mColor);
}

Brush::Brush(COLORREF color)
{
	mBrush = std::make_shared<GdiObj>();
	mColor = color;
	mBrush->mData = CreateSolidBrush(mColor);
}

Brush::Brush(int r, int g, int b)
{
	mBrush = std::make_shared<GdiObj>();
	mColor = RGB(r, g, b);//Color(r,g,b);
	mBrush->mData = CreateSolidBrush(mColor);
}

/*----------------------- Pen ---------------------*/
Pen::Pen()
{
	mPen = std::make_shared<GdiObj>();
	mPen->mData = CreatePen(PS_SOLID, 1, PEN_DEFCOLOR);
}

Pen::Pen(int style, int width, const Color &color)
{
	mPen = std::make_shared<GdiObj>();
	mPen->mData = CreatePen(style, width, color);
}

/*----------------------- Font ---------------------*/

Font Font::SystemFont = Font(FONT_FAMALY_SEGOIUI);

Font::Font()
{
	mFont = std::make_shared<GdiObj>();
	mFont->mData = CreateFont(FONT_DEFSIZE, 0, 0, 0, 0, 0, 0, 0, 0,
		0, 0, 0, 0, FONT_FAMALY_SEGOIUI);
}

Font::Font(LPCWSTR fontFamily, int size)
{
	mFont = std::make_shared<GdiObj>();
	mFont->mData = CreateFont(size, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, fontFamily);
}
