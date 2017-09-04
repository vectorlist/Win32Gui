#include <window.h>
#include <application.h>

Window::Window(HWND parent)
	: WinObject(parent)
{
	SetWindowName("none");
	//Create(parent);
}

Window::Window(int x, int y, int w, int h, std::string title, HWND parent)
	: WinObject(parent)
{
	SetWindowName(title);
	SetX(x); SetY(y); SetWidth(w), SetHeight(h);
	//Create(parent);
}


Window::~Window()
{
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

	PreRegisterClass(wc);

	if (GetClassInfo(App->GetInstance(), wc.lpszClassName, &wc)) {
		LOG << "has already" << ENDN;
	}
	else {
		if (!RegisterClass(&wc))
			LOG_FATAL("failed to register window class");
	}

	CREATESTRUCT cs{};
	DWORD singleStyle = WS_OVERLAPPED | WS_THICKFRAME | WS_VISIBLE;
	DWORD childStyle = WS_CHILD | WS_VISIBLE;
	cs.style = parent ? childStyle : singleStyle;

	cs.x = GetX();
	cs.y = GetY();
	cs.cx = GetWidth();
	cs.cy = GetHeight();

	cs.lpCreateParams = this;

	cs.style &= ~WS_VISIBLE;
	PreCreateStruct(cs);
	mHandle = CreateWindowEx(NULL,
		wc.lpszClassName, GetWideWindowName().c_str(), cs.style,
		cs.x, cs.y, cs.cx, cs.cy, parent, NULL, App->GetInstance(), cs.lpCreateParams);
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
void Window::PreCreateStruct(CREATESTRUCT &cs)
{
	UNUSED(cs);
}

void Window::InitializeEvent(CREATESTRUCT &cs)
{
	UNUSED(cs);
}

void Window::PaintEvent(Painter* painter)
{
	UNUSED(painter);
}

void Window::ResizeEevnt(UINT msg, WPARAM wp, LPARAM lp)
{
	LOG << "resize" << ENDN;
}

void Window::KeyPressEvent(WPARAM wp)
{
	if (wp == VK_ESCAPE) {
		PostQuitMessage(0);
	}
}

LRESULT Window::HitEvent(UINT msg, WPARAM wp, LPARAM lp)
{
	return LNULL;
}

LRESULT Window::LocalWndProc(UINT msg, WPARAM wp, LPARAM lp)
{
	Painter painter;
	
	switch (msg)
	{
	case WM_CREATE:		InitializeEvent(*(CREATESTRUCT*)lp); break;
	case WM_SIZE:		ResizeEevnt(msg, wp, lp); break;
	case WM_PAINT: 
	{
		painter.Begin(*this);
		PaintEvent(&painter); 
		painter.End(*this);
		break;
	}
	//case WM_MOUSEMOVE:	return HitEvent(msg, wp, lp);
	case WM_NCHITTEST:	return HitEvent(msg, wp, lp);
	case WM_KEYDOWN:	KeyPressEvent(wp); break;
	}
	return DefWindowProc(*this, msg, wp, lp);
}

LRESULT Window::GlobalWndProc(HWND handle, UINT msg, WPARAM wp, LPARAM lp)
{
	Window* window = (Window*)GetWindowLongPtr(handle, GWL_USERDATA);
	
	if (WM_NCCREATE == msg)
	{
		window = (Window*)((CREATESTRUCT*)lp)->lpCreateParams;
		window->mHandle = handle;
		SetWindowLongPtr(handle, GWL_USERDATA, (LONG_PTR)window);
	}
	
	if (window) {
		return window->LocalWndProc(msg, wp, lp);
	}
	return DefWindowProc(handle, msg, wp, lp);
}



MainWindow::MainWindow(HWND parent)
	: Window(parent)
{
	Create(parent);
}

MainWindow::MainWindow(int x, int y, int w, int h, std::string title, HWND parent)
	: Window(x, y, w, h, title, parent)
{
	Create(parent);
}

MainWindow::~MainWindow()
{
}

void MainWindow::PreRegisterClass(WNDCLASS &wc)
{

}

void MainWindow::PreCreateStruct(CREATESTRUCT &cs)
{
	cs.style = WS_POPUP;
}



void MainWindow::PaintEvent(Painter * painter)
{
	auto rect = GetRect();
	static Brush b(45, 45, 45);
	painter->SetBrush(b);
	painter->FillRect(rect);

	if (mTitlebar.GetActive()) {
		mTitlebar.PaintEvent(*this, painter);
	}

	painter->SetTextColor(RGB(200, 200, 200));
	painter->SetTextBgColor(painter->brush->GetColor());
	painter->Text(10, 10, TEXT("Hellow"));
}

HRESULT MainWindow::HitEvent(UINT msg, WPARAM wp, LPARAM lp)
{
	HRESULT result = LNULL;
	if (mResizer.GetActive()) {
		result = mResizer.HitEvent(this, lp);
	}
	if (mTitlebar.GetActive()) {
		mTitlebar.HitEvent(this, lp);
	}
	return result;
}


