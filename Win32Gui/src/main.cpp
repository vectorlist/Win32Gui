
#include <application.h>
#include <mainwindow.h>
#include <layout.h>
#include <widget.h>
#include <CommCtrl.h>

#define TAKE01
#ifdef TAKE01

int main(int args, char* argv[])
{
	Application app;
	
	Widget widget(1024, 640);
	Layout* lay = widget.GetLayout();

	//auto bt1 = CreateWindow(WC_BUTTON, TEXT("none"),
	//	WS_CHILD | WS_VISIBLE, 0, 0, 0, 0, lay->GetHandle(), NULL, app.GetInstance(), NULL);

	//auto bt2 = CreateWindow(WC_BUTTON, TEXT("none"),
	//	WS_CHILD | WS_VISIBLE, 0, 0, 0, 0, lay->GetHandle(), NULL, app.GetInstance(), NULL);

	Widget w1(0, 0, TEXT(""), NULL);
	//Widget w2(0, 0, TEXT(""), lay->GetHandle());
	//Widget w3(0, 0, TEXT(""), lay->GetHandle());

	lay->AddWindow(w1);	
	

	int exit = app.Run();
	return exit;

	//SomeData sdata;
	//Data* data = dynamic_cast<Data*>(&sdata);
	//data->run();
	//PAUSE;
	//return 0;
}

#else

#include <CommCtrl.h>

struct MWindow
{
	HWND mHandle;
	Layout* layout = NULL;
};

HRESULT CALLBACK WndProc(HWND handle, UINT msg, WPARAM wp, LPARAM lp);

int main(int args, char* argv[])
{
	Application app;

	//MainWindow window(TEXT("main window"));
	//window.Show();
	const wchar_t* className = TEXT("main window");
	WNDCLASSEX wcex;

	wcex.cbSize = sizeof(WNDCLASSEX);

	wcex.style = CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc = WndProc;
	wcex.cbClsExtra = 0;
	wcex.cbWndExtra = 0;
	wcex.hInstance = App->GetInstance();
	wcex.hIcon = LoadIcon(NULL, IDC_ARROW);
	wcex.hCursor = LoadCursor(NULL, IDC_ARROW);
	wcex.hbrBackground = CreateSolidBrush(RGB(120,100,80));
	wcex.lpszMenuName = NULL;
	wcex.lpszClassName = className;
	wcex.hIconSm = NULL;

	RegisterClassEx(&wcex);

	HWND window = CreateWindow(className, TEXT("my"), WS_OVERLAPPEDWINDOW,
		300, 300, 720, 480, NULL, NULL, App->GetInstance(), NULL);

	/*ShowWindow(window, SW_SHOW);
	UpdateWindow(window);*/

	Layout lay;
	lay.CreateLayout(window);
	lay.SetMargin(Margin(12, 10));
	HWND bt1 = CreateWindow(WC_BUTTON, TEXT("button1"),
		WS_CHILD | WS_VISIBLE, 0, 0, 0, 0,
		window, NULL, App->GetInstance(), NULL);

	HWND bt2 = CreateWindow(WC_BUTTON, TEXT("button2"),
		WS_CHILD | WS_VISIBLE, 0, 0, 0, 0,
		window, NULL, App->GetInstance(), NULL);

	HWND bt3 = CreateWindow(WC_BUTTON, TEXT("button3"),
		WS_CHILD | WS_VISIBLE, 0, 0, 0, 0,
		window, NULL, App->GetInstance(), NULL);

	lay.SetChild(bt1);
	lay.SetChild(bt2);
	lay.SetChild(bt3);

	MWindow w;
	w.mHandle = window;
	w.layout = &lay;

	ShowWindow(window, SW_SHOW);
	UpdateWindow(window);

	int exit = app.Run();
	return exit;
}

HRESULT CALLBACK WndProc(HWND handle, UINT msg, WPARAM wp, LPARAM lp)
{
	switch (msg)
	{
	case WM_CREATE:
		LOG << "created" << ENDN;
		//SetWindowLongPtr(handle, GWLP_USERDATA, (LONG_PTR))
		break;
	case WM_KEYDOWN:
		if (wp == VK_ESCAPE)
			PostQuitMessage(0);
		break;
	case WM_CLOSE:
		PostQuitMessage(0);
		break;
	case WM_SIZE:
		LOG << "main size" << ENDN;
		Layout* lay = (Layout*)GetWindowLongPtr(handle, GWLP_USERDATA);
		if (lay) {
			LOG << "layout alive" << ENDN;

		}
		break;
	}
	
	return DefWindowProc(handle, msg, wp, lp);
}

#endif