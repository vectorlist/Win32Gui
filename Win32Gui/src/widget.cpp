#include "widget.h"
#include <application.h>

Widget::Widget(HWND parent)
	: Window(parent)
{
	Create(parent);
}

Widget::Widget(int x, int y, int w, int h, std::string title, HWND parent)
	: Window(x, y, w, h, title, parent)
{
	Create(parent);
}

Widget::~Widget()
{
}

void Widget::PreRegisterClass(WNDCLASS &wc)
{
	static Brush b(100, 130, 160);
	wc.lpszClassName = TEXT("widget++");
	wc.hbrBackground = b;
}

void Widget::PreCreate(CREATESTRUCT &cs)
{
	if (mParent) {
		cs.style = cs.style | WS_VISIBLE;
	}
}

void Widget::PrePaintEvent(Painter *painter)
{
	//UNUSED(painter);
	Window::PrePaintEvent(painter);
}

void Widget::OnCreateEvent(CREATESTRUCT & cs)
{
	//mTitlebar = new TitleBar(*this, 16);
}

void Widget::PaintEvent(Painter *painter)
{
	LOG << "Widget Paint" << ENDN;
	Rect rect = GetActiveRect();
	static Brush brush(50, 80, 100);
	painter->SetBrush(brush);
	painter->FillRect(rect);
}