#pragma once

#define WIN32_LEAN_AND_MEAN
#include <Windows.h>
#include <typeconfig.h>

#define BRUSH_COLOR_BR				RGB(40,40,40)
#define BRUSH_COLOR_TITLE_BG		RGB(70,70,70)
#define BRUSH_COLOR_TEXT			RGB(190,190,190)
#define BRUSH_COLOR_TITLE_TEXT		RGB(190,190,190)
#define COLOR_BLACK					RGB(0,0,0)

#define BRUSH_MAIN					Brush(40,40,40)
#define BRUSH_TITLE					Brush(70,70,70)
#define BRUSH_WIDGET				Brush(70,70,70)
#define BRUSH_WINDOW				Brush(50,50,50)
#define BRUSH_YELLOW				Brush(170,160,100)
#define BRUSH_BLUE					Brush(50,80,150)
#define BRUSH_ERROR					Brush(255, 0, 0)
#define BRUSH_NULL					Brush(0,0,0)

#include <memory>
//template <typename T>
//struct deref_ptr;
//template <typename T>
//struct deref_ptr<T*> { typedef T type; };
//
//typedef std::shared_ptr<deref_ptr<HBRUSH>::type> brush_ptr;
//
//inline brush_ptr create_brush(COLORREF color) {
//	return brush_ptr(CreateSolidBrush(color), DeleteObject);
//}
//typedef std::shared_ptr<defref>
#include <log.h>

//conversasion Color to COLORREF
class Color
{
public:
	Color()
	{
		mColor = BYTE(0) | (BYTE(0) << 8) | (BYTE(0) << 16);
	}
	Color(int r, int g, int b)
	{
		mColor = BYTE(r) | (BYTE(g) << 8) | (BYTE(b) << 16);
	}

	operator COLORREF()
	{
		return mColor;
	}
private:
	COLORREF mColor;
};

//replace to template all gdi object

class Brush_T
{
public:
	Brush_T()
	{
		mColor = RGB(0, 0, 0);
		mHandle = CreateSolidBrush(mColor);
	}
	Brush_T(int r, int g, int b)
	{
		mColor = RGB(r, g, b);
		mHandle = CreateSolidBrush(mColor);
	}
	~Brush_T()
	{
		Release();
	}

	void Release()
	{
		if (mHandle) {
			DeleteObject(mHandle);
			mHandle = NULL;
		}
	}

	HBRUSH mHandle;
	COLORREF mColor;
};

class Brush
{
public:
	Brush()
	{
		mBrush = std::make_shared<Brush_T>();
	}
	Brush(int r, int g, int b)
	{
		mBrush = std::make_shared<Brush_T>(r,g,b);
	}

	operator std::shared_ptr<Brush_T>&()
	{
		return mBrush;
	}

	operator HBRUSH() const
	{
		return mBrush->mHandle;
	}
	COLORREF GetColor() const
	{
		return mBrush->mColor;
	}
private:
	std::shared_ptr<Brush_T> mBrush;
};


class Pen_T
{
public:
	Pen_T(int style, int width, Color color)
	{
		mColor = color;
		mHandle = ::CreatePen(style, width, mColor);
	}
	
	~Pen_T()
	{
		Release();
	}

	void Release()
	{
		if (mHandle) {
			DeleteObject(mHandle);
			mHandle = NULL;
		}
	}

	HPEN mHandle;
	COLORREF mColor;
};

class Pen
{
public:
	Pen()
	{
		mPen = std::make_shared<Pen_T>(PS_SOLID, 1, Color());
	}
	Pen(int style, int width, Color color = Color())
	{
		mPen = std::make_shared<Pen_T>(style, width, color);
	}


	//counting refference 
	operator std::shared_ptr<Pen_T>&()
	{
		return mPen;
	}

	operator HPEN()
	{
		return mPen->mHandle;
	}

private:
	std::shared_ptr<Pen_T> mPen;
};


inline std::ostream& operator<<(std::ostream &os,  Color& color) 
{
	//LOBYTE
	os  << "Color(" << (int)(color & 0xff) 
		<< ", " << (int)(color >> 8)
		<< ", " << (int)(color >> 16) << ")";
	return os;
}