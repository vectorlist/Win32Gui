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
	cs.dwExStyle = style;
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
	static Brush brush(100, 100, 100);
	static Brush onBrush(130, 130, 130);
	if (OnEnter)
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
		//not safe if it is not main
		//'Window* mainWindow = App->GetWindowFromMap(mParent);

		SendMessage(*this, WM_CLOSE, NULL, NULL);
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
	if (!OnEnter) {
		OnEnter = true;
		LOG << "enter" << ENDN;
		InvalidateRect();
	}
}

void Button::MouseLeaveEvent(MouseEvent & event)
{
	if (OnEnter) {
		OnEnter = false;
		LOG << "leave" << ENDN;
		InvalidateRect();
	}
}

/*
* override local wnd proc for button window
*/
HRESULT CALLBACK Button::LocalWndProc(UINT msg, WPARAM wp, LPARAM lp)
{
	Painter painter;
	//MouseEvent me(msg, wp, lp);
	MouseEvent me{ msg, wp, lp };
	switch (msg)
	{
	case WM_PAINT:
		painter.Begin(*this);
		PaintEvent(&painter);
		painter.End(*this);
		LOG << "button paint" << ENDN;
		break;

	case WM_MOUSEHOVER: this->MouseEnterEvent(me); break;
	case WM_MOUSELEAVE: this->MouseLeaveEvent(me); break;
	case WM_LBUTTONDOWN:
		this->MousePressEvent(me);
		break;

	case WM_COMMAND:
		LOG << "working" << ENDN;
		break;

	case WM_DRAWITEM:
		//TODO : paint item by menu name
		LOG << "draw item enable" << ENDN;
		break;
	case WM_SIZE:
		LOG << "button size" << ENDN;
		break;
	case WM_MOUSEMOVE:
		if (GetTrackMouseEnable()) {
			TRACKMOUSEEVENT tm{};
			tm.cbSize = sizeof(tm);
			tm.dwFlags = TME_HOVER | TME_LEAVE;
			tm.dwHoverTime = 1;				//interval millisecond less num more smooth
			tm.hwndTrack = *this;
			//call track mouse event
			TrackMouseEvent(&tm);
		}
		this->MouseMoveEvent(me);
		break;
	case WM_DESTROY:
		//DestroyEvent(Coustom Event)
		break;
	}
	//replace to static wndproc
	return DefWindowProc(*this, msg, wp, lp);
}

void Button::DrawUser(Painter *painter)
{
	UNUSED(painter);	//nothing for now
}

void Button::DrawMin(Painter *painter)
{
	int space = 9;
	//test
	Pen pen(PS_SOLID, 2, Color(200, 200, 200));
	painter->SetPen(pen);

	Poly p;
	int width = GetSize().cx;
	int height = GetSize().cy;

	p << Point(space, height - space) << Point(width - space, height - space);

	painter->PaintPolygon(p);
}

void Button::DrawMax(Painter * painter)
{
	//TODO MAX
}

void Button::DrawClose(Painter * painter)
{
	int space = 10;

	Pen pen(PS_GEOMETRIC, 2, Color(200, 200, 200));
	painter->SetPen(pen);

	Point a(space , space);
	Point b(Width() - space, Width() - space);

	Point c(space, Height() - space);
	Point d(Width() - space, space);

	painter->PaintLine(a, b);
	painter->PaintLine(c, d);
}


