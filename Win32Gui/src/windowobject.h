#pragma once
#include <config.h>

class WindowObject
{
public:
	WindowObject(HWND parent);
	virtual~WindowObject();

	void			Show();
	void			Hide();
	void			SetWindowName(const std::string &name);
	std::wstring	GetWideWindowName() const;
	Rect			GetRect() const;
	HWND			GetHandle() const;

	int				GetX() const			{ return mPos.x; }
	int				GetY() const			{ return mPos.y; }
	int				GetWidth() const		{ return mSize.cx; }
	int				GetHeight() const		{ return mSize.cy; }
	void			SetX(int x)				{ mPos.x = x; }
	void			SetY(int y)				{ mPos.y = y; }
	void			SetWidth(int w)			{ mSize.cx = w; }
	void			SetHeight(int h)		{ mSize.cy = h; }

	operator HWND()							{ return mHandle; }
protected:
	HWND			mHandle;
	HWND			mParent;

	std::string		mWindowName;
private:
	Point			mPos;
	Size			mSize;
};