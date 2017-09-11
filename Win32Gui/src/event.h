#pragma once

#include <windows.h>
#include <brush.h>
#include <point.h>

struct MouseEvent
{
	//MouseEvent(UINT msg, WPARAM wp, LPARAM lp)
	//	: code(msg), wp(wp), lp(lp)
	//{}
	UINT code;
	WPARAM wp;
	LPARAM lp;

	Point GetPos() const
	{
		return Point(lp);
	}

	/*Point GetGlobalPos()
	{
	::ClientToScreen()
	}*/
};