#pragma once

#include <Windows.h>
#include <gdiobj.h>
#include <string>
/*------------------- custom window message ------------------------*/
#define CWM_WINDOWCREATED		::RegisterWindowMessage(TEXT("CWM_WINDOWCREATED"))
#define CWM_UPDATED				::RegisterWindowMessage(TEXT("CWM_UPDATED"))

/*------------------- custom window notification -------------------*/
#define CWN_BARMOVE				(WM_APP + 0x3F20)


/*------------------- custom window class names  -------------------*/
#define	CLASSNAME_MAINWINDOW	TEXT("MainWindowClass")

//layout
#define CLASSNAME_LAYOUT		TEXT("LayoutClass")		//we dont use this
#define CLASSNAME_HLAYOUT		TEXT("HBoxLayoutClass")
#define CLASSNAME_VLAYOUT		TEXT("VBoxLayoutClass")

//splitter
#define CLASSNAME_SPLITTER		TEXT("SplitterClass")

/*------------------- custom window names  -------------------*/
#define WINDOWNAME_HLAYOUT		"HBox Layout"

//def operators


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

	inline void ChangeWindowStyle(HWND handle, DWORD style)
	{
		SetWindowLong(handle, GWL_STYLE, style);
	}

	inline void SetParentAsWindowStyle(HWND src, HWND parent, DWORD srcStyle)
	{
		SetParent(src, parent);
		SetWindowLong(src, GWL_STYLE, srcStyle);
	}
	/*coverte string to wide string*/
	inline std::wstring ToWString(const std::string &code)
	{
		std::wstring output(code.begin(), code.end());
		return output;
	}
}

#define TO_WSTRING(x)			win::ToWString(x)

inline std::ostream& operator<<(std::ostream &os, const RECT &rc)
{
	os << "Rect(" << rc.left << ", " << rc.right << ", " <<
		rc.top << ", " << rc.bottom << ")";
	return os;
}