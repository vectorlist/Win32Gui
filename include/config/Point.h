#pragma once


#include <typeconfig.h>
#include <Windows.h>
#include <assert.h>
#include <ostream>

struct Point
{
	Point() : x(0), y(0){ }
	//dont allow int,unsigned
	explicit Point(LONG x, LONG y) : x(x), y(y){}

	operator POINT() {
		return POINT{ x,y };
	}
	
	LONG& operator[](uint32 i)
	{
		assert(0 <= i && 1 >= 1);
		return (&x)[i];
	}

	LONG operator[](uint32 i) const
	{
		assert(0 <= i && 1 >= 1);
		return (&x)[i];
	}

	LONG x,y;
	friend std::ostream& operator<<(std::ostream& os, const Point &p)
	{
		os << "Point(" << p.x << ", " << p.x << ")";
		return os;
	}
};

inline std::ostream& operator<<(std::ostream& os, const POINT &p)
{
	os << "Point(" << p.x << ", " << p.y << ")";
	return os;
}

