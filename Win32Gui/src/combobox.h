#pragma once

#include <window.h>

class ComboBox : public Window
{
public:
	ComboBox(HWND parent = NULL);
	~ComboBox();


	void MakeFlatCombo();
protected:
	virtual void PreRegisterClass(WNDCLASS &wc);
	virtual void PreCreate(CREATESTRUCT& cs);

	virtual void OnCreateEvent(CREATESTRUCT &cs);

	

	LRESULT CALLBACK FlatComboProc(HWND handle, UINT msg, WPARAM wp, LPARAM lp);
	virtual LRESULT CALLBACK LocalWndProc(UINT msg, WPARAM wp, LPARAM lp);
};

