#include "wincore.h"
#include <window.h>
#include <log.h>
#include <application.h>

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

bool Resizer::IsActive() const
{
	return mActive;
}

LRESULT Resizer::HitEvent(Window* window, LPARAM lp)
{
	if (!mActive) return HTCLIENT;
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

	return HTCLIENT;
}

/*--------------------- TitleBar -----------------------*/

TitleBar::TitleBar(HWND handle, int fixedSize)
	: mHandle(handle), mFixedSize(fixedSize), mActive(true)
{
	SetBrush(Brush(60, 65, 70));
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

bool TitleBar::IsActive() const
{
	return mActive;
}

Rect TitleBar::GetTitlebarRect() const
{
	Rect rect; 
	GetClientRect(mHandle, &rect);
	rect.bottom = mFixedSize;
	return rect;
}

void TitleBar::SetBrush(Brush &brush)
{
	mBrush = brush;
}

Brush& TitleBar::GetBrush()
{
	return mBrush;
}

void TitleBar::Paint(Painter *painter)
{
	if (!mActive) return;
	
	Window* window = App->GetWindowFromMap(mHandle);
	
	auto rect = GetTitlebarRect();
	painter->SetBrush(GetBrush());
	painter->FillRect(rect);
}

LRESULT TitleBar::HitEvent(LPARAM lp)
{
	if (!mActive) return LNULL;
	Rect rect = GetTitlebarRect();
	//LOG << rect << ENDN;
	return LNULL;
}
