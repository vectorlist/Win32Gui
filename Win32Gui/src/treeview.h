#pragma once

#include <window.h>

class Node
{
public:

};

class NodeTree
{
public:
	Node* root;
};

class TreeView : public Window
{
public:
	TreeView(HWND parent = NULL);
	~TreeView();

protected:
	virtual void PreRegisterClass(WNDCLASS &wc);
	virtual void PreCreate(CREATESTRUCTA &cs);

	virtual void MouseEnterEvent(MouseEvent &event);
};

