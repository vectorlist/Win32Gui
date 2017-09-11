#include "mainwindow.h"
#include <layout.h>

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
	SAFE_DELETE(mLayout);
}

void MainWindow::PreRegisterClass(WNDCLASS &wc)
{
	
}

void MainWindow::PreCreate(CREATESTRUCT &cs)
{
	cs.style = WS_POPUP;
}

void MainWindow::OnCreateEvent(CREATESTRUCT &cs)
{
	mResizer = new Resizer;
	mTitlebar = new TitleBar(*this);
	
	mLayout = new HBoxLayout;
	mLayout->Attach(this);
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
	if (wp == VK_ESCAPE) {
		LOG << "send close event" << ENDN;
		SendMessage(mHandle, WM_CLOSE, NULL, NULL);
	}
}

void MainWindow::ResizeEevnt(UINT msg, WPARAM wp, LPARAM lp)
{
	if (mLayout) {
		Rect layoutRect = GetActiveRect();
		layoutRect = layoutRect - mLayout->GetMargin();
		mLayout->Move(layoutRect);
		mLayout->UpdateLayout();
	}
}

HRESULT MainWindow::HitEvent(UINT msg, WPARAM wp, LPARAM lp)
{
	//HTCLIENT is on window
	HRESULT result = HTCLIENT;
	if (mResizer) {
		result = mResizer->HitEvent(this, lp);
	}
	if (mTitlebar) {
		mTitlebar->HitEvent(lp);
	}
	return result;
}

void MainWindow::Update()
{
	//LOG << GetWindowName() <<" update" << ENDN;
	
	//TODO : resize -> call WM_SIZE(mainwindow) -> resizeEvent -> move(layout)
	//-> call WM_SIZE(layout)

	//if (mLayout) {
	//	mLayout->UpdateLayout();
	//}
}

