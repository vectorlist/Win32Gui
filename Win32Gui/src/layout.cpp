#include <config.h>
#include <layout.h>
#include <application.h>

static LRESULT CALLBACK SplitterWndProc(HWND handle, UINT msg, WPARAM wp, LPARAM lp)
{
	return DefWindowProc(handle, msg, wp, lp);
}

Layout::Layout(HWND parent)
	: mHandle(NULL), mParent(parent), mIsSplitterMove(false)
{
	CreateLayout(parent);
}

Layout::~Layout()
{
}

bool Layout::CreateLayout(HWND parent)
{
	if (!parent|| !IsWindow(parent))
		return false;
	mParent = parent;
	SetRegisterClass();
	CreateLayoutWindow(parent);
	Update();
	return true;
}

void Layout::SetRegisterClass()
{
	static Brush layoutBrush(30, 35, 40);
	static Brush spliiterBrush(200, 200, 200);
	WNDCLASS wc{};
	//check register class redefinition already
	if (!GetClassInfo(App->GetInstance(), GetLayoutClassName(), &wc)) {

		wc.style = CS_HREDRAW | CS_VREDRAW;
		wc.lpfnWndProc = Layout::GlobalWndProc;
		wc.hInstance = App->GetInstance();
		wc.hbrBackground = layoutBrush;
		wc.lpszMenuName = NULL;
		wc.lpszClassName = GetLayoutClassName();
		if (!RegisterClass(&wc)) {
			LOG_FATAL("failed to layout register class");
		}
	}
	
	if (!GetClassInfo(App->GetInstance(), GetSplitterClassName(), &wc))
	{
		wc.style = NULL;
		wc.lpfnWndProc = SplitterWndProc;
		wc.hbrBackground = spliiterBrush;
		wc.hCursor = NULL;
		wc.lpszClassName = GetSplitterClassName();
		wc.hInstance = App->GetInstance();
		if (!RegisterClass(&wc)) {
			LOG_FATAL("failed to register splitter class");
		}
	}

}

void Layout::CreateLayoutWindow(HWND parent)
{
	mHandle = CreateWindowEx(NULL, GetLayoutClassName(), TEXT(""),
		WS_CHILD | WS_CLIPCHILDREN  ,
		0, 0, 0, 0, parent, NULL, App->GetInstance(), this);

	if (!mHandle)
		LOG_FATAL("failed to create layout handle");
}

void Layout::Update()
{
	this->UpdateRect();
}


void Layout::UpdateRect()
{
	
}

void Layout::AddWindow(HWND handle)
{
	if (!handle) return;
	//SetWindowLongPtr(handle, GWL_STYLE, GetClassLong(handle, GCL_STYLE) | CS_VREDRAW | CS_HREDRAW);
	SetWindowLongPtr(handle, GWL_STYLE, WS_CHILD | WS_VISIBLE);
	::SetParent(handle, this->mHandle);
	//SendMessage(handle, WM_CHANGEUISTATE, UIS_INITIALIZE, 0);
	mChilds.push_back(handle);
	Update();

	UpdateWindow(mHandle);
}

void Layout::CreateSplitter()
{
	ResetCursor();
	mIsSplitterMove = false;
	mSplitterHandle = CreateWindowEx(
		WS_EX_WINDOWEDGE | WS_EX_TOPMOST, 
		GetSplitterClassName(), TEXT(""),
		WS_CHILD | WS_BORDER | WS_DISABLED,
		0, 0, 0, 0, mHandle, NULL, App->GetInstance(), NULL);
}

void Layout::MoveSplitter(int x, int y)
{
	RECT rect;
	GetClientRect(mHandle, &rect);
	x -= rect.left;
	
	int space = std::max<int>(rect.right - rect.left - splitter.size, 1);
	if (mChilds.size())
	{

	}

}

void Layout::ResetCursor()
{
	if (splitter.size > 0) {
		SetClassLongPtr(mHandle, GCLP_HCURSOR, (LONG_PTR)LoadCursor(NULL, IDC_SIZEWE));
	}
	else {
		SetClassLongPtr(mHandle, GCLP_HCURSOR, (LONG_PTR)LoadCursor(NULL, IDC_ARROW));
	}
}

LRESULT CALLBACK Layout::GlobalWndProc(HWND handle, UINT msg, WPARAM wp, LPARAM lp)
{

	Layout* layout = (Layout*)GetWindowLongPtr(handle, GWLP_USERDATA);
	switch (msg)
	{
	case WM_NCCREATE:
	{
		layout = (Layout*)((CREATESTRUCT*)lp)->lpCreateParams;
		SetWindowLongPtr(handle, GWLP_USERDATA, (LONG_PTR)layout);
		layout->mHandle = handle;
		return TRUE;
	}
	case WM_CREATE:
	{
		layout->CreateSplitter();
		break;
	}
	case WM_MOUSEMOVE:
	{
		if (layout->splitter.size > 0)
		{
			
			if (wp == MK_LBUTTON && layout->mIsSplitterMove)
			{
				int x = (short)LOWORD(lp);
				int y = (short)HIWORD(lp);
				RECT rect;

				GetClientRect(layout->GetHandle(), &rect);
				
				if (x > rect.right && y > rect.bottom) return LNULL;
				layout->MoveSplitter(x, y);
			}
		}
		
		break;
	}
	case WM_LBUTTONDOWN:
	{
		layout->mIsSplitterMove = true;
		SetCapture(layout->GetHandle());
		if (layout->GetHandle())
		{
			MoveWindow(layout->mSplitterHandle, 0, 0, 10, 10, TRUE);
			ShowWindow(layout->mSplitterHandle, SW_SHOW);
			layout->MoveSplitter((short)LOWORD(lp), (short)HIWORD(lp));

			LOG << "in" << ENDN;
		}
		break;
	}

	case WM_LBUTTONUP:
	{
		layout->mIsSplitterMove = false;
		ReleaseCapture();
		if (layout->GetHandle()) {
			ShowWindow(layout->mSplitterHandle, SW_HIDE);
		}

		break;
	}
	case WM_SIZE:
		LOG << "layout size" << ENDN;
		break;
	case WM_NCHITTEST:
	{
		LOG << "lay hit" << ENDN;
		break;
	}
	default:
		break;
	}
	return DefWindowProc(handle, msg, wp, lp);
}

HLayout::HLayout(HWND parent)
	: Layout(parent)
{
}

HLayout::~HLayout()
{
	if (mHandle) {
		DestroyWindow(mHandle);
		mHandle = NULL;
	}
}

void HLayout::UpdateRect()
{
	if (!mParent) return;
	RECT rect;
	GetClientRect(mParent, &rect);
	int x = rect.left + mMargin.GetSpacing();
	int y = rect.top + mMargin.GetSpacing();
	int w = (rect.right - rect.left) - mMargin.GetSpacingMultiple();
	int h = (rect.bottom - rect.top) - mMargin.GetSpacingMultiple();
	MoveWindow(mHandle, x, y, w, h, TRUE);

	int childs = mChilds.size();
	if (childs == 0) return;

	if (childs == 1) {

		MoveWindow(mChilds[0], x, y, w, h, TRUE);
	}
	else {
		//multiple
		w /= childs;
		int newX = x;
		for (int i = 0; i < childs; ++i)
		{
			HWND child = mChilds[i];
			MoveWindow(child, newX, y, w -6, h, TRUE);
			newX += w;
		}
	}
}

