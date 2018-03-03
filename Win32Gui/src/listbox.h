#pragma once

#include <window.h>

#define ID_LISTBOX			1000

class ListItem
{
public:
	void* mData;
};

#define LISTBOX_FIXEDSIZE		24

class ListBox : public Window
{
public:
	ListBox(int x, int y, int w, int h, HWND parent = NULL);
	ListBox(HWND parent = NULL);
	virtual~ListBox();

protected:
	virtual void PreRegisterClass(WNDCLASS &wc) override;
	virtual void PreCreate(CREATESTRUCT &cs);

	virtual void OnCreateEvent(CREATESTRUCT &cs);
	virtual void PaintEvent(Painter *painter);

	//ListBox Method
	virtual void AddItem(char *item);
	virtual void CommandEvent(WPARAM wp, LPARAM lp);

	virtual HRESULT CALLBACK LocalWndProc(UINT msg, WPARAM wp, LPARAM lp);

	HWND				mListHandle;
	int					mItemHeight;
};

