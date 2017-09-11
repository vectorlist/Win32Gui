#pragma once

#include <winobject.h>

#define WM_USER_PREPAREDESTROY     (WM_USER + 0)

#define POINT_IN_RECT(x,xx)		::PtInRect(x,x)

class Window : public WinObject
{
public:
	Window(HWND parent = NULL);
	Window(const std::string &title, HWND parnet = NULL);
	Window(int x, int y, int w, int h, std::string title = "none", HWND parent = NULL);
	virtual~Window();

	virtual void	Create(HWND parent);
	Window*			GetParentWindow();
	Rect			GetActiveRect() const;
	TitleBar*		GetTitleBar() { return mTitlebar; };
protected:
	//PRE CREATE
	virtual void	PreRegisterClass(WNDCLASS &wc);
	virtual void	PreCreate(CREATESTRUCT &cs);
	virtual void	PrePaintEvent(Painter* painter);
	
	virtual void	OnCreateEvent(CREATESTRUCT& cs);
	virtual void	PaintEvent(Painter* painter);
	virtual void	ResizeEevnt(UINT msg, WPARAM wp, LPARAM lp);
	virtual void	KeyPressedEvent(WPARAM wp);

	//Mouse
	virtual void	MouseMoveEvent(MouseEvent &event);
	virtual void	MousePressEvent(MouseEvent &event);
	virtual void	MouseEnterEvent(MouseEvent &event);
	virtual void	MouseLeaveEvent(MouseEvent &event);

	virtual LRESULT HitEvent(UINT msg, WPARAM wp, LPARAM lp);

	virtual LRESULT CALLBACK LocalWndProc(UINT msg, WPARAM wp, LPARAM lp);
	static LRESULT CALLBACK	 GlobalWndProc(HWND handle, UINT msg, WPARAM wp, LPARAM lp);

	TitleBar*		mTitlebar;
	Resizer*		mResizer;

};

