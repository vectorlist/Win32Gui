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

void Widget::PreCreateStruct(CREATESTRUCT &cs)
{
	if (mParent) {
		cs.style = cs.style | WS_VISIBLE;
	}
	
}

void Widget::PaintEvent(Painter *painter)
{
	LOG << "Widget Paint" << ENDN;
}