#include "widget.h"
#include <application.h>

const wchar_t* widgetClassName = TEXT("WidgetClassName");
const wchar_t* widgetClassSubName = TEXT("WidgetClassSubName");
Brush widgetBrush(100, 100, 100);
Brush widgetSubBrush(30, 30, 30);

Widget::Widget(int width, int height, const std::wstring &title, HWND parent)
	: WinObject(parent), mWidth(width), mHeight(height)
{
	
	CreateClass(parent);
	CreateWidget(parent);

	mLayout = std::make_unique<HLayout>(*this);
}

Widget::~Widget()
{
}

void Widget::Update()
{
	mLayout->Update();
	//this->PaintEvent();
}

void Widget::CreateClass(HWND parent)
{
	WNDCLASSEX wcx{};
	wcx.cbSize			= sizeof(wcx);
	wcx.hCursor			= LoadCursor(NULL, IDC_ARROW);
	wcx.hIcon			= NULL;
	wcx.hInstance		= App->GetInstance();
	wcx.lpfnWndProc		= Widget::GlobalWndProc;
	wcx.style			= CS_HREDRAW | CS_VREDRAW;

	if (parent) {
		wcx.hbrBackground = widgetSubBrush;
		wcx.lpszClassName = widgetClassSubName;
	}
	else {
		wcx.hbrBackground = widgetBrush;
		wcx.lpszClassName = widgetClassName;
	}
	if (GetClassInfoEx(App->GetInstance(), widgetClassName, &wcx) ||
		GetClassInfoEx(App->GetInstance(), widgetClassSubName, &wcx)) 
	{
		return;
	}
	
	if (!RegisterClassEx(&wcx))
		LOG_FATAL("failed to register widget class");
}

void Widget::CreateWidget(HWND parent)
{
	HWND handle = GetHandle();
	if (parent) {
		handle = CreateWindowEx(NULL, widgetClassName, TEXT("sub widget"),
			WS_CHILD | WS_VISIBLE, 0, 0, 0, 0, parent, NULL, App->GetInstance(), this);
	}
	else {
		handle = CreateWindowEx(NULL, widgetClassName, mTitle,
			WS_OVERLAPPED | WS_THICKFRAME | WS_VISIBLE, CENTER_X(mWidth), CENTER_Y(mHeight), mWidth, mHeight,
			NULL, NULL, App->GetInstance(), this);
	}
}

void Widget::SetBackgroundBrush()
{

}

void Widget::Show(int cmd)
{
	ShowWindow(*this, cmd);
	SendMessage(*this, WM_SIZE, NULL, NULL);
}


LRESULT CALLBACK Widget::GlobalWndProc(HWND handle, UINT msg, WPARAM wp, LPARAM lp)
{
	Widget* widget = (Widget*)GetWindowLongPtr(handle, GWLP_USERDATA);

	switch (msg)
	{
	case WM_NCCREATE:
	{
		CREATESTRUCT* crs = (CREATESTRUCT*)lp;
		widget = (Widget*)crs->lpCreateParams;
		widget->SetHandle(handle);
		SetWindowLongPtr(handle, GWLP_USERDATA, (LONG_PTR)widget);
	}
	case WM_CREATE:
		
		break;
	case WM_PAINT:
	{
		break;
	}
	case WM_SIZE:
		//Widget* widget = (Widget*)GetWindowLongPtr(handle, GWLP_USERDATA);
		if (widget && widget->GetLayout()) {
			LOG << "widget update" << ENDN;
			widget->Update();
		}
	case WM_NCHITTEST:
	{
		/*LOG << "widget hit" << ENDN;*/
		Point p;
		Rect rect;
		GetCursorPos(&p);
		GetClientRect(*widget, &rect);

		widget->mOnHoover = win::IsPointOnRect(p, rect);
		LOG << widget->mOnHoover << " " <<rect << ENDN;
		widget->PaintEvent();
		//break;
	}
	}
	
	return DefWindowProc(handle, msg, wp, lp);
}

void Widget::PaintEvent()
{
	PAINTSTRUCT ps;
	HDC dc = BeginPaint(*this, &ps);
	RECT rect;

	GetClientRect(*this, &rect);
	static Brush inB(120, 100, 90);
	static Brush outB(70, 50, 30);
	FillRect(dc, &rect, mOnHoover ? inB : outB);
}
