#pragma once

#include <windows.h>
#include <point.h>

//Global window event
struct Event
{
	UINT code;
	WPARAM wp;
	LPARAM lp;
};

struct MouseEvent
{
	UINT code;
	WPARAM wp;
	LPARAM lp;

	Point GetPos() const
	{
		return Point(lp);
	}
};

struct KeyEvent
{
	WPARAM wp;
	LPARAM lp;
};

typedef struct WndEvent
{

}WndEvent_T, WndEvnetP;