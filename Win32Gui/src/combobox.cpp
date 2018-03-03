#include "combobox.h"



ComboBox::ComboBox(HWND parent)
	: Window(parent)
{
	SetWindowName("combobox");
}

ComboBox::~ComboBox()
{
}

void ComboBox::MakeFlatCombo()
{
	LONG oldComboProc;
	//oldComboProc = GetWindowLong(*this, )
}

void ComboBox::PreRegisterClass(WNDCLASS & wc)
{
	wc.lpszClassName = TEXT("ComboWnd");
}

void ComboBox::PreCreate(CREATESTRUCT &cs)
{
}

void ComboBox::OnCreateEvent(CREATESTRUCT &cs)
{
	//Make
}

LRESULT ComboBox::FlatComboProc(HWND handle, UINT msg, WPARAM wp, LPARAM lp)
{

	return LRESULT();
}

LRESULT ComboBox::LocalWndProc(UINT msg, WPARAM wp, LPARAM lp)
{

	return LRESULT();
}
