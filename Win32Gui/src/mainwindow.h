#pragma once

#include <window.h>

class Button;
class Layout;
class MainWindow : public Window
{
public:
	MainWindow(int w, int h, std::string title = "main window", HWND parent = NULL);
	MainWindow(int x, int y, int w, int h, std::string title = "main window", HWND parent = NULL);
	virtual~MainWindow();

	Layout* GetLayout() { return mLayout; }
protected:
	virtual void PreRegisterClass(WNDCLASS &wc);
	virtual void PreCreate(CREATESTRUCT &cs);

	virtual void OnCreateEvent(CREATESTRUCT &cs);
	virtual void PaintEvent(Painter* painter) OVERRIDE;
	virtual void KeyPressedEvent(WPARAM wp);

	virtual void ResizeEevnt(UINT msg, WPARAM wp, LPARAM lp);

	virtual HRESULT HitEvent(UINT msg, WPARAM wp, LPARAM lp);

	virtual void Update();

private:
	Layout* mLayout;

};
