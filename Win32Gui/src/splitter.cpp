#include "splitter.h"



Splitter::Splitter(int fixedSize)
	: Window(NULL), mLeft(NULL), mRight(NULL), mFixedSize(fixedSize),
	mOnFocusMoving(false)
{
	SetWindowName("Splitter");
}


Splitter::~Splitter()
{
}

/* create splitter on attch */
void Splitter::Attach(Window *parent, Window *left, Window *right)
{
	//check if it exist already
	if (mHandle && !parent) return;
	Create(*parent);

	SetParentWindow(*parent);
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
	//LOG << GetWindowName() << " paint" << ENDN;
	static Brush sBrush(150, 30, 0);
	static Brush moveBrush(220, 30, 0);

	if(!mOnFocusMoving)
		painter->SetBrush(sBrush);
	else
		painter->SetBrush(moveBrush);
	
	painter->FillRect(GetRect());
}

void Splitter::MouseMoveEvent(MouseEvent & event)
{
	if (IsKeyPressed(VK_LBUTTON)) {
		LOG << "will move" << ENDN;
		if (!mOnFocusMoving) {
			mOnFocusMoving = true;
			SetCapture(*this);
		}
		//TODO : move and repaint itself
		if (mOnFocusMoving) {
			//draw position and update
			Point pos = event.GetPos();
			//map to parent coordinate
			//::MapWindowPoints(*this, mParent, &pos, 2);
			ClientToScreen(*this, &pos);

			Rect rect = GetRect();
			LOG << pos << ENDN;
			Move(pos, rect.Width(), rect.Height());
			//::InvalidateRect(*this, GetRect(), TRUE);
		}
	}
}

void Splitter::MouseEnterEvent(MouseEvent &event)
{
	LOG << GetWindowName() << " entered" << ENDN;
	//mLeft->Move(0, 0, 300, 300);
}

void Splitter::MouseReleaseEvent(MouseEvent & event)
{
	if (mOnFocusMoving) {
		LOG << "release focus moving" << ENDN;
		mOnFocusMoving = false;
		//repaint finished
		ReleaseCapture();
		::InvalidateRect(*this, GetRect(), TRUE);
	}
}

bool Splitter::IsSplitter()
{
	return true;
}
