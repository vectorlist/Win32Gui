#pragma once

#include <Windows.h>
#include <rect.h>

class Window;
class Painter;
class Resizer
{
public:
	Resizer(int borderSize = 8);

	int		GetBorderSize() const;
	void	SetActive(bool active);
	bool	GetActive() const;
	LRESULT HitEvent(Window* window, LPARAM lp);
private:
	bool			mActive;
	int				mBorderSize;

};

class TitleBar
{
public:
	TitleBar(HWND handle, int fixedSize = 30);

	void	SetSize(int size);
	int		GetSize() const;
	void	SetActive(bool active);
	bool	GetActive() const;
	Rect	GetTitlebarRect() const;

	void	Paint(Painter* painter);
	LRESULT HitEvent(LPARAM lp);
private:
	int		mFixedSize;
	bool	mActive;
	HWND	mHandle;
};