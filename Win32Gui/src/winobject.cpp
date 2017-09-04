#include <winobject.h>

WinObject::WinObject(HWND parent)
	: mParent(parent), mHandle(NULL)
{
}

WinObject::~WinObject()
{
	if (mHandle) {
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

Rect WinObject::GetRect() const
{
	Rect rect;
	GetClientRect(mHandle, &rect);
	return rect;
}

HWND WinObject::GetHandle() const
{
	return mHandle;
}

Rect WinObject::GetActiveRect()
{
	return Rect();
}
