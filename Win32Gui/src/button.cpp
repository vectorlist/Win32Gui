#include <button.h>
#include <application.h>
#include <painter.h>

Button::Button(HWND parent, ButtonType type, int fixedSize)
	: Window(parent), mType(type), mFixedSize(fixedSize)
{
	Create(parent);
}

Button::~Button()
{
}

void Button::PreRegisterClass(WNDCLASS &wc)
{
	//set unique class name for button
	wc.lpszClassName = TEXT("ButtonClass");
}

void Button::PreCreate(CREATESTRUCT &cs)
{
	//set style and hMenu
	DWORD style = WS_CHILD | WS_VISIBLE | BS_OWNERDRAW;		//item for own draw
	cs.style = style;
	cs.hMenu = (HMENU)BT_CLOSE;
	cs.lpCreateParams = this;

	//check parent window has titlebar
	Window* parentWnd = App->GetWindowFromMap(mParent);			//this is not safe
	auto* titleBar = parentWnd->GetTitleBar();
	int fixedSize = titleBar->GetSize();		//get titlebar height
	cs.x = parentWnd->Width() - fixedSize;
	cs.y = 0;
	cs.cx = fixedSize;
	cs.cy = fixedSize;
}

void Button::PaintEvent(Painter *painter)
{
	//background
	static Brush brush(COLOR_TITLEBAR);
	static Brush onBrush(COLOR_TITLEBAR_HL);
	if (mOnEnter)
		painter->SetBrush(onBrush);
	else
		painter->SetBrush(brush);

	painter->FillRect(GetRect());

	//pen is not init here
	switch (mType)
	{
	case ButtonType::None:
		break;
	case ButtonType::Min:
		DrawMin(painter);
		break;
	case ButtonType::Max:
		DrawMax(painter);
		break;
	case ButtonType::Close:
		DrawClose(painter);
		break;
	case ButtonType::User:
		DrawUser(painter);
		//user can be derived class
		break;
	}
}

void Button::MousePressEvent(MouseEvent &event)
{
	//send message by type
	switch (mType)
	{
	case ButtonType::Min:
		break;
	case ButtonType::Max:
		break;
	case ButtonType::Close:
	{
		//direct to post message to dispatch message loop
		PostQuitMessage(0);
		break;
	}
	case ButtonType::User:
		break;
	}
}

void Button::MouseMoveEvent(MouseEvent &event)
{

	//LOG << event.GetPos() << ENDN;
}

void Button::MouseEnterEvent(MouseEvent &event)
{
	InvalidateRect();
}

void Button::MouseLeaveEvent(MouseEvent & event)
{
	InvalidateRect();
}

void Button::DrawUser(Painter *painter)
{
	UNUSED(painter);	//nothing for now
}

void Button::DrawMin(Painter *painter)
{
	int space = 9;
	//test
	static Pen pen(PS_SOLID, 2, Color(200, 200, 200));
	painter->SetPen(pen);

	Poly p;
	int width = GetSize().cx;
	int height = GetSize().cy;

	p << Point(space, height - space) << Point(width - space, height - space);

	painter->DrawPolygon(p);
}

void Button::DrawMax(Painter *painter)
{
	//TODO MAX
}

void Button::DrawClose(Painter *painter)
{
	int space = 10;

	static Pen pen(PS_GEOMETRIC, 2, Color(200, 200, 200));
	painter->SetPen(pen);

	Point a(space , space);
	Point b(Width() - space, Width() - space);

	Point c(space, Height() - space);
	Point d(Width() - space, space);

	painter->DrawLine(a, b);
	painter->DrawLine(c, d);

	//GGraphics g(painter->dc);
	////GBrush b(GColor(255, 200, 200, 200));
	//GPen gp(GColor(220,220,220), 2);
	////g.SetSmoothingMode(Gdiplus::SmoothingModeAntiAlias);
	//g.SetSmoothingMode(Gdiplus::SmoothingModeAntiAlias);
	//g.DrawLine(&gp, space, space, Width() - space, Width() - space);
	//GPoint p2(space, Height() - space);
	//GPoint p3(Width() - space, space);
	//g.DrawLine(&gp, p2, p3);
}


