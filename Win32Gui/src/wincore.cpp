#include "wincore.h"
#include <window.h>
#include <log.h>

Resizer::Resizer(int borderSize)
	: mBorderSize(borderSize), mActive(true)
{
}

int Resizer::GetBorderSize() const
{
	return mBorderSize;
}

void Resizer::SetActive(bool active)
{
	mActive = active;
}

bool Resizer::GetActive() const
{
	return mActive;
}

LRESULT Resizer::HitEvent(Window* window, LPARAM lp)
{
	Point pos(lp);
	ScreenToClient(*window, &pos);

	auto rect = window->GetRect();

	bool hitLeft = pos.x >= rect.left && pos.x <= rect.left + mBorderSize;
	bool hitTop = pos.y >= rect.top && pos.y <= rect.top + mBorderSize;
	bool hitRight = pos.x <= rect.right && pos.x >= rect.right - mBorderSize;
	bool hitBottom = pos.y <= rect.bottom && pos.y >= rect.bottom - mBorderSize;

	if (hitLeft) {
		if (hitTop) return HTTOPLEFT;
		if (hitBottom) return HTBOTTOMLEFT;
		return HTLEFT;
	}
	if (hitRight) {
		if (hitTop) return HTTOPRIGHT;
		if (hitBottom) return HTBOTTOMRIGHT;
		return HTRIGHT;
	}
	if (hitTop) return HTTOP;
	if (hitBottom) return HTBOTTOM;

	return LNULL;
}

/*--------------------- TitleBar -----------------------*/

TitleBar::TitleBar(int fixedSize)
	: mFixedSize(fixedSize), mActive(true)
{
}

void TitleBar::SetSize(int size)
{
	mFixedSize = size;
}

int TitleBar::GetSize() const
{
	return mFixedSize;
}

void TitleBar::SetActive(bool active)
{
	mActive = active;
}

bool TitleBar::GetActive() const
{
	return mActive;
}

Rect TitleBar::GetTitlebarRect(HWND handle)
{
	Rect rect; 
	GetClientRect(handle, &rect);
	rect.bottom = mFixedSize;
	return rect;
}

void TitleBar::PaintEvent(HWND handle, Painter *painter)
{
	static Brush brush(80, 82, 85);
	auto rect = GetTitlebarRect(handle);
	painter->SetBrush(brush);
	painter->FillRect(rect);
}

LRESULT TitleBar::HitEvent(Window *window, LPARAM lp)
{
	Rect rect = GetTitlebarRect(*window);
	LOG << rect << ENDN;
	return LNULL;
}
