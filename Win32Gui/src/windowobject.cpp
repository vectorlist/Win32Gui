#include <windowobject.h>

WindowObject::WindowObject(HWND parent)
	: mParent(parent), mHandle(NULL)
{
}

WindowObject::~WindowObject()
{
	if (mHandle) {
		DestroyWindow(mHandle);
		mHandle = NULL;
	}
}

void WindowObject::Show()
{
	ShowWindow(*this, TRUE);
	UpdateWindow(*this);
}

void WindowObject::Hide()
{
	ShowWindow(*this, FALSE);
}

void WindowObject::SetWindowName(const std::string &name)
{
	mWindowName = name;
}

std::wstring WindowObject::GetWideWindowName() const
{
	std::wstring wide;
	wide.assign(mWindowName.begin(), mWindowName.end());
	return wide;
}

Rect WindowObject::GetRect() const
{
	Rect rect;
	GetClientRect(mHandle, &rect);
	return rect;
}

HWND WindowObject::GetHandle() const
{
	return mHandle;
}
