
#include <application.h>
#include <layout.h>
#include <widget.h>
//#include <vld.h>
#include <mainwindow.h>
#include <button.h>
#include <custombutton.h>


#define TAKE02
#ifdef TAKE01

int main(int args, char* argv[])
{
	HWND consoleWindow = GetConsoleWindow();
	SetWindowPos(consoleWindow, 0, 0, 0, 500, 900, SWP_NOSIZE | SWP_NOZORDER);

	Application app;
	MainWindow w(1280, 720);
	Button b1(w, ButtonType::Close);
	Button b2(w, ButtonType::Min);
	CustomButtom ct(w, 400, 0, 200, 30);

	b2.Move(w.GetSize().cx - (b1.GetSize().cx * 2), 0, b1.GetSize().cx, b1.GetSize().cy);

	b1.Show();
	b2.Show();
	w.Show();

	int exitCode = app.Run();
	return exitCode;
}



#else

#include <iostream>
#include <queue>        
//using namespace std;

HRESULT CALLBACK WndProc(HWND handle, UINT msg, WPARAM wp, LPARAM lp);

class ZWindow
{
public:
	ZWindow() {
		WNDCLASS wc{};
		wc.hInstance = App->GetInstance();
		wc.hCursor = LoadCursor(NULL, IDC_ARROW);
		wc.lpszClassName = TEXT("ww");
		wc.lpfnWndProc = WndProc;
		wc.hbrBackground = CreateSolidBrush(RGB(100, 80, 110));

		RegisterClass(&wc);

		mHandle = CreateWindow(wc.lpszClassName, TEXT(""), WS_OVERLAPPED, 400, 400, 620, 480,
			NULL, NULL, wc.hInstance, this);

	}
	~ZWindow() {
		if (mHandle) {
			DestroyWindow(mHandle);
			mHandle = NULL;
		}
	}

	void KeyEvent(WPARAM wp) {
		if (wp == VK_ESCAPE)
			PostQuitMessage(0);
	}

	HWND mHandle;
};

class GWindow
{
public:
	GWindow(HWND parent) {
		WNDCLASS wc{};
		wc.hInstance = App->GetInstance();
		wc.hCursor = LoadCursor(NULL, IDC_ARROW);
		wc.lpszClassName = TEXT("wwa");
		wc.lpfnWndProc = WndProc;
		wc.hbrBackground = CreateSolidBrush(RGB(30, 80, 120));

		RegisterClass(&wc);

		mHandle = CreateWindow(wc.lpszClassName, TEXT(""),
			WS_CHILD| WS_VISIBLE, 0, 0, 300, 280,
			parent, NULL, wc.hInstance, this);

	}
	~GWindow() {
		if (mHandle) {
			DestroyWindow(mHandle);
			mHandle = NULL;
		}
	}

	HWND mHandle;
};

HRESULT CALLBACK WndProc(HWND handle, UINT msg, WPARAM wp, LPARAM lp)
{
	ZWindow* window = (ZWindow*)GetWindowLongPtr(handle, GWLP_USERDATA);
	switch (msg)
	{
	case WM_NCCREATE:
		window = (ZWindow*)((CREATESTRUCT*)lp)->lpCreateParams;
		window->mHandle = handle;
		SetWindowLongPtr(handle, GWLP_USERDATA, (LONG_PTR)window);

		break;

	case WM_KEYDOWN:
	{
		window->KeyEvent(wp);
		break;
	}
	default:
		break;
	}
	return DefWindowProc(handle, msg, wp, lp);
}

void main()
{
	Application app;

	ZWindow window;
	GWindow gw(window.mHandle);
	ShowWindow(window.mHandle, TRUE);

	int a = app.Run();
}

#endif


