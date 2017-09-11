#include "mainwindow.h"

MainWindow::MainWindow(int w, int h, std::string title, HWND parent)
	: Window(CENTER_X(w), CENTER_Y(h), w, h, title, parent)
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

void MainWindow::PreCreate(CREATESTRUCT &cs)
{
	cs.style = WS_POPUP;
	//cs.style = WS_OVERLAPPED;

	//Test Button window

}

void MainWindow::OnCreateEvent(CREATESTRUCT &cs)
{
	mResizer = new Resizer;
	mTitlebar = new TitleBar(*this);
}

void MainWindow::PaintEvent(Painter *painter)
{
	painter->SetTextColor(RGB(200, 200, 200));
	painter->SetTextBgColor(painter->GetBrush().GetColor());
	painter->Text(10, 10, TEXT("Hellow"));
	
	LOG << "main window paint" << ENDN;
}

void MainWindow::KeyPressedEvent(WPARAM wp)
{
	if (wp == 'A') {
		LOG << "a " << GetWindowName() << ENDN;
		Rect rect = GetRect();

	}
	Window::KeyPressedEvent(wp);
}

HRESULT MainWindow::HitEvent(UINT msg, WPARAM wp, LPARAM lp)
{
	HRESULT result = HTNOWHERE;
	if (mResizer) {
		result = mResizer->HitEvent(this, lp);
	}
	if (mTitlebar) {
		mTitlebar->HitEvent(lp);
	}
	return result;
}

