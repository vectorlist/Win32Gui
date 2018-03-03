#pragma once

#include <winobject.h>

//User Wnd Message
#define UWM_PREPAREDESTROY		(WM_USER + 0)
#define UWM_ENTEREVENT			(WM_USER + 1)

#define POINT_IN_RECT(x,xx)		::PtInRect(x,x)

class Window : public WinObject
{
public:
	Window(HWND parent = NULL);
	Window(const std::string &title, HWND parnet = NULL);
	Window(int x, int y, int w, int h, std::string title = "none", HWND parent = NULL);
	virtual~Window();

	virtual void	Create(HWND parent);
	virtual void	StaticCreate(HWND parent);
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
	virtual void	KeyPressedEvent(KeyEvent &event);
	virtual void	KeyReleaseEvent(KeyEvent &event);

	//Mouse
	virtual void	MouseMoveEvent(MouseEvent &event);
	virtual void	MousePressEvent(MouseEvent &event);
	virtual void	MouseReleaseEvent(MouseEvent &event);
	virtual void	MouseHooverEvent(MouseEvent &event);
	virtual void	MouseEnterEvent(MouseEvent &event);
	virtual void	MouseLeaveEvent(MouseEvent &event);

	//Update
	virtual void	Update();

	virtual LRESULT HitEvent(UINT msg, WPARAM wp, LPARAM lp);

	virtual LRESULT CALLBACK LocalWndProc(UINT msg, WPARAM wp, LPARAM lp);
	static	LRESULT CALLBACK GlobalWndProc(HWND handle, UINT msg, WPARAM wp, LPARAM lp);

	TitleBar*		mTitlebar;
	Resizer*		mResizer;

};

