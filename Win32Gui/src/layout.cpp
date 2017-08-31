#include <config.h>
#include <layout.h>
#include <application.h>

Layout::Layout(HWND parent)
	: mHandle(NULL), mParent(parent)
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
	WNDCLASS wc{};
	//check register class redefinition already
	if (GetClassInfo(App->GetInstance(), GetLayoutClassName(), &wc)) {
		return;
	}
	
	static Brush lBrush(30, 35, 40);

	wc.style =  CS_HREDRAW | CS_VREDRAW;
	wc.lpfnWndProc = Layout::GlobalWndProc;
	wc.hInstance = App->GetInstance();
	wc.hbrBackground = lBrush;
	wc.lpszMenuName = NULL;
	wc.lpszClassName = GetLayoutClassName();

	if (!RegisterClass(&wc)) {
		LOG_FATAL("failed to layout register class");
	}

}

void Layout::CreateLayoutWindow(HWND parent)
{
	mHandle = CreateWindowEx(NULL, GetLayoutClassName(), TEXT(""),
		WS_CHILD | WS_CLIPCHILDREN | WS_CLIPSIBLINGS | WS_VISIBLE,
		0, 0, 0, 0, parent, NULL, App->GetInstance(), this);

	if (!mHandle)
		LOG_FATAL("failed to create layout handle");
}

void Layout::Update()
{
	this->UpdateRect();
}


LRESULT CALLBACK Layout::GlobalWndProc(HWND handle, UINT msg, WPARAM wp, LPARAM lp)
{

	Layout* layout = (Layout*)GetWindowLongPtr(handle, GWLP_USERDATA);
	switch (msg)
	{
	case WM_CREATE:
	{
		layout = (Layout*)((CREATESTRUCT*)lp)->lpCreateParams;
		SetWindowLongPtr(handle, GWLP_USERDATA, (LONG_PTR)layout);
		layout->mHandle = handle;
		return TRUE;
	}
	case WM_SIZE:
		LOG << "layout size" << ENDN;
		break;
	default:
		break;
	}
	return DefWindowProc(handle, msg, wp, lp);
}



void Layout::UpdateRect()
{
	//if (!mParent) return;
	//RECT rect;
	//GetClientRect(mParent, &rect);
	//int x = rect.left + mMargin.GetSpacing();
	//int y = rect.top + mMargin.GetSpacing();
	//int w = (rect.right - rect.left) - mMargin.GetSpacingMultiple();
	//int h = (rect.bottom - rect.top) - mMargin.GetSpacingMultiple();
	//MoveWindow(mHandle, x, y, w, h, TRUE);
	//
	//int childs = mChilds.size();
	//if (childs == 0) return;

	//if (childs == 1) {

	//	MoveWindow(mChilds[0], x, y, w, h, TRUE);
	//}
	//else {
	//	//multiple
	//	w /= childs;
	//	int newX = x;
	//	for (int i = 0; i < childs; ++i)
	//	{
	//		MoveWindow(mChilds[i], newX, y, w, h, TRUE);
	//		newX += w;
	//	}
	//}

	//UpdateWindow(mHandle);
}

void Layout::AddWindow(HWND handle)
{
	SetWindowLongPtr(handle, GWL_STYLE, WS_CHILD | WS_VISIBLE);
	::SetParent(handle, this->mHandle);
	mChilds.push_back(handle);
	Update();

	//UpdateWindow(mHandle);
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
			MoveWindow(mChilds[i], newX, y, w, h, TRUE);
			newX += w;
		}
	}
}
