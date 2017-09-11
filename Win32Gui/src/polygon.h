#pragma once

#include <point.h>
#include <vector>

class Poly
{
public:
	Poly& operator<<(const Point& point);

	//return itself as mPoint const data
	operator Point*()
	{
		return mPoints.data();
	}

	operator Point*() const
	{
		return (Point*)mPoints.data();
	}
	int Size() const {
		return mPoints.size();
	}
private:
	std::vector<Point> mPoints;
};

inline Poly& Poly::operator<<(const Point& point)
{
	mPoints.emplace_back(point);
	return *this;
}
