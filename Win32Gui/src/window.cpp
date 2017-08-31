#include "window.h"
#include <application.h>


Window::Window(Window* parent)
	: mParent(parent), mName(TEXT("none"))
{

	//BuildWindow();
}

Window::Window(const std::wstring &name, Window* parent)
	: mParent(parent),mName(name)
{

	//BuildWindow();
	mWidth = 1028;
	mHeight = 600;

	mPos.x = CENTER_X(mWidth);
	mPos.y = CENTER_Y(mHeight);
}

Window::~Window()
{
	DestroyWindow(mHandle);
	UnregisterClass(mName.c_str(), App->GetInstance());
}

void Window::BuildWindow()
{
	WNDCLASSEX wc{};

	wc.cbSize = sizeof(WNDCLASSEX);
	wc.style = CS_HREDRAW | CS_VREDRAW;
	wc.hInstance = App->GetInstance();
	wc.hIcon = NULL;
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);
	wc.hbrBackground = CreateSolidBrush(RGB(50, 50, 50));
	wc.lpszClassName = mName.c_str();
	wc.lpfnWndProc = MainWndProc;
	//wc.cbWndExtra
	this->PreRegisterClassEx(wc);

	if (!RegisterClassEx(&wc)) {
		LOG_FATAL("faile to register class");
	}

	mWindowRect.x = mPos.x;
	mWindowRect.y = mPos.y;
	mWindowRect.width = mWidth;
	mWindowRect.height = mHeight;

	
	mParentHandle = mParent ? mParent->GetHandle() : NULL;
	
	if (mParent) {
		/*mHandle = win::CreateWindowHandleEx(NULL, mName.c_str(), mName.c_str(),
			WS_CHILD | WS_VISIBLE | BS_OWNERDRAW | WS_THICKFRAME,
			mWindowRect, mParentHandle, App->GetInstance(), this);*/
		mHandle = win::CreateWindowHandleEx(NULL, mName.c_str(), mName.c_str(),
			WS_CHILD | WS_VISIBLE | BS_GROUPBOX,
			mWindowRect, mParentHandle, (HMENU)0, App->GetInstance(), this);
	}
	else {
		mHandle = win::CreateWindowHandleEx(NULL, mName.c_str(), mName.c_str(),
			WS_POPUP | WS_SIZEBOX,
			mWindowRect, mParentHandle, NULL, App->GetInstance(), this);
	}
	
}

void Window::Show(int cmd)
{
	::ShowWindow(mHandle, cmd);
	::UpdateWindow(mHandle);
}

RECT Window::GetRect() const
{
	RECT rc;
	::GetClientRect(mHandle, &rc);
	return rc;
}

HRESULT CALLBACK Window::MainWndProc(HWND handle, UINT msg, WPARAM wp, LPARAM lp)
{
	Window* window = App->GetWindowFromHandle(handle);
	
	if (msg == WM_NCCREATE)
	{
		CREATESTRUCT* pCreate = (CREATESTRUCT*)lp;
		window = (Window*)pCreate->lpCreateParams;
		window->mHandle = handle;
		SetWindowLongPtr(handle, GWLP_USERDATA, (LONG)pCreate->lpCreateParams);
		App->SetWindowMap(handle, window);
	}
	if (msg == WM_CREATE)
	{
		window->OnCreate();
	}

	if (!window)
		return DefWindowProc(handle, msg, wp, lp);

	return window->LocalWndProc(msg, wp, lp);
}

void Window::OnCreate()
{

}

void Window::OnPaint(PaintEvent &e)
{
	auto trect = win::GetTitleRect(mHandle, 30);
	static Brush titleBrush(80, 80, 80);
	FillRect(e.dc, &trect, titleBrush);
	//if (mParent)
	//{
	//	RECT rect;
	//	HBRUSH brush = CreateSolidBrush(RGB(150,120,80));
	//	GetClientRect(mHandle, &rect);
	//	LOG << rect << ENDN;
	//	FillRect(e.dc, &rect, brush);
	//}
}

void Window::TitleEvent()
{
}

void Window::PreRegisterClassEx(WNDCLASSEX &wc)
{
	UNUSED(wc);
}

HRESULT Window::LocalWndProc(UINT msg, WPARAM wp, LPARAM lp)
{
	PaintEvent pe;
	PAINTSTRUCT ps;

	switch (msg)
	{
	case WM_PAINT:
		pe.dc = BeginPaint(mHandle, &ps);
		OnPaint(pe);
		EndPaint(mHandle, &ps);
		break;
	}

	return DefWindowProc(mHandle,msg,wp,lp);
}
