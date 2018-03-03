#pragma once

#include <window.h>

//TEST hMenu for WM_DRAWITEM
#define BT_CLOSE				0x001
#define BT_MIN					0x002

#define BT_CLASSNAME			TEXT("buttonw")

enum class ButtonType : unsigned int
{
	None,
	Close,
	Min,
	Max,
	User
};

class Painter;
class Button : public Window
{
public:
	Button(HWND parent, ButtonType type = ButtonType::None, int fixedSize = 30);
	virtual~Button();

protected:
	virtual void PreRegisterClass(WNDCLASS &wc);
	virtual void PreCreate(CREATESTRUCT &cs);

	virtual void PaintEvent(Painter* painter);

	virtual void	MousePressEvent(MouseEvent &event);
	virtual void	MouseMoveEvent(MouseEvent &event);
	virtual void	MouseEnterEvent(MouseEvent &event);
	virtual void	MouseLeaveEvent(MouseEvent &event);

	//Draw Override for user Button
	virtual void	DrawUser(Painter* painter);
private:
	//build in draw
	void DrawMin(Painter* painter);
	void DrawMax(Painter* painter);
	void DrawClose(Painter* painter);

	int mFixedSize;
	bool OnEnter = false;
	TitleBar* mTitleBar = NULL;
	ButtonType mType;
	int mPixedSpace;				//TODO : Blank Space for calc button polygon
};
