#include "listbox.h"
#include <application.h>
#include <gdiobj.h>

ListBox::ListBox(int x, int y, int w, int h, HWND parent)
	: Window(x, y, w, h, "listbox", parent), mItemHeight(LISTBOX_FIXEDSIZE)
{
	Create(parent);
}

ListBox::ListBox(HWND parent)
	: Window(parent), mItemHeight(LISTBOX_FIXEDSIZE)
{
	SetWindowName("listbox");
	Create(parent);
}

ListBox::~ListBox()
{
	SAFE_DELETE_WND(mListHandle);
}

void ListBox::PreRegisterClass(WNDCLASS &wc)
{
	wc.lpszClassName = TEXT("ListBoxClassA");
	wc.hbrBackground = CreateSolidBrush(COLOR_LISTBOX_DESELECT);
}

void ListBox::PreCreate(CREATESTRUCT &cs)
{
	cs.style = WS_OVERLAPPEDWINDOW | WS_VISIBLE;
}

void ListBox::OnCreateEvent(CREATESTRUCT &cs)
{
	//LOG << "on create" << ENDN;
	//Move(300, 300, 800, 80);
	//LOG << GetRect() << ENDN;

	auto lpszClass = TEXT("listbox");
	auto style = WS_CHILD | WS_VISIBLE | WS_VSCROLL | LBS_NOTIFY 
		| LBS_OWNERDRAWFIXED | WS_BORDER;
	//style &= ~WS_BORDER;
	auto menu = (HMENU)ID_LISTBOX;

	auto r = GetRect();

	mListHandle = CreateWindowEx(NULL, lpszClass, TEXT(""), style,
		0, 0, 0, 0, *this, menu, App->GetInstance(), NULL);

	std::vector<char*> buffers= {
		"One", "Two" , "Three", "Four", "Five"
	};

	for (int i = 0; i < buffers.size(); ++i)
	{
		SendMessageA(mListHandle, LB_ADDSTRING, 0, (LPARAM)buffers[i]);
	}
}

void ListBox::PaintEvent(Painter * painter)
{
	LOG << "p" << ENDN;
	//Rect rc = GetRect();
	//win::PaintRect(painter->dc, &rc, COLOR_LISTBOX_SELECT);
}

void ListBox::AddItem(char *item)
{
	SendMessageA(mListHandle, LB_ADDSTRING, 0, *item);
}

HRESULT CALLBACK ListBox::LocalWndProc(UINT msg, WPARAM wp, LPARAM lp)
{
	LPMEASUREITEMSTRUCT is;
	LPDRAWITEMSTRUCT dis;
	switch (msg)
	{
	case WM_CREATE: OnCreateEvent(*(CREATESTRUCT*)&lp); break;
	case WM_MEASUREITEM:
		LOG << "mesure" << ENDN;
		is = (LPMEASUREITEMSTRUCT)lp;
		is->itemHeight = mItemHeight;
		return TRUE;

	case WM_DRAWITEM:
	{
		LOG << "draw item" << ENDN;
		dis = (LPDRAWITEMSTRUCT)lp;

		
		Color textColor = COLOR_LISTBOX_TEXT;
		Color textBgColor = COLOR_LISTBOX_DESELECT;
		if (dis->itemState & ODS_SELECTED) {
			textColor = COLOR_LISTBOX_SELTEXT;
			textBgColor = COLOR_LISTBOX_SELECT;
		}

		::SetTextColor(dis->hDC, textColor);
		win::PaintRect(dis->hDC, &dis->rcItem, textBgColor);
		::SetBkColor(dis->hDC, textBgColor);
		static const Font f(TEXT("Segoi UI"), 14);
		static HFONT ff = CreateFont(17, 0, 0, 0, 450, 0, 0, 0, 0, 0, 0, 0, 0,
			TEXT("Segoi UI"));
		::SelectObject(dis->hDC, ff);
	
		auto code = (char*)SendMessageA(dis->hwndItem, LB_GETITEMDATA, dis->itemID, 0);

		DrawTextA(dis->hDC, code, -1, &dis->rcItem, DT_VCENTER | DT_LEFT | DT_SINGLELINE);

		switch (dis->itemState)
		{
		case ODS_SELECTED:
		{
			LOG << "seletct" << ENDN;
			auto s = dis->itemData;
			break;
		}
		case ODS_NOFOCUSRECT:
			LOG << dis->itemID << " active" << ENDN;
			break;
		}

		return TRUE;
	}
	case WM_COMMAND:
	{
		CommandEvent(wp, lp);
		break;
	}
	case WM_SIZE:
	{
		if (!mListHandle) return TRUE;
		Rect rect = GetRect();
		int itemCount = SendMessage(mListHandle, LB_GETCOUNT, 0, 0);
		int itemsHeight = mItemHeight * (itemCount + 1);
		int listBoxHeight = itemsHeight >= rect.Height() ? rect.Height() : itemsHeight;
		MoveWindow(mListHandle, rect.left, rect.top, rect.Width(), listBoxHeight, TRUE);

	}
	case WM_PAINT:
		LOG << "paint" << ENDN;
		Painter p(*this);
		PaintEvent(&p);
		break;

	}
	return DefWindowProc(*this, msg, wp, lp);
}

void ListBox::CommandEvent(WPARAM wp, LPARAM lp)
{
	switch (LOWORD(wp))
	{
	case ID_LISTBOX:
	{
		switch (HIWORD(wp))
		{
		case LBN_SELCHANGE:
		{
			int index = SendMessage(mListHandle, LB_GETCURSEL, 0, 0);
			LOG << index << ENDN;
			break;
		}
		
		}
		break;
	}
	}
}