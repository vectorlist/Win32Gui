#include <config.h>
#include <layout.h>
#include <application.h>
#include <splitter.h>

Layout::Layout(HWND parent)
	: Window(parent)			//not parent window atm
{
	//we dont create here
	//Create(NULL);
}

Layout::~Layout()
{
}

/*set parent and hold main window*/
void Layout::Attach(Window* parent)
{
	//set Parent and change style and draw active rect
	SetParentWindow(*parent);

	DWORD style = WS_CHILD | WS_VISIBLE;
	win::ChangeWindowStyle(*this, style);

	//calc parent window with margin
	Rect layoutRect = parent->GetActiveRect();

	layoutRect = layoutRect - mMargin;
	Move(layoutRect);
}

void Layout::PreRegisterClass(WNDCLASS & wc)
{
	//we dont need to here layout are same
	wc.lpszClassName = CLASSNAME_HLAYOUT;
	wc.hbrBackground = CreateSolidBrush(COLOR_BLACK);
}

void Layout::AddWindow(Window *item)
{
	//Check childs size and add splitter automaicly

	
	mWindows.AddElement(this, item);
	
	//update and change style as child
	item->SetParentWindow(*this);

	DWORD style = WS_CHILD | WS_VISIBLE;
	win::ChangeWindowStyle(*item, style);

	/*Rect activeRect = Rect(0,300,0,400);
	window->Move(activeRect);*/
	UpdateLayout();
}

std::vector<Window*>& Layout::GetChilds()
{
	return mWindows.mWindow;
}

SplitterList& Layout::GetSplitters()
{
	return mWindows.mSplitters;
}

void Layout::MouseMoveEvent(MouseEvent &event)
{
	//LOG << event.GetPos() << ENDN;
}

/*local custom window procedule func*/
LRESULT Layout::LocalWndProc(UINT msg, WPARAM wp, LPARAM lp)
{
	Painter painter;
	MouseEvent me{ msg, wp, lp };
	switch (msg)
	{
	case WM_PAINT:
		//LOG << "layout paint" << ENDN;
		painter.Begin(*this);
		//PrePaintEvent(&painter);
		PaintEvent(&painter);
		painter.End(*this);
		break;
	case WM_MOUSEMOVE: MouseMoveEvent(me); break;
	case WM_NOTIFY:
		LOG << "call notify" << ENDN;
		break;

	case WM_SIZE:
		LOG << "layout wm_size" << ENDN;
		break;
	
	}
	return DefWindowProc(*this, msg, wp, lp);
}

 /*-------------------------- HBox Layout -----------------------------*/

HBoxLayout::HBoxLayout(HWND parent)
	: Layout(parent)
{
	Create(parent);
}

HBoxLayout::~HBoxLayout()
{
}

void HBoxLayout::PreCreate(CREATESTRUCT & cs)
{
	
}

void HBoxLayout::PaintEvent(Painter * painter)
{
	LOG << "HBox layout paint" << ENDN;
	painter->SetBrush(Brush(70, 100, 130));
	painter->FillRect(GetRect());
}

void HBoxLayout::UpdateLayout()
{
	//we dont update without parent
	if (!mParent && !GetChilds().size()) return;

	Window* child = NULL;
	auto& childs = GetChilds();
	//check child windows size
	if (childs.size() == 1)
	{
		//no splitter just fill whole rect
		child = GetChilds()[0];
		Rect rect = GetRect() - mMargin;
		child->Move(rect);				//move call WM_PAINT
	}

	int layWidth = Width();
	int layHeight = Height();
	/*if (childs.size() > 1)
	{
		if (child->IsSplitter()) {

		}
		int winSize =  layWidth / childs.size();
		LOG << "dynamic winsize " << winSize << ENDN;
		int x = 0;
		for (int i = 0; i < childs.size(); ++i)
		{
			x = winSize * i;
			child = childs[i];
			child->Move(x, GetRect().top, winSize, Height());
		}
	}*/
	//draw by splitter
	auto& splitters = GetSplitters();

	SplitterList::iterator it;

	int i = 0;
	
	for (it = splitters.begin(); it != splitters.end(); ++it,++i)
	{
		Splitter* splitter = (Splitter*)it._Ptr;
		Window* left = splitter->mLeft;
		Window* right = splitter->mLeft;

		int wndSize = (layWidth / 2 ) - (splitter->mFixedSize/2);
		int x = wndSize;

		left->Move(x * 0, GetPos().y, wndSize, Height());
		splitter->Move(left->GetRect().left, GetPos().y, splitter->mFixedSize, Height());
		right->Move(x * 1 + splitter->mFixedSize, GetPos().y, wndSize, Height());
	}
	/*for (int i = 0; i < splitter.size(); ++i)
	{
		Splitter* splitter = splitter[i].;
	}*/


	LOG << "update layouts and childs" << ENDN;
	//recalc rect then repaint
	//call WM_PAINT to active rect
	//::InvalidateRect(mHandle, GetRect(), TRUE);
}

void LayoutContainer::AddElement(Window* parent, Window *window)
{
	//add splitter btw windows
	mWindow.push_back(window);
	if (mWindow.size() == 2) {
		//just allocate splitter
		//attach on outside
		auto splitter = std::make_shared<Splitter>();
		
		LOG << "add splitter" << ENDN;
		//parent is layout
		//left window, right window
		splitter->Attach(parent, mWindow[0], mWindow[1]);

		mSplitters.push_back(splitter);
		mWindow.push_back((Window*)splitter.get());

		//swap position (splitter center)
		std::swap(mWindow[1], mWindow.back());
	}
}
