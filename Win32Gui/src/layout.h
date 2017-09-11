#pragma once

#include <window.h>

class Splitter;
typedef std::vector<std::shared_ptr<Splitter>> SplitterList;

class LayoutContainer
{
public:
	void AddElement(Window* parent,Window* window);

	operator std::vector<Window*>&()
	{
		//return itself as vector windows
		return mWindow;
	}

	Window* operator[](unsigned int index)
	{
		return mWindow[index];
	}

	//std::vector<std::shared_ptr<Splitter>> mSplitters;
	SplitterList mSplitters;
	std::vector<Window*> mWindow;
};

class Layout : public Window
{
public:
	//no situable pos
	Layout(HWND parent);
	virtual~Layout();

	//unique this func
	void Attach(Window* parent);
	void AddWindow(Window* item);
	std::vector<Window*>&	GetChilds();
	SplitterList&			GetSplitters();
	
	Margin&					GetMargin() { return mMargin; };
	//override
	virtual void	UpdateLayout() = 0;
protected:
	virtual void	PreRegisterClass(WNDCLASS &wc);
	virtual void	MouseMoveEvent(MouseEvent& event);


	//layout built override
	/*virtual void	UpdateLayout() = 0;*/

	//custom window procedule func
	LRESULT CALLBACK LocalWndProc(UINT msg, WPARAM wp, LPARAM lp);

	Margin mMargin;
private:
	//std::vector<Window*> mWindow;
	LayoutContainer mWindows;
};

class HBoxLayout : public Layout
{
public:
	HBoxLayout(HWND parent = NULL);
	virtual ~HBoxLayout();

	virtual void UpdateLayout();
protected:
	virtual void PreCreate(CREATESTRUCT& cs);

	virtual void PaintEvent(Painter* painter);


private:
};

