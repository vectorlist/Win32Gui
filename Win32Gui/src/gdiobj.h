#pragma once

#include <Windows.h>
#include <memory>

#define COLOR_BLACK				Color(0,0,0)
#define PEN_DEFCOLOR			Color(200,200,200)

#define FONT_DEFSIZE			18
#define FONT_DEFCOLOR			PEN_DEFCOLOR
#define FONT_FAMALY_SEGOIUI		TEXT("Segoi UI")

#define FONT_SYSTEM				Font::SystemFont

class Color
{
public:
	Color(){ mColor = BYTE(0) | (BYTE(0) << 8) | (BYTE(0) << 16);}
	Color(int r, int g, int b){ mColor = BYTE(r) | (BYTE(g) << 8) | (BYTE(b) << 16);}
	Color(int x) { mColor = BYTE(x) | (BYTE(x) << 8) | (BYTE(x) << 16); }
	operator COLORREF(){ return mColor;}
	operator COLORREF() const { return mColor; }
private:
	COLORREF mColor;
};

#define SAFE_DELETE_GDIOBJ(x)	if(x) { ::DeleteObject(x); x = NULL;}
#define SAFE_DELETE_WND(x)		if(x) { ::DestroyWindow(x); x = NULL;}

/*----------------------- Base Gdi Object ---------------------*/

class GdiObj
{
public:
	GdiObj() {}
	~GdiObj() { SAFE_DELETE_GDIOBJ(mData); }
	HGDIOBJ mData;
};

/*----------------------- Brush ---------------------*/
class Brush
{
public:
	Brush();
	Brush(COLORREF color);
	Brush(int r, int g, int b);

	operator std::shared_ptr<GdiObj>&() { return mBrush; }

	COLORREF Color() const { return mColor; }
	operator HBRUSH() const { return (HBRUSH)mBrush->mData; }
	static Brush WindowBrush;
	static Brush WidgetBrush;
	static Brush TitleBrush;
private:
	std::shared_ptr<GdiObj> mBrush;			//not just gdiobject for color
	COLORREF mColor;
};
 
/*----------------------- Pen ---------------------*/
class Pen
{
public:
	Pen();
	Pen(int syle, int width, const Color &color);

	operator std::shared_ptr<GdiObj>&() { return mPen; }
	operator HPEN() const { return (HPEN)mPen->mData; }
private:
	std::shared_ptr<GdiObj> mPen;
};

/*----------------------- Font ---------------------*/

class Font
{
public:
	Font();
	Font(LPCWSTR fontFamily, int size = 18);

	operator std::shared_ptr<GdiObj>&() { return mFont; }
	operator HFONT() const { return (HFONT)mFont->mData; }
	static Font SystemFont;
private:
	std::shared_ptr<GdiObj> mFont;
};

