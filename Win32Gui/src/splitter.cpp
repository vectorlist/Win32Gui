#include "splitter.h"



Splitter::Splitter(int fixedSize)
	: Window(NULL), mLeft(NULL), mRight(NULL)
{
	SetWindowName("Splitter");
}


Splitter::~Splitter()
{
}

/* create splitter on attch */
void Splitter::Attach(Window *parent, Window *left, Window *right)
{
	Create(*parent);
	//TODO : set parent to layout and change style
	::SetParent(*this, *parent);
	DWORD style = WS_CHILD | WS_VISIBLE;
	SetWindowLong(*this, GWL_STYLE, style);
	mLeft = left;
	mRight = right;
}

Splitter* Splitter::CreateSplitter()
{
	Splitter* splitter ;
	return nullptr;
}

void Splitter::PreRegisterClass(WNDCLASS &wc)
{
	wc.lpszClassName = CLASSNAME_SPLITTER;
}

void Splitter::PreCreate(CREATESTRUCT &cs)
{
	//
	cs.style = WS_CLIPSIBLINGS | WS_VISIBLE;
	cs.x = 100;
	cs.y = 100;
	cs.cx = 200;
	cs.cy = 200;
}

void Splitter::PaintEvent(Painter *painter)
{
	LOG << GetWindowName() << " paint" << ENDN;
	static Brush sBrsuh(250, 0, 0);
	painter->SetBrush(sBrsuh);
	painter->FillRect(GetRect());
}

bool Splitter::IsSplitter()
{
	return true;
}
