#pragma once

#include <winobject.h>

struct WinEvent
{
	UINT msg;
	WPARAM wp;
	LPARAM lp;
};

struct WinState
{
	bool isTopWindow;
	bool resizeable;
};

#define WMU_WINDOWCREATED		::RegisterWindowMessage(TEXT("WMU_WINDOWCREATED"))
#define WMU_UPDATED				::RegisterWindowMessage(TEXT("WMU_UPDATED"))

class Window : public WinObject
{
public:
	Window(HWND parent = NULL);
	Window(int x, int y, int w, int h, std::string title = "none", HWND parent = NULL);
	virtual~Window();

	virtual void Create(HWND parent);
protected:
	//PRE CREATE
	virtual void PreRegisterClass(WNDCLASS &wc);
	virtual void PreCreateStruct(CREATESTRUCT &cs);

	virtual void InitializeEvent(CREATESTRUCT& cs);
	virtual void PaintEvent(Painter* painter);
	virtual void ResizeEevnt(UINT msg, WPARAM wp, LPARAM lp);
	virtual void KeyPressEvent(WPARAM wp);
	virtual LRESULT HitEvent(UINT msg, WPARAM wp, LPARAM lp);

	LRESULT CALLBACK		LocalWndProc(UINT msg, WPARAM wp, LPARAM lp);
	static LRESULT CALLBACK	GlobalWndProc(HWND handle, UINT msg, WPARAM wp, LPARAM lp);

	WinState mState;

};


class MainWindow : public Window
{
public:
	MainWindow(HWND parent = NULL);
	MainWindow(int x, int y, int w, int h, std::string title = "none", HWND parent = NULL);
	virtual~MainWindow();

protected:
	virtual void PreRegisterClass(WNDCLASS &wc);
	virtual void PreCreateStruct(CREATESTRUCT &cs);
	virtual void PaintEvent(Painter* painter) override;
	virtual HRESULT HitEvent(UINT msg, WPARAM wp, LPARAM lp);

	TitleBar	mTitlebar;
	Resizer		mResizer;
};
