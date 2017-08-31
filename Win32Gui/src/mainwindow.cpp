#include "mainwindow.h"

MainWindow::MainWindow(Window* parent)
	: Window(parent)
{
	BuildWindow();
}

MainWindow::MainWindow(const std::wstring &name, Window* parent)
	: Window(name, parent)
{
	BuildWindow();
}

MainWindow::~MainWindow()
{
}

void MainWindow::OnCreate()
{
	LOG << "created main window" << ENDN;
	mWindow = new Window(TEXT("hello"), this);
	mWindow->SetSize(200, 200);
	mWindow->SetPosition(0, 30);
	mWindow->BuildWindow();
	//mWindow->Show();
}

//HRESULT MainWindow::LocalWndProc(UINT msg, WPARAM wp, LPARAM lp)
//{
//	//LOG << "shit" << ENDN;
//	switch (msg)
//	{
//	case WM_SIZE:
//		//LOG << "create" << ENDN;
//		//OnCreate();
//		//break;
//	case WM_KEYDOWN:
//	{
//		if (wp == VK_ESCAPE)
//			PostQuitMessage(0);
//		break;
//	}
//	}
//	return DefWindowProc(mHandle, msg, wp, lp);
//	
//}

void MainWindow::PreRegisterClassEx(WNDCLASSEX & wc)
{

}
