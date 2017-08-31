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

	HBRUSH GetData()const;

	//static HBRUSH MainBrush;
	//static HBRUSH TitleBrush;
private:
	HBRUSH mBrush;
};

//HBRUSH Brush::MainBrush		= Brush(50, 50, 50);
//HBRUSH Brush::TitleBrush	= Brush(70, 70, 70);

inline Brush::Brush(int32 r, int32 g, int32 b)
{
	mBrush = CreateSolidBrush(RGB(r, g, b));
}

inline Brush::Brush(COLORREF color)
{
	mBrush = CreateSolidBrush(color);
}

inline Brush::operator HBRUSH()
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

inline HBRUSH Brush::GetData() const
{
	return mBrush;
}