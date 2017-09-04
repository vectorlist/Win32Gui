#pragma once
#include <config.h>

class WinObject
{
public:
	WinObject(HWND parent);
	virtual~WinObject();

	void			Show();
	void			Hide();
	void			SetWindowName(const std::string &name);
	std::wstring	GetWideWindowName() const;
	std::string     GetWindowName() const;
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
	virtual Rect	GetActiveRect();
	HWND			mHandle;
	HWND			mParent;
	//Window*			

	std::string		mWindowName;
private:
	Point			mPos;
	Size			mSize;
};