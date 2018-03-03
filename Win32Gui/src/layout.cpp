#include <config.h>
#include <layout.h>
#include <application.h>
#include <splitter.h>

Layout::Layout(HWND parent)
	: Window(parent)			//not parent window atm
{
	//we dont create here
	//Create(NULL);
	SetWindowName(WINDOWNAME_HLAYOUT);
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
	mWindows.AddElement(this, item);
	item->SetParentWindow(*this);

	DWORD style = WS_CHILD | WS_VISIBLE;
	win::ChangeWindowStyle(*item, style);

	UpdateLayout();
}

void Layout::AddWindow(Layout *item)
{
	mWindows.AddElement(this, item);
	item->SetParentWindow(*this);

	DWORD style = WS_CHILD | WS_VISIBLE;
	win::ChangeWindowStyle(*item, style);

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
	painter->SetBrush(GetBrush());
	painter->FillRect(GetRect());
	painter->SetFont(FONT_SYSTEM);
	auto a = GetWindowName();
	painter->FillText(0, 0, GetWindowName());
}

void HBoxLayout::MouseEnterEvent(MouseEvent & event)
{
	LOG << GetWindowName() << " entered" << ENDN;
}

//void HBoxLayout::ResizeEevnt(UINT msg, WPARAM wp, LPARAM lp)
//{
//	//UpdateLayout();
//}

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
	//over 2 windows on layout
	Rect layRect = GetRect() - mMargin;

	auto& splitters = GetSplitters();

	//initial position (handle by splitter)
	for (int i = 0; i < splitters.size(); ++i)
	{
		Splitter* splitter = splitters[i].get();
		Window* left = splitter->mLeft;
		Window* right = splitter->mRight;

		int wndSize = (layRect.Width() / 2) - (splitter->mFixedSize / 2);
		int pureW = GetRect().Width();
		int totalW = layRect.Width();

		int x = wndSize;

		//TODO : Left rect -> Splitter rect -> Right Rect
		left->Move(layRect.left, layRect.top, wndSize, layRect.Height());
		Rect lRect = left->MapFormParentRect(*this);
		splitter->Move(lRect.right, lRect.top, splitter->mFixedSize, lRect.Height());
		Rect spRect = splitter->MapFormParentRect(*this);
		
		right->Move(spRect.right, spRect.top, wndSize, spRect.Height());
	}
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
