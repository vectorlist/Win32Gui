#pragma once

#include <window.h>

class LineEdit : public Window
{
public:
	LineEdit(HWND parent = NULL);
	virtual~LineEdit();


	static WNDPROC mOldProc;
	static LRESULT CALLBACK InputWndProc(HWND handle, UINT msg, WPARAM wp, LPARAM lp);
protected:
	virtual void PreRegisterClass(WNDCLASS &wc);
	virtual void OnCreateEvent(CREATESTRUCT &cs);

	HWND mLineEdit;
	//LRESULT CALLBACK InputWndProc(HWND handle, UINT msg, WPARAM wp, LPARAM lp);

private:

};

