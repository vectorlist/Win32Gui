
#include <application.h>
#include <layout.h>
#include <widget.h>
//#include <vld.h>
#include <mainwindow.h>
#include <button.h>
#include <custombutton.h>

#define MAINWINDOW	0
#define LISTBOX		1
#define COMBOBOX	2
#define OWNERDRAW	3
#define CONTROL		4
#define LISTBOX2	5

#define TAKE MAINWINDOW
#if (TAKE == MAINWINDOW)

int main(int args, char* argv[])
{
	HWND consoleWindow = GetConsoleWindow();
	SetWindowPos(consoleWindow, 0, 0, 0, 500, 900, SWP_NOSIZE | SWP_NOZORDER);

	Application app;
	MainWindow w(1280, 720);
	Button b1(w, ButtonType::Close);
	Button b2(w, ButtonType::Min);
	//CustomButtom ct(w, 400, 0, 200, 30);

	Widget item1(100, 100, 200, 200, "left widget");
	item1.SetBrush(Brush(40, 40, 40));
	Widget item2("right widget");
	item2.SetBrush(Brush(40, 40, 40));


	Layout* lay = w.GetLayout();
	lay->SetBrush(Brush(25, 30, 40));
	lay->AddWindow(&item1);
	lay->AddWindow(&item2);
	
	lay->Show();
	b2.Move(w.GetSize().cx - (b1.GetSize().cx * 2), 0, b1.GetSize().cx, b1.GetSize().cy);

	w.Show();

	return app.Run();
}

#elif (TAKE == LISTBOX)

#define ID_LISTVIEW	1000
#define UWM_TEST	(WM_USER + 5)
//Test ListBox with Custom draw
LRESULT CALLBACK WndProc(HWND handle, UINT msg, WPARAM wp, LPARAM lp);
void listViewInit(HWND handle);
LRESULT paint(HWND handle, NMLVCUSTOMDRAW* ncd);

HWND mainHandle = NULL;
HWND childHandle = NULL;

struct TextItem
{
	TCHAR* name;
	int w;
};

std::array<TextItem, 3> gTextItem = { { { TEXT("One"),300 },
										{ TEXT("Two"),300 },
										{ TEXT("three"),300 }} };

//int main(int args, char* argv[])
//{
//	HWND consoleWindow = GetConsoleWindow();
//	SetWindowPos(consoleWindow, 0, 0, 0, 500, 900, SWP_NOSIZE | SWP_NOZORDER);
//
//	Application app;
//
//	InitCommonControls();			//enable to window ex control(must be )
//	WNDCLASS wc{};
//	wc.style = CS_VREDRAW | CS_HREDRAW;
//	wc.lpfnWndProc = WndProc;
//	wc.hInstance = App->GetInstance();
//	wc.hbrBackground = CreateSolidBrush(Color(100, 130, 150));
//	wc.lpszClassName = TEXT("MainClass");
//	wc.hCursor = LoadCursor(NULL, IDC_ARROW);
//	RegisterClass(&wc);
//
//	DWORD mainStyle = WS_POPUPWINDOW | WS_THICKFRAME | WS_VISIBLE;
//	mainHandle = CreateWindowEx(NULL, wc.lpszClassName, TEXT("custom main"),
//		mainStyle, 700, 300, 800, 600, NULL, NULL, App->GetInstance(), NULL);
//
//	ShowWindow(mainHandle, TRUE);
//	return app.Run();
//}

//int WinMain(HINSTANCE inst, HINSTANCE preInst, PSTR cmdLine, int cmdShow)
//{
//	win::SetConsoleOutput(0, 0, 500, 600);
//
//	Application app;
//
//	InitCommonControls();			//enable to window ex control(must be )
//	WNDCLASS wc{};
//	wc.style = CS_VREDRAW | CS_HREDRAW;
//	wc.lpfnWndProc = WndProc;
//	wc.hInstance = App->GetInstance();
//	wc.hbrBackground = CreateSolidBrush(Color(100, 130, 150));
//	wc.lpszClassName = TEXT("MainClass");
//	wc.hCursor = LoadCursor(NULL, IDC_ARROW);
//	RegisterClass(&wc);
//
//	DWORD mainStyle = WS_OVERLAPPEDWINDOW | WS_THICKFRAME | WS_VISIBLE;
//	mainHandle = CreateWindowEx(NULL, wc.lpszClassName, TEXT("custom main"),
//		mainStyle, 700, 300, 800, 600, NULL, NULL, App->GetInstance(), NULL);
//
//	ShowWindow(mainHandle, TRUE);
//
//	return app.Run();
//}
//
//LRESULT CALLBACK WndProc(HWND handle, UINT msg, WPARAM wp, LPARAM lp)
//{
//	switch (msg)
//	{
//	case WM_NOTIFY:
//	{
//		//LPARAM
//		//A pointer to an NMHDR structure that contains the notification code and 
//		//additional information.For some notification messages,
//		//this parameter points to a larger 
//		//structure that has the NMHDR structure as its first member.
//		NMHDR* hdr = (NMHDR*)lp;
//		if (hdr->idFrom == ID_LISTVIEW) //check handle ID
//		{
//			//LOG << "id : listbox" << ENDN;
//			if (hdr->code == NM_CUSTOMDRAW) {
//				//LOG << "custom draw" << ENDN;
//				return paint(handle,(NMLVCUSTOMDRAW*)hdr);
//			}
//
//		}
//		//LOG << "notify" << ENDN;
//		break;
//	}
//	case WM_CREATE:
//	{
//		LOG << "create main" << ENDN;
//		//Test new window (main window parent)
//		DWORD style = LVS_REPORT | WS_TABSTOP | WS_BORDER | WS_CHILD | WS_VISIBLE;
//		/*childHandle = CreateWindow(WC_LISTVIEW, NULL,
//			style, 0, 0, 0, 0, handle, (HMENU)ID_LISTVIEW, App->GetInstance(), NULL);*/
//		childHandle = CreateWindowEx(NULL,WC_LISTVIEW, NULL,
//			style, 0, 0, 0, 0, handle, (HMENU)ID_LISTVIEW, App->GetInstance(), NULL);
//		listViewInit(childHandle);
//		return 0;
//	}
//	case UWM_TEST:
//	{
//		
//		LOG << "user test message" << ENDN;
//		break;
//	}
//	case WM_SIZE:
//	{
//		if (childHandle) {
//			LOG << "child resizing" << ENDN;
//			//fit child to main LPARAM (parent size)
//			//The low - order word of lParam specifies the new width of the client area.
//			//The high - order word of lParam specifies the new height of the client area.
//			int childW = (int)LOWORD(lp) - 20;
//			int childH = (int)HIWORD(lp) - 20;
//			SetWindowPos(childHandle, NULL, 10, 10, childW, childH, SWP_NOZORDER);
//		}
//		break;
//	}
//	case WM_CLOSE:
//		PostQuitMessage(0);
//		return 0;
//	}
//	return DefWindowProc(handle, msg, wp, lp);
//}
//
//void listViewInit(HWND handle)
//{
//	LVCOLUMN col;
//	LVITEM item;
//	//test send message to list control
//	//SendMessage(childHandle, UWM_TEST, NULL, NULL);
//	col.mask = LVCF_WIDTH | LVCF_TEXT;
//
//	for (int i = 0; i < gTextItem.size(); i++)
//	{
//		col.pszText = gTextItem[i].name;
//		col.cx = gTextItem[i].w;
//		SendMessage(handle, LVM_INSERTCOLUMN, i, (LPARAM)&col);
//	}
//
//	for (int i = 0; i < 2; ++i)
//	{
//		item.iItem = i;
//		item.mask = LVIF_PARAM | LVIF_TEXT;
//		item.pszText = TEXT("item");
//		item.iSubItem = 0;
//		item.lParam = 10;
//		SendMessage(handle, LVM_INSERTITEM, 0, (LPARAM)&item);
//
//		item.mask = LVIF_TEXT;
//		item.iSubItem = 1;
//		item.pszText = TEXT("Pre");
//		SendMessage(handle, LVM_SETITEM, 0, (LPARAM)&item);
//
//		item.iSubItem = 2;
//		item.pszText = TEXT("Pre");
//		SendMessage(handle, LVM_SETITEM, 0, (LPARAM)&item);
//
//		
//	}
//}
//
//LRESULT paint(HWND handle, NMLVCUSTOMDRAW* ncd)
//{
//	LVITEM item;
//	TCHAR buffer[16];			//prepare item text allocated
//	//behaviour with ncd type
//	switch (ncd->nmcd.dwDrawStage)
//	{
//	case CDDS_PREPAINT:
//		//tell the comm control interested in per item notificatuon
//		LOG << "cdds pre paint" << ENDN;
//		return CDRF_DODEFAULT | CDRF_NOTIFYITEMDRAW;
//	case (CDDS_ITEM | CDDS_PREPAINT):
//	{
//		LOG << "cdds item" << ENDN;
//		return CDRF_DODEFAULT | CDRF_NOTIFYSUBITEMDRAW;
//
//	}
//	case (CDDS_ITEM | CDDS_SUBITEM | CDDS_PREPAINT):
//		LOG << "cdds sub item" << ENDN;
//		switch (ncd->iSubItem)
//		{
//		case 0:						//column 0 Items
//		{
//			//test draw
//			NMCUSTOMDRAW &cd = ncd->nmcd;			//custom draw info struct
//			int divCount = cd.lItemlParam;
//			HDC dc = ncd->nmcd.hdc;
//			Color bk(60, 60, 60);
//			
//			Brush bgBrush(Color(50, 50, 50));
//			Brush itemBgBrush(Color(80, 90, 100));
//			Pen pen(PS_SOLID, 1, Color(200, 200, 200));
//
//			FillRect(dc, &cd.rc, bgBrush);
//
//			int width = cd.rc.right - cd.rc.left - 6;
//			if (width < 0) width = 0;
//
//			//calc item rect
//			Rect rc;
//			int space = 10;
//			rc.left = cd.rc.left + space;
//			rc.right = rc.left + width /** divCount*/;
//			rc.top = cd.rc.top + space;
//			rc.bottom = cd.rc.bottom - space;
//			
//			FillRect(dc, &rc, itemBgBrush);
//
//			item.iSubItem = ncd->iSubItem;
//			item.pszText = buffer;
//			item.cchTextMax = sizeof(buffer) / sizeof(buffer[0]);
//			//TODO : it dosent work for getting text buffer
//			SendMessage(handle, LVM_GETITEMTEXT, ncd->nmcd.dwItemSpec, (LPARAM)&item);
//
//			//sets
//			::SelectObject(dc, pen);
//
//			SetBkColor(dc,Color(0, 0, 0));
//			SetTextColor(dc, Color(200, 200, 200));
//			//TextOut(dc, rc.left, rc.top, TEXT("Test"), lstrlenW(TEXT("text")));
//			
//			DrawText(dc, TEXT("check"), -1, &rc,
//				DT_CENTER | DT_VCENTER | DT_NOPREFIX | DT_SINGLELINE | DT_END_ELLIPSIS);
//			return CDRF_SKIPDEFAULT;
//		}
//		case 1:
//		{
//			//test draw
//			NMCUSTOMDRAW &cd = ncd->nmcd;			//custom draw info struct
//			int divCount = cd.lItemlParam;
//			HDC dc = ncd->nmcd.hdc;
//			Color bk(60, 60, 60);
//
//			Brush bgBrush(Color(50, 50, 50));
//			Brush itemBgBrush(Color(80, 90, 100));
//			Pen pen(PS_SOLID, 1, Color(200, 200, 200));
//
//			FillRect(dc, &cd.rc, bgBrush);
//
//			int width = cd.rc.right - cd.rc.left - 6;
//			if (width < 0) width = 0;
//
//			//calc item rect
//			Rect rc;
//			int space = 10;
//			rc.left = cd.rc.left + space;
//			rc.right = rc.left + width /** divCount*/;
//			rc.top = cd.rc.top + space;
//			rc.bottom = cd.rc.bottom - space;
//
//			FillRect(dc, &rc, itemBgBrush);
//
//			item.iSubItem = ncd->iSubItem;
//			item.pszText = buffer;
//			item.cchTextMax = sizeof(buffer) / sizeof(buffer[0]);
//			//TODO : it dosent work for getting text buffer
//			SendMessage(handle, LVM_GETITEMTEXT, ncd->nmcd.dwItemSpec, (LPARAM)&item);
//
//			//sets
//			::SelectObject(dc, pen);
//
//			//TextOut(dc, 0, 0, TEXT("Test"), lstrlenW(TEXT("text")));
//
//			DrawText(dc, TEXT("check"), -1, &rc,
//				DT_CENTER | DT_VCENTER | DT_NOPREFIX | DT_SINGLELINE | DT_END_ELLIPSIS);
//			return CDRF_SKIPDEFAULT;
//		}
//		}
//		break;
//	}
//	//return defualt
//	return CDRF_DODEFAULT;
//}


#define ID_LISTVIEW  1000

static HINSTANCE hInstance;
static HWND hwndMain;
static HWND hwndListView;


static const struct {
	TCHAR* pszText;
	int cx;
} columnMap[] = {
	{ _T("Task"),     150 },
	{ _T("Priority"),  60 },
	{ _T("Progress"), 120 },
	{ 0 }
};

static const struct {
	TCHAR* pszName;
	TCHAR* pszPriority;
	int iProgress;
} taskMap[] = {
	{ _T("Fix bug #237"),         _T("High"),   15 },
	{ _T("Write user manual"),    _T("Normal"), 80 },
	{ _T("Test performance"),     _T("Low"),     5 },
	{ _T("Fix bug #239"),         _T("Done"),  100 },
	{ _T("Prepare presentation"), _T("High"),   90 },
	{ 0 }
};


static void PopulateListView(void)
{
	LVCOLUMN col;
	LVITEM item;
	TCHAR pszBuffer[16];
	int i;

	col.mask = LVCF_WIDTH | LVCF_TEXT;
	for (i = 0; columnMap[i].pszText != NULL; i++) {
		col.pszText = columnMap[i].pszText;
		col.cx = columnMap[i].cx;
		SendMessage(hwndListView, LVM_INSERTCOLUMN, i, (LPARAM)&col);
	}

	for (i = 0; taskMap[i].pszName != NULL; i++)
	{
		item.mask = LVIF_PARAM | LVIF_TEXT;
		item.iItem = i;
		item.iSubItem = 0;
		item.pszText = taskMap[i].pszName;
		item.lParam = taskMap[i].iProgress;
		SendMessage(hwndListView, LVM_INSERTITEM, 0, (LPARAM)&item);

		item.mask = LVIF_TEXT;
		item.iSubItem = 1;
		item.pszText = taskMap[i].pszPriority;
		SendMessage(hwndListView, LVM_SETITEM, 0, (LPARAM)&item);

		item.iSubItem = 2;
		item.pszText = pszBuffer;
		_stprintf(pszBuffer, _T("%d %%"), taskMap[i].iProgress);
		SendMessage(hwndListView, LVM_SETITEM, 0, (LPARAM)&item);
	}
}

static LRESULT HandleCustomDraw(NMLVCUSTOMDRAW* pcd)
{
	TCHAR buffer[16];
	LVITEM item;

	switch (pcd->nmcd.dwDrawStage) {
	case CDDS_PREPAINT:
		/* Tell the control we are interested in per-item notifications.
		* (We need it just to tell the control we want per-subitem
		* notifications.) */
		return CDRF_DODEFAULT | CDRF_NOTIFYITEMDRAW;

	case (CDDS_ITEM | CDDS_PREPAINT):
		/* Tell the control we are interested in per-subitem notifications. */
		return CDRF_DODEFAULT | CDRF_NOTIFYSUBITEMDRAW;

	case (CDDS_ITEM | CDDS_SUBITEM | CDDS_PREPAINT):
		switch (pcd->iSubItem) {
		case 1:
			/* Customize "priority" column by marking some priority levels
			* with appropriate color. */
			item.iSubItem = pcd->iSubItem;
			item.pszText = buffer;
			item.cchTextMax = sizeof(buffer) / sizeof(buffer[0]);
			SendMessage(hwndListView, LVM_GETITEMTEXT, pcd->nmcd.dwItemSpec, (LPARAM)&item);

			if (_tcsicmp(_T("High"), buffer) == 0)
				pcd->clrText = RGB(190, 0, 0);
			else if (_tcsicmp(_T("Done"), buffer) == 0)
				pcd->clrText = RGB(0, 160, 0);
			/* Let the control do the painting itself with the new color. */
			return CDRF_DODEFAULT;

		case 2:
		{
			/* Customize "progress" column. We paint simple progress
			* indicator. */
			int iProgress = pcd->nmcd.lItemlParam;
			int cx;
			HDC hdc = pcd->nmcd.hdc;
			COLORREF clrBack;
			HBRUSH hBackBrush;
			HBRUSH hProgressBrush;
			HBRUSH hOldBrush;
			HPEN hPen;
			HPEN hOldPen;
			RECT rc;

			clrBack = pcd->clrTextBk;
			if (clrBack == CLR_NONE || clrBack == CLR_DEFAULT)
				clrBack = RGB(255, 255, 255);

			hBackBrush = CreateSolidBrush(clrBack);
			hProgressBrush = CreateSolidBrush(RGB(190, 190, 255));
			hPen = CreatePen(PS_SOLID, 0, RGB(190, 190, 255));

			hOldBrush = (HBRUSH)SelectObject(hdc, hBackBrush);
			FillRect(hdc, &pcd->nmcd.rc, hBackBrush);

			cx = pcd->nmcd.rc.right - pcd->nmcd.rc.left - 6;
			if (cx < 0)
				cx = 0;
			rc.left = pcd->nmcd.rc.left + 3;
			rc.top = pcd->nmcd.rc.top + 2;
			rc.right = rc.left + cx * iProgress / 100;
			rc.bottom = pcd->nmcd.rc.bottom - 2;
			SelectObject(hdc, hProgressBrush);
			FillRect(hdc, &rc, hProgressBrush);

			rc.right = pcd->nmcd.rc.right - 3;
			SelectObject(hdc, GetStockObject(HOLLOW_BRUSH));
			SelectObject(hdc, hPen);
			Rectangle(hdc, rc.left, rc.top, rc.right, rc.bottom);

			item.iSubItem = pcd->iSubItem;
			item.pszText = buffer;
			item.cchTextMax = sizeof(buffer) / sizeof(buffer[0]);
			SendMessage(hwndListView, LVM_GETITEMTEXT, pcd->nmcd.dwItemSpec, (LPARAM)&item);
			DrawText(hdc, buffer, -1, &rc,
				DT_CENTER | DT_VCENTER | DT_NOPREFIX | DT_SINGLELINE | DT_END_ELLIPSIS);

			SelectObject(hdc, hOldBrush);
			DeleteObject(hProgressBrush);
			DeleteObject(hBackBrush);
			//SelectObject(hdc, hOldPen);
			DeleteObject(hPen);

			/* Tell the control to not paint as we did so. */
			return CDRF_SKIPDEFAULT;
				}
			}
		break;
	}

	/* For all unhandled cases, we let the control do the default. */
	return CDRF_DODEFAULT;
}

static LRESULT CALLBACK MainWinProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch (uMsg) {
	case WM_NOTIFY:
	{
		NMHDR* pHdr = (NMHDR*)lParam;
		if (pHdr->idFrom == ID_LISTVIEW  &&  pHdr->code == NM_CUSTOMDRAW)
			return HandleCustomDraw((NMLVCUSTOMDRAW*)pHdr);
		break;
	}

	case WM_SIZE:
		if (wParam != SIZE_MAXHIDE  &&
			wParam != SIZE_MAXSHOW  &&
			wParam != SIZE_MINIMIZED) {
			SetWindowPos(hwndListView, NULL, 10, 10, LOWORD(lParam) - 20,
				HIWORD(lParam) - 20, SWP_NOZORDER);
			
		}
		break;

	case WM_CREATE:
		INITCOMMONCONTROLSEX icex;
		icex.dwICC = ICC_LISTVIEW_CLASSES;
		InitCommonControlsEx(&icex);
		hwndListView = CreateWindow( WC_LISTVIEW, NULL,
			LVS_REPORT | WS_TABSTOP | WS_BORDER | WS_CHILD | WS_VISIBLE ,
			0, 0, 0, 0, hwnd, (HMENU)ID_LISTVIEW, hInstance, 0);
		PopulateListView();
		return 0;

	case WM_CLOSE:
		PostQuitMessage(0);
		return 0;
	}

	return DefWindowProc(hwnd, uMsg, wParam, lParam);
}

int APIENTRY _tWinMain(HINSTANCE hInst, HINSTANCE hInstPrev, TCHAR* lpszCmdLine, int iCmdShow)
{
	WNDCLASS wc = { 0 };
	MSG msg;

	hInstance = hInst;
	InitCommonControls();

	wc.style = CS_HREDRAW | CS_VREDRAW;
	wc.lpfnWndProc = MainWinProc;
	wc.hInstance = hInstance;
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);
	wc.hbrBackground = (HBRUSH)(COLOR_BTNFACE + 1);
	wc.lpszClassName = _T("main_win");
	RegisterClass(&wc);

	hwndMain = CreateWindow(_T("main_win"), _T("Custom Draw Demo"),
		WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT, 700, 800,
		NULL, NULL, hInstance, NULL);
	ShowWindow(hwndMain, iCmdShow);
	//ShowWindow(hwndMain, FALSE);
	while (GetMessage(&msg, NULL, 0, 0)) {
		if (IsDialogMessage(hwndMain, &msg))
			continue;

		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	return (int)msg.wParam;
}
#elif (TAKE == COMBOBOX)
#include <tchar.h>
LRESULT CALLBACK WndProc(HWND handle, UINT msg, WPARAM wp, LPARAM lp);

HWND gHandle = NULL;
HWND gCombo = NULL;

int main(int args, char* argv[])
{
	HWND consoleWindow = GetConsoleWindow();
	SetWindowPos(consoleWindow, 0, 0, 0, 500, 900, SWP_NOSIZE | SWP_NOZORDER);

	Application app;

	WNDCLASS wc{};
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);
	wc.hInstance = App->GetInstance();
	wc.lpfnWndProc = WndProc;
	wc.lpszClassName = TEXT("mainwindow");
	wc.hbrBackground = CreateSolidBrush(RGB(50,50,50));
	wc.style = CS_VREDRAW | CS_HREDRAW;

	RegisterClass(&wc);

	gHandle = CreateWindowEx(NULL, wc.lpszClassName, TEXT("main window"),
		WS_POPUP | WS_VISIBLE, 600, 300, 700, 500, NULL, NULL,
		App->GetInstance(), NULL);

	ShowWindow(gHandle, TRUE);

	return app.Run();
}

#define ID_COMBO 1001

void PrepareCobmbo()
{
	TCHAR* st = _T("hey");
	
	SendMessage(gCombo, CB_ADDSTRING, 0, LPARAM(st));
}

LRESULT CALLBACK WndProc(HWND handle, UINT msg, WPARAM wp, LPARAM lp)
{
	if (msg == WM_CREATE)
	{
		DWORD style = CBS_DROPDOWN | WS_CHILD | WS_VISIBLE;
		gCombo = CreateWindowEx(WS_EX_CLIENTEDGE, TEXT("COMBOBOX"), TEXT("combo"),
			style, 100, 100, 200, 200, handle, (HMENU)ID_COMBO,
			App->GetInstance(), NULL);
		PrepareCobmbo();
		//InvalidateRect(gCombo, NULL, TRUE);
		
		return 0;
	}

	switch (msg)
	{
	case WM_COMMAND:
	{
		switch (LOWORD(wp))
		{
		case ID_COMBO:
		{
			LOG << "dia" << ENDN;
		}
		}
		
		break;
	}
	case WM_DRAWITEM:
	{
		LPDRAWITEMSTRUCT item = (LPDRAWITEMSTRUCT)lp;
		if (item->itemID == -1) break;

		//HDC &dc = item->hDC;
		SetBkColor(item->hDC, RGB(100,0,0));
		
		

		
		LOG << "item paint" << ENDN;
		break;
	}
	case WM_MEASUREITEM:
		LOG << "me" << ENDN;
		break;
	case WM_NOTIFY:
	{
		LOG << "notify" << ENDN;
		break;
	}
	case WM_PAINT:
	{
		LOG << "paint" << ENDN;
		HWND h = GetDlgItem(gCombo, ID_COMBO);
		Rect rect;
		::GetClientRect(h, &rect);
		PAINTSTRUCT ps;
		HDC dc = BeginPaint(h, &ps);

		::SetBkColor(dc, RGB(100, 100, 100));

		EndPaint(h, &ps);
		if (gCombo == handle)
		{
			LOG << "paint" << ENDN;
		}
		break;
	}
	}
	return DefWindowProc(handle, msg, wp, lp);
}

#elif (TAKE == OWNERDRAW)

/* File main.c
* (application code)
*/

#include <tchar.h>
#include <windows.h>
#include <commctrl.h>

#include <string.h>
#include <stdio.h>


#define ID_LISTVIEW  1000

HWND gHandle = NULL;
HWND gChild = NULL;

static void PopulateListView(void)
{

}

static LRESULT HandleCustomDraw(NMLVCUSTOMDRAW* pcd)
{
	return 0;
}

static LRESULT CALLBACK MainWinProc(HWND handle, UINT msg, WPARAM wp, LPARAM lp)
{
	switch (msg) 
	{
	case WM_CREATE:
	{
		DWORD style = WS_CHILD | WS_VISIBLE | SS_OWNERDRAW;
		gChild = CreateWindowEx(0, _T("STATIC"), _T("static"),
			style, 20, 200, 150, 20, handle, 0, 0, 0);
		break;
	}
	case WM_DRAWITEM:
	{
		LOG << "item" << ENDN;
		LPDRAWITEMSTRUCT item = (LPDRAWITEMSTRUCT)lp;
		if (item->hwndItem == gChild) 
		{
			SetTextColor(item->hDC, RGB(200,200,200));
			SetBkColor(item->hDC, RGB(60, 60, 60));

			Rect rect;
			::GetClientRect(gChild, &rect);
			LOG << rect << ENDN;

			TCHAR t[99];
			int len = SendMessage(gChild, WM_GETTEXT, ARRAYSIZE(t), (LPARAM)t);

			int g = 10;
			TextOut(item->hDC, item->rcItem.left, item->rcItem.top, t, len);
		}
		return TRUE;
		break;
	}
	case WM_CLOSE:
		PostQuitMessage(0);
		break;
	}

	

	return DefWindowProc(handle, msg, wp, lp);
}

int main(int args, char* argv[])
{
	HWND consoleWindow = GetConsoleWindow();
	SetWindowPos(consoleWindow, 0, 0, 0, 500, 900, SWP_NOSIZE | SWP_NOZORDER);

	Application app;
	WNDCLASS wc = {};
	InitCommonControls();

	wc.style = CS_HREDRAW | CS_VREDRAW;
	wc.lpfnWndProc = MainWinProc;
	wc.hInstance = App->GetInstance();
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);
	wc.hbrBackground = CreateSolidBrush(RGB(100,100,100));
	wc.lpszClassName = _T("main_win");
	RegisterClass(&wc);

	gHandle = CreateWindowEx(NULL,_T("main_win"), _T("Custom Draw Demo"),
		WS_OVERLAPPEDWINDOW, 600, 300, 700, 500,
		NULL, NULL, App->GetInstance(), NULL);
	ShowWindow(gHandle, TRUE);
	//ShowWindow(hwndMain, FALSE);
	return app.Run();
}

#elif (TAKE == CONTROL)

//LRESULT CALLBACK PanelProc(HWND handle, UINT msg, WPARAM wp, LPARAM lp);
//LRESULT CALLBACK WndProc(HWND handle, UINT msg, WPARAM wp, LPARAM lp);
//
//int main(int args, char* argv[])
//{
//	Application app;
//	HWND handle;
//	WNDCLASS wc{};
//	wc.hInstance = App->GetInstance();
//	wc.lpfnWndProc = WndProc;
//	wc.hbrBackground = CreateSolidBrush(RGB(100, 100, 100));
//	wc.hCursor = LoadCursor(NULL, IDC_ARROW);
//	wc.lpszClassName = _T("Application");
//
//	RegisterClass(&wc);
//
//	handle = CreateWindowEx(NULL, wc.lpszClassName, _T("window"),
//		WS_OVERLAPPEDWINDOW | WS_VISIBLE | WS_CLIPCHILDREN,
//		400, 400, 700, 400, 0, 0, App->GetInstance(), NULL);
//
//	return app.Run();
//}
//
//LRESULT CALLBACK WndProc(HWND handle, UINT msg, WPARAM wp, LPARAM lp)
//{
//	static HWND child;
//
//	WNDCLASS wc{};
//
//	//INITCOMMONCONTROLSEX initCtrl;
//	//initCtrl.dwSize = sizeof(initCtrl);
//	//initCtrl.dwICC = ICC_BAR_CLASSES;
//
//	//InitCommonControlsEx(&initCtrl);
//
//	switch (msg)
//	{
//	case WM_CREATE:
//	{
//		wc.lpszClassName = _T("ChildCtrl");
//		wc.hbrBackground = GetSysColorBrush(COLOR_BTNFACE);
//		wc.lpfnWndProc = PanelProc;
//		wc.hCursor = LoadCursor(NULL, IDC_ARROW);
//		wc.style = CS_HREDRAW;
//
//		if (!RegisterClass(&wc))
//			LOG_FATAL("failed to rsgister class");
//		
//		child = CreateWindowEx(NULL, wc.lpszClassName, NULL,
//			WS_CHILD | WS_VISIBLE, 0, 300, 450, 30, handle, (HMENU)1, NULL, NULL);
//
//		break;
//	}
//
//	case WM_SIZE:
//	{
//		int w = LOWORD(lp);
//		int h = HIWORD(lp);
//		SetWindowPos(child, NULL, 0, h - 30, w, 30, SWP_NOZORDER);
//		break;
//	}
//
//	}
//	return DefWindowProc(handle, msg, wp, lp);
//}
//
//LRESULT CALLBACK PanelProc(HWND handle, UINT msg, WPARAM wp, LPARAM lp)
//{
//	switch (msg)
//	{
//	case WM_PAINT:
//	{
//		Painter painter(handle);
//
//		painter.SetBrush(Brush(20, 50, 80));
//		Rect rc;
//		::GetClientRect(handle, &rc);
//		painter.FillRect(rc);
//		break;
//	}
//	}
//
//	return DefWindowProc(handle, msg, wp, lp);
//}
#include <treeview.h>

int main(int args, char* argv[])
{
	Application app;
	MainWindow mainWindow(1000, 500);
	TreeView tv;

	mainWindow.GetLayout()->AddWindow(&tv);

	//tv.Show();
	mainWindow.Show();
	return app.Run();
}

#elif(TAKE == LISTBOX2)
#include <windows.h>
#include <listbox.h>
#include <lineedit.h>

int main(int args, char* argv[])
{
	Application app;

	MainWindow mainWin(1280, 680);
	//ListBox listbox(500,300,700,400);
	//ListBox list(200, 200, 300, 300);

	//mainWin.GetLayout()->AddWindow(&listbox);
	//mainWin.GetLayout()->AddWindow(&list);

	LineEdit ed;
	mainWin.GetLayout()->AddWindow(&ed);

	mainWin.Show();

	return app.Run();
}

#else

#endif


