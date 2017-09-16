#include "widget.h"
#include <application.h>

Widget::Widget(HWND parent)
	: Window(parent)
{
	Create(parent);
}

Widget::Widget(const std::string &title, HWND parent)
	: Window(title, parent)
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
	if (mParent)
		cs.style = cs.style | WS_VISIBLE;
	else
		cs.style = WS_POPUP;
}

void Widget::PrePaintEvent(Painter *painter)
{
	//UNUSED(painter);
	//Window::PrePaintEvent(painter);
	//LOG << "HBox layout paint" << ENDN;
}

void Widget::OnCreateEvent(CREATESTRUCT & cs)
{
	mTitlebar = new TitleBar(*this);
	mTitlebar->SetActive(false);
	//mResizer = new Resizer();

}

void Widget::PaintEvent(Painter *painter)
{
	LOG << GetWindowName() << " paint" << ENDN;
	Rect rect = GetActiveRect();
	painter->SetBrush(GetBrush());
	painter->FillRect(rect);
	painter->SetFont(FONT_SYSTEM);
	painter->FillText(0, 0, GetWindowName());
}

void Widget::MouseMoveEvent(MouseEvent &event)
{
	//LOG << event.GetPos() << " " << GetWindowName() << ENDN;
}

void Widget::MousePressEvent(MouseEvent &event)
{
	//LOG << pos << ENDN;
}

void Widget::MouseEnterEvent(MouseEvent & event)
{
	LOG << GetWindowName() << " entered" << ENDN;
}

