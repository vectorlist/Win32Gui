#pragma once

#include <Windows.h>

/*------------------- custom window message ------------------------*/
#define CWM_WINDOWCREATED		::RegisterWindowMessage(TEXT("CWM_WINDOWCREATED"))
#define CWM_UPDATED				::RegisterWindowMessage(TEXT("CWM_UPDATED"))

/*------------------- custom window notification -------------------*/
#define CWN_BARMOVE				(WM_APP + 0x3F20)

struct CompareWindow
{
	bool operator()(HWND a, HWND b) const
	{
		return ((DWORD_PTR)a < (DWORD_PTR)b);
	}
};


namespace  win
{
	inline bool IsPointOnRect(const POINT &point, const RECT &rect)
	{
		if (point.x > rect.left && point.x < rect.right &&
			point.y > rect.top && point.y < rect.bottom) {
			return true;
		}
		return false;
	}

	//Window* GetwindowFromHandle(HWND handle)
	//{
	//	//TODO : register HWND window to custom allocate
	//	return NULL;
	//}
}

inline std::ostream& operator<<(std::ostream &os, const RECT &rc)
{
	os << "Rect(" << rc.left << ", " << rc.right << ", " <<
		rc.top << ", " << rc.bottom << ")";
	return os;
}