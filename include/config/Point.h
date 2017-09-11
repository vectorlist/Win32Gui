#pragma once


#include <typeconfig.h>
#include <Windows.h>
#include <assert.h>
#include <ostream>

class Point : public POINT
{
public:
	Point()				{ x = 0; y = 0; }
	Point(int x, int y) { this->x = x; this->y = y; }
	Point(POINT point)  { x = point.x; y = point.y; }
	Point(LPARAM lp)	{ x = (short)LOWORD(lp); y = (short)HIWORD(lp); }

	Point& operator+(const Point& other)
	{
		x += other.x;
		y += other.y;
		return *this;
	}

	Point& operator-(const Point& other)
	{
		x -= other.x;
		y -= other.y;
		return *this;
	}

	//Point operator+(Point& other)
	//{
	//	x += other.x;
	//	y += other.y;
	//	return *this;
	//}

	//Point operator-(Point& other)
	//{
	//	x -= other.x;
	//	y -= other.y;
	//	return *this;
	//}

	operator POINT() { return *this; }
	operator LPPOINT() { return this; }
};

class Size : public SIZE
{
public:
	Size() { cx = 0; cy = 0; }
	Size(int x, int y) { cx = x; cy = y; }

	Size& operator+(const Size& other)
	{
		cx += other.cx;
		cy += other.cy;
		return *this;
	}

	Size& operator-(const Size& other)
	{
		cx -= other.cx;
		cy -= other.cy;
		return *this;
	}

	operator SIZE() { return *this; }
	operator LPSIZE() { return this; }

	bool operator==(const Size &s) { return cx == s.cx && cy == s.cy; }
};

inline std::ostream& operator<<(std::ostream& os, const POINT &p)
{
	os << "Point(" << p.x << ", " << p.y << ")";
	return os;
}

inline std::ostream& operator<<(std::ostream& os, const SIZE &s)
{
	os << "Size(" << s.cx << ", " << s.cy << ")";
	return os;
}