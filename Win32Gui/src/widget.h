#pragma once

#include <window.h>

class Widget : public Window
{
public:
	Widget(HWND parent = NULL);
	Widget(int x, int y, int w, int h, std::string title = "none", HWND parent = NULL);
	virtual~Widget();

protected:
	virtual void PreRegisterClass(WNDCLASS &wc) override;
	virtual void PreCreateStruct(CREATESTRUCT &cs) override;
	virtual void PaintEvent(Painter* painter) override;
};

