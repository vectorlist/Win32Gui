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
	virtual void PreCreate(CREATESTRUCT &cs) override;
	virtual void PrePaintEvent(Painter* painter) override;

	virtual void OnCreateEvent(CREATESTRUCT &cs);
	virtual void PaintEvent(Painter* painter) override;
};

