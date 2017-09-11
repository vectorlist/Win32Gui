#include <winobject.h>
#include <application.h>

WinObject::WinObject(HWND parent)
	: mParent(parent), mHandle(NULL), mEnableTrackMouse(true)
{
}

WinObject::~WinObject()
{
	if (mHandle) {
		//App->RemoveWindowFromMap(mHandle);
		DestroyWindow(mHandle);
		mHandle = NULL;
	}
}

void WinObject::Show()
{
	ShowWindow(*this, TRUE);
	UpdateWindow(*this);
}

void WinObject::Hide()
{
	ShowWindow(*this, FALSE);
}

void WinObject::SetWindowName(const std::string &name)
{
	mWindowName = name;
}

std::wstring WinObject::GetWideWindowName() const
{
	std::wstring wide;
	wide.assign(mWindowName.begin(), mWindowName.end());
	return wide;
}

std::string WinObject::GetWindowName() const
{
	return mWindowName;
}

/* get client rect, top/left is always 0, coordinate by local client */
Rect WinObject::GetRect() const
{
	Rect rect;
	::GetClientRect(mHandle, &rect);
	return rect;
}

/* get window screen rect, coordinate by screen */
Rect WinObject::GetWindowRect() const
{
	Rect rect;
	::GetWindowRect(mHandle, &rect);
	return rect;
}

HWND WinObject::GetHandle() const
{
	return mHandle;
}

void WinObject::SetFocus()
{
	::SetFocus(mHandle);
}

void WinObject::SetGeometry(int x, int y, int w, int h)
{
	::MoveWindow(mHandle, x, y, w, h, true);
	//TODO : relative position on runtime
}

int WinObject::GetX() const
{
	return GetPos().x;
}

int WinObject::GetY() const
{
	return GetPos().y;
}

int WinObject::Width() const
{
	return GetSize().cx;
}

int WinObject::Height() const
{
	return GetSize().cy;
}

void WinObject::Move(int x, int y, int w, int h, bool bRepaint)
{
	::MoveWindow(mHandle, x, y, w, h, bRepaint);
}

void WinObject::Move(const Point &pos, int w, int h, bool bRepaint)
{
	::MoveWindow(mHandle, pos.x, pos.y, w, h, bRepaint);
}

void WinObject::Move(const Point &pos, const Size &size, bool bRepaint)
{
	::MoveWindow(mHandle, pos.x, pos.y, size.cx, size.cy, bRepaint);
}

void WinObject::Move(const Rect &rect, bool bRepaint)
{
	::MoveWindow(mHandle, rect.left, rect.top, rect.GetWidth(), rect.GetHeight(), bRepaint);
}

/* set postion window on screen without change size*/
void WinObject::SetPos(const Point & pos)
{
	::SetWindowPos(mHandle, NULL, pos.x, pos.y, 0, 0, 
	SWP_ASYNCWINDOWPOS | SWP_NOACTIVATE | SWP_NOOWNERZORDER | SWP_NOSIZE | SWP_NOZORDER);
}

/* set size window on screen without change position*/
void WinObject::SetPos(int w, int h)
{
	::SetWindowPos(mHandle, NULL, 0, 0, w, h,
	SWP_ASYNCWINDOWPOS | SWP_NOACTIVATE | SWP_NOOWNERZORDER | SWP_NOMOVE | SWP_NOZORDER);
}

Point WinObject::GetPos() const
{
	Rect rect = GetRect();
	return Point(rect.left, rect.top);
}

Size WinObject::GetSize() const
{
	Rect rect = GetRect();
	return Size(rect.GetWidth(), rect.GetHeight());
}

Brush& WinObject::GetBrush()
{
	return mBrush;
}

void WinObject::SetBrush(const Brush &brush)
{
	mBrush = brush;
}

void WinObject::PostWndMessage(UINT msg, WPARAM wp, LPARAM lp) const
{
	::PostMessage(mHandle, msg, wp, lp);
}

int WinObject::SendWndMessage(UINT msg, WPARAM wp, LPARAM lp) const
{
	return static_cast<int>(::SendMessage(mHandle, msg, wp, lp));
}

/*update window rect for WM_PAINT*/
void WinObject::InvalidateRect(bool bRepaint)
{
	::InvalidateRect(*this, GetRect(), bRepaint);
}

void WinObject::InvalidateALL(bool bRepaint)
{
	::InvalidateRect(*this, NULL, bRepaint);
}

bool WinObject::GetTrackMouseEnable() const
{
	return mEnableTrackMouse;
}

void WinObject::SetTrackMouseEnable(bool enable)
{
	mEnableTrackMouse = enable;
}

void WinObject::SetParentWindow(HWND parent)
{
	::SetParent(*this, parent);
	mParent = parent;
}

/*for the check splitter window*/


bool WinObject::IsSplitter()
{
	return false;
}

/*it should be override by derived*/
Rect WinObject::GetActiveRect()
{
	Rect rect;
	::GetClientRect(*this, &rect);
	return rect;
}
