#pragma once

#include <config.h>

struct PaintEvent
{
	HDC dc;
};

class Window
{
public:
	Window(Window* parent = NULL);
	Window(const std::wstring &name, Window* parent = NULL);
	virtual~Window();

	virtual void	BuildWindow();

	void			Show(int cmd = SW_SHOW);
	RECT			GetRect() const;
	Window*			GetParent() { return mParent; }
	HWND			GetHandle() { return mHandle; }
	void			SetSize(int width, int height) 
	{ 
		mWidth = width;
		mHeight = height;
	}

	void			SetPosition(int x, int y)
	{
		mPos.x = x;
		mPos.y = y;
	}

	static HRESULT CALLBACK MainWndProc(HWND handle, UINT msg, WPARAM wp, LPARAM lp);

	HWND			mHandle;
protected:
	virtual void OnCreate();
	virtual void OnPaint(PaintEvent &e);
	virtual void TitleEvent();
	virtual void PreRegisterClassEx(WNDCLASSEX &wc);

	virtual HRESULT LocalWndProc(UINT msg, WPARAM wp, LPARAM lp);
private:

	std::wstring	mName;
	Window*			mParent;
	//HWND			mHandle;
	HWND			mParentHandle;

	WindowRect		mWindowRect;
	Point			mPos;
	int				mWidth;
	int				mHeight;
};