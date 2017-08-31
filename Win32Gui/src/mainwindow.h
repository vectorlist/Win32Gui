#pragma once

#include <window.h>

class MainWindow : public Window
{
public:
	MainWindow(Window* parent = NULL);
	MainWindow(const std::wstring &name, Window* parent = NULL);
	virtual ~MainWindow();

protected:
	virtual void OnCreate();
	virtual void PaintEvent() { LOG << "main paint" << ENDN; };
	virtual void PreRegisterClassEx(WNDCLASSEX &wc) OVERRIDE;

	//virtual HRESULT LocalWndProc(UINT msg, WPARAM wp, LPARAM lp);

private:
	std::vector<Window*> mWindows;
	Window* mWindow;
};