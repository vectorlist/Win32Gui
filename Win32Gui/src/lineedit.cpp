#include "lineedit.h"

//LRESULT CALLBACK InputWndProc(HWND handle, UINT msg, WPARAM wp, LPARAM lp);
WNDPROC LineEdit::mOldProc = NULL;

LineEdit::LineEdit(HWND parent)
	: Window(parent)
{
	Create(parent);
}


LineEdit::~LineEdit()
{
}

void LineEdit::PreRegisterClass(WNDCLASS &wc)
{
	wc.lpszClassName = TEXT("lineeditwnd");
	//wc.lpszClassName = L"static";
	//wc.style = WS_CHILD | WS_TABSTOP | SS_LEFT | SS_NOTIFY;
	//wc.lpfnWndProc = NULL;

}

void LineEdit::OnCreateEvent(CREATESTRUCT &cs)
{
	SetWindowPos(*this, 0, 0, 0, 200, 100, 0);
	mLineEdit = CreateWindow(TEXT("static"), 0, WS_CHILD | WS_TABSTOP | SS_LEFT | SS_NOTIFY,
		0, 0, 0, 0, *this, 0, (HINSTANCE)GetWindowLongPtr(*this, GWL_HINSTANCE), 0);

	mOldProc = (WNDPROC)SetWindowLongPtr(*this, GWL_WNDPROC, (LONG_PTR)LineEdit::InputWndProc);
	SetWindowPos(mLineEdit, HWND_TOP, 0, 0, 200, 100, 0);
	ShowWindow(mLineEdit, TRUE);
	//InvalidateRect(TRUE);
}

LRESULT CALLBACK LineEdit::InputWndProc(HWND handle, UINT msg, WPARAM wp, LPARAM lp)
{

	switch (msg)
	{
	case WM_PAINT:
	{
		Painter painter(handle);
		Rect rc;
		GetClientRect(handle, &rc);
		//painter.FillRect(rc);
		return TRUE;
	}
	default:
		break;
	}
	return CallWindowProc(LineEdit::mOldProc, handle, msg, wp, lp);
}
