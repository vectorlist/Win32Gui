#include "treeview.h"



TreeView::TreeView(HWND parent)
{
	SetWindowName("tree view");
	Create(parent);
}


TreeView::~TreeView()
{
}

void TreeView::PreRegisterClass(WNDCLASS &wc)
{
	wc.lpszClassName = _T("listboxex");
}

void TreeView::PreCreate(CREATESTRUCTA &cs)
{
	//cs.style = WS_CHILD | WS_VISIBLE;
}

void TreeView::MouseEnterEvent(MouseEvent &event)
{
	LOG << "enter " << GetWindowName() << ENDN;
}
