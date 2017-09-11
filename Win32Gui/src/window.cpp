#include <window.h>
#include <application.h>

Window::Window(HWND parent)
	: WinObject(parent), mTitlebar(NULL), mResizer(NULL)
{
	SetWindowName("none");
}

Window::Window(const std::string &title, HWND parent)
	: WinObject(parent), mTitlebar(NULL), mResizer(NULL)
{
	SetWindowName(title);
}

Window::Window(int x, int y, int w, int h, std::string title, HWND parent)
	: WinObject(parent), mTitlebar(NULL), mResizer(NULL)
{
	SetWindowName(title);
	mSizeInfo = CreateSizeInfo(x,y,w,h);
}


Window::~Window()
{
	SAFE_DELETE(mTitlebar);
	SAFE_DELETE(mResizer);
}

void Window::Create(HWND parent)
{
	if (!App) LOG_FATAL("application is not running");

	WNDCLASS wc{};
	static Brush b(100, 100, 100);
	wc.hInstance = App->GetInstance();
	wc.hbrBackground = b;
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);
	wc.lpfnWndProc = Window::GlobalWndProc;
	wc.lpszClassName = TEXT("win32++");
	wc.style = CS_HREDRAW | CS_VREDRAW;
	wc.lpszMenuName = NULL;

	//changeable by derived class
	PreRegisterClass(wc);

	if (!GetClassInfo(App->GetInstance(), wc.lpszClassName, &wc))
	{
		if (!RegisterClass(&wc))
			LOG_FATAL("failed to register window class");
	}

	CREATESTRUCT cs{};
	DWORD singleStyle = WS_OVERLAPPED | WS_THICKFRAME | WS_VISIBLE;
	DWORD childStyle = WS_CHILD | WS_VISIBLE;
	cs.style = parent ? childStyle : singleStyle;

	cs.x = mSizeInfo.x;
	cs.y = mSizeInfo.y;
	cs.cx = mSizeInfo.w;
	cs.cy = mSizeInfo.h;

	cs.lpCreateParams = this;

	cs.style &= ~WS_VISIBLE;
	cs.hMenu = NULL;
	

	//changeable by derived class
	PreCreate(cs);

	mHandle = CreateWindowEx(NULL,
		wc.lpszClassName, GetWideWindowName().c_str(), cs.style,
		cs.x, cs.y, cs.cx, cs.cy, parent, cs.hMenu, App->GetInstance(), cs.lpCreateParams);
	if (!mHandle) {
		LOG_FATAL("failed to create window");
	}
}

Window* Window::GetParentWindow()
{
	return App->GetWindowFromMap(mParent);
}

Rect Window::GetActiveRect() const
{
	Rect rect = GetRect();
	if (mTitlebar && mTitlebar->IsActive()) {
		rect.top = rect.top + mTitlebar->GetSize();
	}
	return rect;
}

/*
* fixable register class by derived class
* cursor, class name, background, wndproc ..etc
*/
void Window::PreRegisterClass(WNDCLASS &wc)
{
	UNUSED(wc);
}
/*
* fixable create struct by derived class
* cs.x....cs.cy, cs.style
*/
void Window::PreCreate(CREATESTRUCT &cs)
{
	UNUSED(cs);
}

/*
* in order to paint background ..etc
*/
void Window::PrePaintEvent(Painter* painter)
{
	//Built in Pre Paint
	Rect rect = GetRect();
	Brush b(45, 45, 45);

	painter->SetBrush(b);
	painter->FillRect(rect);

	if (mTitlebar) {
		mTitlebar->Paint(painter);
	}
}

void Window::OnCreateEvent(CREATESTRUCT &cs)
{
	UNUSED(cs);
}

void Window::PaintEvent(Painter* painter)
{
	UNUSED(painter);
}

void Window::ResizeEevnt(UINT msg, WPARAM wp, LPARAM lp)
{
	//LOG << "resize" << ENDN;
}

void Window::KeyPressedEvent(WPARAM wp)
{
	UNUSED(wp);
}

void Window::MouseMoveEvent(MouseEvent &event)
{
	UNUSED(event);
}

void Window::MousePressEvent(MouseEvent &event)
{
	UNUSED(event);
}

void Window::MouseEnterEvent(MouseEvent &event)
{
	UNUSED(event);
}

void Window::MouseLeaveEvent(MouseEvent &event)
{
	UNUSED(event);
}

/*specific update window (for reclac child rect ..etc)*/
void Window::Update()
{
}


LRESULT Window::HitEvent(UINT msg, WPARAM wp, LPARAM lp)
{
	return HTCLIENT;
}

LRESULT Window::LocalWndProc(UINT msg, WPARAM wp, LPARAM lp)
{
	//local event
	Painter painter;
	MouseEvent me{msg, wp, lp};

	switch (msg)
	{
	case WM_CREATE:		OnCreateEvent(*(CREATESTRUCT*)lp); break;
	case WM_SIZE:
		ResizeEevnt(msg, wp, lp);
		//Update();
		break;
	case WM_PAINT: 
	{
		painter.Begin(*this);
		PrePaintEvent(&painter);
		PaintEvent(&painter); 
		painter.End(*this);
		break;
	}
	//case WM_MOUSEMOVE:	return HitEvent(msg, wp, lp);
	case WM_SETFOCUS:
		LOG << "focus on  : " << GetWindowName() << ENDN;
		break;
	case WM_KILLFOCUS:
		LOG << "focus off : " << GetWindowName()<< ENDN;
		break;
	case WM_ACTIVATE:
		LOG << "active    : " << GetWindowName() << ENDN;
		break;
	case WM_MOUSEMOVE:
	{
		MouseMoveEvent(me);
		break;
	}
	case WM_LBUTTONDOWN:
	{
		MousePressEvent(me);
		break;
	}
	case WM_NCCALCSIZE:
		//LOG << "cal " << GetWindowName() <<ENDN;
		break;
	case WM_NCHITTEST:	return HitEvent(msg, wp, lp);

	case WM_KEYDOWN:	KeyPressedEvent(wp); break;
	case WM_USER_PREPAREDESTROY:
		LOG << "working user message" << ENDN;
		break;
	}

	return DefWindowProc(*this, msg, wp, lp);
}

LRESULT Window::GlobalWndProc(HWND handle, UINT msg, WPARAM wp, LPARAM lp)
{
	//all created HWND will map to Application
	Window* window = (Window*)GetWindowLongPtr(handle, GWL_USERDATA);
	
	if (WM_NCCREATE == msg)
	{
		window = (Window*)((CREATESTRUCT*)lp)->lpCreateParams;
		window->mHandle = handle;
		SetWindowLongPtr(handle, GWL_USERDATA, (LONG_PTR)window);
		//insert HWND and Window to map
		App->SetWindowMap(handle, window);
	}
	
	if (window) {
		return window->LocalWndProc(msg, wp, lp);
	}
	return DefWindowProc(handle, msg, wp, lp);
}


