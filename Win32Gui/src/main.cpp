
#include <application.h>
#include <layout.h>
#include <widget.h>
#include <vld.h>
#include <mainwindow.h>
#include <button.h>
#include <custombutton.h>
#include <layout.h>

#define TAKE01
#ifdef TAKE01

int main(int args, char* argv[])
{
	HWND consoleWindow = GetConsoleWindow();
	SetWindowPos(consoleWindow, 0, 0, 0, 500, 900, SWP_NOSIZE | SWP_NOZORDER);

	Application app;
	MainWindow w(1280, 720);
	Button b1(w, ButtonType::Close);
	Button b2(w, ButtonType::Min);
	//CustomButtom ct(w, 400, 0, 200, 30);

	Widget item1(100, 100, 200, 200, "left widget");
	item1.SetBrush(Brush(10, 80, 30));
	Widget item2("right widget");
	item2.SetBrush(Brush(100, 20, 0));

	Layout* lay = w.GetLayout();
	lay->AddWindow(&item1);
	lay->AddWindow(&item2);
	lay->Show();

	b2.Move(w.GetSize().cx - (b1.GetSize().cx * 2), 0, b1.GetSize().cx, b1.GetSize().cy);

	b1.Show();
	b2.Show();
	w.Show();

	int exitCode = app.Run();
	return exitCode;
	//someting like 2d

}



#else

#include <iostream>
#include <queue>        
//using namespace std;

class Wnd
{
public:
	std::string name;
};

class Sp : public Wnd
{
public:

};

template <typename T>
struct WndCon
{

};



void main()
{

	Wnd w;
	w.name = "window1";
	Wnd w2;
	w2.name = "window2";
	Sp s1;
	s1.name = "splitter1";

	std::vector<Wnd*> windows;

	windows.push_back(&w);
	windows.push_back(&w2);
	windows.push_back(&s1);

	std::swap(windows[1], windows.back());

	for (auto* w : windows) {
		LOG << typeid(w).name() << ENDN;
	}

	PAUSE;
}

#endif


