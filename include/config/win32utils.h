#pragma once

#include <Windows.h>

struct CompareWindow
{
	bool operator()(HWND a, HWND b) const
	{
		return ((DWORD_PTR)a < (DWORD_PTR)b);
	}
};

struct WindowRect
{
	WindowRect() : x(x), y(y), width(0), height(0){}
	WindowRect(int x, int y, int width, int height) 
		: x(x), y(y), width(width), height(height) {}
	int x, y, width, height;
};

namespace  win
{
	inline WindowRect GetWinRectFromRect(RECT &rc)
	{
		//::GetWndpo
		WindowRect wrc;
		wrc.x = rc.left;
		wrc.y = rc.top;
		wrc.width = rc.right - rc.left;
		wrc.height = rc.bottom - rc.top;
		return wrc;
	}

	inline WindowRect GetMapWinRect(HWND handle)
	{
		RECT rc;
		::GetClientRect(handle, &rc);
		//MapWindowPoints(handle)
	}

	inline HWND CreateWindowHandleEx(
		DWORD exStyle,
		LPCTSTR lpClassName,
		LPCTSTR lpWndName,
		DWORD style,
		WindowRect &wrc,
		HWND parent,
		HMENU menu,
		HINSTANCE instance,
		LPVOID lpParam)
	{
		return CreateWindowEx(exStyle, lpClassName, lpWndName, style,
			wrc.x, wrc.y, wrc.width, wrc.height, parent, menu, instance, lpParam);
	}

	inline void MoveWindowRect(HWND handle, WindowRect &wrc, BOOL repaint = TRUE)
	{
		MoveWindow(handle, wrc.x, wrc.y, wrc.width, wrc.height, repaint);
	}

	inline RECT GetTitleRect(HWND handle, int fixedSize)
	{
		RECT rect;
		::GetClientRect(handle, &rect);
		rect.bottom = rect.top + fixedSize;
		return rect;
	}

	inline bool IsPointOnRect(const POINT &point, const RECT &rect)
	{
		if (point.x > rect.left && point.x < rect.right &&
			point.y > rect.top && point.y < rect.bottom) {
			return true;
		}
		return false;
	}
}

inline std::ostream& operator<<(std::ostream &os, const RECT &rc)
{
	os << "Rect(" << rc.left << ", " << rc.right << ", " <<
		rc.top << ", " << rc.bottom << ")";
	return os;
}