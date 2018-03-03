#pragma once

#include <window.h>

#define App Application::gApp

class Application
{
public:
	Application();
	~Application();

	HINSTANCE	GetInstance() { return mInstance; };
	void		SetWindowMap(HWND handle, Window* window);
	Window*		GetWindowFromMap(HWND handle);
	void		RemoveWindowFromMap(HWND handle);
	//GDI+
	void		InitGdiplus();
	void		ReleaseGdiplus();

	int Run();
//private:
	static Application*			gApp;

private:
	int			InitMemoryInstance();

	HINSTANCE								mInstance;
	std::map<HWND, Window*, CompareWindow>	mWindowMap;
	//GDI+
	ULONG_PTR						mGdiplusTokken;
	Gdiplus::GdiplusStartupInput	mGdiplusInput;
};

