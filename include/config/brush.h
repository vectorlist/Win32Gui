#pragma once

#define WIN32_LEAN_AND_MEAN
#include <Windows.h>
#include <typeconfig.h>

#define BRUSH_COLOR_BR				RGB(40,40,40)
#define BRUSH_COLOR_TITLE_BG		RGB(70,70,70)
#define BRUSH_COLOR_TEXT			RGB(190,190,190)
#define BRUSH_COLOR_TITLE_TEXT		RGB(190,190,190)

#define BRUSH_MAIN					Brush(40,40,40)
#define BRUSH_TITLE					Brush(70,70,70)
#define BRUSH_WIDGET				Brush(70,70,70)
#define BRUSH_WINDOW				Brush(50,50,50)
#define BRUSH_YELLOW				Brush(170,160,100)
#define BRUSH_BLUE					Brush(50,80,150)

struct Brush
{
	Brush() = delete;
	Brush(int32 r, int32 g, int32 b);
	Brush(COLORREF color);
	~Brush();

	//delete copy and asign
	Brush(const Brush&) = delete;
	Brush& operator=(const Brush&) = delete;

	//assign conversation with HBRUSH
	operator HBRUSH();
	operator HBRUSH() const;

	COLORREF GetColor() const;

private:
	COLORREF mColor;
	HBRUSH mBrush;
};

inline Brush::Brush(int32 r, int32 g, int32 b)
{
	mColor = RGB(r, g, b);
	mBrush = CreateSolidBrush(mColor);
}

inline Brush::Brush(COLORREF color)
{
	mColor = color;
	mBrush = CreateSolidBrush(mColor);
}

inline Brush::operator HBRUSH()
{
	return mBrush;
}

inline Brush::operator HBRUSH() const
{
	return mBrush;
}


inline Brush::~Brush()
{

	if (mBrush) {
		DeleteObject(mBrush);
	}
	mBrush = NULL;
}

inline COLORREF Brush::GetColor() const
{
	return mColor;
}