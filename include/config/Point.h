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

	operator POINT() { return *this; }
};


inline std::ostream& operator<<(std::ostream& os, const POINT &p)
{
	os << "Point(" << p.x << ", " << p.y << ")";
	return os;
}

class Size : public SIZE
{
public:
	Size() { cx = 0; cy = 0; }
	Size(int x, int y) { cx = x; cy = y; }

	operator SIZE() { return *this; }
	operator LPSIZE() { return this; }

	bool operator==(const Size &s) { return cx == s.cx && cy == s.cy; }
};

