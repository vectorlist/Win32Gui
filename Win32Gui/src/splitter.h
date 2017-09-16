#pragma once

#include <window.h>

class Splitter : public Window
{
public:
	Splitter(int fixedSize = 10);
	~Splitter();

	void Attach(Window* parent, Window* left, Window* right);
	Splitter* CreateSplitter();

	virtual bool IsSplitter() override;

	Window* mLeft;
	Window* mRight;
	int mFixedSize;
protected:

	virtual void PreRegisterClass(WNDCLASS &wc);
	virtual void PreCreate(CREATESTRUCT &cs);

	virtual void PaintEvent(Painter* painter);
	virtual void MouseMoveEvent(MouseEvent &event);
	virtual void MouseEnterEvent(MouseEvent &event);

	virtual void MouseReleaseEvent(MouseEvent &event);

private:
	bool	mOnFocusMoving;
	
};

